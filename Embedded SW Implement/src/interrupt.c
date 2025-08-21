#include <stdbool.h>
#include <stdio.h>

#define MAX_CALLBACKS 10

// Define a function pointer type for callbacks
typedef void (*callback_t)(void);

// Array to store registered callbacks
static callback_t callback_list[MAX_CALLBACKS];
static int callback_count = 0;

// Register a callback function
bool callback_register(callback_t cb) {
    if (!cb) return false; // Null pointer check
    if (callback_count >= MAX_CALLBACKS) return false; // No more space

    // Avoid duplicate registration
    for (int i = 0; i < callback_count; i++) {
        if (callback_list[i] == cb) return false;
    }

    callback_list[callback_count++] = cb;
    return true;
}

// Unregister a callback function
bool callback_unregister(callback_t cb) {
    for (int i = 0; i < callback_count; i++) {
        if (callback_list[i] == cb) {
            // Replace with last element to keep array compact
            callback_list[i] = callback_list[--callback_count];
            return true;
        }
    }
    return false; // Not found
}

// Trigger all registered callbacks
void callback_invoke_all(void) {
    for (int i = 0; i < callback_count; i++) {
        if (callback_list[i]) {
            callback_list[i]();
        }
    }
}

// Example callbacks
void led_toggle(void) {
    printf("LED toggled!\n");
}

void print_hello(void) {
    printf("Hello from callback!\n");
}

int main(void) {
    // Register callbacks
    callback_register(led_toggle);
    callback_register(print_hello);

    // Simulate event trigger
    callback_invoke_all();

    // Unregister one callback
    callback_unregister(led_toggle);

    // Trigger again
    callback_invoke_all();

    return 0;
}

