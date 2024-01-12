#include "interface/rgb.h"

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "low/pwm.h"


static uint chan_num_r, slice_num_r, chan_num_g, slice_num_g, chan_num_b, slice_num_b;

void rgb_init(void) {
    gpio_init(DEFAULT_LED_R);
    gpio_set_dir(DEFAULT_LED_R, GPIO_OUT);

    gpio_init(DEFAULT_LED_G);
    gpio_set_dir(DEFAULT_LED_G, GPIO_OUT);

    gpio_init(DEFAULT_LED_B);
    gpio_set_dir(DEFAULT_LED_B, GPIO_OUT);
}

void rgb_set_color(uint16_t r, uint16_t g, uint16_t b) {
    rgb_set_red(r);
    rgb_set_green(g);
    rgb_set_blue(b);
}

void rgb_set_red(uint16_t n) {
    gpio_put(DEFAULT_LED_R, n);
}

void rgb_set_green(uint16_t n) {
    gpio_put(DEFAULT_LED_G, n);
}

void rgb_set_blue(uint16_t n) {
    gpio_put(DEFAULT_LED_B, n);
}