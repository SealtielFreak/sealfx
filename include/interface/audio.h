#ifndef SOUNDPI_PFX_AUDIO_H
#define SOUNDPI_PFX_AUDIO_H

#include <stdint.h>
#include <stdlib.h>

void encode_init(void);

void decode_init(void);

uint16_t read_audio(void);

void write_audio(uint16_t signal);

#endif //SOUNDPI_PFX_AUDIO_H
