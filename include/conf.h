#ifndef SOUNDPI_PFX_CONF_H
#define SOUNDPI_PFX_CONF_H


#define get_clkdiv_hz(n) ((48000000.f * 256) / (n * 65536))

#define DEFAULT_FRQ_CPU_KHZ         270000

#define LED_PIN_BUILT               25

#define DEFAULT_GPIO_PWM0           17
#define DEFAULT_GPIO_PWM1           16

#define DEFAULT_HZ_PWM              1000000
#define DEFAULT_WRAP_PWM            200
#define DEFAULT_CLKDIV_PWM          1

#define DEFAULT_CLKDIV_ADC          2.0
#define DEFAULT_GPIO_ADC            26
#define DEFAULT_CHANNEL_ADC         0

#define DEFAULT_UART_ID             uart0
#define DEFAULT_BAUD_RATE           9600
#define DEFAULT_DATA_BITS           8
#define DEFAULT_STOP_BITS           1
#define DEFAULT_PARITY              UART_PARITY_NONE

#define DEFAULT_LED_R               11
#define DEFAULT_LED_G               12
#define DEFAULT_LED_B               13
#define DEFAULT_WRAP_RGB            255
#define DEFAULT_CLKDIV_RGB          8

#endif //SOUNDPI_PFX_CONF_H
