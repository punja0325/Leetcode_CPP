typedef struct {
    uint8_t *buffer; // buffer storage
    int head;        // write index
    int tail;        // read index
    int size;        // total capacity
    int count;       // number of elements in the buffer
    pthread_mutex_t lock; // Mutex for thread safety
} CircularQueue;

// Initialize queue
void cq_init(CircularQueue *q, uint8_t *buf, int size);
// Enqueue one byte, return 0 if success, -1 if full
int cq_enqueue(CircularQueue *q, uint8_t data);
// Dequeue one byte, return 0 if success, -1 if empty
int cq_dequeue(CircularQueue *q, uint8_t *data);
// Return 1 if empty, 0 otherwise
int cq_is_empty(CircularQueue *q);
// Return 1 if full, 0 otherwise
int cq_is_full(CircularQueue *q);

// Initialize queue
void cq_init(CircularQueue *q, uint8_t *buf, int size) {
    q->head = 0;
    q->tail = 0;
    q->size = size;
    q->count = 0;
    q->buffer = buf;
    pthread_mutex_init(&q->lock, NULL); // Init mutex
}
//pthread_mutex_lock(&q->lock); // Lock critical section
//pthread_mutex_unlock(&q->lock); // Unlock critical section

// Enqueue one byte, return 0 if success, -1 if full
int cq_enqueue(CircularQueue *q, uint8_t data) {
    pthread_mutex_lock(&q->lock); // Lock critical section
    if (q->count == q->size) { // check full directly to avoid double lock
        pthread_mutex_unlock(&q->lock); // Unlock critical section
        return -1;
    }
    q->buffer[q->head] = data;
    q->count++;
    q->head = (q->head + 1) % q->size;
    pthread_mutex_unlock(&q->lock); // Unlock critical section
    return 0;
}

// Dequeue one byte, return 0 if success, -1 if empty
int cq_dequeue(CircularQueue *q, uint8_t *data) {
    pthread_mutex_lock(&q->lock); // Lock critical section
    if (q->count == 0) { // check empty directly to avoid double lock
        pthread_mutex_unlock(&q->lock); // Unlock critical section
        return -1;
    }
    *data = q->buffer[q->tail];
    q->count--;
    q->tail = (q->tail + 1) % q->size;
    pthread_mutex_unlock(&q->lock); // Unlock critical section
    return 0;
}

// Return 1 if empty, 0 otherwise
int cq_is_empty(CircularQueue *q) {
    pthread_mutex_lock(&q->lock); // Lock critical section
    int result = (q->count == 0) ? 1 : 0;
    pthread_mutex_unlock(&q->lock); // Unlock critical section
    return result;
}

// Return 1 if full, 0 otherwise
int cq_is_full(CircularQueue *q) {
    pthread_mutex_lock(&q->lock); // Lock critical section
    int result = (q->count == q->size) ? 1 : 0;
    pthread_mutex_unlock(&q->lock); // Unlock critical section
    return result;
}

int main(void) {
    uint8_t buffer[BUF_SIZE];  // 靜態分配
    CircularQueue q;           // 靜態分配 queue 結構

    cq_init(&q, buffer, BUF_SIZE);

    cq_enqueue(&q, 10);
    cq_enqueue(&q, 20);

    uint8_t val;
    cq_dequeue(&q, &val);  // val = 10
}