/**
 * config.h
 *
 */

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID  0x4D58   // MX
#define PRODUCT_ID 0x0087   // mod 87
#define DEVICE_VER 0x0001
#define MANUFACTURER matrix
#define PRODUCT NOAH
#define DESCRIPTION 65% keybaord of the Matrix abel family

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5

#define RGB_DI_PIN B2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 4
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif

