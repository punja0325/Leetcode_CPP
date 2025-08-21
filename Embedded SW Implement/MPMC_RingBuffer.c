#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* ===== MPMC bounded ring using per-slot sequence numbers (Vyukov) ===== */

typedef struct {
    _Atomic uint32_t seq;  // per-slot ticket (monotonic)
    uint8_t         *ptr;  // pointer to payload storage for this slot
} mpmc_slot_t;

typedef struct {
    uint32_t        cap;          // power-of-two capacity
    uint32_t        mask;         // cap - 1
    uint32_t        elem_size;    // bytes per element
    mpmc_slot_t    *slots;        // array of slots
    uint8_t        *storage;      // contiguous backing storage: cap * elem_size

    _Atomic uint32_t head;        // consumer index (ticket)
    _Atomic uint32_t tail;        // producer index (ticket)
} mpmc_ring_t;

/* Utility: next power-of-two check is external; ensure cap is power of two. */
static inline bool is_pow2(uint32_t x){ return x && ((x & (x-1)) == 0); }

bool mpmc_init(mpmc_ring_t *q, mpmc_slot_t *slots, uint8_t *storage,
               uint32_t capacity_pow2, uint32_t elem_size)
{
    if (!q || !slots || !storage) return false;
    if (!is_pow2(capacity_pow2) || elem_size == 0) return false;

    q->cap = capacity_pow2;
    q->mask = capacity_pow2 - 1u;
    q->elem_size = elem_size;
    q->slots = slots;
    q->storage = storage;

    for (uint32_t i = 0; i < q->cap; ++i) {
        q->slots[i].ptr = q->storage + (size_t)i * q->elem_size;
        atomic_store_explicit(&q->slots[i].seq, i, memory_order_relaxed);
    }

    atomic_store_explicit(&q->head, 0, memory_order_relaxed);
    atomic_store_explicit(&q->tail, 0, memory_order_relaxed);
    return true;
}

/* Enqueue: copy one element (elem_size bytes). Returns false if queue is full (non-blocking). */
bool mpmc_enqueue(mpmc_ring_t *q, const void *elem)
{
    uint32_t pos;
    mpmc_slot_t *slot;
    uint32_t seq;
    intptr_t dif;

    while (1) {
        pos  = atomic_load_explicit(&q->tail, memory_order_relaxed);
        slot = &q->slots[pos & q->mask];
        seq  = atomic_load_explicit(&slot->seq, memory_order_acquire);
        dif  = (intptr_t)seq - (intptr_t)pos;

        if (dif == 0) {
            /* Slot is empty for this producer turn; try to claim the tail position. */
            if (atomic_compare_exchange_weak_explicit(
                    &q->tail, &pos, pos + 1,
                    memory_order_acq_rel, memory_order_relaxed)) {
                /* We own this slot. Write payload, then publish. */
                memcpy(slot->ptr, elem, q->elem_size);
                atomic_store_explicit(&slot->seq, pos + 1, memory_order_release);
                return true;
            }
            /* CAS failed: another producer advanced tail; retry. */
        } else if (dif < 0) {
            /* seq < pos => the consumer hasn’t caught up: queue full for now. */
            return false;
        } else {
            /* seq > pos => another producer is working ahead; spin/yield briefly. */
            /* Optional backoff here in real systems. */
        }
    }
}

/* Dequeue: copy one element out. Returns false if queue is empty (non-blocking). */
bool mpmc_dequeue(mpmc_ring_t *q, void *out)
{
    uint32_t pos;
    mpmc_slot_t *slot;
    uint32_t seq;
    intptr_t dif;

    while (1) {
        pos  = atomic_load_explicit(&q->head, memory_order_relaxed);
        slot = &q->slots[pos & q->mask];
        seq  = atomic_load_explicit(&slot->seq, memory_order_acquire);
        dif  = (intptr_t)seq - (intptr_t)(pos + 1);

        if (dif == 0) {
            /* Slot has data for this consumer turn; try to claim the head position. */
            if (atomic_compare_exchange_weak_explicit(
                    &q->head, &pos, pos + 1,
                    memory_order_acq_rel, memory_order_relaxed)) {
                /* We own this slot. Read payload, then mark slot empty for next lap. */
                memcpy(out, slot->ptr, q->elem_size);
                atomic_store_explicit(&slot->seq, pos + q->cap, memory_order_release);
                return true;
            }
            /* CAS failed: another consumer advanced head; retry. */
        } else if (dif < 0) {
            /* seq < pos+1 => queue empty for now. */
            return false;
        } else {
            /* seq > pos+1 => a previous consumer not done yet; spin/yield briefly. */
            /* Optional backoff here in real systems. */
        }
    }
}

/* Optional helpers */
static inline uint32_t mpmc_capacity(const mpmc_ring_t *q) { return q->cap; }
