#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
    SE_Q,    SE_W,    SE_F,       SE_P,    SE_B,    SE_J,       SE_L,    SE_U,    SE_Y,    KC_NO,
    SE_A,    SE_R,    SE_S,       SE_T,    SE_G,    SE_M,       SE_N,    SE_E,    SE_I,    SE_O,
    SE_Z,    SE_X,    SE_C,       SE_D,    SE_V,    SE_K,       SE_H,    SE_COMM, SE_DOT,  SE_PLUS,
                                  OSL(1),  KC_LSFT, KC_SPC,     OSL(2)
  ),
	[1] = LAYOUT_split_3x5_2(
    SE_PERC, SE_SLSH, SE_QUOT,    SE_LBRC, SE_DLR,  QK_MACRO_1, SE_RBRC, SE_DQUO, SE_BSLS, QK_MACRO_3,
    SE_ARNG, SE_MINS, SE_EQL,     SE_LPRN, SE_LABK, SE_RABK,    SE_RPRN, SE_ADIA, SE_UNDS, SE_ODIA,
    SE_HASH, SE_ASTR, QK_MACRO_2, SE_LCBR, SE_AT,   QK_MACRO_0, SE_RCBR, SE_PIPE, SE_AMPR, SE_EXLM,
                                  KC_TRNS, KC_TRNS, KC_TRNS,    OSL(2)
  ),
	[2] = LAYOUT_split_3x5_2(
    KC_NO,   SE_7,    SE_8,       SE_9,    KC_NO,   KC_DOWN,    KC_RGHT, KC_DEL,  KC_LGUI, KC_NO,
    SE_0,    SE_1,    SE_2,       SE_3,    KC_NO,   KC_TAB,     KC_ESC,  KC_BSPC, KC_LCTL, CW_TOGG,
    KC_NO,   SE_4,    SE_5,       SE_6,    KC_NO,   KC_UP,      KC_LEFT, KC_ENT,  KC_LALT, KC_NO,
                                  OSL(1),  KC_TRNS, KC_TRNS,    KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case QK_MACRO_0:
        SEND_STRING(SS_DOWN(X_LSFT)".."SS_UP(X_LSFT));
        return false;
      case QK_MACRO_1:
        SEND_STRING(SS_DOWN(X_LSFT)"="SS_UP(X_LSFT)" ");
        return false;
      case QK_MACRO_2:
        SEND_STRING(SS_DOWN(X_LSFT)"]"SS_UP(X_LSFT)" ");
        return false;
      case QK_MACRO_3:
        SEND_STRING(SS_DOWN(X_RALT)"]"SS_UP(X_RALT)" ");
        return false;
    }
  }
  return true;
};
