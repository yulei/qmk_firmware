/**
 * config.h
 *
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0x6583
#define DEVICE_VER      0x6000
#define MANUFACTURER    astro
#define PRODUCT         smk 60
#define DESCRIPTION     60% keyboard for smk switch
#define LANDING_PAGE    yulei.github.io/qmk_webusb_tool/60_wkl_bs.json

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
/* key matrix pins */
#define MATRIX_ROW_PINS { B0, F0, F1, F5, B2 }
#define MATRIX_COL_PINS { B4, B5, B6, C6, C7, F6, F7, F4, B1, B3, D0, D1, D2, D3, D5}
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
#define RGB_DI_PIN      E6
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8



// tapping setting
#define TAPPING_TERM    200
#define RETRO_TAPPING
#define PERMISSIVE_HOLD


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
