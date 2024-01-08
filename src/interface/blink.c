#include "interface/blink.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "conf.h"

#include "hardware/pwm.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

#include "low/pwm.h"

uint chan_num, slice_num;

void init_blink(void) {
    chan_num = pwm_gpio_to_channel(LED_PIN_BUILT);
    slice_num = pwm_gpio_to_slice_num(LED_PIN_BUILT);
    pwm_init_pin(LED_PIN_BUILT, slice_num, chan_num, DEFAULT_CLKDIV_PWM, 255);
}

void blink(void) {
    for (uint16_t i = 0; i < 255; i += 5) {
        pwm_set_chan_level(slice_num, chan_num, i);
        sleep_ms(5);
    }

    for (uint16_t i = 255; i > 0; i -= 5) {
        pwm_set_chan_level(slice_num, chan_num, i);
        sleep_ms(5);
    }
}
