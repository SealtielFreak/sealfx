#include "low/pwm.h"

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"


void pwm_init_pin(uint8_t pin, uint slice, uint chan, float div, uint wrap) {
    gpio_set_function(pin, GPIO_FUNC_PWM);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, div);
    pwm_config_set_wrap(&config, wrap);

    pwm_init(slice, &config, true);
}
