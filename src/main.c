#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "hardware/pwm.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

#include "conf.h"
#include "interface/audio.h"
#include "interface/screen.h"
#include "interface/bluetooth.h"

#include "fx/reverb.h"
#include "fx/longdelay.h"
#include "fx/booster.h"
#include "fx/fuzz.h"
#include "fx/distortion.h"
#include "fx/bitcrush.h"
#include "fx/tremolo.h"
#include "fx/echo.h"
#include "fx/octaver.h"

#include "umath.h"

#define I2C_PORT        i2c0
#define I2C_ADDRESS     0x3C

#define BUFF_INPUT_LENGHT       86

static uint16_t signal;

void init_i2c_communication(void);

static void blink() {
    uint chan_num = pwm_gpio_to_channel(LED_PIN_BUILT);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN_BUILT);
    pwm_init_pin(LED_PIN_BUILT, slice_num, chan_num, DEFAULT_CLKDIV_PWM, 255);

    char buffinput[BUFF_INPUT_LENGHT];

    while (1) {
        if(!ble_read_str(buffinput, BUFF_INPUT_LENGHT)) {
            ble_send_str("Effect selected: ");
            ble_send_str(buffinput);
            ble_send_str("\r\n");

            memset(buffinput, 0, BUFF_INPUT_LENGHT);
        }

        for (uint16_t i = 0; i < 255; i += 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(5);
        }

        for (uint16_t i = 255; i > 0; i -= 5) {
            pwm_set_chan_level(slice_num, chan_num, i);
            sleep_ms(5);
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

    ble_init();

    multicore_launch_core1(blink);

    encode_init();
    decode_init();

    while (1) {
        signal = read_audio();

        signal = longdelay(signal);

        write_audio(signal);
    }
}

void init_i2c_communication(void) {
    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);

    gpio_pull_up(4);
    gpio_pull_up(5);
}
