/**
 * stm60.c
 */

#include "stm60.h"

#include "rgblight.h"

#include "indicator_leds.h"
#include "ws2812.h"
#include "rgb_backlight.h"

extern rgblight_config_t rgblight_config;

void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds)
{
  for (uint16_t i = 0; i < leds; i++) {
    ws2812_write_led(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
  }
}

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }
    ws2812_setleds(led, RGBLED_NUM);
}
/*
void matrix_init_user(void) {
  indicator_leds_init();
  ws2812_init();
  //rb_init();
}

static void test_ws2812(void)
{
  uint8_t r, g, b;
  for ( uint32_t i=0; i< WS2812_LED_N; i++){
    r = rand()%256;
    g = rand()%256;
    b = rand()%256;
    ws2812_write_led(i, r, g, b);
  }
}

void matrix_scan_user(void)
{
  //test_ws2812();
  rgblight_task();
}

void matrix_init_kb(void)
{
  matrix_init_user();
}

void matrix_scan_kb(void)
{
  matrix_scan_user();
}*/
