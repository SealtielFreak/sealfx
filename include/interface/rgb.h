
#ifndef SOUNDPI_PFX_RGB_H
#define SOUNDPI_PFX_RGB_H

#include "stdint.h"

#include "conf.h"

#define MAX_RGB_COLOR               DEFAULT_WRAP_RGB - 1

void rgb_init(void);

void rgb_set_color(uint16_t r, uint16_t g, uint16_t b);

void rgb_set_red(uint16_t n);

void rgb_set_green(uint16_t n);

void rgb_set_blue(uint16_t n);

#endif //SOUNDPI_PFX_RGB_H
