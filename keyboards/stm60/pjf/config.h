/**
 * config.h
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0x00FF
#define DEVICE_VER      0x0001
#define MANUFACTURER    astro
#define PRODUCT         pjf
#define DESCRIPTION     compact 1800 without F row

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { A0, A1, A3, A2, A4, A5}
#define MATRIX_COL_PINS { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 6

/* rgb light */
#define WS2812_LED_N    6
#define RGBLED_NUM      WS2812_LED_N

#define PORT_WS2812     GPIOA
#define PIN_WS2812      3
#define RGBLIGHT_ANIMATIONS

#endif
