#ifndef SOUNDPI_PFX_CONF_H
#define SOUNDPI_PFX_CONF_H


#include "umath.h"

#define DEFAULT_FRQ_CPU_KHZ         270000

#define LED_PIN_BUILT               25

#define DEFAULT_GPIO_PWM0           17
#define DEFAULT_GPIO_PWM1           16

#define DEFAULT_CLKDIV_PWM          1
#define DEFAULT_WRAP_PWM            512 // 9bits

#define DEFAULT_WRAP_ADC            65536 // 16bits
#define DEFAULT_CLKDIV_ADC          0
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
#define DEFAULT_CLKDIV_RGB          2

#define DEFAULT_CHANNEL_ADC_CPU     4

#define MAX_AUDIO_VOLUME                DEFAULT_WRAP_ADC

#endif //SOUNDPI_PFX_CONF_H
