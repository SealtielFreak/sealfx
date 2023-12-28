#include <stdio.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "hardware/pwm.h"
#include "hardware/uart.h"

#include "conf.h"
#include "interface.h"

#include "fx/reverb.h"
#include "fx/longdelay.h"
#include "fx/booster.h"
#include "fx/fuzz.h"
#include "fx/distortion.h"
#include "fx/bitcrush.h"
#include "fx/tremolo.h"
#include "fx/echo.h"
#include "fx/octaver.h"

#define UART_ID         uart0
#define BAUD_RATE       9600
#define DATA_BITS       8
#define STOP_BITS       1
#define PARITY          UART_PARITY_NONE

long mapping(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void blink() {
    uint chan_num = pwm_gpio_to_channel(LED_PIN_BUILT);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN_BUILT);
    pwm_init_pin(LED_PIN_BUILT, slice_num, chan_num, DEFAULT_CLKDIV_PWM, 255);

    while (1) {
        uart_puts(UART_ID, "Hello, UART!\r\n");

        for (uint16_t i = 0; i < 255; i += 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(25);
        }

        for (uint16_t i = 255; i > 0; i -= 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(25);
        }

        sleep_ms(1000);
    }
}

int main() {
    stdio_init_all();
    stdio_usb_init();
    stdio_usb_connected();
    stdio_flush();

    while (!set_sys_clock_khz(DEFAULT_FRQ_CPU_KHZ, true)) {
        printf("Failure config clock");
    }

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    multicore_launch_core1(blink);

    while (1) {
        uint16_t signal = read_audio();

        signal = echo(signal);

        write_audio(signal);
    }
}