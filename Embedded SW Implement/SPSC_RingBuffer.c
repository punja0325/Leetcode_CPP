


typedef struct {
    uint32_t* buf;
    uint32_t size;
    volatile uint32_t head;  // consumer moves, ro
    volatile uint32_t tail;  // producer moves, wo
} ring_t;

/*Helper function */
static inline uint32_t rb_used(const ringb_t *r) {
    uint32_t h = r->head, t = r->tail, n = r->size;
    return (t >= h) ? (t - h) : (uint32_t)(n - (h - t));
}
static inline uint32_t rb_free(const ringb_t *r) {
    return (uint32_t)(r->size - 1u - rb_used(r));  // -1 keeps one byte open
}

static inline void rb_init(ringb_t *r, uint8_t *storage, uint32_t size) {
    r->buf = storage; r->size = size; r->head = r->tail = 0;
}

/* ============ Producer side (ISR) ============ */
/* Write 'len' bytes atomically (all-or-nothing).
 * Returns false if not enough space (no partial write).
 * Safe for ISR as long as head/tail width is naturally atomic (e.g., 16-bit on Cortex-M).
 */

 static inline bool rb_write_isr(ring_t* r, const void *src, uint32_t len) {
    if (len == 0) return true;
    if (len > rb_free(r)) return false;

    uint32_t n = r->size;
    uint32_t t = r->tail;
    uint32_t h = r->head;
    uint32_t first = (uint32_t)((t + len <= n) ? len : (n - t));
    uint32_t second = (uint32_t)(len - first);

    /* 1) copy payload*/
    memcpy(&r->buf[t], src, first);
    if (second) {
        memcpy(&r->buf[0], (const uint8_t*)src + first, second);
    }
    /* 2) pulish new tail AFTER data is visable*/
    uint32_t nt = (uint32_t)((t + len) % n);
    r->tail = nt;
    return true;
}


/* ============ Consumer side (Task) ============ */

/* Read up to 'len' bytes; returns the number of bytes actually copied (0..len).
 * To keep symmetry with write-all-or-nothing, you may prefer a rb_read_exact() that
 * returns false unless len bytes are available; here we allow partial read (caller decides).
 */
static inline uint32_t rb_read(ring_t* r, void* dst, uint32_t len) {
    uint32_t avail = rb_used();
    if (len > avail) return false;
    if (len == 0) return 0;

    uint32_t n = r->size;
    uint32_t h = r->head;

    uint32_t first = h + len > n ? (n - h) : len;
    uint32_t second = len - first;

    /* 1) Copy payload*/
    memcpy(dst, &r->buf[h], first);
    if (second) {
        memcpy(dst, &r->buf[h], first);
    }
    /* 2) publish new head*/
    r->head = (h + len) % n;
    return len;
}


/* Exact-size variant: returns false unless 'len' bytes are available. */
static inline bool rb_read_exact(ringb_t *r, void *dst, uint16_t len) {
    if (len > rb_used(r)) return false;
    (void)rb_read(r, dst, len);
    return true;
}

/* ============ Optional Zero-Copy (two-segment view) ============ */

/* Expose linear readable span without copying.
 * Returns pointer to segment start and its length in *seg_len.
 * Consumer then must call rb_drop(r, consumed_len) after processing.
 */
static inline const uint8_t* rb_peek_read_span(const ringb_t *r, uint16_t *seg_len) {
    uint16_t h = r->head, t = r->tail, n = r->size;
    uint16_t used = rb_used(r);
    if (used == 0) { *seg_len = 0; return NULL; }
    uint16_t linear = (t >= h) ? (t - h) : (uint16_t)(n - h);
    if (linear > used) linear = used;
    *seg_len = linear;
    return &r->buf[h];
}

static inline void rb_drop(ringb_t *r, uint16_t bytes) {
    uint16_t used = rb_used(r);
    if (bytes > used) bytes = used;
    r->head = (uint16_t)((r->head + bytes) % r->size);
}


/* ============ Usage Example ============ */
typedef struct __attribute__((packed)) {
    uint16_t type;
    uint32_t ts;
    uint8_t  payload[12];
} Packet;

ringb_t rx;
uint8_t storage[512];

void init(void){
    rb_init(&rx, storage, sizeof(storage));
}

void ISR_on_data(const Packet* p){
    (void)rb_write_isr(&rx, p, sizeof(*p));  // drop if not enough space
}

bool consume_one_packet(Packet* out){
    return rb_read_exact(&rx, out, sizeof(*out));
}


/*
Notes the interviewer likes to hear
SPSC & volatile: head and tail are written by different contexts; volatile ensures the compiler doesn’t cache them.
Publish order: producer copies bytes first, then updates tail; consumer reads head and only then accesses bytes.
Atomicity: choose index types that the CPU updates atomically (e.g., 16-bit on Cortex-M is fine).
Zero-copy: peek + drop lets parsers process in-place, avoiding copies.
Element alignment: since we’re byte-wise, alignment isn’t guaranteed; if your consumer casts to larger types, use memcpy to aligned locals.
Policy: the example uses all-or-nothing writes to keep frames intact. You can switch to partial writes if that fits your pipeline.
*/