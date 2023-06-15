/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT_all(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_PGDN,
		KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_DEL,
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   MO(_FN),
		CW_TOGG, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_LALT,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

// See https://github.com/qmk/qmk_firmware/issues/4750 for KC_SCRL and KC_PAUS usage instead of KC_BRID and KC_BRIU for brightness control
// https://github.com/qmk/qmk_firmware/pull/4836
    [_FN] = LAYOUT_all(
		QK_BOOT, KC_BRMD, KC_BRMU,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______, KC_VOLU,
		_______, _______, _______, KC_PGUP, _______, _______, _______, _______,   KC_UP, _______, _______, _______, _______,          _______, KC_VOLD,
		_______, _______, KC_HOME, KC_PGDN,  KC_END, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,          KC_MPLY,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, _______,
		KC_CAPS, _______, _______,                            _______,                            _______, _______,          KC_HOME, KC_VOLD, KC_ENT
    ),

    [_FUNC] = LAYOUT_all(
		 KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, _______,
		_______, _______, _______,                            _______,                            _______, _______,          KC_HOME, KC_VOLD, KC_ENT
    )

};


// Shift + esc = ~
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRV));

// CTRL + esc = `
// everytime I press the GRV key it sends another CTR. So CTRL hold down and double tap GRV will type two ` but it will also send 2 CTRL KCs
const key_override_t grave_esc_override = ko_make_with_layers_negmods_and_options(
        MOD_MASK_CTRL,
        KC_ESC,
        KC_GRV,
        ~0,
        MOD_MASK_SA,
        ko_option_no_reregister_trigger);

const key_override_t **key_overrides = (const key_override_t *[]){
    &tilde_esc_override,
    &grave_esc_override,
    NULL
};



// Custom Caps Word Word Breaking
// Modifications from Default:
//  KC_SCLN will be shifted and continue caps Word
//  KC_EQL will not be shifted and continue caps word
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_SCLN:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_EQL:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}




