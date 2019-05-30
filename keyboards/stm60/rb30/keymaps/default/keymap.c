#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------.
     * |      Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|Bsp|
     * |-----------------------------------------------|
     * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L| Enter|
     * |-----------------------------------------------|
     * |Ctrl|  Z|  X|  C|  V|  B|  N|  M| Shift|
     * `-----------------------------------------------'
     */
    [0] = LAYOUT_default(
         KC_Q,    KC_W,   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,   KC_BSPC,
       KC_TAB, RGB_TOG,   RGB_MOD, KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,  KC_ENT,
      KC_LSFT,    KC_Z,   KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_RSFT)
};
