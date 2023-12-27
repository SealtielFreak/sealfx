#include "fx/delay.h"

#include "bank_memory.h"

static uint8_t decay = 2;
static uint32_t bank_counter_buff;

uint16_t longdelay(uint16_t signal) {
    set_counter_value_memory_bank(bank_counter_buff, signal);

    bank_counter_buff++;

    if(bank_counter_buff > DEFAULT_SPLIT_BANK_SIZE * 3 || bank_counter_buff > bank_counter_buff * 4) {
        bank_counter_buff = 0;
    }

    return (get_counter_value_memory_bank(bank_counter_buff) + signal) >> decay;
}