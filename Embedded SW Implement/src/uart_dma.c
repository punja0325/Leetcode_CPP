#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define UART_RX_BUF_SIZE 256

static uint8_t uart_rx_buf[UART_RX_BUF_SIZE]; // DMA writes here
static volatile uint16_t uart_rx_head = 0;    // Software read index

// Simulated DMA write index (hardware would update this)
static volatile uint16_t dma_write_index = 0;

// ============================
// UART DMA INIT
// ============================
void uart_dma_init(void) {
    // Configure UART hardware
    // Configure DMA in circular mode:
    //  - Peripheral: UART RX register
    //  - Memory: uart_rx_buf
    //  - Length: UART_RX_BUF_SIZE
    //  - Mode: Circular
    // Enable DMA half-transfer & transfer-complete interrupts
    printf("UART DMA initialized.\n");
}

// ============================
// Get available data in buffer
// ============================
uint16_t uart_dma_available(void) {
    uint16_t write_index = dma_write_index; // DMA current write position
    if (write_index >= uart_rx_head) {
        return write_index - uart_rx_head;
    } else {
        return UART_RX_BUF_SIZE - uart_rx_head + write_index;
    }
}

// ============================
// Read data from buffer
// ============================
uint16_t uart_dma_read(uint8_t *dest, uint16_t len) {
    uint16_t count = 0;
    while (count < len && uart_dma_available() > 0) {
        dest[count++] = uart_rx_buf[uart_rx_head++];
        if (uart_rx_head >= UART_RX_BUF_SIZE) {
            uart_rx_head = 0; // wrap around
        }
    }
    return count;
}

// ============================
// DMA ISR Handler Simulation
// ============================
void DMA_UART_RX_IRQHandler(void) {
    // This ISR would be triggered by:
    //  - Half-transfer interrupt (update dma_write_index to middle)
    //  - Transfer-complete interrupt (update dma_write_index to start)
    // In real hardware, read DMA counter register to get write index
    dma_write_index = (dma_write_index + 64) % UART_RX_BUF_SIZE; // simulate DMA moving
}

// ============================
// Main simulation
// ============================
int main(void) {
    uart_dma_init();

    // Simulate DMA receiving data
    for (int i = 0; i < 128; i++) {
        uart_rx_buf[i] = i; // Simulated incoming bytes
    }

    // Simulate DMA ISR
    DMA_UART_RX_IRQHandler();

    // Read data
    uint8_t read_buf[50];
    uint16_t read_len = uart_dma_read(read_buf, sizeof(read_buf));

    printf("Read %u bytes:\n", read_len);
    for (int i = 0; i < read_len; i++) {
        printf("%d ", read_buf[i]);
    }
    printf("\n");

    return 0;
}
