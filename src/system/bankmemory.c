#include "system/bankmemory.h"

#include <stdlib.h>

volatile uint16_t global_bank_memory[MAX_BUFFER_GLOBAL_SPACE] = {0};

uint16_t get_counter_value_memory_bank(unsigned long index) {
    if(index > MAX_BUFFER_GLOBAL_SPACE - 1) {
        return 0;
    }

    return global_bank_memory[index];
}

void set_counter_value_memory_bank(unsigned long index, uint16_t value) {
    if(index > MAX_BUFFER_GLOBAL_SPACE - 1) {
        return;
    }

    global_bank_memory[index] = value;
}

void flush_memory_bank(void) {
    memset(global_bank_memory, 0, MAX_BUFFER_GLOBAL_SPACE);
}
