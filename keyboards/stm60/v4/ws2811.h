/**
 * ws2811.h
 * spi driver for ws2811
 */

#pragma once

#include <stdint.h>

void ws2811_init(void);
void ws2811_write_led(uint32_t index, uint8_t r, uint8_t g, uint8_t b);
void ws2811_transfer(void);
