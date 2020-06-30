/**
 * rgb_effects.h
 * an simple rgb led effect lib
 */

#pragma once

#include <stdint.h>

#ifndef RGB_EFFECTS_LED_NUM
#error "must defined the led num for rgb effects"
#endif

void rgb_effects_init(void);
void rgb_effects_set_hue(uint8_t hue);
void rgb_effects_set_sat(uint8_t sat);
void rgb_effects_set_val(uint8_t val);
void rgb_effects_set_speed(uint8_t speed);
void rgb_effects_step_mode(void);
void rgb_effects_task(void);
