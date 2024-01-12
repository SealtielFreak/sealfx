#include "fx/daftpunk.h"

uint16_t dist_variable = 15;
uint16_t counter = 0;

uint16_t daftpunk(uint16_t signal) {
    if(counter >= dist_variable) {
        counter = 0;
        return signal;
    }

    counter++;

    return 0;
}