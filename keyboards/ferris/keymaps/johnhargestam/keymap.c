#include QMK_KEYBOARD_H

#include "sendstring_swedish.h"
#include "oneshot.h"

#define _____ KC_NO
#define FN_NWIN A(KC_ESC)
#define FN_AWIN A(KC_TAB)
#define FN_PWIN S(A(KC_ESC))
#define LA_SYM OSL(SYM)
#define LA_FUN OSL(FUN)

enum layers {
  DEF,
  SYM,
  FUN,
};

enum keycodes {
  // Undead versions of dead keys
  UD_CIRC = SAFE_RANGE,
  UD_GRV,
  UD_TILD,

  // Macros
  MC_SCOP,

  // oneshot mods.
  OS_SHFT,
  OS_CTRL,
  OS_ALT,
  OS_CMD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DEF] = LAYOUT_split_3x5_2(
    SE_Q,    SE_W,    SE_F,    SE_P,    SE_B,    SE_J,    SE_L,    SE_U,    SE_Y,    _____,
    SE_A,    SE_R,    SE_S,    SE_T,    SE_G,    SE_M,    SE_N,    SE_E,    SE_I,    SE_O,
    SE_Z,    SE_X,    SE_C,    SE_D,    SE_V,    SE_K,    SE_H,    SE_COMM, SE_DOT,  SE_PLUS,
                               LA_SYM,  OS_SHFT, KC_SPC,  LA_FUN
  ),
	[SYM] = LAYOUT_split_3x5_2(
    SE_PERC, SE_SLSH, SE_QUOT, SE_LBRC, SE_DLR,  UD_GRV,  SE_RBRC, SE_DQUO, SE_BSLS, UD_TILD,
    SE_ARNG, SE_MINS, SE_EQL,  SE_LPRN, SE_LABK, SE_RABK, SE_RPRN, SE_ADIA, SE_UNDS, SE_ODIA,
    SE_HASH, SE_ASTR, UD_CIRC, SE_LCBR, SE_AT,   MC_SCOP, SE_RCBR, SE_PIPE, SE_AMPR, SE_EXLM,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
	[FUN] = LAYOUT_split_3x5_2(
    _____,   SE_7,    SE_8,    SE_9,    FN_NWIN, KC_DOWN, KC_RGHT, KC_DEL,  OS_CMD,  _____,
    SE_0,    SE_1,    SE_2,    SE_3,    FN_AWIN, KC_TAB,  KC_ESC,  KC_BSPC, OS_CTRL, CW_TOGG,
    _____,   SE_4,    SE_5,    SE_6,    FN_PWIN, KC_UP,   KC_LEFT, KC_ENT,  OS_ALT,  _____,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
    case KC_SPC:
      return true;
    default:
      return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_FUN:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  update_oneshot(
    &os_shft_state, KC_LSFT, OS_SHFT,
    keycode, record
  );
  update_oneshot(
    &os_ctrl_state, KC_LCTL, OS_CTRL,
    keycode, record
  );
  update_oneshot(
    &os_alt_state, KC_LALT, OS_ALT,
    keycode, record
  );
  update_oneshot(
    &os_cmd_state, KC_LCMD, OS_CMD,
    keycode, record
  );

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
