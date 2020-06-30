/**
 * rgb_effects.h
 * an simple rgb led effect lib
 */

#pragma once

#include <stdint.h>

#ifndef EFFECTS_LED_NUM
#error "must defined the led num for rgb effects"
#endif

void rgb_effects_init(void);
void rgb_effects_inc_hue(void);
void rgb_effects_dec_hue(void);
void rgb_effects_inc_sat(void);
void rgb_effects_dec_sat(void);
void rgb_effects_inc_val(void);
void rgb_effects_dec_val(void);
void rgb_effects_inc_speed(void);
void rgb_effects_dec_speed(void);
void rgb_effects_inc_mode(void);
void rgb_effects_dec_mode(void);
void rgb_effects_toggle(void);
void rgb_effects_task(void);
