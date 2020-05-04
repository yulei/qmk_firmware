/**
 * matrix.c
 */

#include "quantum.h"
#include "debounce.h"


/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];    //raw values
static matrix_row_t matrix[MATRIX_ROWS];        //debounced values

static const pin_t row_pins[MATRIX_ROWS] = {E6, F6, F7, B7, D4};

static void init_rows(void);
static void init_cols(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


__attribute__ ((weak))
void matrix_init_kb(void)
{
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void)
{
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

void matrix_init(void)
{
    setPinOutput(B4);
    writePinLow(B4);

    init_cols();
    init_rows();

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
    select_col(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        uint8_t tmp = row_index;
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[tmp];

        // Check row pin state
        if ( readPin(row_pins[row_index]) == 0) {
            // Pin Low, set col bit
            current_matrix[tmp] |= (1 << current_col);
        } else {
            // Pin high, clear col bit
            current_matrix[tmp] &= ~(1 << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[tmp]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_cols();

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

inline matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

/*
 * Row pin configuration
 * row: 0    1    2    3    4
 * pin: PE6  PF6  PF7  PB7  PD4
 */
static void init_rows(void)
{
  setPinInputHigh(E6);
  setPinInputHigh(F6);
  setPinInputHigh(F7);
  setPinInputHigh(B7);
  setPinInputHigh(D4);
}

/*
 * Columns 0 - 13
 * These columns uses two 74LVC138 3 to 8 bit demultiplexers.
 * EN Pin, PF5, PD6
 *
 * col / pin:    PF0  PF1  PF4
 * 0:             0    0    0
 * 1:             1    0    0
 * 2:             0    1    0
 * 3:             1    1    0
 * 4:             0    0    1
 * 5:             1    0    1
 * 6:             0    1    1
 *               PD2  PD3  PD5
 * 7:             0    0    0
 * 8:             1    0    0
 * 9:             0    1    0
 * 10:            1    1    0
 * 11:            0    0    1
 * 12:            1    0    1
 * 13:            0    1    1
 *
 */
static void init_cols(void)
{
  setPinOutput(F0);
  setPinOutput(F1);
  setPinOutput(F4);
  setPinOutput(F5);

  setPinOutput(D2);
  setPinOutput(D3);
  setPinOutput(D5);
  setPinOutput(D6);

  unselect_cols();
}

static void unselect_cols(void)
{
  writePinHigh(F0);
  writePinHigh(F1);
  writePinHigh(F4);
  writePinHigh(F5);

  writePinHigh(D2);
  writePinHigh(D3);
  writePinHigh(D5);
  writePinHigh(D6);
}

static void select_col(uint8_t col) {

   switch (col) {
        case 0:
          writePinLow(F0);
          writePinLow(F1);
          writePinLow(F4);
          break;
        case 1:
          writePinHigh(F0);
          writePinLow(F1);
          writePinLow(F4);
          break;
        case 2:
          writePinLow(F0);
          writePinHigh(F1);
          writePinLow(F4);
          break;
        case 3:
          writePinHigh(F0);
          writePinHigh(F1);
          writePinLow(F4);
          break;
        case 4:
          writePinLow(F0);
          writePinLow(F1);
          writePinHigh(F4);
          break;
        case 5:
          writePinHigh(F0);
          writePinLow(F1);
          writePinHigh(F4);
          break;
        case 6:
          writePinLow(F0);
          writePinHigh(F1);
          writePinHigh(F4);
          break;
        case 7:
          writePinLow(D2);
          writePinLow(D3);
          writePinLow(D5);
          break;
        case 8:
          writePinHigh(D2);
          writePinLow(D3);
          writePinLow(D5);
          break;
        case 9:
          writePinLow(D2);
          writePinHigh(D3);
          writePinLow(D5);
          break;
        case 10:
          writePinHigh(D2);
          writePinHigh(D3);
          writePinLow(D5);
          break;
        case 11:
          writePinLow(D2);
          writePinLow(D3);
          writePinHigh(D5);
          break;
        case 12:
          writePinHigh(D2);
          writePinLow(D3);
          writePinHigh(D5);
          break;
        case 13:
          writePinLow(D2);
          writePinHigh(D3);
          writePinHigh(D5);
          break;
    }
}
