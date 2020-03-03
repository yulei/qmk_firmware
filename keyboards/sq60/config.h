/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5351      //'SQ'
#define PRODUCT_ID      0x0060
#define DEVICE_VER      0x0001
#define MANUFACTURER    INETT STUDIO
#define PRODUCT         SQ60
#define DESCRIPTION     60% keyboard of the SQ family

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define MATRIX_ROW_PINS { E6, F7, F5, F1, F0 }
#define MATRIX_COL_PINS { B0, C7, C6, B6, B5, B4, D7, D6, D5, D4, D3, D2, D1, D0 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

// backlight setting
#define BACKLIGHT_PIN       B7
#define BACKLIGHT_LEVELS    5

//rgb light setting
#define RGBLED_NUM          26
#define RGB_DI_PIN          F6
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP   8
#define RGBLIGHT_SAT_STEP   8
#define RGBLIGHT_VAL_STEP   8

#if defined(VIA_ENABLE)
#   define DYNAMIC_KEYMAP_LAYER_COUNT 2
#endif
