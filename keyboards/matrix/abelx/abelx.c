/**
 * abelx.c
 */

#include "abelx.h"

void matrix_init_kb(void) {
    // caps lock
    setPinOutput(B5);
    // scroll lock
    setPinOutput(B6);
    matrix_init_user();
}

void matrix_init_user(void){}
void matrix_scan_user(void){}
void matrix_scan_kb(void){matrix_scan_user();}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(B5, led_state.caps_lock);
        writePin(B6, led_state.scroll_lock);
    }
    return res;
}
