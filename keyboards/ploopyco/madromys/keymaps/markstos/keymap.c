/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

enum tap_dance_actions {
    TD_COPY_BTN4,
    TD_PASTE_BTN5,
};

typedef enum {
    TD_NONE,
    TD_COPY,
    TD_SPACE,
    TD_BTN4,
} td_copy_state_t;

static td_copy_state_t copy_tap_state = TD_NONE;

void copy_each_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        copy_tap_state = TD_BTN4;
        register_code16(MS_BTN4);
        state->finished = true;
    }
}

void copy_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            copy_tap_state = TD_SPACE;
            register_code16(KC_SPACE);
        } else {
            copy_tap_state = TD_COPY;
            register_code16(KC_COPY);
        }
    }
}

void copy_reset(tap_dance_state_t *state, void *user_data) {
    switch (copy_tap_state) {
        case TD_SPACE:
            unregister_code16(KC_SPACE);
            break;
        case TD_COPY:
            wait_ms(TAP_CODE_DELAY);
            unregister_code16(KC_COPY);
            break;
        case TD_BTN4:
            unregister_code16(MS_BTN4);
            break;
        default:
            break;
    }
    copy_tap_state = TD_NONE;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
                  // Middle, Copy, Paste, Scroll
    [0] = LAYOUT( MS_BTN3, TD(TD_COPY_BTN4), TD(TD_PASTE_BTN5), DRAG_SCROLL,
                  // Left                        Right
                  MS_BTN1,                       MS_BTN2 )
};

// Tap for Copy, Double Tap (< 500ms) for browser-back, Hold (> 500ms) for Space
// Tap for Paste, Double Tap (< 500ms) for browser-forward
tap_dance_action_t tap_dance_actions[] = {
    [TD_COPY_BTN4]  = ACTION_TAP_DANCE_FN_ADVANCED(copy_each_tap, copy_finished, copy_reset),
    [TD_PASTE_BTN5] = ACTION_TAP_DANCE_DOUBLE(KC_PASTE, MS_BTN5),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_COPY_BTN4):
        case TD(TD_PASTE_BTN5):
            return 500;
        default:
            return TAPPING_TERM;
    }
}

