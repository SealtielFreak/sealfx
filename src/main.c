#include <stdio.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "conf.h"
#include "interface.h"
#include "bankmemory.h"

#include "fx/reverb.h"
#include "fx/longdelay.h"
#include "fx/booster.h"
#include "fx/fuzz.h"
#include "fx/distortion.h"
#include "fx/bitcrush.h"
#include "fx/tremolo.h"
#include "fx/echo.h"
#include "fx/octaver.h"

long mapping(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void blink() {
    uint chan_num = pwm_gpio_to_channel(LED_PIN_BUILT);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN_BUILT);
    pwm_init_pin(LED_PIN_BUILT, slice_num, chan_num, DEFAULT_CLKDIV_PWM, 255);

    while (1) {
        for (uint16_t i = 0; i < 255; i += 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(25);
        }

        for (uint16_t i = 255; i > 0; i -= 5) {
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

    while (!set_sys_clock_khz(DEFAULT_FRQ_CPU_KHZ, true)) {
        printf("Failure config clock");
    }

    multicore_launch_core1(blink);

    while (1) {
        uint16_t signal = read_audio();

        signal = echo(signal);

        write_audio(signal);
    }
}