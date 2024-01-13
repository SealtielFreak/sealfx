#include "system/cpu.h"

#include <stdint.h>

#include "hardware/adc.h"
#include "low/adc.h"

#include "conf.h"

void init_cpu_service(void) {
    adc_select_input(DEFAULT_CHANNEL_ADC_CPU);
    adc_set_clkdiv(1);
}

float get_cpu_temp_celsius(void) {
    float voltage = adc_read_from(DEFAULT_CHANNEL_ADC_CPU) * (3.3 / 4096);

    return 27 - (voltage - 0.706) / 0.001721;
}

float get_cpu_temp_fahrenheit(void) {
    return 32 + (1.8 * get_cpu_temp_celsius());
}