/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/* 
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
#define KEYMAP( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, K3G, \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F, K4G \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F, KC_##K0G }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F, KC_##K1G }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F, KC_##K2G }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F, KC_##K3G }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47, KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F, KC_##K4G } \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    1,              // Fn1
    2,              // Fn2
    3,              // Fn3
    4,              // Fn4
    0,              // Fn5
    3,              // Fn6
    3               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_NO,          // Fn2 ???
    KC_NO,          // Fn3 ???
    KC_NO,          // Fn4 ???
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-------------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0| + |Del|Hom|End|PgD|PgU|
     * |-------------------------------------------------------------------|
     * |Tab|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|'* |¨~^| N7| N8| N9| N/|
     * |-------------------------------------------------------------------|
     * |Cap|  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö|  !|  -| N4| N5| N6| N*|  
     * |-------------------------------------------------------------------|
     * |Shi|  Z|  X|  C|  V|  B|  N|  M|  Ä|  Å|Shi| Dn| Up| N1| N2| N3| N-|
     * |-------------------------------------------------------------------|
     * |Ctl|Alt|Cat|Key|Bsp|Spa|  ,|  .|Ent|Alt|Ctl| Lt| Rt|NEn| N0| N,| N+|
     * `-------------------------------------------------------------------'
     */
    KEYMAP( KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_MINS,KC_DELETE,KC_HOME, KC_END,KC_PGDN,KC_PGUP, \
            KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_BSLS,  KC_RBRC,  KC_P7,  KC_P8,  KC_P9,KC_PSLS, \
             KC_NO,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,KC_SCLN,  KC_NO,  KC_SLSH,  KC_P4,  KC_P5,  KC_P6,KC_PAST, \
           KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,KC_QUOT,KC_LBRC,KC_RSFT,KC_DOWN,    KC_UP,  KC_P1,  KC_P2,  KC_P3,KC_PMNS, \
           KC_LCTL,KC_RALT, KC_FN1, KC_ENT,KC_BSPC, KC_SPC,KC_COMM, KC_DOT, KC_FN2,KC_RALT,KC_RCTL,KC_LEFT,  KC_RGHT,KC_PENT,  KC_P0,KC_PDOT,KC_PPLS),


    /* Layer 1: Cat layer
     * ,-------------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0| + |Del|Hom|End|PgD|PgU|
     * |-------------------------------------------------------------------|
     * |Tab|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|   |   |   |   |   |   |
     * |-------------------------------------------------------------------|
     * |Cap|  A|  S|  D|  F|  G|  H|  J|  K|  L|   |   |   |   |   |   |   |  
     * |-------------------------------------------------------------------|
     * |Shi|  Z|  X|  C|  V|  B|  N|  M|   |   |   |   |   |   |   |   |   |
     * |-------------------------------------------------------------------|
     * |Ctl|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * `-------------------------------------------------------------------'
     */
    KEYMAP(KC_PWR,  KC_F1,  KC_F2,  KC_F3,    KC_F4,KC_F5,KC_F6,KC_F7,  KC_F8,  KC_F9, KC_F10,KC_F11, KC_F12,KC_PSCR,KC_PAUS,KC_NLCK,KC_SLCK, \
               NO,     NO,     NO,     NO,       NO,   NO,   NO,   NO,     NO,KC_MS_U,KC_BTN2,KC_GRV,KC_NUBS,     NO,     NO,     NO,     NO, \
          KC_CAPS,KC_VOLD,KC_VOLU,KC_MUTE,       NO,   NO,   NO,   NO,KC_MS_L,KC_MS_D,KC_MS_R,    NO,     NO,     NO,     NO,     NO,     NO, \
          KC_LSFT,     NO,     NO,     NO,       NO,   NO,   NO,   NO,KC_BTN1,KC_WH_D,KC_WH_U,    NO,     NO,     NO,     NO,     NO,     NO, \
               NO,KC_LALT,     NO,     NO,KC_DELETE,   NO,   NO,   NO,     NO,     NO,     NO,    NO,     NO,     NO,     NO,     NO,     NO), 


    /* Layer 2: Key layer
     * ,-------------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0| + |Del|Hom|End|PgD|PgU|
     * |-------------------------------------------------------------------|
     * |Tab|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|   |   |   |   |   |   |
     * |-------------------------------------------------------------------|
     * |Cap|  A|  S|  D|  F|  G|  H|  J|  K|  L|   |   |   |   |   |   |   |  
     * |-------------------------------------------------------------------|
     * |Shi|  Z|  X|  C|  V|  B|  N|  M|   |   |   |   |   |   |   |   |   |
     * |-------------------------------------------------------------------|
     * |Ctl|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * `-------------------------------------------------------------------'
     */
    KEYMAP(KC_PWR,  KC_F1,  KC_F2,  KC_F3,    KC_F4,KC_F5,KC_F6,KC_F7,  KC_F8,  KC_F9, KC_F10,KC_F11, KC_F12,KC_PSCR,KC_PAUS,KC_NLCK,KC_SLCK, \
               NO,     NO,     NO,     NO,       NO,   NO,   NO,   NO,     NO,KC_MS_U,KC_BTN2,KC_GRV,KC_NUBS,     NO,     NO,     NO,     NO, \
          KC_CAPS,KC_VOLD,KC_VOLU,KC_MUTE,       NO,   NO,   NO,   NO,KC_MS_L,KC_MS_D,KC_MS_R,    NO,     NO,     NO,     NO,     NO,     NO, \
          KC_LSFT,     NO,     NO,     NO,       NO,   NO,   NO,   NO,KC_BTN1,KC_WH_D,KC_WH_U,    NO,     NO,     NO,     NO,     NO,     NO, \
               NO,KC_LALT,     NO,     NO,KC_DELETE,   NO,   NO,   NO,     NO,     NO,     NO,    NO,     NO,     NO,     NO,     NO,     NO), 

};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}
