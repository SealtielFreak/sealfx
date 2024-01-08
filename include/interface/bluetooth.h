#ifndef SOUNDPI_PFX_BLUETOOTH_H
#define SOUNDPI_PFX_BLUETOOTH_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BUFFER_SIZE_UART_DMA 256

void ble_init(void);

void ble_send(char c);

int ble_send_str(const char *s);

char ble_read(void);

int ble_read_str(char *s, size_t len);

bool ble_is_received(void);

void ble_flush(void);

#endif //SOUNDPI_PFX_BLUETOOTH_H
