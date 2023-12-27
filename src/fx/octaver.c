#include "fx/octaver.h"

#include "bankmemory.h"

static uint32_t delay_write = 0, delay_read = 0, counter = 0, divider = 0;

uint16_t octaver(uint16_t signal) {
    set_counter_value_memory_bank(delay_write, signal);
    delay_write++;

    divider++;

    if (divider >= 2) {
        delay_read++;
        divider = 0;

    }

    delay_write %= MAX_BUFFER_GLOBAL_SPACE;

    return get_counter_value_memory_bank(delay_write);
}