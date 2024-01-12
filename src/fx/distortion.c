#include "fx/distortion.h"

uint16_t distortion_value = 25;

uint16_t distortion(uint16_t signal) {
    if (signal > 2047 + distortion_value) {
        signal = 2047 + distortion_value;
    }

    if (signal < 2047 - distortion_value) {
        signal = 2047 - distortion_value;
    }

    return signal;
}