 /* copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include "oled.c"

enum layers
{
    _HALMAK = 0,
    _LOWER,
    _UPPER,
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_HALMAK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),           ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_LOWER] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),           ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [_UPPER] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),           ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * HALMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   W  |   L  |   R  |   B  |   Z  |                    |   ;  |   Q  |   U  |   D  |   J  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   S  |   H  |   N  |   T  |   ,  |-------.    ,-------|   .  |   A  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |       |------+------+------+------+------+------|
 * |LShift|   F  |   M  |   V  |   C  |   /  |-------|    |-------|   G  |   P  |   X  |   K  |   Y  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_HALMAK] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,       KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_W,   KC_L,    KC_R,    KC_B,    KC_Z,                            KC_SCLN,    KC_Q,    KC_U,    KC_D,    KC_J,  KC_BSPC,
  KC_TAB,   KC_S,   KC_H,    KC_N,    KC_T,    KC_COMM,                         KC_DOT,     KC_A,    KC_E,    KC_O,    KC_I,  KC_QUOT,
  KC_LSFT,  KC_F,   KC_M,    KC_V,    KC_C,    KC_SLSH,    KC_MUTE,     XXXXXXX,KC_G,       KC_P,    KC_X,    KC_K,    KC_Y,  KC_RSFT,
                 KC_LGUI,    KC_LALT, KC_LCTL, MO(_LOWER), KC_SPC,      KC_ENT, MO(_UPPER), KC_RCTL, KC_RALT, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
    _______,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    _______,KC_GRV, KC_NUBS,KC_MINS,KC_EQL, KC_NUHS,_______,        _______,S(KC_NUHS),S(KC_EQL),S(KC_MINS),S(KC_NUBS), S(KC_GRV), _______,
                    _______,_______,_______,_______,_______,        _______,_______, _______, _______, _______
),
/* UPPER
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |      |      |   [  |   ]  |      |                    |      |  up  |      | Home | PgUp | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |      |   (  |   )  |      |-------.    ,-------| Left | Down | Right|  End | PgDn | Bspc |
 * |------+------+------+------+------+------|        |   |       |------+------+------+------+------+------|
 * |Shift |      |      |   {  |   }  |      |--------|   |-------|      |      |      |      |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_UPPER] = LAYOUT(
  KC_NO,    KC_NO,  KC_NO,      KC_NO,      KC_NO,      KC_PSCR,                           KC_PSCR,  KC_NO, KC_NO,  KC_NO ,  KC_NO ,C(A(KC_DEL)),
  _______,  KC_NO,  KC_NO,      KC_LBRC,    KC_RBRC,    KC_NO,                        KC_QUOT, KC_UP,S(KC_QUOT), KC_HOME,KC_PGUP, KC_BSPC,
  _______,  KC_NO,  KC_NO,      S(KC_9),    S(KC_0),    KC_NO,                       KC_LEFT,  KC_DOWN, KC_RIGHT, KC_END,  KC_PGDN, KC_BSPC,
  _______,  KC_NO,  KC_NO,      S(KC_LBRC), S(KC_RBRC), KC_NO,      KC_NO,       KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO,
                    _______,    _______,    _______,    _______,    _______,       _______, _______, _______, _______, _______
)
};
