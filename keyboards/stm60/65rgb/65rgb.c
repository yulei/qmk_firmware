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
const is31_led g_is31_leds[DRIVER_LED_TOTAL];
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
/* {row | col << 4}
 *    |           {x=0..224, y=0..64}
 *    |              |            modifier
 *    |              |         | */

#endif
