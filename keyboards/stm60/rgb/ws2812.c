/**
 * ws2812.c
 */

#include "ws2812.h"
#include "ch.h"
#include "hal.h"

/**
 * the APB1 set at 48MHz, spi scale was 8, so the spi running in 6MHz
 * one bit has 1/6MHz ~ 167ns. So we use 1byte(2 for high, 6 for low) to represent one bit data in the RGB
 * buffer
 */
#define T0H             2
#define T1L             T0H
#define T0L             6
#define T1H             T0L
#define RES_CYCLE       0
#define RGB_BITS        24
#define SPI_BITS        (T0H+T0L)
#define BYTE_BITS       8

#define RGB_BUF_SIZE    (RGBLED_NUM*RGB_BITS*SPI_BITS)/(BYTE_BITS)
#define LED_BUF_SIZE    (RGB_BUF_SIZE+RES_CYCLE)

static uint8_t RGB_TX_BUF[LED_BUF_SIZE];

static void write_color(uint32_t index, uint8_t c, uint8_t off)
{
    uint32_t cur = ((index*RGB_BITS+off)*SPI_BITS) / BYTE_BITS;
    uint8_t bit = ((index*RGB_BITS+off)*SPI_BITS) % BYTE_BITS;

    for(uint8_t i = 0; i < BYTE_BITS; i++) {
        if ((c<<i) & 0x80) {
            for(uint8_t j = 0; j < T1H; j++) {
                uint8_t val = RGB_TX_BUF[cur];
                RGB_TX_BUF[cur] = val | (0x01<<(7-bit));
                bit++;
                cur += bit / BYTE_BITS;
                bit = bit % BYTE_BITS;
            }
            for(uint8_t j = 0; j < T1L; j++) {
                uint8_t val = RGB_TX_BUF[cur];
                RGB_TX_BUF[cur] = val & ~(0x01<<(7-bit));
                bit++;
                cur += bit / BYTE_BITS;
                bit = bit % BYTE_BITS;
            }
        } else {
            for(uint8_t j = 0; j < T0H; j++) {
                uint8_t val = RGB_TX_BUF[cur];
                RGB_TX_BUF[cur] = val | (0x01<<(7-bit));
                bit++;
                cur += bit / BYTE_BITS;
                bit = bit % BYTE_BITS;
            }
            for(uint8_t j = 0; j < T0L; j++) {
                uint8_t val = RGB_TX_BUF[cur];
                RGB_TX_BUF[cur] = val & ~(0x01<<(7-bit));
                bit++;
                cur += bit / BYTE_BITS;
                bit = bit % BYTE_BITS;
            }
        }
    }
}

static void write_led(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
  write_color(index, g, 0);
  write_color(index, r, 8);
  write_color(index, b, 16);
}

/*
 * SPI configuration (6MHz, CPHA=1, CPOL=0, MSb first, Tx only mode). Note: the SYSCLK was set at 96MHz. APB1&APB2 were set as 48MHz
 */
static const SPIConfig spicfg = {
    NULL,
    GPIOA,
    4,
    SPI_CR1_MSTR|SPI_CR1_BIDIMODE|SPI_CR1_BIDIOE|SPI_CR1_BR_1,
    0
};

static THD_WORKING_AREA(WS2812_THREAD_WA, 1024);
static THD_FUNCTION(ws2812_thread, arg){
  (void) arg;
  while(1){
    spiAcquireBus(&SPID1);
    spiStart(&SPID1, &spicfg);
    spiSend(&SPID1, LED_BUF_SIZE, &RGB_TX_BUF[0]);
    spiStop(&SPID1);
    spiReleaseBus(&SPID1);
    chThdSleepMicroseconds(280);
  }
}

void ws2812_init(void)
{
  /* turn off all led */
  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    write_led(i, 0x0, 0x0, 0x0);
  }

  for (uint32_t j = 0; j < RES_CYCLE; j ++) {
    RGB_TX_BUF[j + RGB_BUF_SIZE] = 0;
  }
  chThdCreateStatic(WS2812_THREAD_WA, sizeof(WS2812_THREAD_WA),NORMALPRIO, ws2812_thread, NULL);
}

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds)
{
  for (uint16_t i = 0; i < number_of_leds; i++)
  {
    write_led(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
  }
}
