/* Copyright 2021 Vince Yoong (@tehxeno)
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

enum layers {
   _QWERTY,
   _NAVI,
   _NUMB,
   _MOUSE,
   _MEDIA   
};

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)           
#define HOME_K RCTL_T(KC_K)
#define HOME_L RALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_QUOT)

// If these don't work, then define and replace... KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, KC_AGIN,
#define PSTE_K C(KC_V)
#define COPY_K C(KC_C)
#define CUT_K  C(KC_X)
#define UNDO_K C(KC_Z)
#define AGIN_K C(KC_Y)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Increase the hold time for pinky GUI keys
    case HOME_A:
      return TAPPING_TERM + 100;
    case HOME_SCLN:
      return TAPPING_TERM + 100;
    // Increase the hold time for ring ALT keys
    case HOME_S:
      return TAPPING_TERM + 50;
    case HOME_L:
      return TAPPING_TERM + 50;
    // Decrease the hold time for pointer SHIFT keys
    case HOME_F:
      return TAPPING_TERM - 25;
    case HOME_J:
      return TAPPING_TERM - 25;
    default:
      return TAPPING_TERM;
  }
}

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  QWERTY = QK_USER,
  NAVI,
  NUMB,
  MOUSE,
  MEDIA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,                               KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_ENT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    LT(4,KC_ENT), LT(4,KC_ESC),KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SCLN,  
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                          LT(3,KC_DOT), LT(2,KC_COMM), LT(1,KC_BSPC),     LT(1,KC_SPC), LT(2,KC_ENT), LT(3,KC_TAB)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NAVI] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_MINS, KC_EQL,  KC_QUES, KC_EXLM, KC_SCLN,                            PSTE_K,  COPY_K,  CUT_K,   UNDO_K,  AGIN_K,  KC_PSCR, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_PIPE,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  KC_TRNS, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_LPRN, KC_RPRN, KC_LT,   KC_GT,   KC_SLSH,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS, 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS, KC_ENT,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_TRNS, KC_BSPC, KC_DEL,                    KC_BSPC, KC_TRNS, KC_TRNS
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NUMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_NO,                              KC_NUM,  KC_7,    KC_8,    KC_9,    KC_SLSH, KC_PAST, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_NO,                              KC_SCRL, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_NO, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_NO,                              KC_CAPS, KC_1,    KC_2,    KC_3,    KC_MINS, KC_NO, 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,            KC_TRNS, KC_NO,   KC_0,    KC_DOT,  KC_COMM, KC_PENT, KC_NO, 
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCTL, KC_NO,   KC_LSFT,                   KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            PSTE_K,  COPY_K,  CUT_K,   UNDO_K,  AGIN_K,  KC_PSCR, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS,                            KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_TRNS, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_TRNS, KC_TRNS, 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, 
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_NO,   KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MEDIA] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RGB_TOG, BL_TOGG, RGB_M_P, RGB_M_B, RGB_RMOD,RGB_MOD,                            KC_MUTE, KC_MPLY, KC_MSTP, KC_NO,   KC_NO,   KC_NO, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     BL_STEP, BL_UP,   RGB_M_R, RGB_M_SW,RGB_HUD, RGB_HUI,                            KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,   KC_NO, 
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     BL_BRTG, BL_DOWN, RGB_M_SN,RGB_M_K, RGB_SAD, RGB_SAI,                            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_M_T, KC_NO,   RGB_M_X, RGB_M_G, RGB_VAD, RGB_VAI, KC_NO,            KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    RGB_SPD, RGB_SPI, KC_NO,                     KC_MPLY, KC_MSTP, KC_MUTE
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  //Note: index == 1 is the right encoder. My Iris Rev4 does not have a left encoder, so nothing is encoded for it until the default layer.
  switch(get_highest_layer(layer_state)) {
    case _QWERTY:        //if you're on layer 0
      //Perform Alt+Tab magic
      if (clockwise) {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
          }
          alt_tab_timer = timer_read();
          tap_code16(KC_TAB);
      } else {
          if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
          }
          alt_tab_timer = timer_read();
          tap_code16(S(KC_TAB));
      }
      break;
    case _NAVI:         //if you're on layer 1
      if (index == 1) {
        //Tabbing, using ctrl+tab and ctrl+shift+tab shortcuts
        if (clockwise) {
          tap_code16(C(KC_TAB));
        } else {
          tap_code16(S(C(KC_TAB)));
        }
      }
      break;
    case _NUMB:         //if you're on layer 2
      if (index == 1) {
        //Page Scrolling
        if (clockwise) {
          tap_code(KC_PGDN);
        } else {
          tap_code(KC_PGUP);
        }
      }
      break;
    case _MOUSE:        //if you're on layer 3
      if (index == 1) {
        //Undo&Redo
        if (clockwise) {
          tap_code16(C(KC_Y));
        } else {
          tap_code16(C(KC_Z));
        }        
      }
      break;
    case _MEDIA:        //if you're on layer 4
      if (index == 1) {
        //Audio Control
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }      
      }
      break;
    default:                //if you're on any other layer
      //Left side encoder
      if (index == 0) {
          if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
      }
      //Right side encoder
      else if (index == 1) {
          //Perform Alt+Tab magic
          if (clockwise) {
              if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
              }
              alt_tab_timer = timer_read();
              tap_code16(KC_TAB);
          } else {
              if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
              }
              alt_tab_timer = timer_read();
              tap_code16(S(KC_TAB));
          }
      }
      break;
  }
  return false;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

