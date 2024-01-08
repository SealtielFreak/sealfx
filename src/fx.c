#include "fx.h"

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