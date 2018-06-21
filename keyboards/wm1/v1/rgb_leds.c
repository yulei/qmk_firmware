/**
 * rgb_leds.c
 */

#include <avr/io.h>
#include <print.h>
#include "rgb_leds.h"
#include "is31fl3236.h"
#include "is31fl3733.h"
#include "i2c_master.h"
#include "led_tables.h"

#define LOGO_U_INDEX    6 
#define LOGO_L_INDEX    7
#define LOGO_R_INDEX    8
#define LOGO_COLOR_B    19//236//19
#define LOGO_COLOR_R    149//149
#define LOGO_COLOR_G    0//255//0


void rgb_init(void)
{
    i2c_init();
    is3236_init();
//    is3733_init();
}

void rgb_set_logo_state(uint8_t state)
{
    switch (state) { 
        case LOGO_STATE_OFF: 
            is3236_set_led_state(LOGO_U_INDEX, 0, 0);
            is3236_set_led_state(LOGO_L_INDEX, 0, 0);
            is3236_set_led_state(LOGO_R_INDEX, 0, 0);
            is3236_update();
            break;
        case LOGO_STATE_ON:
            is3236_set_led_state(LOGO_U_INDEX, 1, 0);
            is3236_set_led_state(LOGO_L_INDEX, 1, 0);
            is3236_set_led_state(LOGO_R_INDEX, 1, 0);
            /*is3236_set_led_pwm(LOGO_U_INDEX, 0xFF);
            is3236_set_led_pwm(LOGO_L_INDEX, 0xFF);
            is3236_set_led_pwm(LOGO_R_INDEX, 0xFF);
            */
            is3236_set_led_color(LOGO_U_INDEX, 
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_R]),
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_G]),
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_B]));
            is3236_set_led_color(LOGO_L_INDEX, 
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_R]),
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_G]),
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_B]));
            is3236_set_led_color(LOGO_R_INDEX, 
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_R]),
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_G]),
                    pgm_read_byte(&CIE1931_CURVE[LOGO_COLOR_B]));

            is3236_update();
            break;
        default:
            break;
    }
}
