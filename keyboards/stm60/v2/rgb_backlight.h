/**
 * rgb_backlight.h
 *
 */

#pragma once

#include <stdint.h>

int rb_init(void);
int rb_turn_on(void);
int rb_turn_off(void);
int rb_set_color(uint32_t col, uint32_t row, uint8_t r, uint8_t g, uint8_t b);
