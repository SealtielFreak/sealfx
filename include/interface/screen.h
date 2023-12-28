#ifndef SOUNDPI_PFX_SCREEN_H
#define SOUNDPI_PFX_SCREEN_H

#include <stdint.h>

void screen_clear(void);

void screen_show_cursor(void);

void screen_hide_cursor(void);

void screen_putchar(char);

void screen_putstr(const char*);

#endif //SOUNDPI_PFX_SCREEN_H
