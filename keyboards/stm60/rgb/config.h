/**
 * config.h
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0xDEAD
#define DEVICE_VER      0x0002
#define MANUFACTURER    astro
#define PRODUCT         stm60
#define DESCRIPTION     60% rgb keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 6

/* key combination for magic key command */
#define IS_COMMAND() ( \
	keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

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
//#define RGB_DI_PIN A7
//#define RGBLED_NUM 18

#define WS2812_LED_N 18
#define RGBLED_NUM WS2812_LED_N
#define WS2812_TIM_N 3
#define WS2812_TIM_CH 1
#define PORT_WS2812 GPIOA
#define PIN_WS2812 7
#define WS2812_DMA_STREAM STM32_DMA1_STREAM5  // DMA stream for TIMx_UP (look up in reference manual under DMA Channel selection)
#define WS2812_DMA_CHANNEL 5                  // DMA channel for TIMx_UP

#define RGBLIGHT_ANIMATIONS

// i2c setting
#define USE_I2CV1
#define I2C1_SCL 8
#define I2C1_SDA 9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define PAL_MODE_STM32_ALTERNATE_OPENDRAIN (PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN)

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 63
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#endif
