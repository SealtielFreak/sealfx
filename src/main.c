#include <stdio.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "bankmemory.h"

#include "fx/reverb.h"
#include "fx/longdelay.h"
#include "fx/booster.h"
#include "fx/fuzz.h"
#include "fx/distortion.h"
#include "fx/bitcrush.h"
#include "fx/tremolo.h"
#include "fx/echo.h"
#include "fx/octaver.h"

#define get_clkdiv_hz(n) ((48000000.f * 256) / (n * 65536))

#define LED_PIN_BUILT               25

#define DEFAULT_GPIO_PWM0           17
#define DEFAULT_GPIO_PWM1           16

#define DEFAULT_HZ_PWM              1000000

#define DEFAULT_WRAP_PWM            128
#define DEFAULT_CLKDIV_PWM          get_clkdiv_hz(DEFAULT_HZ_PWM)

#define DEFAULT_CLKDIV_ADC          0
#define DEFAULT_GPIO_ADC            26
#define DEFAULT_CHANNEL_ADC         0


long mapping(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void pwm_init_pin(uint8_t pin, uint slice, uint chan, float div, uint wrap) {
    gpio_set_function(pin, GPIO_FUNC_PWM);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, div);
    pwm_config_set_wrap(&config, wrap);

    pwm_init(slice, &config, true);
}

static void blink() {
    uint chan_num = pwm_gpio_to_channel(LED_PIN_BUILT);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN_BUILT);
    pwm_init_pin(LED_PIN_BUILT, slice_num, chan_num, DEFAULT_CLKDIV_PWM, 255);

    while (1) {
        for (uint16_t i = 0; i < 255; i += 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(25);
        }

        for (uint16_t i = 255; i > 0; i -= 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(25);
        }

    }
}


int main() {
    stdio_init_all();
    stdio_usb_init();
    stdio_usb_connected();
    stdio_flush();

    while (!set_sys_clock_khz(270000, true)) {
        printf("Failure config clock");
    }

    adc_init();
    adc_gpio_init(DEFAULT_GPIO_ADC);
    adc_select_input(DEFAULT_CHANNEL_ADC);
    adc_set_clkdiv(DEFAULT_CLKDIV_ADC);

    uint chan_num_0 = pwm_gpio_to_channel(DEFAULT_GPIO_PWM0);
    uint slice_num_0 = pwm_gpio_to_slice_num(DEFAULT_GPIO_PWM0);
    pwm_init_pin(DEFAULT_GPIO_PWM0, slice_num_0, chan_num_0, DEFAULT_CLKDIV_PWM, DEFAULT_WRAP_PWM);

    uint chan_num_1 = pwm_gpio_to_channel(DEFAULT_GPIO_PWM1);
    uint slice_num_1 = pwm_gpio_to_slice_num(DEFAULT_GPIO_PWM1);
    pwm_init_pin(DEFAULT_GPIO_PWM1, chan_num_1, slice_num_1, DEFAULT_CLKDIV_PWM, DEFAULT_WRAP_PWM);

    multicore_launch_core1(blink);

    while (1) {
        uint16_t signal = adc_read();

        // signal = reverb(signal);
        // signal = echo(signal);
        // signal = longdelay(signal);
        // signal = tremolo(signal);
        // signal = longdelay(signal);
        // signal = octaver(signal);
        // signal = distortion(signal);
        // signal = fuzz(signal);
        // signal = booster(signal);

        pwm_set_chan_level(slice_num_0, chan_num_0, signal & 127);
        pwm_set_chan_level(slice_num_1, chan_num_1, signal >> 7);
    }
}