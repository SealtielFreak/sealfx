#include <stdio.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#define LED_PIN_BUILT           25

#define DEFAULT_WRAP_PWM        4096
#define DEFAULT_DIV_PWM         3

#define DEFAULT_CLOCK_DIV_ADC   0
#define DEFAULT_GPIO_ADC        26
#define DEFAULT_CHANNEL_ADC     0

static volatile uint16_t signal = 0;

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
    pwm_init_pin(LED_PIN_BUILT, slice_num, chan_num, DEFAULT_DIV_PWM, 255);

    while(1) {
        for(uint16_t i = 0; i < 255; i += 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(25);
        }

        for(uint16_t i = 255; i > 0; i -= 5) {
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
    adc_set_clkdiv(DEFAULT_CLOCK_DIV_ADC);

    const uint8_t pwm_0 = 0;
    uint chan_num_0 = pwm_gpio_to_channel(pwm_0);
    uint slice_num_0 = pwm_gpio_to_slice_num(pwm_0);
    pwm_init_pin(pwm_0, slice_num_0, chan_num_0, DEFAULT_DIV_PWM, DEFAULT_WRAP_PWM);

    const uint8_t pwm_1 = 1;
    uint chan_num_1 = pwm_gpio_to_channel(pwm_1);
    uint slice_num_1 = pwm_gpio_to_slice_num(pwm_1);
    pwm_init_pin(pwm_1, chan_num_1, slice_num_1, DEFAULT_DIV_PWM, DEFAULT_WRAP_PWM);

    multicore_launch_core1(blink);

    while (1) {
        signal = adc_read();

        pwm_set_chan_level(slice_num_0, chan_num_0, signal);
        pwm_set_chan_level(slice_num_1, chan_num_1, signal & 0x7ff);
    }
}