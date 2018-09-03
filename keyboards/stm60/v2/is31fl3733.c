/**
 * is32fl3733.c
 */

// chibios includes
#include <ch.h>
#include <hal.h>

#include "is31fl3733.h"

#define TX_BUF_LEN 16
#define RX_BUF_LEN 16

static uint8_t txbuf[TX_BUF_LEN];
static uint8_t rxbuf[RX_BUF_LEN];
//static i2cflags_t errors = 0;
static msg_t status = MSG_OK;
//static systime_t tmo = MS2ST(4);

#define fl3733_addr 0b1010000

static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

void is31fl3733_init(void)
{
  //palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
  //palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);

  i2cStart(&I2CD1, &i2cfg1);

  txbuf[0] = 0xFE;
  txbuf[1] = 0xC5; // unlock fdh
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  txbuf[0] = 0xFD;
  txbuf[1] = 0x00; // wirte page 0
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  for (uint8_t i = 0; i < 24; i++) {
    txbuf[0] = i;
    txbuf[1] = 0xFF;
    status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  } // turn all led

  txbuf[0] = 0xFE;
  txbuf[1] = 0xC5;
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  txbuf[0] = 0xFD;
  txbuf[1] = 0x01;  // page 1
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  for (uint8_t i = 0; i < 192; i++) {
    txbuf[0] = i;
    txbuf[1] = 0xFF;
    status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  } // set all pwm

  txbuf[0] = 0xFE;
  txbuf[1] = 0xC5;
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  txbuf[0] = 0xFD;
  txbuf[1] = 0x03;  // page 3
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  txbuf[0] = 0x00;
  txbuf[1] = 0x01;  // normal operation
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
  txbuf[0] = 0x01;
  txbuf[1] = 0xFF;  // global current
  status = i2cMasterTransmit(&I2CD1, fl3733_addr, txbuf, 2, rxbuf, 0);
}
/*
void is31fl3733_set_sw_pull(uint8_t r);
void is31fl3733_set_cs_pull(uint8_t r);
void is31fl3733_set_global_current(uint8_t current);
void is31fl3733_all_on(void);
void is31fl3733_all_off(void);

void is31fl3733_set_brightness(uint8_t level);
void is31fl3733_set_color(uint8_t sw, uint8_t cs, uint8_t r, uint8_t g, uint8_t b);
*/
