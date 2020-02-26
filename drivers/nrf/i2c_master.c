/* Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 astro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This library is only valid for NRF52 processors.
 * This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 */

#include "quantum.h"
#include "i2c_master.h"
#include <string.h>
#include "app_util_platform.h"
#include "app_error.h"
#include "nrfx_twi.h"

#define TWI_INSTANCE_ID     0
#define TWI_SCL_PIN         18
#define TWI_SDA_PIN         19

/* TWI instance. */
static const nrfx_twi_t m_twi = NRFX_TWI_INSTANCE(TWI_INSTANCE_ID);

void i2c_init(void)
{
    ret_code_t err_code;

    nrfx_twi_config_t twi_config = NRFX_TWI_DEFAULT_CONFIG;
    twi_config.scl = TWI_SCL_PIN;
    twi_config.sda = TWI_SDA_PIN;

    err_code = nrfx_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    nrfx_twi_enable(&m_twi);
}

i2c_status_t i2c_start(uint8_t address)
{
    //nrf_drv_twi_enable(&m_twi);
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    ret_code_t err_code = nrfx_twi_tx(&m_twi, address >> 1, data, length, false);
    if (err_code != NRFX_SUCCESS) {
        return I2C_STATUS_ERROR;
    }
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    ret_code_t err_code = nrfx_twi_rx(&m_twi, address >> 1, data, length);
    if (err_code != NRFX_SUCCESS) {
        return I2C_STATUS_ERROR;
    }
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    uint8_t packet[length + 1];
    memcpy(&packet[1], data, length);
    packet[0] = regaddr;
    return i2c_transmit(devaddr, packet, length + 1, 0);
}

i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    nrfx_twi_xfer_desc_t txrx = NRFX_TWI_XFER_DESC_TXRX((devaddr >> 1), &regaddr, 1, data, length);
    ret_code_t err_code = nrfx_twi_xfer(&m_twi, &txrx, 0);
    if (err_code != NRFX_SUCCESS) {
        return I2C_STATUS_ERROR;
    }
    return I2C_STATUS_SUCCESS;
}

void i2c_stop(void)
{
    //nrf_drv_twi_disable(&m_twi);
}
