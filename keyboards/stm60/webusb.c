/**
 * webusb.c
 */

#ifdef WEBUSB_ENABLE
#include "webusb.h"
#include "dynamic_keymap.h"

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
        cmd_data[2] = webusb_keymap[cmd_data[0]].col;
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
