#include QMK_KEYBOARD_H
#include "sendstring_swedish.h"

#define _____ KC_NO

enum keycodes {
    // Undead versions of dead keys
    UD_CIRC = SAFE_RANGE,
    UD_GRV,
    UD_TILD,
    // Macros
    MC_SCOP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
    SE_Q,    SE_W,    SE_F,    SE_P,    SE_B,    SE_J,    SE_L,     SE_U,    SE_Y,    _____,
    SE_A,    SE_R,    SE_S,    SE_T,    SE_G,    SE_M,    SE_N,     SE_E,    SE_I,    SE_O,
    SE_Z,    SE_X,    SE_C,    SE_D,    SE_V,    SE_K,    SE_H,     SE_COMM, SE_DOT,  SE_PLUS,
                               OSL(1),  KC_LSFT, KC_SPC,  OSL(2)
  ),
	[1] = LAYOUT_split_3x5_2(
    SE_PERC, SE_SLSH, SE_QUOT, SE_LBRC, SE_DLR,  UD_GRV,  SE_RBRC, SE_DQUO, SE_BSLS, UD_TILD,
    SE_ARNG, SE_MINS, SE_EQL,  SE_LPRN, SE_LABK, SE_RABK, SE_RPRN, SE_ADIA, SE_UNDS, SE_ODIA,
    SE_HASH, SE_ASTR, UD_CIRC, SE_LCBR, SE_AT,   MC_SCOP, SE_RCBR, SE_PIPE, SE_AMPR, SE_EXLM,
                               KC_TRNS, KC_TRNS, KC_TRNS, OSL(2)
  ),
	[2] = LAYOUT_split_3x5_2(
    _____,  SE_7,    SE_8,    SE_9,     _____,   KC_DOWN, KC_RGHT, KC_DEL,  KC_LGUI, _____,
    SE_0,   SE_1,    SE_2,    SE_3,     _____,   KC_TAB,  KC_ESC,  KC_BSPC, KC_LCTL, CW_TOGG,
    _____,  SE_4,    SE_5,    SE_6,     _____,   KC_UP,   KC_LEFT, KC_ENT,  KC_LALT, _____,
                              OSL(1),   KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case UD_CIRC:
        SEND_STRING("^");
        return false;
      case UD_GRV:
        SEND_STRING("`");
        return false;
      case UD_TILD:
        SEND_STRING("~");
        return false;
      case MC_SCOP:
        SEND_STRING("::");
        return false;
    }
  }
  return true;
};
