/**
 * stm60.c
 */

#include "stm60.h"

#include "rgblight.h"

#include "ws2812.h"

extern rgblight_config_t rgblight_config;

void rgblight_set(void) {
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }

}

uint8_t *o_fb;
void matrix_init_kb(void) {
  //ledDriverInit(2, GPIOB, PAL_PORT_BIT(9), &o_fb);
  ws2812_init();
  //testPatternFB(o_fb);

	matrix_init_user();
}

static void test_ws2812(void)
{
  //uint8_t r, g, b;
  for ( uint32_t i=0; i< WS2812_LED_N; i++){
    //r = rand()%256;
    //g = rand()%256;
    //b = rand()%256;
    ws2812_write_led(i, 255, 0, 0);
  }
}
__attribute__ ((weak))
void matrix_scan_kb(void) {
	matrix_scan_user();
  //testPatternFB(o_fb);
  test_ws2812();
  //rgblight_task();
}
