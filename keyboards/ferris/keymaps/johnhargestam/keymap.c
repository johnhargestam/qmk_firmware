#include QMK_KEYBOARD_H

#include "sendstring_swedish.h"
#include "oneshot.h"

#define _____ KC_NO
#define FN_CWIN A(KC_F4)
#define FN_TSKM C(S(KC_ESC))
#define FN_SDSK G(SE_D)
#define FN_CDSK G(C(KC_F4))
#define FN_ODSK G(C(SE_D))
#define FN_DSKL G(C(KC_LEFT))
#define FN_DSKR G(C(KC_RGHT))
#define FN_SNIP G(S(SE_S))
#define LA_SYM OSL(SYM)
#define LA_NUM OSL(NUM)
#define LA_FUN OSL(FUN)
#define LA_NAV OSL(NAV)

enum layers {
  DEF,
  SYM,
  NUM,
  FUN,
  NAV,
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
                               LA_FUN,  OS_SHFT, KC_SPC,  LA_SYM
  ),
	[SYM] = LAYOUT_split_3x5_2(
    SE_PERC, SE_SLSH, SE_QUOT, SE_LBRC, SE_DLR,  UD_GRV,  SE_RBRC, SE_DQUO, SE_BSLS, UD_TILD,
    SE_ARNG, SE_MINS, SE_EQL,  SE_LPRN, SE_LABK, SE_RABK, SE_RPRN, SE_ADIA, SE_UNDS, SE_ODIA,
    SE_HASH, SE_ASTR, UD_CIRC, SE_LCBR, SE_AT,   MC_SCOP, SE_RCBR, SE_PIPE, SE_AMPR, SE_EXLM,
                               LA_NUM,  KC_TRNS, KC_TRNS, LA_SYM
  ),
  [NUM] = LAYOUT_split_3x5_2(
    KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,   KC_F8,   KC_F10,  KC_F2,   KC_F4,   KC_F6,
    SE_7,    SE_5,    SE_3,    SE_1,    SE_9,    SE_8,    SE_0,    SE_2,    SE_4,    SE_6,
    SE_SLSH, SE_ASTR, SE_MINS, KC_F11,  SE_EQL,  UD_CIRC, KC_F12,  SE_COMM, SE_DOT,  SE_PLUS,
                               LA_NUM,  KC_TRNS, KC_TRNS, LA_SYM
  ),
	[FUN] = LAYOUT_split_3x5_2(
    KC_PSCR, KC_INS,  KC_TAB,  OS_CMD,  FN_CWIN, KC_DOWN, KC_RGHT, KC_DEL,  DM_REC1, DM_REC2,
    _____,   _____,   KC_ENT,  OS_CTRL, KC_HOME, KC_END,  KC_ESC,  KC_BSPC, DM_PLY1, DM_PLY2,
    KC_BRK,  CW_TOGG, QK_REP,  OS_ALT,  FN_TSKM, KC_UP,   KC_LEFT, QK_AREP, DM_RSTP, QK_RBT,
                               LA_FUN,  KC_TRNS, KC_TRNS, LA_NAV
  ),
  [NAV] = LAYOUT_split_3x5_2(
    KC_MUTE, KC_VOLD, KC_VOLU, _____,   KC_WH_D, KC_MS_D, KC_MS_R, FN_DSKR, FN_CDSK, KC_PGDN,
    FN_SDSK, _____,   KC_ACL1, KC_BTN1, KC_WH_L, KC_WH_R, KC_BTN2, KC_ACL0, KC_ACL2, FN_SNIP,
    KC_MPRV, KC_MNXT, KC_MPLY, KC_BTN3, KC_WH_U, KC_MS_U, KC_MS_L, FN_DSKL, FN_ODSK, KC_PGUP,
                               LA_FUN,  KC_TRNS, KC_TRNS, LA_NAV
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
