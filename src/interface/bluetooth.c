#include "interface/bluetooth.h"

#include <stdio.h>

#include <pico/stdlib.h>
#include "hardware/uart.h"

#include "conf.h"

void ble_init(void) {
    uart_init(DEFAULT_UART_ID, DEFAULT_BAUD_RATE);

    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_set_hw_flow(DEFAULT_UART_ID, false, false);
    uart_set_format(DEFAULT_UART_ID, DEFAULT_DATA_BITS, DEFAULT_STOP_BITS, DEFAULT_PARITY);
}

void ble_send(char c) {
    uart_putc_raw(DEFAULT_UART_ID, c);
}

void ble_send_str(const char *s) {
    uart_puts(DEFAULT_UART_ID, s);
}

char ble_read(void) {
    return 0;
}

void ble_read_str(char *s) {

}