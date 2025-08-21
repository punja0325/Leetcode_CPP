typedef struct { uint8_t cnt; bool stable; bool edge; } debounce_t;
#define DB_TH_MS 8

static inline void debounce_update(debounce_t* d, bool raw){
    d->edge = false;
    if (raw == d->stable) { d->cnt = 0; return; }
    if (++d->cnt >= DB_TH_MS){ d->stable = raw; d->cnt = 0; d->edge = true; }
}


//----------------
typedef void (*timer_cb_t)(void*);

typedef struct {
    volatile uint32_t remaining;  // ticks to fire
    uint32_t period;              // 0 for one-shot
    timer_cb_t cb; void* arg;
    volatile uint8_t active, expired;
    uint8_t prio;                 // for dispatch order
} sw_timer_t;

#ifndef MAX_TIMERS
#define MAX_TIMERS 16
#endif

static sw_timer_t g_timers[MAX_TIMERS];

static inline void timer_init_all(void){ for (int i=0;i<MAX_TIMERS;i++){ g_timers[i]=(sw_timer_t){0}; } }

static inline bool timer_start(int id,uint32_t ticks,bool periodic,timer_cb_t cb,void* arg,uint8_t prio){
    if (id<0||id>=MAX_TIMERS||ticks==0||!cb) return false;
    g_timers[id].remaining=ticks; g_timers[id].period = periodic?ticks:0;
    g_timers[id].cb=cb; g_timers[id].arg=arg; g_timers[id].prio=prio;
    g_timers[id].expired=0; g_timers[id].active=1; return true;
}
static inline void timer_stop(int id){ if (id>=0&&id<MAX_TIMERS) g_timers[id].active=0; }

/* ISR tick @1ms: keep it short */
static inline void timer_tick_isr(void){
    for (int i=0;i<MAX_TIMERS;i++){
        if (!g_timers[i].active) continue;
        if (g_timers[i].remaining && --g_timers[i].remaining==0){
            g_timers[i].expired=1;
            if (g_timers[i].period) g_timers[i].remaining=g_timers[i].period;
            else g_timers[i].active=0;
        }
    }
}

/* Dispatch in task context: higher prio first when colliding */
static inline void timer_dispatch(void){
    for (;;){
        int sel=-1; uint8_t best=0;
        for (int i=0;i<MAX_TIMERS;i++){
            if (g_timers[i].expired && g_timers[i].prio>=best){ best=g_timers[i].prio; sel=i; }
        }
        if (sel<0) break;
        g_timers[sel].expired=0;
        g_timers[sel].cb(g_timers[sel].arg);
    }
}

//---------------------


typedef struct {
    volatile uint32_t DIR, OUT, IN, SET, CLR;
} GPIO_Regs;

#define GPIO_BASE 0x40020000UL
#define GPIO ((GPIO_Regs*)GPIO_BASE)
#define PIN(n) (1u<<(n))

static inline void gpio_set_dir(int pin, bool out){
    if (out) GPIO->DIR |= PIN(pin); else GPIO->DIR &= ~PIN(pin);
}
static inline void gpio_write(int pin, bool high){
    if (high) GPIO->SET = PIN(pin); else GPIO->CLR = PIN(pin);
}
static inline bool gpio_read(int pin){ return (GPIO->IN & PIN(pin))!=0; }


//--------------------
typedef struct {
    // HW registers omitted for brevity: USARTx, DMA stream/channel, etc.
    ring_t   rx_ring;          // consumer-visible ring
    uint8_t* rx_dma_buf;       // backing memory that DMA writes into (circular)
    uint16_t rx_dma_size;
    volatile uint32_t overruns;
} uart_t;

/* Called in DMA HT/TC ISR or polled: convert DMA NDTR to ring tail */
static inline void uart_rx_refresh_tail_from_dma(uart_t* u, volatile uint32_t NDTR){
    uint16_t dma_pos = (uint16_t)(u->rx_dma_size - (uint16_t)NDTR); // bytes written so far
    u->rx_ring.tail = (uint16_t)(dma_pos % u->rx_ring.size);
}

/* Task API: pull up to maxlen bytes */
static inline int uart_read(uart_t* u, uint8_t* out, uint16_t maxlen){
    uint16_t got=0;
    while (got<maxlen && rb_pop(&u->rx_ring,&out[got])) got++;
    return (int)got;
}
//------------------------


// See earlier long example; core points:
#define TIMER_CLK_HZ 84000000UL
static void pwm_gpio_init_PA6_TIM3_CH1(void){ /* RCC+GPIO AF2 init */ }
static void pwm_tim3_init_base(void){ /* TIM3 PWM1, OC1PE, ARPE, CC1E */ }

static void pwm_tim3_ch1_set(uint32_t freq_hz, uint16_t duty_permille){
    // compute PSC/ARR ~ f_pwm = clk/((PSC+1)*(ARR+1))
    // set CCR1 = duty*(ARR+1)/10000, EGR.UG to latch
}


//-----------------------
typedef struct node { struct node* next; } node_t;
typedef struct { node_t* free_list; uint8_t* base; uint32_t chunk, count; } mempool_t;

static inline void mp_init(mempool_t* mp, void* buf, uint32_t chunk, uint32_t count){
    mp->base = (uint8_t*)buf; mp->chunk = chunk; mp->count = count; mp->free_list=NULL;
    for (int i=(int)count-1;i>=0;--i){ node_t* n=(node_t*)(mp->base+i*chunk); n->next=mp->free_list; mp->free_list=n; }
}
static inline void* mp_alloc(mempool_t* mp){ node_t* n=mp->free_list; if(!n) return NULL; mp->free_list=n->next; return n; }
static inline void  mp_free (mempool_t* mp, void* p){ node_t* n=(node_t*)p; n->next=mp->free_list; mp->free_list=n; }

//-------------------------
typedef struct {
    uint8_t* buf; size_t esize, cap; size_t head, tail;
    SemaphoreHandle_t space, items, lock;
    volatile bool closed;
} bbq_t;

int bbq_init(bbq_t* q, void* buf,size_t esize,size_t cap){
    q->buf=buf;q->esize=esize;q->cap=cap;q->head=q->tail=0;q->closed=false;
    q->space=xSemaphoreCreateCounting(cap,cap);
    q->items=xSemaphoreCreateCounting(cap,0);
    q->lock =xSemaphoreCreateMutex();
    return (q->space&&q->items&&q->lock)?0:-1;
}
int bbq_enqueue(bbq_t* q,const void* e){
    if (q->closed) return -1;
    if (xSemaphoreTake(q->space, portMAX_DELAY)!=pdTRUE) return -1;
    xSemaphoreTake(q->lock, portMAX_DELAY);
    memcpy(q->buf + (q->head*q->esize), e, q->esize);
    q->head = (q->head+1)%q->cap;
    xSemaphoreGive(q->lock);
    xSemaphoreGive(q->items);
    return 0;
}
int bbq_dequeue(bbq_t* q,void* out){
    if (xSemaphoreTake(q->items, portMAX_DELAY)!=pdTRUE) return -1;
    xSemaphoreTake(q->lock, portMAX_DELAY);
    memcpy(out, q->buf + (q->tail*q->esize), q->esize);
    q->tail=(q->tail+1)%q->cap;
    xSemaphoreGive(q->lock);
    xSemaphoreGive(q->space);
    return 0;
}


