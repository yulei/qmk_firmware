/**
 * config.h
 *
 */

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x60BB
#define PRODUCT_ID      0x00BB
#define DEVICE_VER      0x0001
#define MANUFACTURER    astro
#define PRODUCT         NRFUSB
#define DESCRIPTION     USB controller for NRFBLE

/* key matrix size */
#ifndef MATRIX_ROWS
  #define MATRIX_ROWS 5
#endif

#ifndef MATRIX_COLS
  #define MATRIX_COLS 14
#endif
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
//#define MATRIX_ROW_PINS { 3,  2, 31, 30, 29}
//#define MATRIX_COL_PINS { 4,  5,  6,  7,  8, 9, 10, 11, 12, 13, 14, 15, 16, 17}
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE_DELAY 5
