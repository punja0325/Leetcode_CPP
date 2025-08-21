
#define MAX_TIMER 10

typedef void (*TimerCallback)(void);

typedef struct {
    uint32_t remaining;   // Remining ticks
    uint32_t period;           // Reload value for periodic timer
    bool active;               // Timer is active
    bool periodic;             // One-shot or periodic
    bool expired;              // Expired flag for main loop
    TimerCallback cb;          // Timer callbackj
} software_timer_t;

static software_timer_t timers[MAX_TIMER];

void software_timer_tick(void) {
    // Called in ISR every 1ms
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].active && timers[i].remaining > 0) {
            timers[i].remaining--;
            if (timers[i].remaining == 0) {
                timers[i].expired = true;
                if (timers[i].periodic) {
                    timers[i].remaining = timers[i].period;
                } else {
                    timers[i].active = false;
                }
            }
        }
    }
}

void software_timer_dispatch(void) {
    // Called in main loop
    for (int i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].expired) {
            timers[i].expired = false;
            if (timers[i].cb) timers[i].cb();
        }
    }
}

void timer_start(int id, uint32_t period_ms, bool periodic, timer_callback_t cb) {
    timers[id].remaining = period_ms;
    timers[id].period = period_ms;
    timers[id].periodic = periodic;
    timers[id].cb = cb;
    timers[id].active = true;
    timers[id].expired = false;
}

void timer_stop(int id) {
    timers[id].active = false;
}

void led_toggle(void) {
    printf("LED toggled!\n");
}

void print_hello(void) {
    printf("Hello from timer!\n");
}

// ======================
// Simulated ISR Trigger
// ======================
void SysTick_Handler(void) {
    software_timer_tick(); // ISR 中呼叫
}

int main(void) {
    // 初始化兩個軟體定時器
    timer_start(0, 1000, true, led_toggle);    // 每 1 秒執行一次
    timer_start(1, 3000, false, print_hello);  // 單次 3 秒後執行

    uint32_t ms_counter = 0;

    while (1) {
        // 模擬硬體 timer 每 1ms 觸發 ISR
        SysTick_Handler();
        
        // Main loop 處理到期的 timer callback
        software_timer_dispatch();

        // 模擬 1ms 延遲
        ms_counter++;
        if (ms_counter > 5000) break; // 跑 5 秒結束
    }

    return 0;
}