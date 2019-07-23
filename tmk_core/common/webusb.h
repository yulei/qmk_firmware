/**
 * webusb.h
 */
#pragma once

#include <stdint.h>

void webusb_receive( uint8_t *data, uint8_t length );
void webusb_send( uint8_t *data, uint8_t length );
