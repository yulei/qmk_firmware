/*
 * light weight WS2812 lib V2.0b
 *
 * Controls WS2811/WS2812/WS2812B RGB-LEDs
 * Author: Tim (cpldcpu@gmail.com)
 *
 * Jan 18th, 2014  v2.0b Initial Version
 * Nov 29th, 2015  v2.3  Added SK6812RGBW support
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

/**
 * indicator.c
 */

#include "dp60.h"

#include "rgblight_list.h"
#include "rgblight.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2811/2812 protocol.
*/

// Timing in ns
#define w_zeropulse 350
#define w_onepulse 900
#define w_totalperiod 1250

// Fixed cycles used by the inner loop
#define w_fixedlow 2
#define w_fixedhigh 4
#define w_fixedtotal 8

// Insert NOPs to match the timing, if possible
#define w_zerocycles (((F_CPU / 1000) * w_zeropulse) / 1000000)
#define w_onecycles (((F_CPU / 1000) * w_onepulse + 500000) / 1000000)
#define w_totalcycles (((F_CPU / 1000) * w_totalperiod + 500000) / 1000000)

// w1 - nops between rising edge and falling edge - low
#define w1 (w_zerocycles - w_fixedlow)
// w2   nops between fe low and fe high
#define w2 (w_onecycles - w_fixedhigh - w1)
// w3   nops to complete loop
#define w3 (w_totalcycles - w_fixedtotal - w1 - w2)

#if w1 > 0
#    define w1_nops w1
#else
#    define w1_nops 0
#endif

// The only critical timing parameter is the minimum pulse length of the "0"
// Warn or throw error if this timing can not be met with current F_CPU settings.
#define w_lowtime ((w1_nops + w_fixedlow) * 1000000) / (F_CPU / 1000)
#if w_lowtime > 550
#    error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime > 450
#    warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
#    warning "Please consider a higher clockspeed, if possible"
#endif

#if w2 > 0
#    define w2_nops w2
#else
#    define w2_nops 0
#endif

#if w3 > 0
#    define w3_nops w3
#else
#    define w3_nops 0
#endif

#define w_nop1 "nop      \n\t"
#define w_nop2 "rjmp .+0 \n\t"
#define w_nop4 w_nop2 w_nop2
#define w_nop8 w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8
void indicator_sendarray_mask_ind(uint8_t *data, uint16_t datlen, uint8_t maskhi) {
    uint8_t curbyte, ctr, masklo;
    uint8_t sreg_prev;

    // masklo  =~maskhi&ws2812_PORTREG;
    // maskhi |=        ws2812_PORTREG;
    masklo = ~maskhi & _SFR_IO8((RGB_INDICATOR_PIN >> 4) + 2);
    maskhi |= _SFR_IO8((RGB_INDICATOR_PIN >> 4) + 2);
    sreg_prev = SREG;
    cli();

    while (datlen--) {
        curbyte = (*data++);

        asm volatile("       ldi   %0,8  \n\t"
                     "loop%=:            \n\t"
                     "       out   %2,%3 \n\t"  //  '1' [01] '0' [01] - re
#if (w1_nops & 1)
                     w_nop1
#endif
#if (w1_nops & 2)
                         w_nop2
#endif
#if (w1_nops & 4)
                             w_nop4
#endif
#if (w1_nops & 8)
                                 w_nop8
#endif
#if (w1_nops & 16)
                                     w_nop16
#endif
                     "       sbrs  %1,7  \n\t"  //  '1' [03] '0' [02]
                     "       out   %2,%4 \n\t"  //  '1' [--] '0' [03] - fe-low
                     "       lsl   %1    \n\t"  //  '1' [04] '0' [04]
#if (w2_nops & 1)
                     w_nop1
#endif
#if (w2_nops & 2)
                         w_nop2
#endif
#if (w2_nops & 4)
                             w_nop4
#endif
#if (w2_nops & 8)
                                 w_nop8
#endif
#if (w2_nops & 16)
                                     w_nop16
#endif
                     "       out   %2,%4 \n\t"  //  '1' [+1] '0' [+1] - fe-high
#if (w3_nops & 1)
                     w_nop1
#endif
#if (w3_nops & 2)
                         w_nop2
#endif
#if (w3_nops & 4)
                             w_nop4
#endif
#if (w3_nops & 8)
                                 w_nop8
#endif
#if (w3_nops & 16)
                                     w_nop16
#endif

                     "       dec   %0    \n\t"  //  '1' [+2] '0' [+2]
                     "       brne  loop%=\n\t"  //  '1' [+3] '0' [+4]
                     : "=&d"(ctr)
                     : "r"(curbyte), "I"(_SFR_IO_ADDR(_SFR_IO8((RGB_INDICATOR_PIN >> 4) + 2))), "r"(maskhi), "r"(masklo));
    }

    SREG = sreg_prev;
}

const LED_TYPE PROGMEM led_colors[RGB_INDICATOR_NUM] = {
    {RGB_RED},
    {RGB_GREEN},
    {RGB_BLUE},

    {RGB_PURPLE},
    {RGB_CYAN},
    {RGB_YELLOW},
    {RGB_PINK},
    {RGB_ORANGE},
};

static LED_TYPE indicator_leds[RGB_INDICATOR_NUM] ={{0,0,0}};

void indicator_leds_set(void)
{
    uint8_t pinmask = _BV(RGB_INDICATOR_PIN & 0xF);
    _SFR_IO8((RGB_INDICATOR_PIN >> 4) + 1) |= pinmask;
    indicator_sendarray_mask_ind((uint8_t *)(&indicator_leds[0]), RGB_INDICATOR_NUM * sizeof(LED_TYPE), pinmask);
    _delay_us(50);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            indicator_leds[0].r = led_colors[0].r;
            indicator_leds[0].g = led_colors[0].g;
            indicator_leds[0].b = led_colors[0].b;
        } else {
            indicator_leds[0].r = 0;
            indicator_leds[0].g = 0;
            indicator_leds[0].b = 0;
        }
        if (led_state.scroll_lock) {
            indicator_leds[1].r = led_colors[1].r;
            indicator_leds[1].g = led_colors[1].g;
            indicator_leds[1].b = led_colors[1].b;
        } else {
            indicator_leds[1].r = 0;
            indicator_leds[1].g = 0;
            indicator_leds[1].b = 0;
        }
        if (led_state.num_lock) {
            indicator_leds[2].r = led_colors[2].r;
            indicator_leds[2].g = led_colors[2].g;
            indicator_leds[2].b = led_colors[2].b;
        } else {
            indicator_leds[2].r = 0;
            indicator_leds[2].g = 0;
            indicator_leds[2].b = 0;
        }
        indicator_leds_set();
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    for (int i = 0; i < 5; i++) {
        if (layer_state_cmp(state, i+1)) {
            indicator_leds[i+3].r = led_colors[i+3].r;
            indicator_leds[i+3].g = led_colors[i+3].g;
            indicator_leds[i+3].b = led_colors[i+3].b;
        } else {
            indicator_leds[i+3].r = 0;
            indicator_leds[i+3].g = 0;
            indicator_leds[i+3].b = 0;
        }
    }
    indicator_leds_set();
    return state;
}
