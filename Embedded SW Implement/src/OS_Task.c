


typedef struct TaskControlBlock {
    void (*entry)(void);
    int priority;
    int delay_tick;
    struct TaskControlBlock *next;
} TCB;

void insert_ready_task(TCB** head, TCB *task) {
    if (*head == NULL || task->priority > *head->priority) {
        task-next = *head;
        *head = task;
        return;
    }
    TCB* curr = *head;
    while (curr->next && curr->next->priority >= task->priority) {
        curr = curr->next;
    }
    task->next = curr->next;
    curr->next = task;
}

