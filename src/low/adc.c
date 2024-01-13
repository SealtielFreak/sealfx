#include "low/adc.h"

#include "hardware/adc.h"

void adc_init_pin(uint8_t pin, uint8_t chan, uint16_t clickdiv) {
    adc_gpio_init(pin);
    adc_select_input(chan);
    adc_set_clkdiv(clickdiv);
}

uint16_t adc_read_from(int8_t chan) {
    adc_select_input(chan);
    return adc_read();
}