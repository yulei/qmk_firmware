/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "printf.h"
#include "backlight.h"
#include "matrix.h"

/**
 * stm60 keybaord
 * #define MATRIX_ROW_PINS { PB12, PB13, PB14, PB15, PC6, PC7, PC8, PC9}
 * #define MATRIX_COL_PINS { PB11, PB10, PB1, PB0, PC5, PC4, PA7, PA6, PA5}
 *
 * Row pins are input with internal pull-down.
 * Column pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_COLS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

void matrix_init(void) {
    printf("matrix init\n");

    palSetPadMode(GPIOB, 11, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  6, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  5, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOB, 12, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 14, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 15, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC,  6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC,  7, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC,  8, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC,  9, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
    palSetPadMode(GPIOC, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOC, 10);
}

uint8_t matrix_scan(void) {
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        //#define MATRIX_COL_PINS { PB11, PB10, PB1, PB0, PC5, PC4, PA7, PA6, PA5}
        switch (col) {
            case 0: palSetPad(GPIOB, 11); break;
            case 1: palSetPad(GPIOB, 10); break;
            case 2: palSetPad(GPIOB,  1); break;
            case 3: palSetPad(GPIOB,  0); break;
            case 4: palSetPad(GPIOC,  5); break;
            case 5: palSetPad(GPIOC,  4); break;
            case 6: palSetPad(GPIOA,  7); break;
            case 7: palSetPad(GPIOA,  6); break;
            case 8: palSetPad(GPIOA,  5); break;
        }

        // need wait to settle pin state
        wait_us(20);

        //#define MATRIX_ROW_PINS { PB12, PB13, PB14, PB15, PC6, PC7, PC8, PC9}
        data = (
            (palReadPad(GPIOB, 12) << 0 ) |
            (palReadPad(GPIOB, 13) << 1 ) |
            (palReadPad(GPIOB, 14) << 2 ) |
            (palReadPad(GPIOB, 15) << 3 ) |
            (palReadPad(GPIOC,  6) << 4 ) |
            (palReadPad(GPIOC,  7) << 5 ) |
            (palReadPad(GPIOC,  8) << 6 ) |
            (palReadPad(GPIOC,  9) << 7 )
        );

        switch (col) {
            case 0: palClearPad(GPIOB, 11); break;
            case 1: palClearPad(GPIOB, 10); break;
            case 2: palClearPad(GPIOB,  1); break;
            case 3: palClearPad(GPIOB,  0); break;
            case 4: palClearPad(GPIOC,  5); break;
            case 5: palClearPad(GPIOC,  4); break;
            case 6: palClearPad(GPIOA,  7); break;
            case 7: palClearPad(GPIOA,  6); break;
            case 8: palClearPad(GPIOA,  5); break;
        }

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = 0;
            for (int col = 0; col < MATRIX_COLS; col++) {
                matrix[row] |= ((matrix_debouncing[col] & (1 << row) ? 1 : 0) << col);
            }
        }
        debouncing = false;
    }

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
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
