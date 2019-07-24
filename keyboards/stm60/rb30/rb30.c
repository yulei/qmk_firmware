/**
 * rb30.c
 */

#include "rb30.h"

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
// left CB
    {0, C1_9,   C3_10,  C4_10},
    {0, C1_10,  C2_10,  C4_11},
    {0, C1_11,  C2_11,  C3_11},
    {0, C1_12,  C2_12,  C3_12},
    {0, C1_13,  C2_13,  C3_13},
    {0, C1_14,  C2_14,  C3_14},
    {0, C1_15,  C2_15,  C3_15},
    {0, C1_16,  C2_16,  C3_16},

 //   {0, C5_9,   C4_9,   C6_9},
 //   {0, C5_16,  C4_16,  C6_16},

    {0, C9_9,   C8_9,   C7_9},
    {0, C9_10,  C8_10,  C7_10},
    {0, C9_11,  C8_11,  C7_11},
    {0, C9_12,  C8_12,  C7_12},
    {0, C9_13,  C8_13,  C7_13},
    {0, C9_14,  C8_14,  C7_14},
    {0, C9_15,  C8_15,  C6_14},
    {0, C9_16,  C7_15,  C6_15},
// left CA
    {0, C1_1,   C3_2,   C4_2},
    {0, C1_2,   C2_2,   C4_3},
    {0, C1_3,   C2_3,   C3_3},
    {0, C1_4,   C2_4,   C3_4},
    {0, C1_5,   C2_5,   C3_5},
    {0, C1_6,   C2_6,   C3_6},
    {0, C1_7,   C2_7,   C3_7},
    {0, C1_8,   C2_8,   C3_8},

//    {0, C5_1,   C4_1,   C6_1},
//    {0, C5_8,   C4_8,   C6_8},

    {0, C9_1,   C8_1,   C7_1},
    {0, C9_2,   C8_2,   C7_2},
    {0, C9_3,   C8_3,   C7_3},
    {0, C9_4,   C8_4,   C7_4},
    {0, C9_5,   C8_5,   C7_5},
    {0, C9_6,   C8_6,   C7_6},
    {0, C9_7,   C8_7,   C6_6},
//    {0, C9_8,   C7_7,   C6_7},
};

led_config_t g_led_config = {
    {
        {  0,  1,      2,   3,   4,   5,   6,   7,   8,   NO_LED, 9},
        {  11, 12,     13,  14,  15,  16,  17,  18,  19,  20,     10},
        {  22, NO_LED, 23,  24,  25,  26,  27,  28,  29,  30,     21}
    },
    {
        {  0,   0}, {  22,   0}, {  44,   0}, {  66,   0}, {  88,   0}, { 110,   0}, { 132,   0}, { 154,   0}, { 176,   0}, { 198,   0}, { 220,  0},
        {  0,  32}, {  22,  32}, {  44,  32}, {  66,  32}, {  88,  32}, { 110,  32}, { 132,  32}, { 154,  32}, { 176,  32}, { 198,  32}, { 223, 32},
        {  0,  63}, {  22,  63}, {  44,  63}, {  66,  63}, {  88,  63}, { 110,  63}, { 132,  63}, { 154,  63}, { 176,  63}
    },

    {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 1,
    }
};
#endif
#ifdef WEBUSB_ENABLE
#include "webusb.h"
#include "dynamic_keymap.h"

#define WEBUSB_KEYCOUNT  31
#define WEBUSB_LAYERCOUNT 2
typedef struct {
    uint8_t row;
    uint8_t col;
} webusb_pos_t;
static webusb_pos_t webusb_keymap[] = {
    {0, 0},
    {0, 1},
    {0, 2},
    {0, 3},
    {0, 4},
    {0, 5},
    {0, 6},
    {0, 7},
    {0, 8},
    {0, 10},
    {1, 10},
    {2, 10},

    {1, 0},
    {1, 1},
    {1, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    {1, 6},
    {1, 7},
    {1, 8},
    {1, 9},
    {2, 10},

    {2, 0},
    {2, 2},
    {2, 3},
    {2, 4},
    {2, 5},
    {2, 6},
    {2, 7},
    {2, 8},
};

#define CMD_BUFFER_SIZE     32
#define CMD_ERROR_MASK      0x80    // the highest bit of command byte will be set while in error
#define CMD_VERSION         0x01    // current verison was 1
#define CMD_GET_KEYBOARD    0x02    // get keyboard information[key count][row count][column count][layer count]
#define CMD_GET_POSITION    0x03    // get the key positon[key index][row index][column index]
#define CMD_SET_KEYCODE     0x04    // set the keycode[layer][row index][column index][keycode(2 bytes)]
#define CMD_GET_KEYCODE     0x05    // get the keycode[layer][row index][column index][keycode(2 bytes)]

void webusb_receive( uint8_t *data, uint8_t length )
{
    //uint8_t *cmd_ver  = &(data[0]);
    uint8_t *cmd_type = &(data[1]);
    uint8_t *cmd_data = &(data[2]);
    switch (*cmd_type) {
    case CMD_GET_KEYBOARD:
        cmd_data[0] = WEBUSB_KEYCOUNT;
        cmd_data[1] = MATRIX_ROWS;
        cmd_data[2] = MATRIX_COLS;
        cmd_data[3] = WEBUSB_LAYERCOUNT;
        break;
    case CMD_GET_POSITION:
        cmd_data[1] = webusb_keymap[cmd_data[0]].row;
        cmd_data[2] = webusb_keymap[cmd_data[1]].col;
        break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case CMD_GET_KEYCODE:
        {
            uint16_t keycode = dynamic_keymap_get_keycode(cmd_data[0], cmd_data[1], cmd_data[2]);
            cmd_data[3]  = keycode >> 8;
            cmd_data[4]  = keycode & 0xFF;
        }
        break;
    case CMD_SET_KEYCODE:
        dynamic_keymap_set_keycode(cmd_data[0], cmd_data[1], cmd_data[2], (cmd_data[3] << 8) | cmd_data[4]);
        break;
#endif
    default:
      *cmd_type |= CMD_ERROR_MASK;
      break;
	}

	// Return same buffer with values changed
	webusb_send( data, length );
}

#endif
