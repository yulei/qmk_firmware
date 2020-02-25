/**
 * config.h
 *
 */
#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x60BE
#define PRODUCT_ID      0x00BE
#define DEVICE_VER      0x0001
#define MANUFACTURER    astro
#define PRODUCT         NRFBLE
#define DESCRIPTION     60% BLE keyboard

/* key matrix size */
#ifndef MATRIX_ROWS
  #define MATRIX_ROWS 5
#endif

#ifndef MATRIX_COLS
  #define MATRIX_COLS 14
#endif
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS { 3,  2, 31, 30, 29}
#define MATRIX_COL_PINS { 4,  5,  6,  7,  8, 9, 10, 11, 12, 13, 14, 15, 16, 17}
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE_DELAY 5

#define RGBLED_NUM 18
#define WS2812_RGB_PIN      20
#define WS2812_EN_PIN       22
#define RGBLIGHT_ANIMATIONS

#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
