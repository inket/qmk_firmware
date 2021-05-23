 /* Copyright 2020 Hekeke
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

enum custom_keycodes {
    SPACE_INDENTATION = SAFE_RANGE,

    SAFE_SPACE,
    UNSTUCK_LALT,
    UNSTUCK_RALT,
};

bool disabled_lalt = false;
bool disabled_ralt = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SPACE_INDENTATION:
        if (record->event.pressed) {
            // when keycode SPACE_INDENTATION is pressed
            SEND_STRING("    "); // 4 spaces
        } else {
            // when keycode SPACE_INDENTATION is released
        }
        break;
    case SAFE_SPACE:
        if (record->event.pressed) {
            if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
              unregister_code(KC_LALT);
              disabled_lalt = true;
            }

            if (keyboard_report->mods & MOD_BIT(KC_RALT)) {
              unregister_code(KC_RALT);
              disabled_ralt = true;
            }

            register_code(KC_SPC);
        } else {
            unregister_code(KC_SPC);

            if (disabled_lalt) {
              register_code(KC_LALT);
              disabled_lalt = false;
            }

            if (disabled_ralt) {
              register_code(KC_RALT);
              disabled_ralt = false;
            }
        }
        break;
    case UNSTUCK_LALT:
        if (record->event.pressed) {
            register_code(KC_LALT);
        } else {
            // We don't want SAFE_SPACE to register LALT once it's done
            disabled_lalt = false;
            unregister_code(KC_LALT);
        }
        break;
    case UNSTUCK_RALT:
        if (record->event.pressed) {
            register_code(KC_RALT);
        } else {
            // We don't want SAFE_SPACE to register RALT once it's done
            disabled_ralt = false;
            unregister_code(KC_RALT);
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_65_iso(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, MO(1),
    LT(2,KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT, KC_PGUP,
    KC_LSFT, KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
    KC_LCTL, UNSTUCK_LALT, KC_LGUI, SAFE_SPACE, KC_RGUI, KC_NO, UNSTUCK_RALT, KC_LEFT, KC_DOWN, KC_RGHT
  ),

	[1] = LAYOUT_65_iso(
    KC_NUBS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RGB_TOG,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_PAUS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC__VOLUP, KC_SLCK,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD, KC__VOLDOWN, KC_MFFD
  ),

  [2] = LAYOUT_65_iso(
    KC_NUBS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RGB_TOG,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_PAUS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC__VOLUP, KC_SLCK,
    KC_TRNS, KC_TRNS, KC_TRNS, SPACE_INDENTATION, KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD, KC__VOLDOWN, KC_MFFD
  )
};
