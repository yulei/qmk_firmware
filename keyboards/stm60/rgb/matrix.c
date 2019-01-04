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

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"
#endif

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
extern void ws2812_init(void);
extern void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);
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
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
//cs1
    {0, K_1,    J_1,    L_1},
    {0, H_1,    G_1,    I_1},
    {0, E_1,    D_1,    F_1},
    {0, B_1,    A_1,    C_1},

//cs2
    {0, K_2,    J_2,    L_2},
    {0, H_2,    G_2,    I_2},
    {0, E_2,    D_2,    F_2},
    {0, B_2,    A_2,    C_2},
//cs3
    {0, K_3,    J_3,    L_3},
    {0, H_3,    G_3,    I_3},
    {0, E_3,    D_3,    F_3},
    {0, B_3,    A_3,    C_3},
//cs4
    {0, K_4,    J_4,    L_4},
    {0, H_4,    G_4,    I_4},
    {0, E_4,    D_4,    F_4},
    {0, B_4,    A_4,    C_4},
//cs5
    {0, K_5,    J_5,    L_5},
    {0, H_5,    G_5,    I_5},
    {0, E_5,    D_5,    F_5},
    {0, B_5,    A_5,    C_5},
//cs6
    {0, K_6,    J_6,    L_6},
    {0, H_6,    G_6,    I_6},
    {0, E_6,    D_6,    F_6},
    {0, B_6,    A_6,    C_6},
//cs7
    {0, K_7,    J_7,    L_7},
    {0, H_7,    G_7,    I_7},
    {0, E_7,    D_7,    F_7},
    {0, B_7,    A_7,    C_7},
//cs8
    {0, K_8,    J_8,    L_8},
    {0, H_8,    G_8,    I_8},
    {0, E_8,    D_8,    F_8},
    {0, B_8,    A_8,    C_8},
//cs9
    {0, K_9,    J_9,    L_9},
    {0, H_9,    G_9,    I_9},
    {0, E_9,    D_9,    F_9},
    {0, B_9,    A_9,    C_9},
//cs10
    {0, K_10,   J_10,   L_10},
    {0, H_10,   G_10,   I_10},
    {0, E_10,   D_10,   F_10},
    {0, B_10,   A_10,   C_10},
//cs11
    {0, K_11,   J_11,   L_11},
    {0, H_11,   G_11,   I_11},
    {0, E_11,   D_11,   F_11},
    {0, B_11,   A_11,   C_11},
//cs12
    {0, K_12,   J_12,   L_12},
    {0, H_12,   G_12,   I_12},
    {0, E_12,   D_12,   F_12},
    {0, B_12,   A_12,   C_12},
//cs13
    {0, K_13,   J_13,   L_13},
    {0, H_13,   G_13,   I_13},
    {0, E_13,   D_13,   F_13},
    {0, B_13,   A_13,   C_13},
//cs14
    {0, K_14,   J_14,   L_14},
    {0, H_14,   G_14,   I_14},
    {0, E_14,   D_14,   F_14},
    {0, B_14,   A_14,   C_14},
//cs15
    {0, K_15,   J_15,   L_15},

    {0, E_15,   D_15,   F_15},
    {0, B_15,   A_15,   C_15},
//cs16
    {0, K_16,   J_16,   L_16},
    {0, H_16,   G_16,   I_16},
    {0, E_16,   D_16,   F_16},
    {0, B_16,   A_16,   C_16},
};
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
    {{4|(6<<4)},    {136, 48}, 1},
//cs14
    {{2|(11<<4)},   {187, 32}, 0},
    {{3|(10<<4)},   {170, 48}, 0},
    {{3|(11<<4)},   {187, 48}, 1},
    {{4|(7<<4)},    {153, 48}, 1},
//cs15
    {{3|(12<<4)},   {221, 48}, 1},

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
    indicator_leds_init();

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(255,255,255);
    rgb_matrix_update_pwm_buffers();
#endif

#ifdef RGBLIGHT_ENABLE
    ws2812_init();
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
