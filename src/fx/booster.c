#include "fx/booster.h"

uint16_t booster_value = 2047;

uint16_t booster(uint16_t signal) {
    return (uint16_t) ((float) (signal) * (float) ((float) booster_value / (float) 4095.0));
}