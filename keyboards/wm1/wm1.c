#include "wm1.h"
#include "rgb_leds.h"

void matrix_init_kb(void)
{
    matrix_init_user();
    rgb_init();
}

void matrix_scan_kb(void)
{
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_user(uint8_t usb_led) {
}
