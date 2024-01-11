#include "fx/vibrato.h"

#include <stdbool.h>

#include "system/bankmemory.h"

static uint32_t bank_counter_buff = 0, delay_depth = 100, delay_depth_max = 100, delay_depth_min = 10;
static bool count_up;

uint16_t vibrato(uint16_t signal) {
    set_counter_value_memory_bank(bank_counter_buff, signal);
    bank_counter_buff++;

    if (bank_counter_buff >= delay_depth) {
        bank_counter_buff = 0;

        if (count_up) {
            for (uint8_t p = 0; p < 10; p++) {
                set_counter_value_memory_bank(bank_counter_buff + p, get_counter_value_memory_bank(delay_depth - 1));
            }

            delay_depth++;

            if (delay_depth >= delay_depth_max){
                count_up = 0;
            }
        } else {
            delay_depth--;

            if (delay_depth <= delay_depth_min) {
                count_up = 1;
            }
        }
    }

    return get_counter_value_memory_bank(bank_counter_buff);
}