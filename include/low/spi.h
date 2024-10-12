#ifndef SOUNDPI_PFX_SPI_H
#define SOUNDPI_PFX_SPI_H

#include "stdint.h"

void spi_init_pin(void);

uint8_t spi_read(uint8_t addr, uint8_t *data, size_t len);

uint8_t spi_write(uint8_t addr, uint8_t *data, size_t len);

#endif //SOUNDPI_PFX_SPI_H
