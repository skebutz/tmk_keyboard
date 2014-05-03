#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(ESC,    1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS,DELETE,HOME, END,PGDN,PGUP, \
           TAB,    Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,BSLS,  PAUS,  P7,  P8,  P9,PSLS, \
           NO,     A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN, FN2,  SLSH,  P4,  P5,  P6,PAST, \
           LSFT,   Z,   X,   C,   V,   B,   N,   M,QUOT,LBRC,RSFT,DOWN,    UP,  P1,  P2,  P3,PMNS, \
           LCTL,LALT, FN0, ENT,BSPC, SPC,COMM, DOT, FN1,RALT,RCTL,LEFT,  RGHT,  F4,  P0,PDOT,PPLS),
           
    /* 1: Cat */   
    KEYMAP(PWR,   F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11,   F12,PSCR,PAUS,NLCK,SLCK, \
           NO,    NO,  NO,  NO,  NO,  NO,  NO,ACL2,  NO,MS_U,BTN2, GRV,  RBRC,  NO,  UP,  NO,  NO, \
           CAPS,VOLD,VOLU,MUTE,  NO,  NO,  NO,ACL1,MS_L,MS_D,MS_R, FN3,    NO,LEFT,DOWN,RGHT,  NO, \
           LSFT,  NO,  NO,  NO,  NO,  NO,  NO,ACL0,BTN1,WH_D,WH_U,  NO,    NO,  NO,  NO,  NO,  NO, \
           LCTL,LALT, FN0,  NO, DEL,  NO,  FN2,FN3, FN1,RALT,  NO,  NO,    NO,  NO,  NO,  NO,  NO),
           
    /* 2: Key */       
    KEYMAP(PWR, F1,   F2,   F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11,   INS,PSCR,PAUS,NLCK,SLCK, \
           NO,  NO,   NO,   NO,  NO,  NO,  NO,ACL2,  NO,MS_U,BTN2, GRV,  NUBS,  NO,  NO,  NO,  NO, \
           CAPS,VOLD,VOLU,MUTE,  NO,  NO,  NO,ACL1,MS_L,MS_D,MS_R,  NO,    NO,  NO,  NO,  NO,  NO, \
           LSFT, NO,  NO,   NO,  NO,  NO,  NO,ACL0,BTN1,WH_D,WH_U,  NO,    NO,  NO,  NO,  NO,  NO, \
           LCTL,LALT, FN0,  NO, DEL,  NO,  FN2,FN3, FN1,RALT,  NO,  NO,    NO,  NO,  NO,  NO,  NO),
};
const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_MOMENTARY(1),
    ACTION_LAYER_TAP(2, KC_ENT),
    ACTION_MODS_KEY(MOD_LSFT, KC_1),
    ACTION_MODS_KEY(MOD_LSFT, KC_MINS),
    ACTION_LAYER_MOMENTARY(1, PENT)
};
