/**
 * @file ws2812_nrf.h
 */

#pragma once

#include <stdint.h>
#include "color.h"

void ws2812_init(void);
void ws2812_setleds(LED_TYPE* leds, uint16_t number);
