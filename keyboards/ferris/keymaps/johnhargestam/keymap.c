#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_NO, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_MINS, OSL(1), KC_LSFT, KC_SPC, OSL(2)),
	[1] = LAYOUT_split_3x5_2(LSFT(KC_5), LSFT(KC_7), KC_NUHS, ALGR(KC_8), ALGR(KC_4), QK_MACRO_1, ALGR(KC_9), LSFT(KC_2), ALGR(KC_MINS), QK_MACRO_3, KC_LBRC, KC_SLSH, LSFT(KC_0), LSFT(KC_8), KC_NUBS, LSFT(KC_NUBS), LSFT(KC_9), KC_QUOT, LSFT(KC_SLSH), KC_SCLN, LSFT(KC_3), LSFT(KC_NUHS), QK_MACRO_2, ALGR(KC_7), ALGR(KC_2), QK_MACRO_0, ALGR(KC_0), ALGR(KC_NUBS), LSFT(KC_6), LSFT(KC_1), KC_TRNS, KC_TRNS, KC_TRNS, OSL(2)),
	[2] = LAYOUT_split_3x5_2(KC_NO, KC_7, KC_8, KC_9, KC_NO, KC_DOWN, KC_RGHT, KC_DEL, KC_LGUI, KC_NO, KC_0, KC_1, KC_2, KC_3, KC_NO, KC_TAB, KC_ESC, KC_BSPC, KC_LCTL, CW_TOGG, KC_NO, KC_4, KC_5, KC_6, KC_NO, KC_UP, KC_LEFT, KC_ENT, KC_LALT, KC_NO, OSL(1), KC_TRNS, KC_TRNS, KC_TRNS)
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
