/**
 * is31fl3741.c
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
#ifdef RGB_MATRIX_ENABLE

#ifdef __AVR__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#else
#include "wait.h"
#endif

#include "is31fl3741.h"
#include <string.h>
#include "i2c_master.h"
#include "progmem.h"

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR represents A1:A0 of the 7-bit address.
// The result is: 0b01100(ADDR)
#define ISSI_ADDR_DEFAULT 0x30

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_COMMANDREGISTER_WRITELOCK 0xFE
#define ISSI_INTERRUPTMASKREGISTER 0xF0
#define ISSI_INTERRUPTSTATUSREGISTER 0xF1
#define ISSI_IDREGISTER 0xFC

#define ISSI_PAGE_PWM_0 0x00 // pwm page 0
#define ISSI_PAGE_PWM_1 0x01 // pwm page 1
#define ISSI_PAGE_SCALING_0 0x02 // scaling page 0
#define ISSI_PAGE_SCALING_1 0x03 // scaling page 1
#define ISSI_PAGE_FUNCTION 0x04 // function page

#define ISSI_REG_CONFIGURATION 0x00 // function page
#define ISSI_REG_GLOBALCURRENT 0x01 // function page
#define ISSI_REG_PULLUPDOWN 0x02 // function page
#define ISSI_REG_RESET 0x3F // function page

#ifndef ISSI_TIMEOUT
  #define ISSI_TIMEOUT 100
#endif

#ifndef ISSI_PERSISTENCE
  #define ISSI_PERSISTENCE 0
#endif

// Transfer buffer for TWITransmitData()
uint8_t g_twi_transfer_buffer[32];

// These buffers match the IS31FL3741 PWM registers.
// The scaling buffers match the LED current scaling registers.
uint8_t g_pwm_buffer[2][180];
bool g_pwm_buffer_update_required = false;

uint8_t g_scaling_buffer[2][180] = { { 0 }, { 0 }};
bool g_scaling_buffer_update_required = false;

void IS31FL3741_write_register( uint8_t addr, uint8_t reg, uint8_t data )
{
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;

  #if ISSI_PERSISTENCE > 0
    for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
      if (i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, ISSI_TIMEOUT) == 0)
        break;
    }
  #else
    i2c_transmit(addr << 1, g_twi_transfer_buffer, 2, ISSI_TIMEOUT);
  #endif
}

static void IS31FL3741_write_buffer(uint8_t addr, uint8_t reg, uint16_t total, uint16_t step, uint8_t* buffer)
{
  // assume page was ready
    // set the start register
    g_twi_transfer_buffer[0] = reg;

    for (int i = 0; i < total; i += step) {
      for (int j = 0; j < step; j++) {
        g_twi_transfer_buffer[1+j] = buffer[i + j];
      }

    #if ISSI_PERSISTENCE > 0
      for (uint8_t i = 0; i < ISSI_PERSISTENCE; i++) {
        if (i2c_transmit(addr << 1, g_twi_transfer_buffer, step+1, ISSI_TIMEOUT) == 0)
          break;
      }
    #else
      i2c_transmit(addr << 1, g_twi_transfer_buffer, step+1, ISSI_TIMEOUT);
    #endif
    }

}

void IS31FL3741_write_pwm_buffer( uint8_t addr, uint8_t page, uint8_t *pwm_buffer )
{
  if (page==ISSI_PAGE_PWM_0) {
    IS31FL3741_write_buffer(addr, 0, 180, 18, pwm_buffer);
  } else if (page==ISSI_PAGE_PWM_1) {
    IS31FL3741_write_buffer(addr, 0, 171, 19, pwm_buffer);
  }
}

void IS31FL3741_write_scaling_buffer( uint8_t addr, uint8_t page, uint8_t *scaling_buffer )
{
  if (page==ISSI_PAGE_SCALING_0) {
    IS31FL3741_write_buffer(addr, 0, 180, 18, scaling_buffer);
  } else if (page==ISSI_PAGE_SCALING_1) {
    IS31FL3741_write_buffer(addr, 0, 171, 19, scaling_buffer);
  }
}

void IS31FL3741_init( uint8_t addr )
{
    // In order to avoid the LEDs being driven with garbage data
    // in the LED driver's PWM registers, shutdown is enabled last.
    // Set up the mode and other settings, clear the PWM registers,
    // then disable software shutdown.

    // Unlock the command register.
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );

    // Select scaling page 0
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING_0);
    // Turn off page 0 LEDs.
    for ( int i = 0; i <= 180; i++ )
    {
        IS31FL3741_write_register( addr, i, 0);
    }

    // Unlock the command register.
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );

    // Select scaling page 1
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING_1);
    // Turn off page 0 LEDs.
    for ( int i = 0; i <= 171; i++ )
    {
        IS31FL3741_write_register( addr, i, 0);
    }

    // Unlock the command register.
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );

    // Select pwm page 0
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_0 );
    // Set PWM on all LEDs to 0
    for ( int i = 0; i <= 180; i++ )
    {
        IS31FL3741_write_register( addr, i, 0xff);
    }

    // Unlock the command register.
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );

    // Select pwm page 1
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_1 );
    // Set PWM on all LEDs to 0
    for ( int i = 0; i <= 171; i++ )
    {
        IS31FL3741_write_register( addr, i, 0xff);
    }

    // Unlock the command register.
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );

    // Select function page
    IS31FL3741_write_register( addr, ISSI_COMMANDREGISTER, ISSI_PAGE_FUNCTION );
    // Set global current to maximum.
    IS31FL3741_write_register( addr, ISSI_REG_GLOBALCURRENT, 0xFF );
    // Disable software shutdown and set H/L to 2.4/0.6.
    IS31FL3741_write_register( addr, ISSI_REG_CONFIGURATION, 0x03 );

    // Wait 10ms to ensure the device has woken up.
    #ifdef __AVR__
    _delay_ms( 10 );
    #else
    wait_ms(10);
    #endif
}

void IS31FL3741_set_color( int index, uint8_t red, uint8_t green, uint8_t blue )
{
    if ( index >= 0 && index < DRIVER_LED_TOTAL ) {
        is31_led led = g_is31_leds[index];

        g_pwm_buffer[led.driver][led.r] = red;
        g_pwm_buffer[led.driver][led.g] = green;
        g_pwm_buffer[led.driver][led.b] = blue;
        g_pwm_buffer_update_required = true;
    }
}

void IS31FL3741_set_color_all( uint8_t red, uint8_t green, uint8_t blue )
{
    for ( int i = 0; i < DRIVER_LED_TOTAL; i++ )
    {
        IS31FL3741_set_color( i, red, green, blue );
    }
}

void IS31FL3741_set_led_color(const is31_led *led, uint8_t r, uint8_t g, uint8_t b)
{
  g_pwm_buffer[led->driver][led->r] = r;
  g_pwm_buffer[led->driver][led->g] = g;
  g_pwm_buffer[led->driver][led->b] = b;
  g_pwm_buffer_update_required = true;
}

void IS31FL3741_set_led_scaling(const is31_led *led, uint8_t r, uint8_t g, uint8_t b)
{
  g_scaling_buffer[led->driver][led->r] = r;
  g_scaling_buffer[led->driver][led->g] = g;
  g_scaling_buffer[led->driver][led->b] = b;
  g_scaling_buffer_update_required = true;
}

void IS31FL3741_set_led_control_register( uint8_t index, bool red, bool green, bool blue )
{
    is31_led led = g_is31_leds[index];

    if ( red ) {
        g_scaling_buffer[led.driver][led.r] = 255;
    } else {
        g_scaling_buffer[led.driver][led.r] = 0;
    }
    if ( green ) {
        g_scaling_buffer[led.driver][led.g] = 255;
    } else {
        g_scaling_buffer[led.driver][led.g] = 0;
    }
    if ( blue ) {
        g_scaling_buffer[led.driver][led.b] = 255;
    } else {
        g_scaling_buffer[led.driver][led.b] = 0;
    }

    g_scaling_buffer_update_required = true;

}

void IS31FL3741_update_pwm_buffers( uint8_t addr1, uint8_t addr2 )
{
    if ( g_pwm_buffer_update_required )
    {
        // unlock and select pwm page 0
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_0 );
        IS31FL3741_write_pwm_buffer( addr1, ISSI_PAGE_PWM_0, g_pwm_buffer[0] );

        // unlock and select pwm page 1
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_PWM_1 );
        IS31FL3741_write_pwm_buffer( addr1, ISSI_PAGE_PWM_1, g_pwm_buffer[1] );
    }
    g_pwm_buffer_update_required = false;
}

void IS31FL3741_update_scaling_buffers( uint8_t addr1, uint8_t addr2 )
{
    if ( g_scaling_buffer_update_required )
    {
        // unlock and select scaling page 0
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING_0);
        IS31FL3741_write_scaling_buffer( addr1, ISSI_PAGE_SCALING_0, g_scaling_buffer[0] );

        // unlock and select scaling page 1
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER_WRITELOCK, 0xC5 );
        IS31FL3741_write_register( addr1, ISSI_COMMANDREGISTER, ISSI_PAGE_SCALING_1);
        IS31FL3741_write_scaling_buffer( addr1, ISSI_PAGE_SCALING_1, g_scaling_buffer[1] );
    }

    g_scaling_buffer_update_required = false;
}

#endif
