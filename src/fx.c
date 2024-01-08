#include "fx.h"

#include "interface/rgb.h"

#include "string.h"

uint16_t fx_select_effect(effect index, uint16_t signal) {
    switch (index) {
        case REVERB: return reverb(signal);
        case DELAY: return longdelay(signal);
        case ECHO: return echo(signal);
        case BOOSTER: return booster(signal);
        case FUZZ: return fuzz(signal);
        case DISTORTION: return distortion(signal);
        case BITCRUSH: return bitcrush(signal);
        case TREMOLO: return tremolo(signal);
        case OCTAVER: return octaver(signal);
    }

    return signal;
}

effect fx_from_string(const char* str) {
    if(!strcmp("clean", str)) {
        return CLEAN;
    } else if(!strcmp("delay", str)) {
        return DELAY;
    }  else if(!strcmp("reverb", str)) {
        return REVERB;
    } else if(!strcmp("echo", str)) {
        return ECHO;
    } else if(!strcmp("booster", str)) {
        return BOOSTER;
    } else if(!strcmp("fuzz", str)) {
        return FUZZ;
    } else if(!strcmp("distortion", str)) {
        return DISTORTION;
    } else if(!strcmp("bitcrush", str)) {
        return BITCRUSH;
    } else if(!strcmp("tremolo", str)) {
        return TREMOLO;
    } else if(!strcmp("octaver", str)) {
        return OCTAVER;
    }

    return UNKNOWN;
}

effect_rgb fx_rgb_color(effect index) {
    switch (index) {
        case REVERB: return (effect_rgb) {MAX_RGB_COLOR, 0, 0};
        case DELAY: return (effect_rgb) {0, MAX_RGB_COLOR, 0};
        case ECHO: return (effect_rgb) {0, 0, MAX_RGB_COLOR};
        case BOOSTER: return (effect_rgb) {MAX_RGB_COLOR, MAX_RGB_COLOR, 0};
        case FUZZ: return (effect_rgb) {0, MAX_RGB_COLOR, MAX_RGB_COLOR};
        case DISTORTION: return (effect_rgb) {MAX_RGB_COLOR, 0, MAX_RGB_COLOR};
        case BITCRUSH: return (effect_rgb) {MAX_RGB_COLOR/2, MAX_RGB_COLOR/4, 0};
        case TREMOLO: return (effect_rgb) {MAX_RGB_COLOR/3, 0, MAX_RGB_COLOR/3};
        case OCTAVER: return (effect_rgb) {MAX_RGB_COLOR/3, MAX_RGB_COLOR/2, MAX_RGB_COLOR/5};
    }

    return (effect_rgb) {MAX_RGB_COLOR, MAX_RGB_COLOR, MAX_RGB_COLOR};
}