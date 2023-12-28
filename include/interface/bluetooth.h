#ifndef SOUNDPI_PFX_BLUETOOTH_H
#define SOUNDPI_PFX_BLUETOOTH_H

#include <stdint.h>

void ble_init(void);

void ble_send(char c);

void ble_send_str(const char *s);

char ble_read(void);

void ble_read_str(char *s);

#endif //SOUNDPI_PFX_BLUETOOTH_H
