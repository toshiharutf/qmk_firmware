/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Alejandro Jarovisky <@ajarov>

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
#include "keymap_latin_spanish.h"
#include "logo.h"

enum layers {
    L_0,
    L_1,
    L_2,
    SETUP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_0] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC,    ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,                         ES_Y,    ES_U,    ES_I,    ES_O,   ES_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_TAB,    ES_A,    ES_S,    ES_D,    ES_F,    ES_G,                         ES_H,    ES_J,    ES_K,    ES_L, ES_COLN, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---:-----+--------|
        KC_LCTL,    ES_Z,    ES_X,    ES_C,    ES_V,    ES_B,                         ES_N,    ES_M, ES_COMM,  ES_DOT, ES_UNDS, ES_QUES,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LSFT,   MO(1),  KC_SPC,     KC_ENT,   MO(2), ES_EQL
                                        //`--------------------------'  `--------------------------'
    ),

    [L_1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, XXXXXXX, XXXXXXX, ES_ASTR, ES_SLSH,  XXXXXXX,                      ES_EQL,    ES_7,    ES_8, ES_9,   XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--|                    |--------+------+--------+-----+-  -------+--------|
        KC_CAPS, XXXXXXX, XXXXXXX, ES_MINS, ES_PLUS,  XXXXXXX,                      ES_0,       ES_4,    ES_5, ES_6,   XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--|                    |--------+------+--------+-----+-  -------+--------|
        KC_LCTL, XXXXXXX, XXXXXXX, ES_LABK, ES_RABK,  XXXXXXX,                      XXXXXXX,    ES_1,    ES_2, ES_3,   XXXXXXX, KC_RCTL,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LSFT, _______,  KC_SPC,     KC_ENT, _______, ES_DOT
                                        //`--------------------------'  `--------------------------'
    ),

    [L_2] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, ES_CIRC, ES_PIPE, ES_LBRC,  ES_RBRC, ES_HASH,                    KC_BSPC,  KC_PGUP, XXXXXXX, KC_PGDN, ES_TILD, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, ES_AT,   ES_AMPR, ES_LPRN,  ES_RPRN, ES_UNDS,                    XXXXXXX, KC_HOME, KC_UP, KC_END, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, ES_PERC, ES_EXLM, ES_LCBR,  ES_RCBR, ES_MINS,                    KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LSFT, _______,  KC_SPC,     KC_ENT, _______, KC_RSFT
                                        //`--------------------------'  `--------------------------'
    ),


    [SETUP] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        XXXXXXX, XXXXXXX, XXXXXXX, QK_REBOOT, QK_MAKE, QK_BOOTLOADER,              RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_TOG,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_PSCR), KC_PSCR, XXXXXXX,                RGB_M_K, RGB_VAI, RGB_SAI, RGB_HUI, RGB_SAI,  RGB_M_G,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     RGB_M_X, RGB_VAD, RGB_SAD, RGB_HUD, RGB_SAD, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LSFT, _______,  KC_SPC,     KC_ENT, _______, _______
                                        //`--------------------------'  `--------------------------'
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, L_1, L_2, SETUP);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_layer_state(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case L_0:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_1:
            oled_write_ln_P(PSTR("Layer 1"), false);
            break;
        case L_2:
            oled_write_ln_P(PSTR("Layer 2"), false);
            break;
        case SETUP:
            oled_write_ln_P(PSTR("Fuck you Tom!"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAPS LOCK") : PSTR("         "), false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
