#include "fx/fuzz.h"

#include "conf.h"

#define MAX_FUZZ_VOLUME (MAX_AUDIO_VOLUME / 2)

uint16_t fuzz_value = 1024;

uint16_t fuzz(uint16_t signal) {
    if (signal > MAX_FUZZ_VOLUME + fuzz_value) {
        signal = MAX_FUZZ_VOLUME;
    }

    if (signal < MAX_FUZZ_VOLUME - fuzz_value) {
        signal = 0;
    }

    return signal;
}
