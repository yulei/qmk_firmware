/**
 * matrix.c
 */

#include "quantum.h"
#include "matrix.h"

/**
 * seems the A9 pin can's work in input pull high,
 * thus have to implement the custom matrix scan.
 */
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static void init_pins(void)
{
    for (int i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(col_pins[i]);
        writePinLow(col_pins[i]);
    }

    for (int j = 0; j < MATRIX_ROWS; j++) {
        setPinInputLow(row_pins[j]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    writePinHigh(col_pins[current_col]);
    matrix_io_delay();

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        uint8_t tmp = row_index;
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[tmp];

        // Check row pin state
        if (readPin(row_pins[row_index])) {
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
    writePinLow(col_pins[current_col]);

    return matrix_changed;
}

void matrix_init_custom(void)
{
    init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[])
{
    bool changed = false;
    for (int col = 0; col < MATRIX_COLS; col++) {
        changed |= read_rows_on_col(current_matrix, col);
    }
    return changed;
}
