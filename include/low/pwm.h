#ifndef SOUNDPI_PFX_PWM_H
#define SOUNDPI_PFX_PWM_H

#include <stdint.h>
#include <stdlib.h>

void pwm_init_pin(uint8_t pin, uint slice, uint chan, float div, uint wrap);

#endif //SOUNDPI_PFX_PWM_H
