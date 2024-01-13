#include "interface/screen.h"

#include "hardware/i2c.h"

#define MASK_RS 0x01
#define MASK_RW 0x02
#define MASK_E  0x04

#define SHIFT_BACKLIGHT 3
#define SHIFT_DATA      4

#define I2C_PORT        i2c0
#define I2C_ADDRESS     0x3C


#define LCD_CLR 0x01
#define LCD_HOME 0x02

#define LCD_ENTRY_MODE 0x04
#define LCD_ENTRY_INC 0x02
#define LCD_ENTRY_SHIFT 0x01

#define LCD_ON_CTRL 0x08
#define LCD_ON_DISPLAY 0x04
#define LCD_ON_CURSOR 0x02
#define LCD_ON_BLINK 0x01

#define LCD_MOVE 0x10
#define LCD_MOVE_DISP 0x08
#define LCD_MOVE_RIGHT 0x04

#define LCD_FUNCTION 0x20
#define LCD_FUNCTION_8BIT 0x10
#define LCD_FUNCTION_2LINES 0x08
#define LCD_FUNCTION_10DOTS 0x04
#define LCD_FUNCTION_RESET 0x30

#define LCD_CGRAM 0x40
#define LCD_DDRAM 0x80

#define LCD_RS_CMD 0
#define LCD_RS_DATA 1

#define LCD_RW_WRITE 0
#define LCD_RW_READ 1

static uint8_t backlight = 0;

void write_blocking_data(uint8_t data) {
    uint8_t src1[] = {data};
    i2c_write_blocking(I2C_PORT, I2C_ADDRESS, src1, 1, false);
}

void hal_write_command(uint8_t cmd) {

}

void hal_write_data(uint8_t data) {
    uint8_t byte = (MASK_RS |
            (backlight << SHIFT_BACKLIGHT) |
            (((data >> 4) & 0x0f) << SHIFT_DATA));

    write_blocking_data(byte | MASK_E);
    write_blocking_data(byte);

    byte = (MASK_RS | (backlight << SHIFT_BACKLIGHT) | ((data & 0x0f) << SHIFT_DATA));

    write_blocking_data(byte | MASK_E);
    write_blocking_data(byte);
}

void screen_clear(void) {

}

void show_cursor(void) {

}

void hide_cursor(void) {

}

void putchr(char chr) {
    if(chr == '\n') {

    } else {
        hal_write_data(chr);
    }
}

void putstr(const char* str) {

}
