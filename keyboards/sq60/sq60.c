/**
 * @file sq60.c
 */

#include "sq60.h"

void matrix_init_kb(void) {
    setPinOutput(F4);
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(F4, led_state.caps_lock);
    }
    return res;
}
