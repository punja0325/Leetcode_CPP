#include <stdint.h>
#include <stdbool.h>

/* ===== Hardware mapping (example addresses) ===== */
#define GPIO_BASE_ADDR 0x40020000UL

typedef struct {
    volatile uint32_t DIR;   // 0x00: 1=output, 0=input
    volatile uint32_t OUT;   // 0x04: output data (avoid direct RMW if SET/CLR exist)
    volatile uint32_t IN;    // 0x08: input status
    volatile uint32_t SET;   // 0x0C: write 1 to set corresponding OUT bit
    volatile uint32_t CLR;   // 0x10: write 1 to clear corresponding OUT bit
} GPIO_Regs;

#define GPIO ((GPIO_Regs *)GPIO_BASE_ADDR)

/* ===== Basic helpers ===== */
static inline uint32_t pin_mask(int pin) {
    return (uint32_t)1u << pin;
}

/* Set pin direction: true=output, false=input */
void gpio_set_dir(int pin, bool output)
{
    uint32_t m = pin_mask(pin);
    if (output) {
        /* Set bit to 1 -> output */
        GPIO->DIR |= m;  // If DIR has no SET/CLR, RMW is acceptable for config
    } else {
        /* Clear bit -> input */
        GPIO->DIR &= ~m;
    }
}

/* Write output level using SET/CLR to avoid RMW hazards */
void gpio_write(int pin, bool value)
{
    uint32_t m = pin_mask(pin);
    if (value) {
        GPIO->SET = m;   // atomic set of the bit
    } else {
        GPIO->CLR = m;   // atomic clear of the bit
    }
}

/* Read current pin state from input register */
bool gpio_read(int pin)
{
    return (GPIO->IN & pin_mask(pin)) != 0u;
}

/* Optional: toggle using OUT read (if HW also provides TOGGLE register, prefer that) */
void gpio_toggle(int pin)
{
    uint32_t m = pin_mask(pin);
    /* Fallback: RMW on OUT (acceptable if no concurrent writers).
       If hardware provides TOGGLE-on-write register, use it instead. */
    uint32_t out = GPIO->OUT;
    if (out & m) GPIO->CLR = m; else GPIO->SET = m;
}

/* ===== Example usage =====
int main(void)
{
    // Configure pin 3 as output, pin 5 as input
    gpio_set_dir(3, true);
    gpio_set_dir(5, false);

    // Drive pin 3 high, then toggle
    gpio_write(3, true);
    gpio_toggle(3);

    // Read pin 5
    bool btn = gpio_read(5);
    (void)btn;

    return 0;
}
*/
