#include "fx/booster.h"

#include "conf.h"

uint16_t booster_value = 4096;

uint16_t booster(uint16_t signal) {
    return (uint16_t) ((float) (signal) * (float) ((float) booster_value / (float) MAX_AUDIO_VOLUME));
}