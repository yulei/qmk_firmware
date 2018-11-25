/**
 * rgb_backlight.h
 *
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct  _color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color;

typedef struct _rgb_config
{
    bool on;            // turn light on or off
    uint8_t cur_col;    // current column number
} rgb_config;

void rb_init(void);
void rb_set_state(bool on);
void rb_update(void);
