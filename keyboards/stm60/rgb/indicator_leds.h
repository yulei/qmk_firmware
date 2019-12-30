/**
 * indicator_leds.h
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

void indicator_leds_init(void);
void indicator_leds_set(uint32_t index, bool on);
