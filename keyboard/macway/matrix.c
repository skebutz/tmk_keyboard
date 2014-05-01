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
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static matrix_row_t read_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    // Input with pull-up(DDR:0, PORT:1)
    DDRB  &= ~0b00000000;
    PORTB &= ~0b01110000;
    DDRD  &= ~0b00000000;
    PORTD &= ~0b11000111;
    DDRC  &= ~0b00000000;
    PORTC &= ~0b11000000;
    DDRF  &= ~0b00000000;
    PORTF &= ~0b11110011;
    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }

    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]))
            return true;
    }
    return false;
}
#endif

inline
static matrix_row_t read_cols(void)
{
    return (PIND&(1<<0) ? 0 : (1<<0)) |
           (PIND&(1<<1) ? 0 : (1<<1)) |
           (PIND&(1<<2) ? 0 : (1<<2)) |
           (PIND&(1<<3) ? 0 : (1<<3)) |
           (PINC&(1<<6) ? 0 : (1<<4)) |
           (PINC&(1<<7) ? 0 : (1<<5)) |
           (PINF&(1<<0) ? 0 : (1<<6)) |
           (PINF&(1<<1) ? 0 : (1<<7)) |
           (PINF&(1<<4) ? 0 : (1<<8)) |
           (PINF&(1<<5) ? 0 : (1<<9)) |
           (PINF&(1<<6) ? 0 : (1<<10)) |
           (PINF&(1<<7) ? 0 : (1<<11)) |
           (PINB&(1<<6) ? 0 : (1<<12)) |
           (PINB&(1<<5) ? 0 : (1<<13)) |
           (PINB&(1<<4) ? 0 : (1<<14)) |
           (PIND&(1<<7) ? 0 : (1<<15)) |
           (PIND&(1<<6) ? 0 : (1<<16)) ;
}

inline
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~0b10001111;
    PORTB &= ~0b10001111;
}

inline
static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    // row: 0    1    2    3    4    
    // pin: PB0, PB1, PB2, PB3, PB7
    switch (row) {
        case 0:
            DDRB  |= (1<<0);
            PORTB &= ~(1<<0);
            break;
        case 1:
            DDRB  |= (1<<1);
            PORTB &= ~(1<<1);
            break;
        case 2:
            DDRB  |= (1<<2);
            PORTB &= ~(1<<2);
            break;
        case 3:
            DDRB  |= (1<<3);
            PORTB &= ~(1<<3);
            break;
        case 4:
            DDRB  |= (1<<7);
            PORTB &= ~(1<<7);
            break;
    }
}
