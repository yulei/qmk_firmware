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
#include "indicator_leds.h"
#include "matrix.h"

#ifdef RGBLIGHT_ENABLE
#include <string.h>
#include "rgblight.h"
#include "ws2812_f4.h"
extern rgblight_config_t rgblight_config;

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }

    ws2812_setleds(led, RGBLED_NUM);
}
#endif


void matrix_scan_kb(void) {
  matrix_scan_user();
}
void matrix_init_kb(void) {
  matrix_init_user();
}
__attribute__((weak))
void matrix_init_user(void) {
    indicator_leds_init();
#ifdef RGBLIGHT_ENABLE
    ws2812_init();
    rgblight_enable();
#endif
}

__attribute__((weak))
void matrix_scan_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_task();
#endif
}

/**
 * stm60 keybaord
 * #define MATRIX_ROW_PINS { PB5, PB6, PB7, PB8, PB12}
 * #define MATRIX_COL_PINS { PC6, PA9, PA10, PC10, PC4, PC5, PB0, PB9, PC14, PC13, PC0, PC1, PC2, P3}
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

void matrix_init(void) {
  // enable 3733
  palSetLineMode(LINE_3733_SDB, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(LINE_3733_SDB);

  //debug_enable = true;
  printf("matrix init\n");

  // PC6, PA9, PA10, PC10, PC4, PC5, PB0, PB9, PC14, PC13, PC0, PC1, PC2, P3
  palSetLineMode(LINE_COL_1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_2, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_3, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_4, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_5, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_6, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_7, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_8, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_9, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_10, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_11, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_12, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_13, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_COL_14, PAL_MODE_OUTPUT_PUSHPULL);

  // PB5, PB6, PB7, PB8, PB12
  palSetLineMode(LINE_ROW_1, PAL_MODE_INPUT_PULLDOWN);
  palSetLineMode(LINE_ROW_2, PAL_MODE_INPUT_PULLDOWN);
  palSetLineMode(LINE_ROW_3, PAL_MODE_INPUT_PULLDOWN);
  palSetLineMode(LINE_ROW_4, PAL_MODE_INPUT_PULLDOWN);
  palSetLineMode(LINE_ROW_5, PAL_MODE_INPUT_PULLDOWN);

  memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
  memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
        switch (col) {
            case 0: palSetLine(LINE_COL_1); break;
            case 1: palSetLine(LINE_COL_2); break;
            case 2: palSetLine(LINE_COL_3); break;
            case 3: palSetLine(LINE_COL_4); break;
            case 4: palSetLine(LINE_COL_5); break;
            case 5: palSetLine(LINE_COL_6); break;
            case 6: palSetLine(LINE_COL_7); break;
            case 7: palSetLine(LINE_COL_8); break;
            case 8: palSetLine(LINE_COL_9); break;
            case 9: palSetLine(LINE_COL_10); break;
            case 10: palSetLine(LINE_COL_11); break;
            case 11: palSetLine(LINE_COL_12); break;
            case 12: palSetLine(LINE_COL_13); break;
            case 13: palSetLine(LINE_COL_14); break;
        }

        // need wait to settle pin state
        wait_us(20);

        data = (
            (palReadLine(LINE_ROW_1) << 0 ) |
            (palReadLine(LINE_ROW_2) << 1 ) |
            (palReadLine(LINE_ROW_3) << 2 ) |
            (palReadLine(LINE_ROW_4) << 3 ) |
            (palReadLine(LINE_ROW_5) << 4 )
        );

        switch (col) {
            case 0: palClearLine(LINE_COL_1); break;
            case 1: palClearLine(LINE_COL_2); break;
            case 2: palClearLine(LINE_COL_3); break;
            case 3: palClearLine(LINE_COL_4); break;
            case 4: palClearLine(LINE_COL_5); break;
            case 5: palClearLine(LINE_COL_6); break;
            case 6: palClearLine(LINE_COL_7); break;
            case 7: palClearLine(LINE_COL_8); break;
            case 8: palClearLine(LINE_COL_9); break;
            case 9: palClearLine(LINE_COL_10); break;
            case 10: palClearLine(LINE_COL_11); break;
            case 11: palClearLine(LINE_COL_12); break;
            case 12: palClearLine(LINE_COL_13); break;
            case 13: palClearLine(LINE_COL_14); break;
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
