/*
Copyright 2021 weteor

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#ifdef POINTING_DEVICE_ENABLE
#include <stdlib.h>
#endif

enum layers
{
    _HALMAK,
    _LOWER,
    _RAISE,
    _SUPER,
    _FUNCTION
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_DOUBLE,
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_ALT_WIN,
    L1_SHFT,
    L2_CTRL,
};

td_state_t cur_dance(tap_dance_state_t *state);

void l1_finished(tap_dance_state_t *state, void *user_data);
void l1_reset(tap_dance_state_t *state, void *user_data);
void l2_finished(tap_dance_state_t *state, void *user_data);
void l2_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    [L1_SHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l1_finished, l1_reset),
    [L2_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l2_finished, l2_reset),
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        return TD_SINGLE_HOLD;
    } else {
        return TD_DOUBLE;
    }

    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'l1' tap dance.
static td_tap_t l1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Create an instance of 'td_tap_t' for the 'l2' tap dance.
static td_tap_t l2_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void l1_finished(tap_dance_state_t *state, void *user_data) {
    l1_tap_state.state = cur_dance(state);
    switch (l1_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(1);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: register_code(KC_LSFT); break;
        default: break;
    }
}

void l1_reset(tap_dance_state_t *state, void *user_data) {
    switch (l1_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(1);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: unregister_code(KC_LSFT); break;
        default: break;
    }
    l1_tap_state.state = TD_NONE;
}

void l2_finished(tap_dance_state_t *state, void *user_data) {
    l2_tap_state.state = cur_dance(state);
    switch (l2_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(2);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: register_code(KC_LCTL); break;
        default: break;
    }
}

void l2_reset(tap_dance_state_t *state, void *user_data) {
    switch (l2_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(2);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: unregister_code(KC_LCTL); break;
        default: break;
    }
    l2_tap_state.state = TD_NONE;
}

#define LTF LT(_FUNCTION, KC_F)
#define TD1 TD(TD_ALT_WIN)
#define TD2 TD(L1_SHFT)
#define LCT_SPC LCTL_T(KC_SPC)
#define LST_ENT LSFT_T(KC_ENT)
#define TD3 TD(L2_CTRL)
#define KC_NUTL S(KC_NUHS)
#define KC_NUPI S(KC_NUBS)
#define KC_NUAT S(KC_QUOT)
#define KC_TASK C(S(KC_ESC))
#define KC_CAD C(A(KC_DEL))
#define AT_BCK A(S(KC_TAB))
#define AT_FWD A(KC_TAB)
#define TAB_BCK C(S(KC_TAB))
#define TAB_FWD C(KC_TAB)
#define DSK_LFT C(G(KC_LEFT))
#define DSK_RGT C(G(KC_RIGHT))
#define KC_EURO RALT(KC_4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
     * │ W │ L │ R │ B │ Z │       │ ; │ Q │ U │ D │ J │
     * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
     * │ S │ H │ N │ T │ , │       │ . │ A │ E │ O │ I │
     * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
     * │ F │ M │ V │ C │ / │       │ G │ P │ X │ K │ Y │
     * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
     *           ┌───┐
     *           │ALT├───┐           ┌───┐
     *           └───┤LOW├───┐   ┌───┤RSE│
     *               └───│SPC│   │ENT├───┘
     *                   └───┘   └───┘
     */


    [_HALMAK] = LAYOUT(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
            KC_W,    KC_L,    KC_R,    KC_B,    KC_Z,    KC_SCLN,    KC_Q,    KC_U,    KC_D,    KC_J,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
            KC_S,    KC_H,    KC_N,    KC_T, KC_COMM,     KC_DOT,    KC_A,    KC_E,    KC_O,    KC_I,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
             LTF,    KC_M,    KC_V,    KC_C, KC_SLSH,       KC_G,    KC_P,    KC_X,    KC_K,    KC_Y,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                               TD1,     TD2, LCT_SPC,    LST_ENT,     TD3
    //                   ╰───────────────────────────╯ ╰──────────────────╯
    ),

    [_LOWER] = LAYOUT(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    S(KC_6), S(KC_7), S(KC_8), KC_QUOT, KC_BSPC,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_GRV, KC_NUBS, KC_MINS,  KC_EQL, KC_NUHS,    KC_NUTL, KC_PLUS, KC_UNDS, KC_NUPI,  KC_DEL,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                           KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    //                   ╰───────────────────────────╯ ╰──────────────────╯
    ),

    [_RAISE] = LAYOUT(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_ESC, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,    KC_QUOT,   KC_UP, KC_NUAT, KC_HOME, KC_PGUP,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_TAB, XXXXXXX, KC_LPRN, KC_RPRN, KC_EURO,    KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END, KC_PGDN,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                           KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    //                   ╰───────────────────────────╯ ╰──────────────────╯
    ),

    [_SUPER] = LAYOUT(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_TASK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX,  KC_CAD,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         XXXXXXX, XXXXXXX,  AT_BCK,  AT_FWD, XXXXXXX,    XXXXXXX, DSK_LFT, DSK_RGT, XXXXXXX, XXXXXXX,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         XXXXXXX, XXXXXXX, TAB_BCK, TAB_FWD, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                           KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    //                   ╰───────────────────────────╯ ╰──────────────────╯
    ),

    [_FUNCTION] = LAYOUT(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN3, XXXXXXX,      KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_BTN4,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2,      KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_BTN5,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                           KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS
    //                   ╰───────────────────────────╯ ╰──────────────────╯
    ),
};

#define DEFAULT_DPI 400
#define FOCUS_DPI 200
#define DRAGSCROLL_DPI 80
#define DRAGSCROLL_BUFFER_SIZE 6

static bool set_scrolling = false;
static uint8_t current_layer = _HALMAK;
/** 
 * \brief reduce dpi when in certain layers
 *
 * Less DPI when dragscrolling and in the function layer
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    current_layer = get_highest_layer(state);
    switch (current_layer) {
        case _LOWER:
            set_scrolling = true;
            pointing_device_set_cpi(DRAGSCROLL_DPI);
            break;
        case _FUNCTION:
            set_scrolling = false;
            pointing_device_set_cpi(FOCUS_DPI);
            break;
        default:
            pointing_device_set_cpi(DEFAULT_DPI);
            set_scrolling = false;
    }

    return state;
}

/**
 * \brief Augment the pointing device behavior.
 *
 * Implement drag-scroll.
 */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;

    switch (current_layer) {
        case _LOWER:
            pointing_device_set_cpi(DRAGSCROLL_DPI);
            break;
        case _FUNCTION:
            pointing_device_set_cpi(FOCUS_DPI);
            break;
        default:
            pointing_device_set_cpi(DEFAULT_DPI);
    }

    if (set_scrolling) {
        scroll_buffer_x += mouse_report.x;
        scroll_buffer_y -= mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
        if (abs(scroll_buffer_x) > DRAGSCROLL_BUFFER_SIZE) {
            mouse_report.h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > DRAGSCROLL_BUFFER_SIZE) {
            mouse_report.v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }

    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *recort) {
    switch (current_layer) {
        case _LOWER:
            pointing_device_set_cpi(DRAGSCROLL_DPI);
            break;
        case _FUNCTION:
            pointing_device_set_cpi(FOCUS_DPI);
            break;
        default:
            pointing_device_set_cpi(DEFAULT_DPI);
    }

    return true;
}
void keyboard_post_init_kb(void) {
    pointing_device_set_cpi(DEFAULT_DPI);
    keyboard_post_init_user();
}
