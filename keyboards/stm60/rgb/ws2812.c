/**
 * ws2812.c
 */

#include "ws2812.h"
#include "ch.h"
#include "hal.h"

/**
 * the MCU frequency was set at 72Mhz, spi scale was 8, so the spi running in 4.5MHz
 * one bit has 1/4.5MHz ~ 222ns. So we use 4 bit to represent one bit data in the RGB
 * buffer
 */

#define ZERO  0x07
#define ONE   0x0E

#define RGB_BUF_LEN (RGBLED_NUM*3*4)
uint8_t RGBBuf[RGB_BUF_LEN];

/*
 * SPI configuration (4.5MHz, CPHA=0, CPOL=0, MSb first, Tx only mode). Note: the SYSCLK was set at 72MHz. APB1&APB2 were set as 36MHz
 */
static const SPIConfig spicfg = {
    NULL,
    GPIOB,
    12,
    SPI_CR1_MSTR|SPI_CR1_BIDIMODE|SPI_CR1_BIDIOE|SPI_CR1_BR_1,
    0
};

static void update_color(uint8_t c, uint8_t *p);
void ws2812_init(void)
{
  for (uint16_t i = 0; i < RGB_BUF_LEN; i++) {
    RGBBuf[i] = 0;
  }
  spiStart(&SPID1, &spicfg);
}

void update_color(uint8_t c, uint8_t *p)
{
  for (uint8_t i = 0; i < 4; i++) {
    uint8_t d = 0;
    if ( (c<<2*i) & 0x80) {
      d |= ONE << 4;
    } else {
      d |= ZERO << 4;
    }

    if ((c<<(2*i+1)) & 0x80) {
      d |= ONE;
    } else {
      d |= ZERO;
    }
    *p++ = d;
  }
}

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds)
{
  uint8_t *p = &RGBBuf[0];
  LED_TYPE *led = ledarray;
  for (uint16_t i = 0; i < number_of_leds; i++)
  {
    update_color(led->g, p);
    p += 4;
    update_color(led->r, p);
    p += 4;
    update_color(led->b, p);
    p += 4;
  }
  spiExchange(&SPID1, RGB_BUF_LEN, &RGBBuf[0], NULL);
}
