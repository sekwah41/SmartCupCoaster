//
// Created by alast on 28/04/2021.
//

#include "Color.h"

/**
 *
 * @param r red intensity 0-255
 * @param g green intensity 0-255
 * @param b blue intensity 0-255
 */
Color::Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {
}

uint32_t Color::result() {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
