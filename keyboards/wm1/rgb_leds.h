#ifndef RGB_LEDS_H__
#define RGB_LEDS_H__

#include <stdint.h>

int map_key_index(int row, int col);
void set_capslock(uint8_t on, uint8_t r, uint8_t g, uint8_t b);

void rgb_init();
void rgb_shutdown();

void update_rgb_leds();

#endif
