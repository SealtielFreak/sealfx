#include "fx/bitcrush.h"

uint16_t bit_crush = 1;

uint16_t bitcrush(uint16_t signal) {
    return signal << bit_crush;
}