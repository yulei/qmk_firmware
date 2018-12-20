/**
 * config.h
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBEEF
#define PRODUCT_ID      0x9999
#define DEVICE_VER      0x0002
#define MANUFACTURER    astro
#define PRODUCT         stm60
#define DESCRIPTION     60% rgb keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
/* Note: These are not used for arm boards. They're here purely as documentation.
 * #define MATRIX_ROW_PINS { PB12, PB13, PB14, PB15, PC6, PC7, PC8, PC9}
 * #define MATRIX_COL_PINS { PB11, PB10, PB1, PB0, PC5, PC4, PA7, PA6, PA5}
 * #define UNUSED_PINS
 */

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 6

/* Prevent modifiers from being stuck on after layer changes. */
#define PREVENT_STUCK_MODIFIERS

/* backlight */
//#define BACKLIGHT_LEVELS 1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

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

#define WS2812_LED_N    18
#define RGBLED_NUM      WS2812_LED_N

#define PORT_WS2812     GPIOA
#define PIN_WS2812      7

#define RGBLIGHT_ANIMATIONS

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010000 // this is here for compliancy reasons.

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 63
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#endif
