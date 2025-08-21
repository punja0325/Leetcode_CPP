
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* ===== Config ===== */
#define MAX_TASKS     8
#define MAX_PRIO      8                  /* priorities: 0..7 (7 is highest) */
#define TICK_HZ       1000               /* 1 ms tick */
#define TIME_SLICE    10                 /* ticks per time slice (RR) */

/* ===== TCB ===== */
typedef void (*task_entry_t)(void*);

typedef enum { TS_READY, TS_RUNNING, TS_BLOCKED } task_state_t;

typedef struct tcb {
    /* scheduling */
    struct tcb *rq_next;                 /* ready-queue next */
    struct tcb *blk_next;                /* blocked list next */
    uint8_t     prio;                    /* 0..MAX_PRIO-1 */
    uint8_t     slice;                   /* remaining time slice *
    task_state_t state;

    /* timing */
    uint32_t    delay_ticks;             /* remaining sleep ticks */

    /* context (placeholder for real CPU context) */
    void       *sp;                      /* stack pointer (ignored in demo) */

    /* task body */
    task_entry_t entry;
    void        *arg;

    /* bookkeeping */
    uint8_t     id;
} tcb_t;

/* ===== Globals ===== */
static tcb_t     g_tasks[MAX_TASKS];
static uint8_t   g_task_count = 0;

static tcb_t    *g_ready_head[MAX_PRIO];
static tcb_t    *g_ready_tail[MAX_PRIO];
static uint32_t  g_ready_bitmap = 0;           /* bit p set => prio p has tasks */

static tcb_t    *g_blocked_head = NULL;        /* simple unordered list */
static tcb_t    *g_curr = NULL;

static volatile uint32_t g_tick = 0;
static volatile uint8_t  g_need_resched = 0;

/* ===== Bitmap helpers ===== */
static inline void rq_bitmap_set(uint8_t p){ g_ready_bitmap |=  (1u << p); }
static inline void rq_bitmap_clr(uint8_t p){ if(!g_ready_head[p]) g_ready_bitmap &= ~(1u << p); }
/* find highest set bit (MAX_PRIO<=32). Portable slow fallback: */
static inline int highest_prio(void){
    for (int p = MAX_PRIO - 1; p >= 0; --p) if (g_ready_bitmap & (1u<<p)) return p;
    return -1;
}

/* ===== Ready queue ops (per priority FIFO) ===== */
static void rq_push_tail(uint8_t p, tcb_t *t){
    t->rq_next = NULL;
    if (!g_ready_head[p]) g_ready_head[p] = g_ready_tail[p] = t;
    else { g_ready_tail[p]->rq_next = t; g_ready_tail[p] = t; }
    rq_bitmap_set(p);
    t->state = TS_READY;
}

static tcb_t* rq_pop_head(uint8_t p){
    tcb_t *t = g_ready_head[p];
    if (!t) return NULL;
    g_ready_head[p] = t->rq_next;
    if (!g_ready_head[p]) g_ready_tail[p] = NULL;
    rq_bitmap_clr(p);
    t->rq_next = NULL;
    return t;
}

/* ===== Blocked list ops (unsorted for simplicity) ===== */
static void blocked_insert(tcb_t *t){
    t->blk_next = g_blocked_head;
    g_blocked_head = t;
    t->state = TS_BLOCKED;
}

static void blocked_tick_and_wake(void){
    tcb_t *prev = NULL, *cur = g_blocked_head;
    while (cur){
        if (cur->delay_ticks > 0 && --cur->delay_ticks == 0){
            /* remove from blocked */
            tcb_t *done = cur;
            if (prev) prev->blk_next = cur->blk_next; else g_blocked_head = cur->blk_next;
            cur = (prev) ? prev->blk_next : g_blocked_head;

            /* back to ready */
            done->slice = TIME_SLICE;
            rq_push_tail(done->prio, done);
            g_need_resched = 1;          /* a task became ready */
        } else {
            prev = cur; cur = cur->blk_next;
        }
    }
}

/* ===== API for tasks ===== */
void os_delay(uint32_t ticks){
    /* put current to blocked and trigger resched */
    if (!g_curr) return;
    g_curr->delay_ticks = ticks;
    blocked_insert(g_curr);
    g_need_resched = 1;
    /* In a real RTOS we would PendSV here */
}

void os_yield(void){
    if (!g_curr) return;
    g_curr->slice = 0;                   /* force RR rotation */
    g_need_resched = 1;
}

/* ===== SysTick ISR ===== */
void SysTick_Handler(void){
    g_tick++;
    /* time slicing */
    if (g_curr && g_curr->state == TS_RUNNING){
        if (g_curr->slice) {
            if (--g_curr->slice == 0) g_need_resched = 1;
        } else {
            g_need_resched = 1;
        }
    }
    /* wake sleepers */
    blocked_tick_and_wake();

    /* request context switch (PendSV on Cortex-M). Here we just set a flag. */
}

/* ===== Core scheduler ===== */
static tcb_t* pick_next(void){
    int p = highest_prio();
    if (p < 0) return NULL;
    return rq_pop_head((uint8_t)p);
}

static void make_ready_or_rr(tcb_t *t){
    if (!t) return;
    /* If time slice expired and still runnable, RR: put to tail */
    t->slice = TIME_SLICE;
    rq_push_tail(t->prio, t);
}

/* Very simplified "context switch" stub:
 * In a real system, save g_curr context, load next->context, switch SP/PSP.
 */
static void context_switch(tcb_t *next){
    g_curr = next;
    if (!g_curr) return;
    g_curr->state = TS_RUNNING;
    /* call the task entry once; tasks are expected to loop internally */
    g_curr->entry(g_curr->arg);
    /* If the task function returns, consider it done; do not reschedule. */
    g_curr = NULL;
}

/* Dispatch point (soft interrupt / main loop). Call when g_need_resched set. */
void os_schedule(void){
    if (!g_need_resched) return;
    g_need_resched = 0;

    /* If there is a current running task whose slice expired (or it called delay/yield),
       put it back to ready unless it blocked. */
    if (g_curr && g_curr->state == TS_RUNNING && g_curr->slice == 0){
        make_ready_or_rr(g_curr);        /* RR */
        g_curr = NULL;
    }

    tcb_t *next = pick_next();
    if (next){
        context_switch(next);
    }
}

/* ===== Task creation (static TCBs; no stacks here for brevity) ===== */
tcb_t* os_create_task(task_entry_t entry, void *arg, uint8_t prio){
    if (g_task_count >= MAX_TASKS || prio >= MAX_PRIO || !entry) return NULL;
    tcb_t *t = &g_tasks[g_task_count];
    *t = (tcb_t){0};
    t->id    = g_task_count++;
    t->prio  = prio;
    t->slice = TIME_SLICE;
    t->entry = entry;
    t->arg   = arg;
    rq_push_tail(prio, t);
    return t;
}

/* ===== Demo tasks ===== */
#include <stdio.h>

static void task_A(void *arg){
    (void)arg;
    for (;;){
        printf("[A] tick=%lu\n", (unsigned long)g_tick);
        os_delay(50);                    /* sleep 50 ms */
    }
}

static void task_B(void *arg){
    (void)arg;
    for (;;){
        printf("  [B] tick=%lu\n", (unsigned long)g_tick);
        os_delay(30);                    /* sleep 30 ms */
    }
}

/* ===== "Kernel" bootstrap ===== */
void os_start(void){
    /* In MCU: enable SysTick to fire every 1 ms and pend the first schedule.
       Here we just run a fake loop that calls the ISRs and scheduler. */
    while (1){
        /* simulate 1 ms tick */
        SysTick_Handler();

        /* do context switch if needed */
        os_schedule();

        /* In a real system, CPU would return to the newly running task.
           Our context_switch() calls task entry directly for demo. */
        if (g_task_count == 0) break;
        if (g_tick > 200) break;         /* stop demo early */
    }
}

/* ===== Example main ===== */
int main(void){
    os_create_task(task_A, NULL, 3);     /* prio 3 (higher) */
    os_create_task(task_B, NULL, 2);     /* prio 2 (lower)  */
    os_start();
    return 0;
}