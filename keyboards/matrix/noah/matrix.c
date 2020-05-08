/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "printf.h"

/**
 *
 * Row pins are input with internal pull-down.
 * Column pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 */

/* matrix state(1:on, 0:off) */
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void select_col(uint8_t col)
{
    writePinHigh(col_pins[col]);
}

static void unselect_col(uint8_t col)
{
    writePinLow(col_pins[col]);
}

static uint8_t read_row_pin(int row)
{
    return readPin(row_pins[row]) ? 1 : 0;
}

void matrix_init_custom(void)
{
    // init pins
    for (int i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(col_pins[i]);
        writePinLow(col_pins[i]);
    }

    for (int i = 0; i < MATRIX_ROWS; i++) {
        setPinInputLow(row_pins[i]);
    }
}


static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

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
    unselect_col(current_col);

    return matrix_changed;
}

bool matrix_scan_custom(matrix_row_t current_matrix[])
{
    bool changed = false;
    for (int col = 0; col < MATRIX_COLS; col++) {
        changed |= read_rows_on_col(current_matrix, col);
    }
    return changed;
}

/*
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
*/
