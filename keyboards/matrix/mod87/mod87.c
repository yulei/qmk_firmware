/**
 * mod87.c
 */

#include "mod87.h"


__attribute__((weak))
void matrix_scan_kb(void) { matrix_scan_user(); }

void matrix_init_kb(void) {
    palSetLineMode(LINE_CAPS_LOCK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LINE_SCROLL_LOCK, PAL_MODE_OUTPUT_PUSHPULL);
    matrix_init_user();
}

__attribute__((weak))
void matrix_init_user(void) {}

__attribute__((weak))
void matrix_scan_user(void) {}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            palSetLine(LINE_CAPS_LOCK);
        } else {
            palClearLine(LINE_CAPS_LOCK);
        }
        if (led_state.scroll_lock) {
            palSetLine(LINE_SCROLL_LOCK);
        } else {
            palClearLine(LINE_SCROLL_LOCK);
        }
    }
    return res;
}
