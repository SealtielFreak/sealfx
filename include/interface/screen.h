#ifndef SOUNDPI_PFX_SCREEN_H
#define SOUNDPI_PFX_SCREEN_H

#include <stdint.h>

void screen_clear(void);

void show_cursor(void);

void hide_cursor(void);

void putchr(char);

void putstr(const char*);

#endif //SOUNDPI_PFX_SCREEN_H
