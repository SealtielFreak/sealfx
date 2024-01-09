#ifndef SOUNDPI_PFX_FX_H
#define SOUNDPI_PFX_FX_H

#include "fx/reverb.h"
#include "fx/longdelay.h"
#include "fx/echo.h"
#include "fx/booster.h"
#include "fx/fuzz.h"
#include "fx/distortion.h"
#include "fx/bitcrush.h"
#include "fx/tremolo.h"
#include "fx/octaver.h"

typedef enum {
    UNKNOWN, CLEAN, REVERB, DELAY, ECHO, BOOSTER, FUZZ, DISTORTION, BITCRUSH, TREMOLO, OCTAVER, DAFTPUNK
} effect;

typedef struct {
    uint16_t r, g, b;
} effect_rgb;

#define LENGTH_EFFECTS_REGISTER         11

uint16_t fx_select_effect(effect index, uint16_t signal);

effect fx_from_string(const char* str);

effect_rgb fx_rgb_color(effect index);

#endif //SOUNDPI_PFX_FX_H
