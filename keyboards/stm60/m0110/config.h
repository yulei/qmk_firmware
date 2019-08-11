/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0x0110
#define DEVICE_VER      0x6000
#define MANUFACTURER    astro
#define PRODUCT         m0110
#define DESCRIPTION     60% keyboard for m0110
#define LANDING_PAGE    yulei.github.io/qmk_webusb_tool/60_wkl_bs.json

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
/* key matrix pins */
#define MATRIX_ROW_PINS { F0, F1, F4, F5, D3}
#define MATRIX_COL_PINS { D4, D6, B5, B6, C6, C7, F7, F6, E6, B0, B7, D5, B3, B2, B1}
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5
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
#define RGBLED_NUM      4
#define RGB_DI_PIN      B4
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8


#define BACKLIGHT_PIN D2
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 4
#endif

// tapping setting
//#define TAPPING_TERM    200
//#define RETRO_TAPPING
//#define PERMISSIVE_HOLD


#ifdef WEBUSB_ENABLE
#define WEBUSB_KEYCOUNT  62
#define WEBUSB_LAYERCOUNT 2
#endif

#ifdef DYNAMIC_KEYMAP_ENABLE
//VIA
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
#endif
