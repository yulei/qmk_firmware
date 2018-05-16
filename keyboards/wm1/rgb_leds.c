/**
 * rgb_leds.c
 */

#include <avr/io.h>
#include "rgb_leds.h"
#include "is31fl3236.h"

#define LOGO_U_INDEX    6 
#define LOGO_L_INDEX    7
#define LOGO_R_INDEX    8


void rgb_init(void)
{
    is3236_init();
}

void rgb_set_logo_state(uint8_t state)
{
    switch (state) {
    case LOGO_STATE_OFF: 
        break;
    case LOGO_STATE_ON:
        is3236_set_led_state(LOGO_U_INDEX, 1, 0);
        is3236_set_led_state(LOGO_L_INDEX, 1, 0);
        is3236_set_led_state(LOGO_R_INDEX, 1, 0);
        is3236_set_led_pwm(LOGO_U_INDEX, 0xFF);
        is3236_set_led_pwm(LOGO_L_INDEX, 0xFF);
        is3236_set_led_pwm(LOGO_R_INDEX, 0xFF);
        is3236_update();
        break;
    default:
        break;
    }
}
