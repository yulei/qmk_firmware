#include "wm1.h"
#include "rgb_leds.h"

void matrix_init_kb(void)
{
    matrix_init_user();
  //  rgb_init();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_user(uint8_t usb_led) {
}
/*
static bool rgb_on = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { 
        case KC_W:
            if (record->event.pressed) {
                rgb_on = !rgb_on;
                rgb_set_logo_state(rgb_on?LOGO_STATE_ON:LOGO_STATE_OFF);
            }
            return false;
        default:
            return true;
    }
}*/
