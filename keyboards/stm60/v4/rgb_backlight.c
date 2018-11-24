/**
 * rgb_backlight.c
 */

#include "rgb_backlight.h"
#include "is31fl3733.h"

int rb_init(void)
{
  is31fl3733_init();
  return 0;
}

/*
int rb_turn_on(void);
int rb_turn_off(void);
int rb_set_color(uint32_t col, uint32_t row, uint8_t r, uint8_t g, uint8_t b);
*/
