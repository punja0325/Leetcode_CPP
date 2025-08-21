

/*
API:
1. regiter_callback
2. unregiter_callback
3. ISR_handler -> change the event status
4. Main loop -> execute event callback
*/

#define MAX_EVENTS 10
#define EVENT_QUEUE_SIZE 10
typedef void (*callback_t)(void* arg);

typedef enum {
    EVNET_STATUS_UNREGISTER = 0,
    EVNET_STATUS_REGISTER,
} event_status_t;

typedef struct {
    event_status_t status;
    callback_t *cb;
    void* arg;
} Event_t;

/* Global variable*/
static Event_t EventManager[MAX_EVENTS];
static uint32_t EventQueue[EVENT_QUEUE_SIZE];
static volatile uint32_t q_head = 0, q_tail = 0;

bool EventManagerInit () {
    for (int i = 0; i < MAX_EVENTS; i++) {
        EventManager[i].status = EVNET_STATUS_UNREGISTER;
        EventManager[i].cb     = NULL;
        EventManager[i].arg    = NULL;
    }
    q_head = 0;
    q_tail = 0;
    return true;
}


/*return false if id is not correct or the id had been register*/
bool EventManagerRegisterCallback(uint32_t id, callback_t* cb, void* arg) {
    if (id >= MAX_EVENTS) return false;
    if (cb == NULL)       return false;
    if (EventManager[id].cb != NULL) return false; // already registered
    EventManager[id].cb = cb;
    EventManager[id].arg = arg;
    EventManager[id].status = EVNET_STATUS_REGISTER;
    return true;
}

bool EventManagerUnregisterCallback(uint32_t id) {
    if (id >= MAX_EVENTS) return false;
    EventManager[id].cb     = NULL;
    EventManager[id].arg    = NULL;
    EventManager[id].status = EVNET_STATUS_UNREGISTER;
    return true;
}

//Post event ID to queue
bool EventTriggerFromISR (uint32_t event_id) {
    if (event_id >= MAX_EVENTS) return false;
    uint32_t next = (q_tail + 1u) % EVENT_QUEUE_SIZE;

    if (q_head == next) return false; //queue fail
    EventQueue[q_tail] = event_id;
    q_tail = next;
    return true;
}

// Called in main loop: dispatch queued events
void EventDispatch(viod) {
    while (q_head != q_tail) {
        uint32_t event_id = EventQueue[q_head];
        q_head = (q_head + 1u) % EVENT_QUEUE_SIZE;

        if (event_id < MAX_EVENTS) {
            callback_t cb = EventManager[event_id].cb;
            void* arg     = EventManager[event_id].arg;
            if (cb) {
                cb(arg);
            }
        }
    }
}

// ==================== Example Callbacks ====================

void on_button_press(void) {
    printf("Button pressed!\n");
}
void on_uart_rx(void) {
    printf("UART received data!\n");
}


// ==================== Main Demo ====================
int main (void) {
    EventManagerInit();
    EventManagerRegisterCallback(0, on_button_press);
    EventManagerRegisterCallback(1, on_uart_rx);

}

/* Follow-up
Multiple callbacks per event: store a small array per event (callbacks[] and count), iterate on dispatch.
Event priorities: use multiple queues (high/low) or a priority queue.
Event payloads: change queue to store a small struct { id, payload }.
Blocking wait (RTOS): have ISR give a semaphore; main task take then call EventDispatch().
Reentrancy policy: prevent re-entrancy per event (e.g., drop or coalesce if already in progress).
*/
#define Multiple_callbacks_per_event
#ifdef Multiple_callbacks_per_event
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ==== Config ==== */
#define MAX_EVENTS               16
#define MAX_CALLBACKS_PER_EVENT   8
#define EVENT_QUEUE_SIZE         32

typedef void (*event_cb_t)(void *arg);

/* ==== Event table: each event has a list of callbacks ==== */
typedef struct {
    event_cb_t cb[MAX_CALLBACKS_PER_EVENT];
    void      *arg[MAX_CALLBACKS_PER_EVENT];
    uint8_t    count;              // number of active callbacks
} event_slot_t;

/* ==== Globals ==== */
static event_slot_t  g_events[MAX_EVENTS];

/* Ring queue for ISR->main event IDs */
static uint32_t      g_evq[EVENT_QUEUE_SIZE];
static volatile uint32_t g_q_head = 0;   // updated by main
static volatile uint32_t g_q_tail = 0;   // updated by ISR
static volatile uint32_t g_overruns = 0; // queue full counter (optional)

/* ==== Init ==== */
bool EventMgr_Init(void)
{
    for (int i = 0; i < MAX_EVENTS; ++i) {
        g_events[i].count = 0;
        for (int j = 0; j < MAX_CALLBACKS_PER_EVENT; ++j) {
            g_events[i].cb[j]  = NULL;
            g_events[i].arg[j] = NULL;
        }
    }
    g_q_head = g_q_tail = 0;
    g_overruns = 0;
    return true;
}

/* ==== Registration helpers ==== */

static bool already_registered(event_slot_t *slot, event_cb_t cb, void *arg)
{
    for (uint8_t i = 0; i < slot->count; ++i) {
        if (slot->cb[i] == cb && slot->arg[i] == arg) return true;
    }
    return false;
}

/* Register (cb,arg) to an event. Returns false if full, invalid id, or duplicate. */
bool EventMgr_Register(uint32_t event_id, event_cb_t cb, void *arg)
{
    if (event_id >= MAX_EVENTS || cb == NULL) return false;
    event_slot_t *slot = &g_events[event_id];

    if (slot->count >= MAX_CALLBACKS_PER_EVENT) return false;
    if (already_registered(slot, cb, arg))      return false;  // avoid duplicates

    slot->cb[slot->count]  = cb;
    slot->arg[slot->count] = arg;
    slot->count++;
    return true;
}

/* Unregister exactly the (cb,arg) pair; returns false if not found/invalid. */
bool EventMgr_Unregister(uint32_t event_id, event_cb_t cb, void *arg)
{
    if (event_id >= MAX_EVENTS || cb == NULL) return false;
    event_slot_t *slot = &g_events[event_id];

    for (uint8_t i = 0; i < slot->count; ++i) {
        if (slot->cb[i] == cb && slot->arg[i] == arg) {
            // swap-remove to keep the array compact
            uint8_t last = (uint8_t)(slot->count - 1);
            slot->cb[i]  = slot->cb[last];
            slot->arg[i] = slot->arg[last];
            slot->cb[last]  = NULL;
            slot->arg[last] = NULL;
            slot->count--;
            return true;
        }
    }
    return false;
}

/* Optional: unregister all listeners for an event. */
void EventMgr_UnregisterAll(uint32_t event_id)
{
    if (event_id >= MAX_EVENTS) return;
    g_events[event_id].count = 0;
    for (uint8_t i = 0; i < MAX_CALLBACKS_PER_EVENT; ++i) {
        g_events[event_id].cb[i]  = NULL;
        g_events[event_id].arg[i] = NULL;
    }
}

/* ==== ISR side: post event ID (fast, non-blocking) ==== */
/* Returns false if queue is full. */
bool EventMgr_TriggerFromISR(uint32_t event_id)
{
    if (event_id >= MAX_EVENTS) return false;

    uint32_t next = (g_q_tail + 1u) % EVENT_QUEUE_SIZE;
    if (next == g_q_head) {
        /* queue full: record and drop (or replace oldest if you prefer) */
        g_overruns++;
        return false;
    }
    g_evq[g_q_tail] = event_id;
    g_q_tail = next;   // publish
    return true;
}

/* ==== Main loop: dispatch all queued events ==== */
void EventMgr_Dispatch(void)
{
    /* Drain the queue: for each event ID, call all registered callbacks. */
    while (g_q_head != g_q_tail) {
        uint32_t event_id = g_evq[g_q_head];
        g_q_head = (g_q_head + 1u) % EVENT_QUEUE_SIZE;

        if (event_id >= MAX_EVENTS) continue;

        event_slot_t *slot = &g_events[event_id];

        /* Snapshot the current callback list to avoid iterator invalidation
         * if callbacks register/unregister during execution.
         */
        event_cb_t tmp_cb[MAX_CALLBACKS_PER_EVENT];
        void      *tmp_arg[MAX_CALLBACKS_PER_EVENT];
        uint8_t    n = slot->count;                  // single-byte read
        if (n > MAX_CALLBACKS_PER_EVENT) n = MAX_CALLBACKS_PER_EVENT;

        for (uint8_t i = 0; i < n; ++i) {
            tmp_cb[i]  = slot->cb[i];
            tmp_arg[i] = slot->arg[i];
        }

        for (uint8_t i = 0; i < n; ++i) {
            if (tmp_cb[i]) {
                tmp_cb[i](tmp_arg[i]);
            }
        }
    }
}

/* ==== Optional diagnostics ==== */
uint32_t EventMgr_GetOverruns(void) { return g_overruns; }
uint8_t  EventMgr_GetListenerCount(uint32_t event_id)
{
    if (event_id >= MAX_EVENTS) return 0;
    return g_events[event_id].count;
}

/* ==== Example usage (pseudo) ====

static void on_btn(void *arg){ (void)arg; /* handle button */ }
static void on_uart(void *arg){ (void)arg; /* handle uart */ }

int main(void)
{
    EventMgr_Init();
    EventMgr_Register(0, on_btn,  NULL);
    EventMgr_Register(0, on_uart, NULL);

    // ISR somewhere:
    //   EventMgr_TriggerFromISR(0);

    for (;;) {
        EventMgr_Dispatch();   // run in main loop or a dedicated task
        // ... other work, low-power idle, etc.
    }
}
#endif


#define RTOS_integration_version
#ifdef RTOS_integration_version

#endif