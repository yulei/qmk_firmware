/*
 * alice_clone.c
 */
#include "alice_clone.h"

void keyboard_pre_init_kb(void) {
    led_init_ports();
    keyboard_pre_init_user();
}

void led_init_ports(void) {
    setPinOutput(D7);
    setPinOutput(B4);
    setPinOutput(D6);
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(D7, led_state.num_lock);
        writePin(B4, led_state.caps_lock);
        writePin(D6, led_state.scroll_lock);
    }
    return true;
}
