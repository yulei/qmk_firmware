/**
 * pjf.c
 */

#include "pjf.h"

void matrix_init_kb(void) {
    // caps lock
    setPinOutput(B6);
    // num lock
    setPinOutput(B5);
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(B6, led_state.num_lock);
        writePin(B5, led_state.caps_lock);
    }
    return res;
}
