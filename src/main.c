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
#include "interface/rgb.h"
#include "interface/blink.h"

#include "low/pwm.h"

#include "fx.h"
#include "umath.h"
#include "ustr.h"

#define I2C_PORT        i2c0
#define I2C_ADDRESS     0x3C

#define BUFF_INPUT_LENGHT       86

static uint16_t signal;

void init_i2c_communication(void);

effect current_effect = CLEAN;

static void core1(void) {
    init_blink();
    ble_init();
    rgb_init();

    char buffinput[BUFF_INPUT_LENGHT];

    while (1) {
        if(!ble_read_str(buffinput, BUFF_INPUT_LENGHT)) {
            buffinput[findchr(buffinput, '\r')] = '\0';
            effect effect_selected = fx_from_string(buffinput);

            if(effect_selected != UNKNOWN) {

                current_effect = fx_from_string(buffinput);

                ble_send_str("OK+Effect=");
                ble_send_str(buffinput);
                ble_send_str("\r\n");
            } else {
                ble_send_str("ERROR+EffectNoFound=");
                ble_send_str(buffinput);
                ble_send_str("\r\n");
            }

            memset(buffinput, 0, BUFF_INPUT_LENGHT);
        }

        blink();
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

    multicore_launch_core1(core1);

    encode_init();
    decode_init();

    while (1) {
        signal = read_audio();

        signal = fx_select_effect(current_effect, signal);

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
