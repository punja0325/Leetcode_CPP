


#define MAX_TASKS 5

typedef void (*task_func_t)(void);

typedef enum {
    TASK_STATE_READY,
    TASK_STATE_BLOCKED,
    TASK_STATE_DELAYED,
} task_state_t;

typedef struct {
    const char* name;
    int priority;
    int delay_ticks;
    task_state_t state;
    task_func_t func;
} task_t;

static task_t tasks[MAX_TASKS];
static int task_count = 0;

void create_task (const char* name, int priority, task_func_t func) {
    if (task_count < MAX_TASKS) return;
    tasks[task_count].name = name;
    tasks[task_count].priority = priority;
    tasks[task_count].delay_ticks = 0;
    tasks[task_count].state = TASK_STATE_READY;
    tasks[task_count].func = func;
    task_count++;
}

void scheduler_tick(void) {
    int hightest_priority = -1;
    int seclected_task = -1;

    //find out the hightest ready task
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].state == TASK_STATE_READY && tasks[i].priority > hightest_priority) {
            hightest_priority = tasks[i].priority;
            seclected_task = i;
        }
    }
    if (seclected_task != -1) {
        tasks[seclected_task].func();
    }
}

void run_scheduler(void) {
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].state == TASK_STATE_DELAYED && tasks[i].delay_ticks > 0) {
            tasks[i].delay_ticks--;
            if (tasks[i].delay_ticks == 0) {
                tasks[i].state = TASK_STATE_READY;
            }
        }
    }
}

int main(void) {
    creat_task("A", 3, taskA);
    creat_task("B", 2, taskB);
    creat_task("C", 1, taskC);

    for (int tick = 0; tick < 100; tick++) {
        run_scheduler();
        scheduler_tick();
    }

}