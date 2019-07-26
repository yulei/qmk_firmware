/**
 * webusb.h
 */
#pragma once

#include <stdint.h>
typedef struct {
    uint8_t row;
    uint8_t col;
} webusb_pos_t;

extern webusb_pos_t webusb_keymap[];

void webusb_receive( uint8_t *data, uint8_t length );
void webusb_send( uint8_t *data, uint8_t length );
