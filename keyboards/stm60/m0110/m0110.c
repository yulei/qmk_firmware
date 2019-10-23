/**
 * m0110.c
 */

#include QMK_KEYBOARD_H

#ifdef WEBUSB_ENABLE
#include "webusb.h"
#include "dynamic_keymap.h"

webusb_pos_t webusb_keymap[] = {
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14},

    {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},         {1, 8}, {1, 9}, {1, 10}, {1, 11}, {1, 12}, {1, 13}, {1, 14},

    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},         {2, 8}, {2, 9}, {2, 10}, {2, 11}, {2, 12},          {2, 14},

    {3, 0},         {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11},          {3, 13}, {3, 14},

    {4, 0}, {4, 1}, {4, 2},                         {4, 6},                                  {4, 11},          {4, 13}, {4, 14},
};
#endif

void matrix_init_user(void)
{
    setPinOutput(D7);
    setPinOutput(D2);
	writePinHigh(D2);
}

void led_set_user(uint8_t usb_led) {
	if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
		writePinHigh(D7);
	} else {
		writePinLow(D7);
	}
}
