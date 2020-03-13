/**
 * config.h
 *
 */
#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID  0x4D58   // MX
#define PRODUCT_ID 0xBE65   // noah 65
#define DEVICE_VER 0x0001
#define MANUFACTURER astro
#define PRODUCT NOAHBLE
#define DESCRIPTION 65% keybaord with BLE support

/* key matrix size */
#ifndef MATRIX_ROWS
  #define MATRIX_ROWS 5
#endif

#ifndef MATRIX_COLS
  #define MATRIX_COLS 15
#endif
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS { 3,  2, 27, 26, 25}
#define MATRIX_COL_PINS { 4,  5,  6,  7,  8,  9, 16, 15, 14, 13, 12, 11, 24, 23, 22}
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE        5

#define USB_SENSE_PIN   31
#define UART_RX_PIN     20
#define UART_TX_PIN     19
#define BATTERY_SAADC_ENABLE_PIN    29
#define BATTERY_SAADC_PIN           NRF_SAADC_INPUT_AIN6

#define RGBLED_NUM 7
#define WS2812_RGB_PIN      10
#define WS2812_EN_PIN       28
#define RGBLIGHT_ANIMATIONS

#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
