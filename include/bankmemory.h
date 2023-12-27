#ifndef SOUNDPI_PFX_BANKMEMORY_H
#define SOUNDPI_PFX_BANKMEMORY_H

#include <stdint.h>

#define MAX_BUFFER_GLOBAL_SPACE         102400
#define DEFAULT_SPLIT_BANK_SIZE         MAX_BUFFER_GLOBAL_SPACE / 4

uint16_t get_counter_value_memory_bank(unsigned long index);

void set_counter_value_memory_bank(unsigned long index, uint16_t value);

#endif //SOUNDPI_PFX_BANKMEMORY_H
