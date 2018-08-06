/**
 * is31fl3733.h
 */

#pragma once
#include <stdint.h>

void is31fl3733_init(void);

void is31fl3733_set_sw_pull(uint8_t r);
void is31fl3733_set_cs_pull(uint8_t r);
void is31fl3733_set_global_current(uint8_t current);
void is31fl3733_all_on(void);
void is31fl3733_all_off(void);

void is31fl3733_set_brightness(uint8_t level);
void is31fl3733_set_color(uint8_t sw, uint8_t cs, uint8_t r, uint8_t g, uint8_t b);
