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
#include "rgb_backlight.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#include "ws2812.h"

// rgb bottom light stuff
extern rgblight_config_t rgblight_config;
void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds)
{
  for (uint16_t i = 0; i < leds; i++) {
    ws2812_write_led(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
  }
}

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
}

__attribute__((weak))
void matrix_scan_user(void) {
  //rgblight_task();
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
    indicator_leds_init();
    //ws2812_init();
    rb_init();
    //debug_enable = true;
    printf("matrix init\n");

 //#define MATRIX_COL_PINS { PC6, PA9, PA10, PC10, PC4, PC5, PB0, PB9, PC14, PC13, PC0, PC1, PC2, P3}
    palSetPadMode(GPIOC,  6, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,  9, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 10, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  4, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  5, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,  9, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 14, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,  3, PAL_MODE_OUTPUT_PUSHPULL);
    // PB5, PB6, PB7, PB8, PB12
    palSetPadMode(GPIOB, 5, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 7, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 8, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 12, PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_COLS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    for (int col = 0; col < MATRIX_COLS; col++) {
        matrix_row_t data = 0;
 //#define MATRIX_COL_PINS { PC6, PA9, PA10, PC10, PC4, PC5, PB0, PB9, PC14, PC13, PC0, PC1, PC2, P3}
        switch (col) {
            case 0: palSetPad(GPIOC,  6); break;
            case 1: palSetPad(GPIOA,  9); break;
            case 2: palSetPad(GPIOA,  10); break;
            case 3: palSetPad(GPIOC,  10); break;
            case 4: palSetPad(GPIOC,  4); break;
            case 5: palSetPad(GPIOC,  5); break;
            case 6: palSetPad(GPIOB,  0); break;
            case 7: palSetPad(GPIOB,  9); break;
            case 8: palSetPad(GPIOC,  14); break;
            case 9: palSetPad(GPIOC,  13); break;
            case 10: palSetPad(GPIOC,  0); break;
            case 11: palSetPad(GPIOC,  1); break;
            case 12: palSetPad(GPIOA,  2); break;
            case 13: palSetPad(GPIOA,  3); break;
        }

        // need wait to settle pin state
        wait_us(20);

    // PB5, PB6, PB7, PB8, PB12
        data = (
            (palReadPad(GPIOB, 5) << 0 ) |
            (palReadPad(GPIOB, 6) << 1 ) |
            (palReadPad(GPIOB, 7) << 2 ) |
            (palReadPad(GPIOB, 8) << 3 ) |
            (palReadPad(GPIOB, 12) << 4 )
        );

 //#define MATRIX_COL_PINS { PC6, PA9, PA10, PC10, PC4, PC5, PB0, PB9, PC14, PC13, PC0, PC1, PC2, P3}
        switch (col) {
            case 0: palClearPad(GPIOC,  6); break;
            case 1: palClearPad(GPIOA,  9); break;
            case 2: palClearPad(GPIOA,  10); break;
            case 3: palClearPad(GPIOC,  10); break;
            case 4: palClearPad(GPIOC,  4); break;
            case 5: palClearPad(GPIOC,  5); break;
            case 6: palClearPad(GPIOB,  0); break;
            case 7: palClearPad(GPIOB,  9); break;
            case 8: palClearPad(GPIOC,  14); break;
            case 9: palClearPad(GPIOC,  13); break;
            case 10: palClearPad(GPIOC,  0); break;
            case 11: palClearPad(GPIOC,  1); break;
            case 12: palClearPad(GPIOA,  2); break;
            case 13: palClearPad(GPIOA,  3); break;
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
