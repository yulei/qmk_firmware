/**
 * spi.c
 */

#include "spi.h"

#include <ch.h>
#include <hal.h>

#define SPI_USE_REG 0

#define SPIDEV SPID1
#define SPI_CS_PORT GPIOA
#define SPI_CS_PIN 4
#define SPI_SCK_PORT GPIOA
#define SPI_SCK_PIN 5
#define SPI_MISO_PORT GPIOA
#define SPI_MISO_PIN 6
#define SPI_MOSI_PORT GPIOA
#define SPI_MOSI_PIN 7

// APB run at 32MHz, need divided with 8 to 4MHz
// CPOL=0, CPHA=0
SPIConfig spicfg = {
    NULL,
    SPI_CS_PORT,
    SPI_CS_PIN,
    SPI_CR1_MSTR | SPI_CR1_BR_1,
    0};

void SPI_init(void)
{
    palSetPadMode(SPI_CS_PORT, SPI_CS_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(SPI_SCK_PORT, SPI_SCK_PIN, PAL_MODE_ALTERNATE(5)|PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(SPI_MISO_PORT, SPI_MISO_PIN, PAL_MODE_ALTERNATE(5)|PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(SPI_MOSI_PORT, SPI_MOSI_PIN, PAL_MODE_ALTERNATE(5)|PAL_STM32_OSPEED_HIGHEST);

    palSetPad(SPI_CS_PORT, SPI_CS_PIN);
}

void SPI_begin(void)
{
#if SPI_USE_REG
    SPIDriver* spip = &SPIDEV;
    spip->spi->CR1 &= ~SPI_CR1_SPE;
    spip->spi->CR1 = spip->config->cr1 | SPI_CR1_SSM;
    spip->spi->CR2 = spip->config->cr2;
    spip->spi->CR1 |= SPI_CR1_SPE;
#else
    spiStart(&SPIDEV, &spicfg);
#endif
}

void SPI_end(void)
{
#if SPI_USE_REG
    SPIDriver* spip = &SPIDEV;
    spip->spi->CR1 &= ~SPI_CR1_SPE;
    spip->spi->CR1 = 0;
    spip->spi->CR2 = 0;
#else
    spiStop(&SPIDEV);
#endif
}

void SPI_select(void) { palClearPad(spicfg.ssport, spicfg.sspad); }
void SPI_unselect(void) { palSetPad(spicfg.ssport, spicfg.sspad); }

#if SPI_USE_REG
static uint8_t spi_dummy;
static void wait_txe(SPIDriver* spip) {
  while (!(spip->spi->SR & SPI_SR_TXE))
    ;
}
static void wait_rxe(SPIDriver* spip)
{
    while (!(spip->spi->SR & SPI_SR_RXNE))
        ;
}
static void wait_bsy(SPIDriver* spip)
{
    while ((spip->spi->SR & SPI_SR_BSY))
        ;
}
#endif
void SPI_send(const void *buffer, uint32_t len)
{
#if SPI_USE_REG
    SPIDriver* spip = &SPIDEV;
    const uint8_t* p = (const uint8_t*)buffer;
    //wait_txe(spip);
    spip->spi->DR = *p++;
    for (uint32_t i = 0; i < len-1; i++) {
        wait_txe(spip);
        spip->spi->DR = *p++;
        wait_rxe(spip);
        spi_dummy = spip->spi->DR;
    }
    wait_rxe(spip);
    spi_dummy = spip->spi->DR;
    wait_bsy(spip);
#else
  spiSend(&SPIDEV, len, buffer);
#endif
}

void SPI_recv(void *buffer, uint32_t len)
{
#if SPI_USE_REG
    SPIDriver* spip = &SPIDEV;
    uint8_t* p = (uint8_t*)buffer;
    spi_dummy = 0;
    //wait_txe(spip);
    spip->spi->DR = spi_dummy;
    for (uint32_t i = 0; i < len - 1; i++) {
        wait_txe(spip);
        spip->spi->DR = spi_dummy;
        wait_rxe(spip);
        *p++ = spip->spi->DR;
    }
    wait_rxe(spip);
    *p = spip->spi->DR;
    wait_bsy(spip);
#else
    spiReceive(&SPIDEV, len, buffer);
#endif
}

void SPI_exchange(const void* tx_buf, void* rx_buf, uint32_t len)
{
#if SPI_USE_REG
    SPIDriver* spip = &SPIDEV;
    const uint8_t* tx = (const uint8_t*)tx_buf;
    uint8_t* rx = (uint8_t*)rx_buf;
    //wait_txe(spip);
    spip->spi->DR = *tx++;
    for (uint32_t i = 0; i < len - 1; i++) {
        wait_txe(spip);
        spip->spi->DR = *tx++;
        wait_rxe(spip);
        *rx++ = spip->spi->DR;
    }
    wait_rxe(spip);
    *rx = spip->spi->DR;
    wait_bsy(spip);
#else
    spiExchange(&SPIDEV, len, tx_buf, rx_buf);
#endif
}
