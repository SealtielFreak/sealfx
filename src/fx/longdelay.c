#include "fx/longdelay.h"

#include "bankmemory.h"

static uint8_t decay = 2;
static uint32_t bank_counter_buff = 0;

uint16_t longdelay(uint16_t signal) {
    set_counter_value_memory_bank(bank_counter_buff, signal);

    bank_counter_buff = (bank_counter_buff + 1) % MAX_BUFFER_GLOBAL_SPACE;

    return (get_counter_value_memory_bank(bank_counter_buff) + signal) >> decay;
}