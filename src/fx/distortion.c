#include "fx/distortion.h"

#include "conf.h"

#define MAX_DISTORTION_VOLUME (MAX_AUDIO_VOLUME / 2)

uint16_t distortion_value = 512;

uint16_t distortion(uint16_t signal) {
    if (signal > MAX_DISTORTION_VOLUME + distortion_value) {
        signal = MAX_DISTORTION_VOLUME + distortion_value;
    }

    if (signal < MAX_DISTORTION_VOLUME - distortion_value) {
        signal = MAX_DISTORTION_VOLUME - distortion_value;
    }

    return signal;
}