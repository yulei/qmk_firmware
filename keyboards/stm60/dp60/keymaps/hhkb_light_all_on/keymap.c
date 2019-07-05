#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_60_hhkb(
    KC_ESC,   RGBM_TOG, RGBM_MOD, RGBM_HUI, RGBM_HUD, RGBM_SAI, RGBM_SAD, RGBM_VAI, RGBM_VAD, KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_GRV,
    KC_TAB,   RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_BSPC,
    KC_LCTRL, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  MO(1),
              KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RGUI
  ),

  [1] = LAYOUT_60_hhkb(
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  KC_PSCR,
    KC_CAPS,  RGB_TOG,  RGB_MOD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UP,    _______,            KC_DEL,
    _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_LEFT,  KC_RGHT,                      _______,
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_END,   KC_PGDN,  KC_DOWN,            _______,  _______,
              _______,  _______,                                _______,                                _______,  _______
	),
};
