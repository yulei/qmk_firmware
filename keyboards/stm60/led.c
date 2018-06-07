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
}

void backlight_set(uint8_t level) {
    printf("backlight_set(%d)\n", level);
    #ifdef BACKLIGHT_ENABLE
    if (level == 0) {
        // Turn backlight off
        palSetPad(GPIOA, 2);
    } else {
        // Turn backlight on
        palClearPad(GPIOA, 2);
    }
    #endif
}
