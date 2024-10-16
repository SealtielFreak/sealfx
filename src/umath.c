#include <stdlib.h>
#include "umath.h"


float get_clkdiv_hz(float n) {
    return (48000000.f * 256) / (n * 65536);
}

uint16_t mapping_u16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t range_random_u16(uint16_t min, uint16_t max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}