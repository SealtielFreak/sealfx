#include "fx/fuzz.h"

uint16_t fuzz_value = 300;

uint16_t fuzz(uint16_t signal) {
    if (signal > 2047 + fuzz_value) {
        signal = 4095;
    }

    if (signal < 2047 - fuzz_value) {
        signal = 0;
    }

    return signal;
}
