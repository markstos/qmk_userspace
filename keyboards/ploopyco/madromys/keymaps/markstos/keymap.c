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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
                  // Middle, Copy, Paste, Scroll
    [0] = LAYOUT( MS_BTN3, TD(TD_COPY_BTN4), TD(TD_PASTE_BTN5), DRAG_SCROLL,
                  // Left                        Right
                  MS_BTN1,                       MS_BTN2 )
};

// Double Tap (< 200ms) copy for browser-back
// Double Tap (< 200ms) paste for browser-forward
tap_dance_action_t tap_dance_actions[] = {
    [TD_COPY_BTN4]  = ACTION_TAP_DANCE_DOUBLE(C(KC_INSERT), MS_BTN4),
    [TD_PASTE_BTN5] = ACTION_TAP_DANCE_DOUBLE(S(KC_INSERT), MS_BTN5),
};
