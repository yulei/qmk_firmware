/**
 * 65rgb.c
 */

#include "65rgb.h"

#ifdef RGB_MATRIX_ENABLE
#include "i2c_master.h"
#include "is31fl3741.h"

static void init( void )
{
    i2c_init();
    IS31FL3741_init( DRIVER_ADDR_1 );
    for ( int index = 0; index < DRIVER_LED_TOTAL; index++ ) {
        bool enabled = true;
        // This only caches it for later
        IS31FL3741_set_led_control_register( index, enabled, enabled, enabled );
    }
    // This actually updates the LED drivers
    IS31FL3741_update_scaling_buffers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
}

static void flush( void )
{
    IS31FL3741_update_pwm_buffers( DRIVER_ADDR_1, DRIVER_ADDR_2 );
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = IS31FL3741_set_color,
    .set_color_all = IS31FL3741_set_color_all,
};
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0,  CS3_SW1,   CS2_SW1,   CS1_SW1},
    {0,  CS3_SW3,   CS2_SW3,   CS1_SW3},
    {0,  CS3_SW4,   CS2_SW4,   CS1_SW4},
    {0,  CS3_SW5,   CS2_SW5,   CS1_SW5},
    {0,  CS3_SW6,   CS2_SW6,   CS1_SW6},
    {1,  CS3_SW7,   CS2_SW7,   CS1_SW7},
    {1,  CS3_SW8,   CS2_SW8,   CS1_SW8},
    {1,  CS3_SW9,   CS2_SW9,   CS1_SW9},

    {0, CS15_SW1,  CS14_SW1,  CS13_SW1},
    {0, CS15_SW2,  CS14_SW2,  CS13_SW2},
    {0, CS15_SW3,  CS14_SW3,  CS13_SW3},
    {0, CS15_SW4,  CS14_SW4,  CS13_SW4},
    {0, CS15_SW5,  CS14_SW5,  CS13_SW5},
    {0, CS15_SW6,  CS14_SW6,  CS13_SW6},
    {1, CS15_SW7,  CS14_SW7,  CS13_SW7},
    {1, CS15_SW8,  CS14_SW8,  CS13_SW8},
    {1, CS15_SW9,  CS14_SW9,  CS13_SW9},

    {0,  CS6_SW1,   CS5_SW1,   CS4_SW1},
    {0,  CS6_SW3,   CS5_SW3,   CS4_SW3},
    {0,  CS6_SW4,   CS5_SW4,   CS4_SW4},
    {0,  CS6_SW5,   CS5_SW5,   CS4_SW5},
    {0,  CS6_SW6,   CS5_SW6,   CS4_SW6},
    {1,  CS6_SW7,   CS5_SW7,   CS4_SW7},
    {1,  CS6_SW8,   CS5_SW8,   CS4_SW8},

    {0, CS18_SW1,  CS17_SW1,  CS16_SW1},
    {0, CS18_SW2,  CS17_SW2,  CS16_SW2},
    {0, CS18_SW3,  CS17_SW3,  CS16_SW3},
    {0, CS18_SW4,  CS17_SW4,  CS16_SW4},
    {0, CS18_SW5,  CS17_SW5,  CS16_SW5},
    {0, CS18_SW6,  CS17_SW6,  CS16_SW6},
    {1, CS18_SW7,  CS17_SW7,  CS16_SW7},
    {1, CS18_SW9,  CS17_SW9,  CS16_SW9},

    {0, CS21_SW1,  CS20_SW1,  CS19_SW1},
    {0, CS21_SW2,  CS20_SW2,  CS19_SW2},
    {0, CS21_SW3,  CS20_SW3,  CS19_SW3},
    {0, CS21_SW4,  CS20_SW4,  CS19_SW4},
    {0, CS21_SW5,  CS20_SW5,  CS19_SW5},
    {0, CS21_SW6,  CS20_SW6,  CS19_SW6},
    {1, CS21_SW7,  CS20_SW7,  CS19_SW7},
    {1, CS21_SW8,  CS20_SW8,  CS19_SW8},
    {1, CS21_SW9,  CS20_SW9,  CS19_SW9},

    {0, CS12_SW1,  CS11_SW1,  CS10_SW1},
    {0, CS12_SW3,  CS11_SW3,  CS10_SW3},
    {0, CS12_SW4,  CS11_SW4,  CS10_SW4},
    {0, CS12_SW5,  CS11_SW5,  CS10_SW5},
    {0, CS12_SW6,  CS11_SW6,  CS10_SW6},
    {1, CS12_SW7,  CS11_SW7,  CS10_SW7},
    {1, CS12_SW8,  CS11_SW8,  CS10_SW8},
    {1, CS12_SW9,  CS11_SW9,  CS10_SW9},

    {0, CS24_SW1,  CS23_SW1,  CS22_SW1},
    {0, CS24_SW2,  CS23_SW2,  CS22_SW2},
    {0, CS24_SW3,  CS23_SW3,  CS22_SW3},
    {0, CS24_SW4,  CS23_SW4,  CS22_SW4},
    {0, CS24_SW6,  CS23_SW6,  CS22_SW6},
    {1, CS24_SW7,  CS23_SW7,  CS22_SW7},
    {1, CS24_SW8,  CS23_SW8,  CS22_SW8},
    {1, CS24_SW9,  CS23_SW9,  CS22_SW9},

    {1, CS39_SW1,  CS38_SW1,  CS37_SW1},
    {1, CS39_SW3,  CS38_SW3,  CS37_SW3},
    {1, CS39_SW4,  CS38_SW4,  CS37_SW4},
    {1, CS39_SW5,  CS38_SW5,  CS37_SW5},
    {1, CS39_SW6,  CS38_SW6,  CS37_SW6},
    {1, CS39_SW7,  CS38_SW7,  CS37_SW7},
    {1, CS39_SW8,  CS38_SW8,  CS37_SW8},
    {1, CS39_SW9,  CS38_SW9,  CS37_SW9},

    {0, CS30_SW1,  CS29_SW1,  CS28_SW1},
    {0, CS30_SW2,  CS29_SW2,  CS28_SW2},
    {0, CS30_SW3,  CS29_SW3,  CS28_SW3},
    {0, CS30_SW4,  CS29_SW4,  CS28_SW4},
    {0, CS30_SW5,  CS29_SW5,  CS28_SW5},
    {0, CS30_SW6,  CS29_SW6,  CS28_SW6},
    {1, CS30_SW7,  CS29_SW7,  CS28_SW7},
    {1, CS30_SW8,  CS29_SW8,  CS28_SW8},
    {1, CS30_SW9,  CS29_SW9,  CS28_SW9},

    {1, CS36_SW1,  CS35_SW1,  CS34_SW1},
    {1, CS36_SW3,  CS35_SW3,  CS34_SW3},
    {1, CS36_SW4,  CS35_SW4,  CS34_SW4},
    {1, CS36_SW5,  CS35_SW5,  CS34_SW5},
    {1, CS36_SW7,  CS35_SW7,  CS34_SW7},
    {1, CS36_SW8,  CS35_SW8,  CS34_SW8},
    {1, CS36_SW9,  CS35_SW9,  CS34_SW9},
};
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL] = {
    /* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */
    {{0 | (0 << 4)}, {0, 0}, 1},
    {{0 | (1 << 4)}, {15, 0}, 0},
    {{0 | (2 << 4)}, {30, 0}, 0},
    {{0 | (3 << 4)}, {45, 0}, 0},
    {{0 | (4 << 4)}, {60, 0}, 0},
    {{0 | (5 << 4)}, {75, 0}, 0},
    {{0 | (6 << 4)}, {90, 0}, 0},
    {{0 | (7 << 4)}, {105, 0}, 0},

    {{0 | (8 << 4)}, {120, 0}, 1},
    {{0 | (9 << 4)}, {135, 0}, 0},
    {{0 | (10 << 4)}, {150, 0}, 0},
    {{0 | (11 << 4)}, {165, 0}, 0},
    {{0 | (12 << 4)}, {180, 0}, 0},
    {{0 | (13 << 4)}, {195, 0}, 0},
    {{0 | (14 << 4)}, {210, 0}, 0},
    {{0 | (14 << 4)}, {217, 0}, 0},
    {{0 | (15 << 4)}, {224, 0}, 1},

    {{1 | (0 << 4)}, {7, 0}, 1},
    {{1 | (1 << 4)}, {22, 0}, 0},
    {{1 | (2 << 4)}, {37, 0}, 0},
    {{1 | (3 << 4)}, {53, 0}, 0},
    {{1 | (4 << 4)}, {68, 0}, 0},
    {{1 | (5 << 4)}, {83, 0}, 0},
    {{1 | (6 << 4)}, {98, 0}, 0},

    {{1 | (8 << 4)}, {113, 0}, 0},
    {{1 | (9 << 4)}, {128, 0}, 0},
    {{1 | (10 << 4)}, {143, 0}, 0},
    {{1 | (11 << 4)}, {158, 0}, 0},
    {{1 | (12 << 4)}, {173, 0}, 0},
    {{1 | (13 << 4)}, {188, 0}, 0},
    {{1 | (14 << 4)}, {203, 0}, 0},
    {{1 | (15 << 4)}, {224, 0}, 1},

    {{2 | (0 << 4)}, {10, 0}, 1},
    {{2 | (1 << 4)}, {25, 0}, 0},
    {{2 | (2 << 4)}, {40, 0}, 0},
    {{2 | (3 << 4)}, {55, 0}, 0},
    {{2 | (4 << 4)}, {70, 0}, 0},
    {{2 | (5 << 4)}, {85, 0}, 0},
    {{2 | (6 << 4)}, {100, 0}, 0},

    {{2 | (8 << 4)}, {115, 0}, 0},
    {{2 | (9 << 4)}, {130, 0}, 0},
    {{2 | (10 << 4)}, {145, 0}, 0},
    {{2 | (11 << 4)}, {160, 0}, 0},
    {{2 | (12 << 4)}, {175, 0}, 0},
    {{2 | (13 << 4)}, {190, 0}, 0},
    {{2 | (14 << 4)}, {210, 0}, 1},
    {{2 | (14 << 4)}, {215, 0}, 1},
    {{2 | (15 << 4)}, {224, 0}, 1},

    {{3 | (0 << 4)}, {0, 0}, 1},
    {{3 | (1 << 4)}, {30, 0}, 0},
    {{3 | (2 << 4)}, {45, 0}, 0},
    {{3 | (3 << 4)}, {60, 0}, 0},
    {{3 | (4 << 4)}, {75, 0}, 0},
    {{3 | (5 << 4)}, {90, 0}, 0},
    {{3 | (6 << 4)}, {105, 0}, 0},
    {{3 | (7 << 4)}, {120, 0}, 0},

    {{3 | (8 << 4)}, {135, 0}, 0},
    {{3 | (9 << 4)}, {150, 0}, 0},
    {{3 | (10 << 4)}, {165, 0}, 0},
    {{3 | (11 << 4)}, {180, 0}, 0},
    {{3 | (13 << 4)}, {195, 0}, 0},
    {{3 | (13 << 4)}, {200, 0}, 1},
    {{3 | (14 << 4)}, {210, 0}, 1},
    {{3 | (15 << 4)}, {224, 0}, 1},

    {{4 | (0 << 4)}, {0, 0}, 1},
    {{3 | (0 << 4)}, {15, 0}, 1},
    {{4 | (1 << 4)}, {15, 0}, 1},
    {{4 | (2 << 4)}, {30, 0}, 1},
    {{4 | (3 << 4)}, {45, 0}, 0},
    {{4 | (4 << 4)}, {60, 0}, 0},
    {{4 | (6 << 4)}, {75, 0}, 0},
    {{4 | (6 << 4)}, {90, 0}, 0},

    {{4 | (7 << 4)}, {105, 0}, 0},
    {{4 | (8 << 4)}, {120, 0}, 0},
    {{4 | (10 << 4)}, {135, 0}, 1},
    {{4 | (11 << 4)}, {150, 0}, 1},
    {{4 | (11 << 4)}, {165, 0}, 1},
    {{4 | (12 << 4)}, {180, 0}, 1},
    {{4 | (13 << 4)}, {195, 0}, 1},
    {{4 | (14 << 4)}, {210, 0}, 1},
    {{4 | (15 << 4)}, {224, 0}, 1},
};
#endif
