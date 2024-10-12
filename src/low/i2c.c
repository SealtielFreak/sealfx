#include "low/i2c.h"

#include <pico/stdlib.h>

#include "hardware/i2c.h"

#define I2C_PORT        i2c0
#define I2C_ADDRESS     0x3C

void init_i2c_communication(void) {
    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);

    gpio_pull_up(4);
    gpio_pull_up(5);
}
