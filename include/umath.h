
#ifndef SOUNDPI_PFX_UMATH_H
#define SOUNDPI_PFX_UMATH_H

#include <stdint.h>

uint16_t mapping_u16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

uint16_t range_random_u16(uint16_t min, uint16_t max);

#endif //SOUNDPI_PFX_UMATH_H
