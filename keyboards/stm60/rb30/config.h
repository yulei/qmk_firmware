/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x2019
#define PRODUCT_ID      0x30BE
#define DEVICE_VER      0x0001
#define MANUFACTURER    astro
#define PRODUCT         30rgbble
#define DESCRIPTION     30% rgb ble keyboard

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 11
/* key matrix pins */
#define MATRIX_ROW_PINS { F5, F6, D3}
#define MATRIX_COL_PINS { D5, D4, D6, D7, B4, B5, B6, C6, C7, F7, F4 }
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

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

//rgb light setting
#define RGBLED_NUM      14
#define RGB_DI_PIN      F0

//#define RGBLED_NUM      3
//#define RGB_DI_PIN      F1
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8



//rgb matrix setting
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110100 // this is here for compliancy reasons.
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 31
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

// tapping setting
//#define TAPPING_TERM    200
//#define RETRO_TAPPING
//#define PERMISSIVE_HOLD

// bluetooth setting
#define AdafruitBleResetPin E6
#define AdafruitBleCSPin    B0
#define AdafruitBleIRQPin   B7
