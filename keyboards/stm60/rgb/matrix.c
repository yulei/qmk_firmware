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
#include "rgb_matrix.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#include "ws2812.h"

// rgb bottom light stuff
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

#ifdef RGB_MATRIX_ENABLE
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
//cs1
    {{0|(0<<4)},    {  0,  0}, 1},
    {{0|(1<<4)},    { 17,  0}, 0},
    {{1|(0<<4)},    {  0, 16}, 1},
    {{2|(0<<4)},    {  0, 32}, 1},

//cs2
    {{0|(2<<4)},    { 34,  0}, 0},
    {{0|(3<<4)},    { 51,  0}, 0},
    {{1|(1<<4)},    { 17, 16}, 0},
    {{1|(2<<4)},    { 34, 16}, 0},
//cs3
    {{2|(1<<4)},    { 17, 32}, 0},
    {{2|(2<<4)},    { 34, 32}, 0},
    {{3|(1<<4)},    { 17, 48}, 0},
    {{3|(2<<4)},    { 34, 48}, 0},
//cs4
    {{0|(4<<4)},    { 68,  0}, 0},
    {{0|(5<<4)},    { 85,  0}, 0},
    {{1|(3<<4)},    { 51, 16}, 0},
    {{1|(4<<4)},    { 68, 16}, 0},
//cs5
    {{0|(11<<4)},   {187,  0}, 0},
    {{0|(12<<4)},   {204,  0}, 0},
    {{1|(11<<4)},   {187, 16}, 0},
    {{1|(12<<4)},   {204, 16}, 0},
//cs6
    {{0|(7<<4)},    {119,  0}, 0},
    {{0|(8<<4)},    {136,  0}, 0},
    {{1|(7<<4)},    {119, 16}, 0},
    {{1|(8<<4)},    {136, 16}, 0},
//cs7
    {{0|(9<<4)},    {153,  0}, 0},
    {{0|(10<<4)},   {170,  0}, 0},
    {{1|(9<<4)},    {153, 16}, 0},
    {{1|(10<<4)},   {170, 16}, 0},
//cs8
    {{0|(13<<4)},   {221,  0}, 0},
    {{0|(14<<4)},   {221,  0}, 0},
    {{1|(13<<4)},   {221, 32}, 1},
    {{2|(12<<4)},   {221, 16}, 1},
//cs9
    {{2|(3<<4)},    { 51, 32}, 0},
    {{2|(4<<4)},    { 68, 32}, 0},
    {{3|(3<<4)},    { 51, 48}, 0},
    {{3|(4<<4)},    { 68, 48}, 0},
//cs10
    {{0|(6<<4)},    {102,  0}, 0},
    {{1|(5<<4)},    { 85, 16}, 0},
    {{1|(6<<4)},    {102, 16}, 0},
    {{2|(5<<4)},    { 85, 32}, 0},
//cs11
    {{2|(6<<4)},    {102, 32}, 0},
    {{3|(5<<4)},    { 85, 48}, 0},
    {{3|(6<<4)},    {102, 48}, 0},
    {{4|(5<<4)},    {102, 64}, 0},
//cs12
    {{2|(7<<4)},    {119, 32}, 0},
    {{2|(8<<4)},    {136, 32}, 0},
    {{3|(7<<4)},    {119, 48}, 0},
    {{3|(8<<4)},    {136, 48}, 0},
//cs13
    {{2|(9<<4)},    {153, 32}, 0},
    {{2|(10<<4)},   {170, 32}, 0},
    {{3|(9<<4)},    {153, 48}, 0},
    {{4|(6<<4)},    {102, 48}, 1},
//cs14
    {{2|(11<<4)},   {187, 32}, 0},
    {{3|(10<<4)},   {170, 48}, 0},
    {{3|(11<<4)},   {187, 48}, 1},
    {{4|(7<<4)},    {153, 48}, 1},
//cs15
    {{3|(12<<4)},   {221, 48}, 1},
    {{4|(10<<4)},   {221, 64}, 1},
    {{4|(9<<4)},    {221, 64}, 1},
    {{4|(8<<4)},    {204, 64}, 1},
//cs16
    {{3|(0<<4)},    {  0, 48}, 1},
    {{4|(0<<4)},    {  0, 64}, 1},
    {{4|(1<<4)},    { 17, 64}, 1},
    {{4|(2<<4)},    { 34, 64}, 1},
};
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

#ifdef RGBLIGHT_ENABLE
    ws2812_init();
#endif

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
