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
#include "matrix.h"

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"
#endif

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#include "is31fl3741.h"
const is31_led rgb_leds[RGBLED_NUM] = {
    /* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {1, CS36_SW9, CS35_SW9, CS34_SW9},
    {1, CS36_SW8, CS35_SW8, CS34_SW8},
    {1, CS36_SW7, CS35_SW7, CS34_SW7},
    {1, CS36_SW5, CS35_SW5, CS34_SW5},
    {1, CS36_SW4, CS35_SW4, CS34_SW4},
    {1, CS36_SW3, CS35_SW3, CS34_SW3},
    {1, CS36_SW1, CS35_SW1, CS34_SW1},

    {1, CS33_SW1, CS32_SW1, CS31_SW1},
    {1, CS33_SW4, CS32_SW4, CS31_SW4},
    {1, CS33_SW5, CS32_SW5, CS31_SW5},
    {1, CS33_SW7, CS32_SW7, CS31_SW7},
    {1, CS33_SW2, CS32_SW2, CS31_SW2},
    {1, CS33_SW3, CS32_SW3, CS31_SW3},
    {1, CS33_SW6, CS32_SW6, CS31_SW6},

    {0, CS27_SW6, CS26_SW6, CS25_SW6},
    {1, CS27_SW8, CS26_SW8, CS25_SW8},
    {1, CS27_SW9, CS26_SW9, CS25_SW9},
    {0, CS27_SW5, CS26_SW5, CS25_SW5},
    {0, CS27_SW4, CS26_SW4, CS25_SW4},
    {1, CS27_SW7, CS26_SW7, CS25_SW7},
    {0, CS27_SW3, CS26_SW3, CS25_SW3}
    };

void rgbligtht_init(void)
{
  for(int i = 0; i < RGBLED_NUM; i++) {
    IS31FL3741_set_led_color(&rgb_leds[i], 255, 255, 255);
    IS31FL3741_set_led_scaling(&rgb_leds[i], 255, 255, 255);
  }
}

void rgblight_setleds(LED_TYPE *ledarray, uint16_t number_of_leds)
{
  for (int i = 0; i < number_of_leds; i++) {
    IS31FL3741_set_led_color(&rgb_leds[i], ledarray[i].r, ledarray[i].g, ledarray[i].b);
  }
}

extern rgblight_config_t rgblight_config;
void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }
    rgblight_setleds(led, RGBLED_NUM);
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

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(255,255,255);
    rgb_matrix_update_pwm_buffers();
#endif

#ifdef RGBLIGHT_ENABLE
    rgblight_init();
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
