/* Copyright 2019 funderburker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "hmo.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
    setPinOutput(E6);
    writePinLow(E6);

    setPinOutput(F1);
    writePinLow(F1);

	matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
		writePinLow(F1);
	} else {
		writePinHigh(F1);
	}

    led_set_user(usb_led);
}

uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 1, turn on B1 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinHigh(E6);
    } else {
        writePinLow(E6);
    }

    return state;
}
