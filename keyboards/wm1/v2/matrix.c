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
 * wm1 keybaord
 * #define MATRIX_ROW_PINS { PA4, PA5, PA6, PA7, PC4}
 * #define MATRIX_COL_PINS { PA1, PA0, PC3, PC2, PC13, PB7, PB6, PB5, PD2, PC12, PC11, PC10, PC9, PC8, PC7, PC6}
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

    palSetPadMode(GPIOA,  1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  3, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  6, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD,  2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 12, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 11, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  9, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  8, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  7, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  6, PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOA,  4, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA,  5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA,  6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA,  7, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC,  4, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;

        //#define MATRIX_COL_PINS { PA1, PA0, PC3, PC2, PC13, PB7, PB6, PB5, PD2, PC12, PC11, PC10, PC9, PC8, PC7, PC6}
        switch (col) {
            case 0: palSetPad(GPIOA,  1); break;
            case 1: palSetPad(GPIOA,  0); break;
            case 2: palSetPad(GPIOC,  3); break;
            case 3: palSetPad(GPIOC,  2); break;
            case 4: palSetPad(GPIOC, 13); break;
            case 5: palSetPad(GPIOB,  7); break;
            case 6: palSetPad(GPIOB,  6); break;
            case 7: palSetPad(GPIOB,  5); break;
            case 8: palSetPad(GPIOD,  2); break;
            case 9: palSetPad(GPIOC, 12); break;
            case 10: palSetPad(GPIOC,11); break;
            case 11: palSetPad(GPIOC,10); break;
            case 12: palSetPad(GPIOC, 9); break;
            case 13: palSetPad(GPIOC, 8); break;
            case 14: palSetPad(GPIOC, 7); break;
            case 15: palSetPad(GPIOC, 6); break;
        }

        // need wait to settle pin state
        wait_us(20);

        //#define MATRIX_ROW_PINS { PA4, PA5, PA6, PA7, PC4}
        data = (
            (palReadPad(GPIOA,  4) << 0 ) |
            (palReadPad(GPIOA,  5) << 1 ) |
            (palReadPad(GPIOA,  6) << 2 ) |
            (palReadPad(GPIOA,  7) << 3 ) |
            (palReadPad(GPIOC,  4) << 4 )
        );

        switch (col) {
            case 0: palSetPad(GPIOA,  1); break;
            case 1: palSetPad(GPIOA,  0); break;
            case 2: palSetPad(GPIOC,  3); break;
            case 3: palSetPad(GPIOC,  2); break;
            case 4: palSetPad(GPIOC, 13); break;
            case 5: palSetPad(GPIOB,  7); break;
            case 6: palSetPad(GPIOB,  6); break;
            case 7: palSetPad(GPIOB,  5); break;
            case 8: palSetPad(GPIOD,  2); break;
            case 9: palSetPad(GPIOC, 12); break;
            case 10: palSetPad(GPIOC,11); break;
            case 11: palSetPad(GPIOC,10); break;
            case 12: palSetPad(GPIOC, 9); break;
            case 13: palSetPad(GPIOC, 8); break;
            case 14: palSetPad(GPIOC, 7); break;
            case 15: palSetPad(GPIOC, 6); break;
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
