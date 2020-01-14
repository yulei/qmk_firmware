/**
 * @file ble_keybaord.h
 * @brief qmk integration
 */

#pragma once

//#include "ble_config.h"
#include <stdint.h>

void ble_keyboard_init(void);

void ble_keyboard_start(void);

void ble_keyboard_set_led(uint8_t led);
