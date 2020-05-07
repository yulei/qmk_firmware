/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "quantum.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "matrix.h"
#include "debounce.h"

/**
 *
 * Row pins are input with internal pull-down.
 * Column pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 */

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];    //raw values
static matrix_row_t matrix[MATRIX_ROWS];        //debounced values

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void init_pins(void)
{
    for (int i = 0; i < MATRIX_ROWS; i++) {
        setPinInputLow(row_pins[i]);
    }

    for (int i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(col_pins[i]);
        writePinLow(col_pins[i]);
    }
}

static void set_col_pin(int col)
{
    writePinHigh(col_pins[col]);
}

static void clear_col_pin(int col)
{
    writePinLow(col_pins[col]);
}

static uint8_t read_row_pin(int row)
{
    return readPin(row_pins[row]) ? 1 : 0;
}

void matrix_init(void)
{
    // init pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }

    debounce_init(MATRIX_ROWS);
    matrix_init_quantum();
}


static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    set_col_pin(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        uint8_t tmp = row_index;
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[tmp];

        // Check row pin state
        if (read_row_pin(row_index)) {
            // Pin HI, set col bit
            current_matrix[tmp] |= (1 << current_col);
        } else {
            // Pin LOW, clear col bit
            current_matrix[tmp] &= ~(1 << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[tmp]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    clear_col_pin(current_col);

    return matrix_changed;
}

uint8_t matrix_scan(void)
{
    bool changed = false;
    for (int col = 0; col < MATRIX_COLS; col++) {
        changed |= read_rows_on_col(raw_matrix, col);
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & (1<<col)); }

matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void)
{
    printf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        printf("%X0: ", row);
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}
