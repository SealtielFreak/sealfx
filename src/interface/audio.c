#include "interface/audio.h"

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "low/pwm.h"
#include "low/adc.h"

#include "umath.h"

#include "conf.h"

static uint8_t chan_num_0, slice_num_0, chan_num_1, slice_num_1;
uint16_t adj_min = 900, adj_max = 4096;

void encode_init(void) {
    chan_num_0 = pwm_gpio_to_channel(DEFAULT_GPIO_PWM0);
    slice_num_0 = pwm_gpio_to_slice_num(DEFAULT_GPIO_PWM0);
    pwm_init_pin(DEFAULT_GPIO_PWM0, slice_num_0, chan_num_0, DEFAULT_CLKDIV_PWM, DEFAULT_WRAP_PWM);

    chan_num_1 = pwm_gpio_to_channel(DEFAULT_GPIO_PWM1);
    slice_num_1 = pwm_gpio_to_slice_num(DEFAULT_GPIO_PWM1);
    pwm_init_pin(DEFAULT_GPIO_PWM1, chan_num_1, slice_num_1, DEFAULT_CLKDIV_PWM, DEFAULT_WRAP_PWM);
}

void decode_init(void) {
    adc_init();
    adc_init_pin(DEFAULT_GPIO_ADC, DEFAULT_CHANNEL_ADC, DEFAULT_CLKDIV_ADC);
}

uint16_t read_audio(void) {
    return adc_read_from(DEFAULT_CHANNEL_ADC);
}

void write_audio(uint16_t signal) {
    const uint16_t signal_out = cleaner_audio(signal);

    pwm_set_chan_level(chan_num_1, chan_num_1, signal_out);

    // pwm_set_chan_level(slice_num_0, chan_num_0, signal_out & 63);
    // pwm_set_chan_level(slice_num_1, chan_num_1, signal_out >> 6);
}

uint16_t cleaner_audio(uint16_t signal) {
    return signal;
}

void encode_cleaner_adjust(uint16_t min, uint16_t max) {
    adj_min = min;
    adj_max = max;
}
