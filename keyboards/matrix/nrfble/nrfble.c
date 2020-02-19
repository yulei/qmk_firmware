/**
 * nrfble.c
 */

#include "nrfble.h"
#ifdef RGBLIGHT_ENABLE
#include <string.h>
#include "rgblight.h"
#include "ws2812_nrf.h"
#include "nrf_log.h"
extern rgblight_config_t rgblight_config;

void rgblight_set(void)
{
    if (!rgblight_config.enable) {
        for (uint8_t i = 0; i < RGBLED_NUM; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    }
    ws2812_setleds(led, RGBLED_NUM);
    NRF_LOG_INFO("WS2812 setleds: enable=%d", rgblight_config.enable);
}
#endif
void matrix_init_kb(void)
{
#ifdef RGBLIGHT_ENABLE
  ws2812_init();
#endif
  matrix_init_user();
}

__attribute__((weak))
void matrix_init_user(void) { }

void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak))
void matrix_scan_user(void) { }
