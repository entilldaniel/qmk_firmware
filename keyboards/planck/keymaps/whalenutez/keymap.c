/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 **/

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS,
  _NUMS,
  _MOUSE,
  _FBTNS,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
};


enum unicode_names {
    RING_ABOVE_UPPER,
	RING_ABOVE_LOWER,
    DIAERESIS_A_UPPER,
	DIAERESIS_A_LOWER,
    DIAERESIS_O_UPPER,
	DIAERESIS_O_LOWER,	
    SNEK
};


const uint32_t PROGMEM unicode_map[] = {
	[RING_ABOVE_LOWER] = 0x00E5,
	[RING_ABOVE_UPPER] = 0x00C5,
	[DIAERESIS_A_LOWER] = 0x00E4,
	[DIAERESIS_A_UPPER] = 0x00C4,
	[DIAERESIS_O_LOWER] = 0x00F6,
	[DIAERESIS_O_UPPER] = 0x00D6,
    [SNEK]  = 0x1F40D, // 🐍
};

//LAYERS
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ARROWS MO(_ARROWS)
#define NUMS MO(_NUMS)
#define MOUSE MO(_MOUSE)
#define FBTNS MO(_FBTNS)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Brite|  GUI | ALT  |Lower |    Space    |Raise | Left | Down | LAlt |Rctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,     KC_U ,     KC_I   ,  KC_O,     KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_J ,     KC_K   ,  KC_L,     KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_M ,     KC_COMM,  KC_DOT,   KC_SLSH, LSFT_T(KC_ENT),
    KC_LCTL, ARROWS,  KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,   RAISE,     FBTNS  ,  _______,  KC_RALT, KC_RCTL
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |insert|   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |   [  |   ]  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next |   <  |   >  | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_INS , KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,
    _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, KC_LT,   KC_GT  , KC_EQL ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LT  , KC_GT  , KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPLY
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
	_______, _______, _______, _______, _______, _______, _______, _______, XP(RING_ABOVE_LOWER, RING_ABOVE_UPPER), XP(DIAERESIS_A_LOWER, DIAERESIS_A_UPPER), XP(DIAERESIS_O_LOWER, DIAERESIS_O_UPPER), X(SNEK),
	_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),


/* Arrows
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |  up  |      |pg up |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | left | down |right |pg dwn|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |home  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | mouse|             |nums  |      |      |      | end  |
 * `-----------------------------------------------------------------------------------''
 */
[_ARROWS] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______,  KC_UP , _______, _______, KC_PGUP,
    _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PGDN,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
    _______, _______, _______, _______, MOUSE  , _______, _______, NUMS   , _______, _______, _______, KC_END
), 


/* Nums
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   1  |  2   |  3   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |  5   |  6   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   7  |  8   |  9   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |  0   |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */  
[_NUMS] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, KC_1   , KC_2   , KC_3   , _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_4   , KC_5   , KC_6   , _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_7   , KC_8   , KC_9   , _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_0   , _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------''
 */  
[_MOUSE] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______	
),

/* Adjust (RAISE++)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------''
 */  
[_FBTNS] = LAYOUT_planck_grid(
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______	
)
  
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
}
return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


void keyboard_post_init_user(void) {
  planck_ez_right_led_level(60);
  planck_ez_left_led_level(60);
}






