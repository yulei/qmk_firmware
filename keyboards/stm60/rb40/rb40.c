/**
 * rb40.c
 */

#include "rb40.h"

#ifdef RGBLIGHT_ENABLE
__attribute__ ((weak))
void matrix_init_kb(void)
{
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_init_user(void)
{
  setPinOutput(D2);
  writePinLow(D2);
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
// left CA
    {0, C1_1,   C3_2,   C4_2},
    {0, C1_2,   C2_2,   C4_3},
    {0, C1_3,   C2_3,   C3_3},
    {0, C1_4,   C2_4,   C3_4},
    {0, C1_5,   C2_5,   C3_5},
    {0, C1_6,   C2_6,   C3_6},
    {0, C1_7,   C2_7,   C3_7},
    {0, C1_8,   C2_8,   C3_8},

    {0, C5_1,   C4_1,   C6_1},
    {0, C5_8,   C4_8,   C6_8},

    {0, C9_1,   C8_1,   C7_1},
    {0, C9_2,   C8_2,   C7_2},
    {0, C9_3,   C8_3,   C7_3},
    {0, C9_4,   C8_4,   C7_4},
    {0, C9_5,   C8_5,   C7_5},
    {0, C9_6,   C8_6,   C7_6},
    {0, C9_7,   C8_7,   C6_6},
    {0, C9_8,   C7_7,   C6_7},
// left CB
    {0, C1_9,   C3_10,  C4_10},
    {0, C1_10,  C2_10,  C4_11},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
    {0, C1_13,  C2_13,  C3_13},
    {0, C1_14,  C2_14,  C3_14},
    {0, C1_15,  C2_15,  C3_15},
    {0, C1_16,  C2_16,  C3_16},

    {0, C5_9,   C4_9,   C6_9},
    {0, C5_16,  C4_16,  C6_16},

    {0, C9_9,   C8_9,   C7_9},
    {0, C9_10,  C8_10,  C7_10},
    {0, C9_11,  C8_11,  C7_11},
    {0, C9_12,  C8_12,  C7_12},
    {0, C9_13,  C8_13,  C7_13},
    {0, C9_14,  C8_14,  C7_14},
    {0, C9_15,  C8_15,  C6_14},
    {0, C9_16,  C7_15,  C6_15},

// right CA
    {1, C1_1,   C3_2,   C4_2},
    {1, C1_2,   C2_2,   C4_3},
    {1, C1_3,   C2_3,   C3_3},
    {1, C1_4,   C2_4,   C3_4},
    {1, C1_5,   C2_5,   C3_5},
    {1, C1_6,   C2_6,   C3_6},
    {1, C1_7,   C2_7,   C3_7},
    {1, C1_8,   C2_8,   C3_8},

    {1, C5_1,   C4_1,   C6_1},
    {1, C5_8,   C4_8,   C6_8},

    {1, C9_1,   C8_1,   C7_1},
    {1, C9_2,   C8_2,   C7_2},
    {1, C9_3,   C8_3,   C7_3},
    {1, C9_4,   C8_4,   C7_4},
    {1, C9_5,   C8_5,   C7_5},
    {1, C9_6,   C8_6,   C7_6},
    {1, C9_7,   C8_7,   C6_6},
    {1, C9_8,   C7_7,   C6_7},
// right CB
    {1, C1_9,   C3_10,  C4_10},
    {1, C1_10,  C2_10,  C4_11},
    {1, C1_11,  C2_11,  C3_11},
    {1, C1_12,  C2_12,  C3_12},
    {1, C1_13,  C2_13,  C3_13},
    {1, C1_14,  C2_14,  C3_14},
    {1, C1_15,  C2_15,  C3_15},
    {1, C1_16,  C2_16,  C3_16},

    {1, C5_9,   C4_9,   C6_9},
    {1, C5_16,  C4_16,  C6_16},

    {1, C9_9,   C8_9,   C7_9},
    {1, C9_10,  C8_10,  C7_10},
    {1, C9_11,  C8_11,  C7_11},
    {1, C9_12,  C8_12,  C7_12},
    {1, C9_13,  C8_13,  C7_13},
    {1, C9_14,  C8_14,  C7_14},
    {1, C9_15,  C8_15,  C6_14},
    {1, C9_16,  C7_15,  C6_15},
};

const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
// left CB
    {{2|(2<<4)},    { 32, 32}, 0},
    {{3|(3<<4)},    { 48, 48}, 0},
    {{3|(4<<4)},    { 64, 48}, 0},
    {{3|(5<<4)},    { 80, 48}, 0},
    {{3|(6<<4)},    { 96, 48}, 0},
    {{3|(7<<4)},    {112, 48}, 0},
    {{4|(6<<4)},    { 96, 64}, 0},
    {{4|(6<<4)},    { 96, 64}, 0},

    {{2|(0<<4)},    {  0, 32}, 1},
    {{2|(1<<4)},    { 16, 32}, 0},

    {{3|(0<<4)},    {  0, 48}, 1},
    {{3|(0<<4)},    {  0, 48}, 1},
    {{3|(1<<4)},    { 16, 48}, 0},
    {{3|(2<<4)},    { 32, 48}, 0},
    {{4|(4<<4)},    { 64, 64}, 0},
    {{4|(2<<4)},    { 32, 64}, 1},
    {{4|(1<<4)},    { 16, 64}, 1},
    {{4|(0<<4)},    {  0, 64}, 1},
// left CA
    {{0|(0<<4)},    {  0,  0}, 1},
    {{0|(1<<4)},    { 16,  0}, 0},
    {{0|(2<<4)},    { 32,  0}, 0},
    {{0|(3<<4)},    { 48,  0}, 0},
    {{0|(4<<4)},    { 64,  0}, 0},
    {{0|(5<<4)},    { 80,  0}, 0},
    {{0|(6<<4)},    { 96,  0}, 0},
    {{1|(6<<4)},    { 96, 16}, 0},

    {{1|(0<<4)},    { 0,  16}, 1},
    {{1|(1<<4)},    { 16, 16}, 0},

    {{1|(2<<4)},    { 32, 16}, 0},
    {{1|(3<<4)},    { 48, 16}, 0},
    {{1|(4<<4)},    { 64, 16}, 0},
    {{1|(5<<4)},    { 80, 16}, 0},
    {{2|(3<<4)},    { 48, 32}, 0},
    {{2|(4<<4)},    { 64, 32}, 0},
    {{2|(5<<4)},    { 80, 32}, 0},
    {{2|(6<<4)},    { 96, 32}, 0},

// right CA
    {{0|(8<<4)},    {128,  0}, 0},
    {{0|(9<<4)},    {144,  0}, 0},
    {{0|(10<<4)},   {160,  0}, 0},
    {{0|(11<<4)},   {176,  0}, 0},
    {{0|(12<<4)},   {192,  0}, 0},
    {{0|(13<<4)},   {208,  0}, 0},
    {{0|(14<<4)},   {216,  0}, 1},
    {{0|(14<<4)},   {224,  0}, 1},

    {{0|(7<<4)},    {112,  0}, 0},
    {{1|(8<<4)},    {128, 16}, 0},

    {{1|(9<<4)},    {144, 16}, 0},
    {{1|(10<<4)},   {160, 16}, 0},
    {{1|(11<<4)},   {176, 16}, 0},
    {{1|(12<<4)},   {192, 16}, 0},
    {{1|(13<<4)},   {208, 16}, 0},
    {{1|(14<<4)},   {224, 16}, 1},
    {{2|(14<<4)},   {224, 32}, 1},
    {{2|(14<<4)},   {216, 32}, 1},

// right CB
    {{2|(8<<4)},    {128, 32}, 0},
    {{2|(9<<4)},    {144, 32}, 0},
    {{2|(10<<4)},   {160, 32}, 0},
    {{2|(11<<4)},   {176, 32}, 0},
    {{2|(12<<4)},   {192, 32}, 0},
    {{2|(13<<4)},   {208, 32}, 0},
    {{3|(13<<4)},   {208, 48}, 0},
    {{3|(14<<4)},   {224, 48}, 1},

    {{3|(8<<4)},    {128, 48}, 0},
    {{3|(9<<4)},    {144, 48}, 0},

    {{3|(10<<4)},   {160, 48}, 0},
    {{3|(11<<4)},   {176, 48}, 0},
    {{3|(12<<4)},   {192, 48}, 0},
    {{4|(9<<4)},    {142, 64}, 0},
    {{4|(10<<4)},   {160, 64}, 1},
    {{4|(11<<4)},   {176, 64}, 1},
    {{4|(13<<4)},   {208, 64}, 1},
    {{4|(14<<4)},   {224, 64}, 1},
};
#endif
