#include "fx/echo.h"

#include "bankmemory.h"

static uint8_t decay = 1;
static uint32_t bank_counter_buff = 0;

uint16_t echo(uint16_t signal) {
    set_counter_value_memory_bank(bank_counter_buff, (signal + get_counter_value_memory_bank(bank_counter_buff)) >> decay);

    bank_counter_buff = (bank_counter_buff + 1) % MAX_BUFFER_GLOBAL_SPACE;

    return (get_counter_value_memory_bank(bank_counter_buff) + signal) >> decay;
}