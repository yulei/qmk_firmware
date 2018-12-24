/*
 * LEDDriver.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Omri Iluz
 */

#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

#include <stdint.h>
#include "rgblight_types.h"

void ws2812_init(void);
void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);

#endif /* LEDDRIVER_H_ */
