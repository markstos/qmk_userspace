/*
Copyright 2022 aki27

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
#include <stdio.h>
#include "quantum.h"

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC,
};

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _QWERTY = 0,
    _LOWER = 1,
    _RAISE = 2,
    _FUNC = 3,
};

enum combos {
  THREE_FOUR_DASH,
  DF_DASH,
  JK_ESC
};

const uint16_t PROGMEM three_four_combo[] = {KC_3, KC_4, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  // Add commonly used dash to home row
  [DF_DASH]    = COMBO(df_combo, KC_MINS),
  [THREE_FOUR_DASH]    = COMBO(three_four_combo, KC_MINS),
  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),
};


// For _QWERTY layer
#define GUI_ENT  GUI_T(KC_ENT)
#define LOW_TAB  LT(_LOWER, KC_TAB)
#define OSL_FUN  OSL(_FUNC)
#define OSM_AGR  OSM(MOD_RALT)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_SFT  OSM(MOD_LSFT)
#define RSE_BSP  LT(_RAISE, KC_BSPC)


// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

// These are special keycodes which can be used
/*
#define CPI_SW USER00  // Switch CPI
#define SCRL_SW USER01 // Switch scroll divider. Larger values = smaller scroll motion.
#define ROT_R15 USER02 // Rotate sensor coordinate by 15 degrees clockwise
#define ROT_L15 USER03 // Rotate sensor coordinate by 15 degrees counterclockwise
#define SCRL_MO USER04 // Enable scroll mode while being pressed
#define SCRL_TO USER05 // Toggle scroll mode and mouse mode
#define SCRL_IN USER06 // Invert scroll direction
*/

// Mouse Buttons 4 and 5 are recognized as "Browser Back" and "Browser Forward"
// The bottom row in each layer is for the encoder: CCW, button click, CW
// The last three matrix positions in the bottom row are not used.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                                     ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                      KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LALT),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                      KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_QUOT ,OSM_AGR ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
 OSM(MOD_LSFT),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                      KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,OSL_FUN ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
                         KC_LGUI,  OSM_LCTL, GUI_ENT, LOW_TAB, KC_MS_BTN1,             KC_MS_BTN2, RSE_BSP,  KC_SPC, OSM_SFT, KC_ESC,
                                                                 XXXXXXX, KC_MS_BTN3,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                                     ,-----------------------------------------------------.
      _______, KC_EXLM, KC_AT,  KC_HASH, KC_DLR,  KC_PERC,                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
      _______, KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX , KC_TILD,KC_GRV, KC_LBRC, KC_LCBR,                                        KC_RCBR, KC_RBRC, KC_COMM,KC_DOT,  KC_SLSH, _______ ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        KC_LGUI, KC_TRNS, KC_TRNS,   LOWER, KC_MS_BTN4,               KC_MS_BTN5,  KC_TRNS, KC_TRNS, KC_COLON, KC_ESC,
                                                                 XXXXXXX, KC_MS_BTN3,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
    
  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                                     ,-----------------------------------------------------.
      _______, KC_DEL , KC_INS, KC_UNDS, KC_PLUS, KC_PGUP,                                       XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_PIPE,_______ ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END , KC_MINS, KC_EQL , KC_PGDN,                                       KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_APP ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
      _______, KC_LT  , KC_GT  , KC_COPY, KC_PSTE, KC_SCLN,                                       KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,_______ ,
  //|--------+--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------+--------+--------|
                        KC_LGUI, CTL_ESC, KC_TRNS, XXXXXXX, KC_MS_BTN4,             KC_MS_BTN5,   RAISE  , KC_TRNS, KC_TRNS, KC_ESC,
                                                            XXXXXXX,  KC_MS_BTN3,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
  [_FUNC] = LAYOUT(
  // I don't really use lighting, so the following are not included:
  // RGB_VIA, RGB_SAI, RGB_HUI, RGB_MOD, RGB_RMOD, RGB_VAD, RGB_DSAD, RGB_HUD

  //,-----------------------------------------------------.                                     ,-----------------------------------------------------.
      _______, KC_F1  , KC_F2  , KC_F3   , KC_F4 ,  KC_F5 ,                                      KC_F6   , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,_______ ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,                                      SCRL_TO,  SCRL_MO, SCRL_IN, ROT_L15, ROT_R15,_______ ,
  //|--------+--------+--------+--------+--------+--------|                                     |--------+--------+--------+--------+--------+--------|
      _______,KC_CAPS,S(KC_DEL),C(KC_INS),S(KC_INS),XXXXXXX,                                       RGB_TOG,  CPI_SW, SCRL_SW, XXXXXXX, QK_BOOT,XXXXXXX ,
  //|--------+--------+--------+--------+--------+--------+--------|                   |--------+--------+--------+--------+--------+--------+--------|
                        KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX,  KC_MS_BTN1,             KC_MS_BTN2,   XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,
                                                                 XXXXXXX, KC_MS_BTN3,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                                            //`--------------'  `--------------'
    ),
};

// Same function on all layers for now.
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [1] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [2] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [3] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        #ifdef RGBLIGHT_ENABLE
        rgblight_sethsv_range(HSV_BLUE, 0, 2);
        #endif
        cocot_set_scroll_mode(true);
        break;
    case _RAISE:
        #ifdef RGBLIGHT_ENABLE
        rgblight_sethsv_range(HSV_RED, 0, 2);
        #endif
        cocot_set_scroll_mode(true);
        break;
    case _FUNC:
        #ifdef RGBLIGHT_ENABLE
        rgblight_sethsv_range(HSV_GREEN, 0, 2);
        #endif
        cocot_set_scroll_mode(false);
        break;
    default:
        #ifdef RGBLIGHT_ENABLE
        rgblight_sethsv_range( 0, 0, 0, 0, 2);
        #endif
        cocot_set_scroll_mode(false);
        break;
    }
    #ifdef RGBLIGHT_ENABLE
    rgblight_set_effect_range( 2, 10);
    #endif
      return state;
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    render_logo();
    oled_write_layer_state();
    return false;
}
#endif

// Used by markstos layout
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(_RAISE, KC_BSPC):
            return TAPPING_TERM_THUMB;
      case LT(_LOWER, KC_TAB):
            return TAPPING_TERM_THUMB;
      default:
            return TAPPING_TERM;
    }
}
