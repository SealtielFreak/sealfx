#include "fx/reverb.h"

#include "bank_memory.h"


static uint8_t decay = 1;
static uint32_t bank_counter_buff0 = 10000, bank_counter_buff1 = 5000, bank_counter_buff2 = 2500;

uint16_t reverb(uint16_t signal) {
    get_counter_value_memory_bank(bank_counter_buff0);

    set_counter_value_memory_bank(
            bank_counter_buff0,
            (signal + get_counter_value_memory_bank(bank_counter_buff0)) >> decay
    );

    set_counter_value_memory_bank(
            bank_counter_buff1,
            (signal + get_counter_value_memory_bank(bank_counter_buff1)) >> decay
    );

    set_counter_value_memory_bank(
            bank_counter_buff2,
            (signal + get_counter_value_memory_bank(bank_counter_buff2)) >> decay
    );

    bank_counter_buff0++;

    if (bank_counter_buff0 > DEFAULT_SPLIT_BANK_SIZE) {
        bank_counter_buff0 = 0; // % MAX_BUFFER_GLOBAL_SPACE
    }

    bank_counter_buff1++;

    if ((bank_counter_buff1 > DEFAULT_SPLIT_BANK_SIZE) || (bank_counter_buff1 > DEFAULT_SPLIT_BANK_SIZE * 2)) {
        bank_counter_buff1 = DEFAULT_SPLIT_BANK_SIZE;
    }

    bank_counter_buff2++;

    if ((bank_counter_buff2 > DEFAULT_SPLIT_BANK_SIZE * 2) || (bank_counter_buff2 > DEFAULT_SPLIT_BANK_SIZE * 3)) {
        bank_counter_buff1 = DEFAULT_SPLIT_BANK_SIZE * 2;
    }

    return (signal + (get_counter_value_memory_bank(bank_counter_buff0)) +
            (get_counter_value_memory_bank(bank_counter_buff1)) +
            (get_counter_value_memory_bank(bank_counter_buff2))) >> 2;
}
