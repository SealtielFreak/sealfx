#ifndef SOUNDPI_PFX_CONF_H
#define SOUNDPI_PFX_CONF_H


#define get_clkdiv_hz(n) ((48000000.f * 256) / (n * 65536))

#define DEFAULT_FRQ_CPU_KHZ         270000

#define LED_PIN_BUILT               25

#define DEFAULT_GPIO_PWM0           17
#define DEFAULT_GPIO_PWM1           16

#define DEFAULT_HZ_PWM              1000000

#define DEFAULT_WRAP_PWM            128
#define DEFAULT_CLKDIV_PWM          get_clkdiv_hz(DEFAULT_HZ_PWM)

#define DEFAULT_CLKDIV_ADC          0
#define DEFAULT_GPIO_ADC            26
#define DEFAULT_CHANNEL_ADC         0

#endif //SOUNDPI_PFX_CONF_H
