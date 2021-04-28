//
// Created by alast on 28/04/2021.
//

#ifndef SMARTCUPCOASTER_COLOR_H
#define SMARTCUPCOASTER_COLOR_H


#include <stdint-gcc.h>

class Color {
private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
public:
    Color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t result();
};


#endif //SMARTCUPCOASTER_COLOR_H
