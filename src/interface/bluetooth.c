#include "interface/bluetooth.h"

#include <stdio.h>
#include <string.h>

#include <pico/stdlib.h>
#include "hardware/uart.h"
#include "hardware/dma.h"

#include "conf.h"
#include "ustr.h"

#define DMA_TX_CHANNEL 0
#define DMA_RX_CHANNEL 1

volatile uint8_t tx_buffer[BUFFER_SIZE_UART_DMA];
volatile uint8_t rx_buffer[BUFFER_SIZE_UART_DMA];
dma_channel_config dma_chan;

void ble_dma_init(void) {
    dma_chan = dma_channel_get_default_config(DMA_TX_CHANNEL);
    channel_config_set_transfer_data_size(&dma_chan, DMA_SIZE_8);
    channel_config_set_read_increment(&dma_chan, true);
    channel_config_set_write_increment(&dma_chan, false);
    channel_config_set_dreq(&dma_chan, DREQ_UART0_TX);
    dma_channel_configure(DMA_TX_CHANNEL, &dma_chan,
                          &uart_get_hw(DEFAULT_UART_ID)->dr,
                          tx_buffer,
                          BUFFER_SIZE_UART_DMA,
                          false
    );

    dma_chan = dma_channel_get_default_config(DMA_RX_CHANNEL);
    channel_config_set_transfer_data_size(&dma_chan, DMA_SIZE_8);
    channel_config_set_read_increment(&dma_chan, false);
    channel_config_set_write_increment(&dma_chan, true);
    channel_config_set_dreq(&dma_chan, DREQ_UART0_RX);
    dma_channel_configure(DMA_RX_CHANNEL, &dma_chan,
                          rx_buffer,
                          &uart_get_hw(DEFAULT_UART_ID)->dr,
                          BUFFER_SIZE_UART_DMA,
                          false
    );

    ble_flush();

    dma_channel_start(DMA_TX_CHANNEL);
    dma_channel_start(DMA_RX_CHANNEL);
}

void ble_flush_rx(void) {
    memset(rx_buffer, 0, BUFFER_SIZE_UART_DMA);

}

void ble_flush_tx(void) {
    memset(tx_buffer, 0, BUFFER_SIZE_UART_DMA);
}

void ble_init(void) {
    uart_init(DEFAULT_UART_ID, DEFAULT_BAUD_RATE);

    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_set_hw_flow(DEFAULT_UART_ID, false, false);
    uart_set_format(DEFAULT_UART_ID, DEFAULT_DATA_BITS, DEFAULT_STOP_BITS, DEFAULT_PARITY);
    uart_set_fifo_enabled(DEFAULT_UART_ID, false);

    ble_dma_init();
}

void ble_send(char c) {

}

int ble_send_str(const char *s) {
    size_t len = strlen(s);

    if(len > BUFFER_SIZE_UART_DMA) {
        return 1;
    }

    ble_flush_tx();
    memcpy(tx_buffer, s, len);

    dma_channel_transfer_from_buffer_now(DMA_TX_CHANNEL, tx_buffer, len);
    dma_channel_wait_for_finish_blocking(DMA_TX_CHANNEL);

    return 0;
}

char ble_read(void) {
    return 0;
}

int ble_read_str(char *s, size_t len) {
    if(s == NULL || len > BUFFER_SIZE_UART_DMA) {
        return 1;
    }

    dma_channel_transfer_to_buffer_now(DMA_RX_CHANNEL, rx_buffer, BUFFER_SIZE_UART_DMA);

    if (rx_buffer[0] == '\0') {
        return 1;
    }

    for (size_t i = 0; i < BUFFER_SIZE_UART_DMA; i++) {
        s[i] = rx_buffer[i];
        if (rx_buffer[i] == '\0') break;
    }

    memset(rx_buffer, 0, BUFFER_SIZE_UART_DMA);

    return 0;
}

bool ble_is_received(void) {
    return strlen(rx_buffer) > 0;
}

void ble_flush(void) {
    ble_flush_rx();
    ble_flush_tx();
}