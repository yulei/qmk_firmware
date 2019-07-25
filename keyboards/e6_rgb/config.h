/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0xFEED
#define DEVICE_VER      0x0062
#define MANUFACTURER    astro
#define PRODUCT         e6rgb
#define DESCRIPTION     60% rgb keyboard
#define LANDING_PAGE    matrixzj.github.io/astro/30.json

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
/* key matrix pins */
#define MATRIX_ROW_PINS { F1, F4, F5, F6, D6 }
#define MATRIX_COL_PINS { D7, B4, B5, B6, C6, C7, F7, F0, B0, B1, D2, D3, B3, B2 }
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
#define RGBLED_NUM      6
#define RGB_DI_PIN      B7
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 63
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

// tapping setting
#define TAPPING_TERM    200
#define RETRO_TAPPING
#define PERMISSIVE_HOLD

// WEBUSB
#define DYNAMIC_KEYMAP_LAYER_COUNT 2
// EEPROM usage

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 32
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x08
#define EEPROM_VERSION_ADDR 34

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR 35
// Dynamic macro starts after dynamic keymaps (35+(4*10*6*2)) = (35+480)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 635
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 389    // 1024-DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#define DYNAMIC_KEYMAP_MACRO_COUNT 16
