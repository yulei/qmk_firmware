#ifndef RGB_LEDS_H__
#define RGB_LEDS_H__

#include <stdint.h>

int map_key_index(int row, int col);
void set_capslock(uint8_t on, uint8_t r, uint8_t g, uint8_t b);

void rgb_init(void);
void rgb_shutdown(void);

void update_rgb_leds(void);

#define LOGO_STATE_OFF  0x00
#define LOGO_STATE_ON   0x01

void rgb_set_logo_state(uint8_t state);

#endif
