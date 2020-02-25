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
#include "nrf_drv_twi.h"

#define TWI_INSTANCE_ID         0

#define TWI_SCL_PIN         18
#define TWI_SDA_PIN         19

/* Indicates if operation on TWI has ended. */
static volatile bool m_xfer_done = false;

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/**
 * @brief TWI events handler.
 */
static void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            m_xfer_done = true;
            break;
        case NRF_DRV_TWI_EVT_ADDRESS_NACK:
        case NRF_DRV_TWI_EVT_DATA_NACK:

            break;
        default:
            break;
    }
}

void i2c_init(void)
{
    ret_code_t err_code;

    nrf_drv_twi_config_t twi_config = NRFX_TWI_DEFAULT_CONFIG;
    twi_config.scl = TWI_SCL_PIN;
    twi_config.sda = TWI_SDA_PIN;

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_twi_enable(&m_twi);
}

i2c_status_t i2c_start(uint8_t address)
{
    //nrf_drv_twi_enable(&m_twi);
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    ret_code_t err_code;
    m_xfer_done = false;
    err_code    = nrf_drv_twi_tx(&m_twi, address >> 1, data, length, false);
    if (err_code != NRF_SUCCESS) {
        return I2C_STATUS_ERROR;
    }
    while (m_xfer_done == false);
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    ret_code_t err_code;
    m_xfer_done = false;
    err_code    = nrf_drv_twi_rx(&m_twi, address >> 1, data, length);
    if (err_code != NRF_SUCCESS) {
        return I2C_STATUS_ERROR;
    }
    while (m_xfer_done == false);
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout)
{
    (void)timeout;
    uint8_t complete_packet[length + 1];
    for (uint8_t i = 0; i < length; i++) {
        complete_packet[i + 1] = data[i];
    }
    complete_packet[0] = regaddr;
    return i2c_transmit(devaddr, complete_packet, sizeof(complete_packet), 0);
}

i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout)
{
    if (I2C_STATUS_SUCCESS != i2c_transmit(devaddr, &regaddr, 1, 0))
    {
        return I2C_STATUS_ERROR;
    }

    return i2c_receive(devaddr, data, length, 0);
}

void i2c_stop(void)
{
    //nrf_drv_twi_disable(&m_twi);
}
