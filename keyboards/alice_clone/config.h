/**
 * config.h
 */

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAC00
#define PRODUCT_ID      0x0060
#define DEVICE_VER      0x0001
#define MANUFACTURER    astro
#define PRODUCT         Alice Clone
#define DESCRIPTION     Alice clone according to the open source alice pcb

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { E6, F0, C7, B5, D3}
#define MATRIX_COL_PINS { F1, F4, F5, F6, F7, C6, B6, D2, D1, D0, B7, B3, B2, B1, B0 }
#define DIODE_DIRECTION COL2ROW
#define UNUSED_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define BACKLIGHT_PIN D5
#define BACKLIGHT_LEVELS 3

#define RGBLIGHT_LIMIT_VAL 128
#define RGBLED_NUM      20
#define RGB_DI_PIN      D4
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
