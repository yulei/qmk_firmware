/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "nrf_gpio.h"
#include "quantum.h"
#include "printf.h"
#include "matrix.h"

/**
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
static uint32_t row_pins[] = MATRIX_ROW_PINS;
static uint32_t col_pins[] = MATRIX_COL_PINS;

__attribute__((weak))
void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak))
void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak))
void matrix_init_user(void) {}
__attribute__((weak))
void matrix_scan_user(void) {}

void matrix_init(void) {
    uint8_t i = 0;
    for (i = 0; i < MATRIX_COLS; i++) {
        nrf_gpio_cfg_output(col_pins[i]);
        nrf_gpio_pin_clear(col_pins[i]);
    }

    for (i = 0; i < MATRIX_ROWS; i++) {
        nrf_gpio_cfg_input(row_pins[i], NRF_GPIO_PIN_PULLDOWN);
    }

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
        nrf_gpio_pin_set(col_pins[col]);

        // need wait to settle pin state
        wait_us(20);

        for( int row = 0; row < MATRIX_ROWS; row++) {
            data |= (nrf_gpio_pin_read(row_pins[row]) ? 1 : 0) << row;
        };

        nrf_gpio_pin_clear(col_pins[col]);

        if (matrix_debouncing[col] != data) {
            matrix_debouncing[col] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE_DELAY) {
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
