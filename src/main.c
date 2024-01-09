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

#include "system/cpu.h"

#include "fx.h"
#include "ustr.h"

#define BUFF_STR_LENGHT       86

static uint16_t signal;

effect current_effect = CLEAN;
effect_rgb current_color = {0, 0, 0};

static void core1(void) {
    init_blink();
    ble_init();
    rgb_init();

    char buffstr[BUFF_STR_LENGHT];

    while (1) {
        if(!ble_read_str(buffstr, BUFF_STR_LENGHT)) {
            buffstr[findchr(buffstr, '\r')] = '\0';

            tolower_str(buffstr);
            effect effect_selected = fx_from_string(buffstr);

            if(effect_selected != UNKNOWN) {
                current_effect = fx_from_string(buffstr);
                current_color = fx_rgb_color(current_effect);

                ble_send_str("OK+Effect=");
                ble_send_str(buffstr);
                ble_send_str("\r\n");
            } else if(!strcmp(buffstr, "cpu")) {
                sprintf(buffstr, "%.2f", get_cpu_temp_celsius());

                ble_send_str("OK+CPUTemperature=");
                ble_send_str(buffstr);
                ble_send_str("\r\n");
            } else {
                ble_send_str("ERROR+EffectNoFound=");
                ble_send_str(buffstr);
                ble_send_str("\r\n");
            }

            memset(buffstr, 0, BUFF_STR_LENGHT);
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
