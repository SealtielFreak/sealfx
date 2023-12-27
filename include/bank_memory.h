#ifndef SOUNDPI_PFX_BANK_MEMORY_H
#define SOUNDPI_PFX_BANK_MEMORY_H

#include <stdint.h>

#define MAX_BUFFER_GLOBAL_SPACE     100000
#define DEFAULT_SPLIT_BANK_SIZE       MAX_BUFFER_GLOBAL_SPACE / 4

uint16_t get_counter_value_memory_bank(unsigned long index);

void set_counter_value_memory_bank(unsigned long index, uint16_t value);

#endif //SOUNDPI_PFX_BANK_MEMORY_H
