#include <stdint.h>
#include <stdbool.h>

/* ===== Low-level raw access (32-bit) ===== */
static inline uint32_t REG_READ(uintptr_t addr)
{
    return *(volatile uint32_t *)addr;
}

static inline void REG_WRITE(uintptr_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
}

/* ===== Bit operations via Read-Modify-Write (use only if no HW SET/CLR) ===== */
static inline void REG_SET_BITS(uintptr_t addr, uint32_t mask)
{
    volatile uint32_t *r = (volatile uint32_t *)addr;
    *r = *r | mask;
}

static inline void REG_CLR_BITS(uintptr_t addr, uint32_t mask)
{
    volatile uint32_t *r = (volatile uint32_t *)addr;
    *r = *r & ~mask;
}

/* Read masked bits (not shifted) */
static inline uint32_t REG_GET_BITS(uintptr_t addr, uint32_t mask)
{
    return REG_READ(addr) & mask;
}

/* ===== Field helpers (mask + shift) ===== */
static inline uint32_t REG_GET_FIELD(uintptr_t addr, uint32_t mask, unsigned shift)
{
    return (REG_READ(addr) & mask) >> shift;
}

static inline void REG_SET_FIELD(uintptr_t addr, uint32_t mask, unsigned shift, uint32_t val)
{
    volatile uint32_t *r = (volatile uint32_t *)addr;
    uint32_t v = *r;
    v &= ~mask;                              // clear field
    v |= ((val << shift) & mask);            // set new field value
    *r = v;
}

/* ===== Write-1 semantics (use when HW docs specify W1S/W1C etc.) ===== */
/* Write-1-to-Set: writing 1 sets corresponding bits */
static inline void REG_WRITE_W1S(uintptr_t addr, uint32_t mask)
{
    *(volatile uint32_t *)addr = mask;
}

/* Write-1-to-Clear: writing 1 clears corresponding bits */
static inline void REG_WRITE_W1C(uintptr_t addr, uint32_t mask)
{
    *(volatile uint32_t *)addr = mask;
}

/* ===== Pointer-based overloads (when you already have a mapped pointer) ===== */
static inline uint32_t REGP_READ(volatile uint32_t *reg)
{
    return *reg;
}

static inline void REGP_WRITE(volatile uint32_t *reg, uint32_t value)
{
    *reg = value;
}

static inline void REGP_SET_BITS(volatile uint32_t *reg, uint32_t mask)
{
    *reg = *reg | mask;
}

static inline void REGP_CLR_BITS(volatile uint32_t *reg, uint32_t mask)
{
    *reg = *reg & ~mask;
}

static inline uint32_t REGP_GET_FIELD(volatile uint32_t *reg, uint32_t mask, unsigned shift)
{
    return (*reg & mask) >> shift;
}

static inline void REGP_SET_FIELD(volatile uint32_t *reg, uint32_t mask, unsigned shift, uint32_t val)
{
    uint32_t v = *reg;
    v &= ~mask;
    v |= ((val << shift) & mask);
    *reg = v;
}
