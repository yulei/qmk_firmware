/**
 * led.c
 *
 */

#include "hal.h"
#include "backlight.h"
#include "led.h"
#include "printf.h"

void backlight_init_ports(void) {
    printf("backlight_init_ports()\n");
    #ifdef BACKLIGHT_ENABLE
    palSetPadMode(GPIOA, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOA, 2);
    #endif
    palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOB, 13);
}

void backlight_set(uint8_t level) {
    printf("backlight_set(%d)\n", level);
    #ifdef BACKLIGHT_ENABLE
    if (level == 0) {
        // Turn backlight off
        palClearPad(GPIOA, 2);
        palClearPad(GPIOB, 13);
    } else {
        // Turn backlight on
        palSetPad(GPIOA, 2);
        palClearPad(GPIOB, 13);
    }
    #endif
}


void led_set_kb(uint8_t usb_led) {
    printf("led_set_kb(%d)\n", usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        palSetPad(GPIOB, 14);
    } else {
        // Turn capslock off
        palClearPad(GPIOB, 14);
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
      palSetPad(GPIOB, 15);
    } else {
      palClearPad(GPIOB, 15);
    }
}
