#ifndef SOUNDPI_PFX_ADC_H
#define SOUNDPI_PFX_ADC_H

#include "stdint.h"

void adc_init_pin(uint8_t pin, uint8_t chan, uint16_t clickdiv);

uint16_t adc_read_from(int8_t chan);

#endif //SOUNDPI_PFX_ADC_H
