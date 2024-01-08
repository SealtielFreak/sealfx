#include "interface/rgb.h"

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "low/pwm.h"


static uint chan_num_r, slice_num_r, chan_num_g, slice_num_g, chan_num_b, slice_num_b;

void rgb_init(void) {
    chan_num_r = pwm_gpio_to_channel(DEFAULT_LED_R);
    slice_num_r = pwm_gpio_to_slice_num(DEFAULT_LED_R);
    pwm_init_pin(DEFAULT_LED_R, chan_num_r, slice_num_r, DEFAULT_CLKDIV_RGB, DEFAULT_WRAP_RGB);

    chan_num_g = pwm_gpio_to_channel(DEFAULT_LED_G);
    slice_num_g = pwm_gpio_to_slice_num(DEFAULT_LED_G);
    pwm_init_pin(DEFAULT_LED_G, chan_num_g, slice_num_g, DEFAULT_CLKDIV_RGB, DEFAULT_WRAP_RGB);

    chan_num_b = pwm_gpio_to_channel(DEFAULT_LED_B);
    slice_num_b = pwm_gpio_to_slice_num(DEFAULT_LED_B);
    pwm_init_pin(DEFAULT_LED_B, chan_num_b, slice_num_b, DEFAULT_CLKDIV_RGB, DEFAULT_WRAP_RGB);
}

void rgb_set_color(uint16_t r, uint16_t g, uint16_t b) {
    rgb_set_red(r);
    rgb_set_green(g);
    rgb_set_blue(b);
}

void rgb_set_red(uint16_t n) {
    pwm_set_chan_level(slice_num_r, chan_num_r, n);
}

void rgb_set_green(uint16_t n) {
    pwm_set_chan_level(slice_num_g, chan_num_g, n);
}

void rgb_set_blue(uint16_t n) {
    pwm_set_chan_level(slice_num_b, chan_num_b, n);
}