/**
 * ws2811.c
 * spi dma based ws2811 driver
 */

/**
 * According to the ws2811 data sheet, T0H: 220-380ns, T0L: 580-1000ns, T1H: 580-1000ns, T1L: 220-420ns, RESET: >280us.
 * While using an 6MHz spi, one bit time is about 167ns( 1/6000000), so 7 bits data can be used to compose one bit for ws2811 signal.
 * 2 bits for T0H or T1L, 5 bits for T0L or T1H
 */

#include "ws2811.h"

#include "ch.h"
#include "hal.h"

#define T0H             2
#define T1L             T0H
#define T0L             5
#define T1H             T0L
#define RES_CYCLE       200
#define RGB_BITS        24
#define SPI_BITS        (T0H+T0L)
#define BYTE_BITS       8
#define RGB_LED_NUM     8

#define RGB_BUF_SIZE    (RGB_LED_NUM*RGB_BITS*SPI_BITS)/(BYTE_BITS)
#define LED_BUF_SIZE    (RGB_BUF_SIZE+RES_CYCLE)

/*
 * SPI configuration (6MHz, CPHA=0, CPOL=0, MSb first, Tx only mode). Note: the SYSCLK was set at 96MHz. APB1&APB2 were set as 48MHz
 */
static const SPIConfig spicfg = {
    NULL,
    GPIOB,
    12,
    SPI_CR1_BIDIMODE|SPI_CR1_BIDIOE|SPI_CR1_BR_1,
    0
};

static uint8_t RGB_TX_BUF[LED_BUF_SIZE];

static void write_color(uint32_t index, uint8_t c, uint8_t off)
{
    uint32_t cur = ((index*RGB_BITS+off)*SPI_BITS) / BYTE_BITS;
    uint8_t bit = ((index*RGB_BITS+off)*SPI_BITS) % BYTE_BITS;

    for(uint8_t i = 0; i < BYTE_BITS; i++) {
        if ((c>>i) & 0x01) {
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

void ws2811_init(void)
{
    /* turn off all led */
    for (uint8_t i = 0; i < RGB_LED_NUM; i++) {
        ws2811_write_led(i, 0, 0, 0);
    }

    for (uint32_t j = 0; j < RES_CYCLE; j ++) {
        RGB_TX_BUF[j + RGB_BUF_SIZE] = 0;
    }
}

void ws2811_write_led(uint32_t index, uint8_t r, uint8_t g, uint8_t b)
{
    write_color(index, r, 0);
    write_color(index, g, 8);
    write_color(index, b, 16);
}

void ws2811_transfer(void)
{
    spiStart(&SPID2, &spicfg);
    spiExchange(&SPID2, LED_BUF_SIZE, &RGB_TX_BUF[0], NULL);
}
