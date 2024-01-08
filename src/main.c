#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>

#include "conf.h"

#include "interface/audio.h"
#include "interface/bluetooth.h"
#include "interface/rgb.h"
#include "interface/blink.h"

#include "fx.h"
#include "ustr.h"

#define BUFF_INPUT_LENGHT       86

static uint16_t signal;

effect current_effect = CLEAN;
effect_rgb current_color = {0, 0, 0};

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
                current_color = fx_rgb_color(current_effect);

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

        rgb_set_color(current_color.r, current_color.g, current_color.b);

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
