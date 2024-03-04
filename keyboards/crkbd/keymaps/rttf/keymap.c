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
#include "keymap_us.h"
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
         KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_QUOTE, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---:-----+--------|
        KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_UNDS, KC_RGUI,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             MO(2), KC_LCTL,  KC_SPC ,    KC_ENT,  KC_RSFT ,  MO(1)
                                        //`--------------------------'  `--------------------------'
    ),

    [L_1] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, KC_LBRC, KC_RBRC, KC_SLSH , KC_ASTR, XXXXXXX,                      XXXXXXX,   KC_7,    KC_8, KC_9,   KC_EQL, KC_BSPC,
    //|--------+--------+-------++--------+--------+-|------+-|                    |--------+------+--------+-----+-  -------+--------|
        _______, KC_LPRN, KC_RPRN, KC_MINS, KC_PLUS, KC_CIRC,                      XXXXXXX,   KC_4,    KC_5, KC_6,   KC_0,     KC_DEL,
    //|--------+--------+-------++--------+--------+-|------+-|                    |--------+------+--------+-----+-  -------+--------|
        _______, KC_LCBR, KC_RCBR, KC_LABK, KC_RABK, XXXXXXX,                      XXXXXXX ,   KC_1,    KC_2, KC_3,   KC_DOT, KC_RALT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, KC_ENT, _______,    _______ , _______, _______
                                        //`--------------------------'  `--------------------------'
    ),

    [L_2] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                    XXXXXXX,  KC_AT, KC_HASH, KC_DLR, KC_TILD, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_HOME,  KC_UP,  KC_END,  KC_PGUP,  XXXXXXX,                    LCTL(KC_SLSH), KC_COLN, KC_SEMICOLON, KC_EXLM, KC_GRAVE, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_LEFT, KC_DOWN, KC_RIGHT,  KC_PGDN, XXXXXXX,                    XXXXXXX, KC_QUES, KC_AMPR, KC_PIPE, KC_PERC, KC_RALT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,_______, _______  ,     _______ , _______, _______
                                        //`--------------------------'  `--------------------------'
    ),


    [SETUP] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  QK_BOOT,                       BL_BRTG, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_TOG,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_PSCR,                  RGB_M_K, RGB_VAI, RGB_SAI, RGB_HUI, RGB_SAI,  RGB_M_G,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F11, KC_F12, KC_CALC, KC_VOLD, KC_VOLU, KC_MUTE,                        RGB_M_X, RGB_VAD, RGB_SAD, RGB_HUD, RGB_SAD, KC_RALT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,     _______, _______, _______
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
