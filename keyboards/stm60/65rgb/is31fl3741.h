/**
 * is31fl3741.h
 */
/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 astro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct is31_led {
  uint8_t driver:2;  // use driver to represent the register page
  uint8_t r;
  uint8_t g;
  uint8_t b;
} __attribute__((packed)) is31_led;

extern const is31_led g_is31_leds[DRIVER_LED_TOTAL];

void IS31FL3741_init( uint8_t addr );
void IS31FL3741_write_register( uint8_t addr, uint8_t reg, uint8_t data );
void IS31FL3741_write_pwm_buffer( uint8_t addr, uint8_t page, uint8_t *pwm_buffer );
void IS31FL3741_write_scaling_buffer( uint8_t addr, uint8_t page, uint8_t *scaling_buffer );

void IS31FL3741_set_color( int index, uint8_t red, uint8_t green, uint8_t blue );
void IS31FL3741_set_color_all( uint8_t red, uint8_t green, uint8_t blue );

void IS31FL3741_set_led_control_register( uint8_t index, bool red, bool green, bool blue );

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3741_update_pwm_buffers( uint8_t addr1, uint8_t addr2 );
void IS31FL3741_update_scaling_buffers( uint8_t addr1, uint8_t addr2 );

// pwm page 0
#define CS1_SW1  0x00
#define CS2_SW1  0x01
#define CS3_SW1  0x02
#define CS4_SW1  0x03
#define CS5_SW1  0x04
#define CS6_SW1  0x05
#define CS7_SW1  0x06
#define CS8_SW1  0x07
#define CS9_SW1  0x08
#define CS10_SW1  0x09
#define CS11_SW1  0x0A
#define CS12_SW1  0x0B
#define CS13_SW1  0x0C
#define CS14_SW1  0x0D
#define CS15_SW1  0x0E
#define CS16_SW1  0x0F
#define CS17_SW1  0x10
#define CS18_SW1  0x11
#define CS19_SW1  0x12
#define CS20_SW1  0x13
#define CS21_SW1  0x14
#define CS22_SW1  0x15
#define CS23_SW1  0x16
#define CS24_SW1  0x17
#define CS25_SW1  0x18
#define CS26_SW1  0x19
#define CS27_SW1  0x1A
#define CS28_SW1  0x1B
#define CS29_SW1  0x1C
#define CS30_SW1  0x1D

#define CS1_SW2  0x1E
#define CS2_SW2  0x1F
#define CS3_SW2  0x20
#define CS4_SW2  0x21
#define CS5_SW2  0x22
#define CS6_SW2  0x23
#define CS7_SW2  0x24
#define CS8_SW2  0x25
#define CS9_SW2  0x26
#define CS10_SW2  0x27
#define CS11_SW2  0x28
#define CS12_SW2  0x29
#define CS13_SW2  0x2A
#define CS14_SW2  0x2B
#define CS15_SW2  0x2C
#define CS16_SW2  0x2D
#define CS17_SW2  0x2E
#define CS18_SW2  0x2F
#define CS19_SW2  0x30
#define CS20_SW2  0x31
#define CS21_SW2  0x32
#define CS22_SW2  0x33
#define CS23_SW2  0x34
#define CS24_SW2  0x35
#define CS25_SW2  0x36
#define CS26_SW2  0x37
#define CS27_SW2  0x38
#define CS28_SW2  0x39
#define CS29_SW2  0x3A
#define CS30_SW2  0x3B

#define CS1_SW3  0x3C
#define CS2_SW3  0x3D
#define CS3_SW3  0x3E
#define CS4_SW3  0x3F
#define CS5_SW3  0x40
#define CS6_SW3  0x41
#define CS7_SW3  0x42
#define CS8_SW3  0x43
#define CS9_SW3  0x44
#define CS10_SW3  0x45
#define CS11_SW3  0x46
#define CS12_SW3  0x47
#define CS13_SW3  0x48
#define CS14_SW3  0x49
#define CS15_SW3  0x4A
#define CS16_SW3  0x4B
#define CS17_SW3  0x4C
#define CS18_SW3  0x4D
#define CS19_SW3  0x4E
#define CS20_SW3  0x4F
#define CS21_SW3  0x50
#define CS22_SW3  0x51
#define CS23_SW3  0x52
#define CS24_SW3  0x53
#define CS25_SW3  0x54
#define CS26_SW3  0x55
#define CS27_SW3  0x56
#define CS28_SW3  0x57
#define CS29_SW3  0x58
#define CS30_SW3  0x59

#define CS1_SW4  0x5A
#define CS2_SW4  0x5B
#define CS3_SW4  0x5C
#define CS4_SW4  0x5D
#define CS5_SW4  0x5E
#define CS6_SW4  0x5F
#define CS7_SW4  0x60
#define CS8_SW4  0x61
#define CS9_SW4  0x62
#define CS10_SW4  0x63
#define CS11_SW4  0x64
#define CS12_SW4  0x65
#define CS13_SW4  0x66
#define CS14_SW4  0x67
#define CS15_SW4  0x68
#define CS16_SW4  0x69
#define CS17_SW4  0x6A
#define CS18_SW4  0x6B
#define CS19_SW4  0x6C
#define CS20_SW4  0x6D
#define CS21_SW4  0x6E
#define CS22_SW4  0x6F
#define CS23_SW4  0x70
#define CS24_SW4  0x71
#define CS25_SW4  0x72
#define CS26_SW4  0x73
#define CS27_SW4  0x74
#define CS28_SW4  0x75
#define CS29_SW4  0x76
#define CS30_SW4  0x77

#define CS1_SW5  0x78
#define CS2_SW5  0x79
#define CS3_SW5  0x7A
#define CS4_SW5  0x7B
#define CS5_SW5  0x7C
#define CS6_SW5  0x7D
#define CS7_SW5  0x7E
#define CS8_SW5  0x7F
#define CS9_SW5  0x80
#define CS10_SW5  0x81
#define CS11_SW5  0x82
#define CS12_SW5  0x83
#define CS13_SW5  0x84
#define CS14_SW5  0x85
#define CS15_SW5  0x86
#define CS16_SW5  0x87
#define CS17_SW5  0x88
#define CS18_SW5  0x89
#define CS19_SW5  0x8A
#define CS20_SW5  0x8B
#define CS21_SW5  0x8C
#define CS22_SW5  0x8D
#define CS23_SW5  0x8E
#define CS24_SW5  0x8F
#define CS25_SW5  0x90
#define CS26_SW5  0x91
#define CS27_SW5  0x92
#define CS28_SW5  0x93
#define CS29_SW5  0x94
#define CS30_SW5  0x95

#define CS1_SW6  0x96
#define CS2_SW6  0x97
#define CS3_SW6  0x98
#define CS4_SW6  0x99
#define CS5_SW6  0x9A
#define CS6_SW6  0x9B
#define CS7_SW6  0x9C
#define CS8_SW6  0x9D
#define CS9_SW6  0x9E
#define CS10_SW6  0x9F
#define CS11_SW6  0xA0
#define CS12_SW6  0xA1
#define CS13_SW6  0xA2
#define CS14_SW6  0xA3
#define CS15_SW6  0xA4
#define CS16_SW6  0xA5
#define CS17_SW6  0xA6
#define CS18_SW6  0xA7
#define CS19_SW6  0xA8
#define CS20_SW6  0xA9
#define CS21_SW6  0xAA
#define CS22_SW6  0xAB
#define CS23_SW6  0xAC
#define CS24_SW6  0xAD
#define CS25_SW6  0xAE
#define CS26_SW6  0xAF
#define CS27_SW6  0xB0
#define CS28_SW6  0xB1
#define CS29_SW6  0xB2
#define CS30_SW6  0xB3

// pwm page 1
#define CS1_SW7  0x00
#define CS2_SW7  0x01
#define CS3_SW7  0x02
#define CS4_SW7  0x03
#define CS5_SW7  0x04
#define CS6_SW7  0x05
#define CS7_SW7  0x06
#define CS8_SW7  0x07
#define CS9_SW7  0x08
#define CS10_SW7  0x09
#define CS11_SW7  0x0A
#define CS12_SW7  0x0B
#define CS13_SW7  0x0C
#define CS14_SW7  0x0D
#define CS15_SW7  0x0E
#define CS16_SW7  0x0F
#define CS17_SW7  0x10
#define CS18_SW7  0x11
#define CS19_SW7  0x12
#define CS20_SW7  0x13
#define CS21_SW7  0x14
#define CS22_SW7  0x15
#define CS23_SW7  0x16
#define CS24_SW7  0x17
#define CS25_SW7  0x18
#define CS26_SW7  0x19
#define CS27_SW7  0x1A
#define CS28_SW7  0x1B
#define CS29_SW7  0x1C
#define CS30_SW7  0x1D

#define CS1_SW8  0x1E
#define CS2_SW8  0x1F
#define CS3_SW8  0x20
#define CS4_SW8  0x21
#define CS5_SW8  0x22
#define CS6_SW8  0x23
#define CS7_SW8  0x24
#define CS8_SW8  0x25
#define CS9_SW8  0x26
#define CS10_SW8  0x27
#define CS11_SW8  0x28
#define CS12_SW8  0x29
#define CS13_SW8  0x2A
#define CS14_SW8  0x2B
#define CS15_SW8  0x2C
#define CS16_SW8  0x2D
#define CS17_SW8  0x2E
#define CS18_SW8  0x2F
#define CS19_SW8  0x30
#define CS20_SW8  0x31
#define CS21_SW8  0x32
#define CS22_SW8  0x33
#define CS23_SW8  0x34
#define CS24_SW8  0x35
#define CS25_SW8  0x36
#define CS26_SW8  0x37
#define CS27_SW8  0x38
#define CS28_SW8  0x39
#define CS29_SW8  0x3A
#define CS30_SW8  0x3B

#define CS1_SW9  0x3C
#define CS2_SW9  0x3D
#define CS3_SW9  0x3E
#define CS4_SW9  0x3F
#define CS5_SW9  0x40
#define CS6_SW9  0x41
#define CS7_SW9  0x42
#define CS8_SW9  0x43
#define CS9_SW9  0x44
#define CS10_SW9  0x45
#define CS11_SW9  0x46
#define CS12_SW9  0x47
#define CS13_SW9  0x48
#define CS14_SW9  0x49
#define CS15_SW9  0x4A
#define CS16_SW9  0x4B
#define CS17_SW9  0x4C
#define CS18_SW9  0x4D
#define CS19_SW9  0x4E
#define CS20_SW9  0x4F
#define CS21_SW9  0x50
#define CS22_SW9  0x51
#define CS23_SW9  0x52
#define CS24_SW9  0x53
#define CS25_SW9  0x54
#define CS26_SW9  0x55
#define CS27_SW9  0x56
#define CS28_SW9  0x57
#define CS29_SW9  0x58
#define CS30_SW9  0x59

#define CS31_SW1  0x5A
#define CS32_SW1  0x5B
#define CS33_SW1  0x5C
#define CS34_SW1  0x5D
#define CS35_SW1  0x5E
#define CS36_SW1  0x5F
#define CS37_SW1  0x60
#define CS38_SW1  0x61
#define CS39_SW1  0x62

#define CS31_SW2  0x63
#define CS32_SW2  0x64
#define CS33_SW2  0x65
#define CS34_SW2  0x66
#define CS35_SW2  0x67
#define CS36_SW2  0x68
#define CS37_SW2  0x69
#define CS38_SW2  0x6A
#define CS39_SW2  0x6B

#define CS31_SW3  0x6C
#define CS32_SW3  0x6D
#define CS33_SW3  0x6E
#define CS34_SW3  0x6F
#define CS35_SW3  0x70
#define CS36_SW3  0x71
#define CS37_SW3  0x72
#define CS38_SW3  0x73
#define CS39_SW3  0x74

#define CS31_SW4  0x75
#define CS32_SW4  0x76
#define CS33_SW4  0x77
#define CS34_SW4  0x78
#define CS35_SW4  0x79
#define CS36_SW4  0x7A
#define CS37_SW4  0x7B
#define CS38_SW4  0x7C
#define CS39_SW4  0x7D

#define CS31_SW5  0x7E
#define CS32_SW5  0x7F
#define CS33_SW5  0x80
#define CS34_SW5  0x81
#define CS35_SW5  0x82
#define CS36_SW5  0x83
#define CS37_SW5  0x84
#define CS38_SW5  0x85
#define CS39_SW5  0x86

#define CS31_SW6  0x87
#define CS32_SW6  0x88
#define CS33_SW6  0x89
#define CS34_SW6  0x8A
#define CS35_SW6  0x8B
#define CS36_SW6  0x8C
#define CS37_SW6  0x8D
#define CS38_SW6  0x8E
#define CS39_SW6  0x8F

#define CS31_SW7  0x90
#define CS32_SW7  0x91
#define CS33_SW7  0x92
#define CS34_SW7  0x93
#define CS35_SW7  0x94
#define CS36_SW7  0x95
#define CS37_SW7  0x96
#define CS38_SW7  0x97
#define CS39_SW7  0x98

#define CS31_SW8  0x99
#define CS32_SW8  0x9A
#define CS33_SW8  0x9B
#define CS34_SW8  0x9C
#define CS35_SW8  0x9D
#define CS36_SW8  0x9E
#define CS37_SW8  0x9F
#define CS38_SW8  0xA0
#define CS39_SW8  0xA1

#define CS31_SW9  0xA2
#define CS32_SW9  0xA3
#define CS33_SW9  0xA4
#define CS34_SW9  0xA5
#define CS35_SW9  0xA6
#define CS36_SW9  0xA7
#define CS37_SW9  0xA8
#define CS38_SW9  0xA9
#define CS39_SW9  0xAA
