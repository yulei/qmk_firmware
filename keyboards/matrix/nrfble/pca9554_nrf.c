/**
 * @file pca9554_nrf.c
 */

#include "pca9554_nrf.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"

#define TWI_INSTANCE_ID         0

#define PCA9554_ADDR            0x20

#define PCA9554_SCL_PIN         18
#define PCA9554_SDA_PIN         19

#define PCA9554_CMD_INPUT       0
#define PCA9554_CMD_OUTPUT      1
#define PCA9554_CMD_POLARITY    2
#define PCA9554_CMD_CONFIG      3

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

void pca9554_nrf_init(void)
{
    ret_code_t err_code;
    uint8_t reg[2];

    const nrf_drv_twi_config_t twi_pca9554_config = {
       .scl                = PCA9554_SCL_PIN,
       .sda                = PCA9554_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_pca9554_config, twi_handler, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);

    /* set to output mode */
    reg[0] = PCA9554_CMD_CONFIG;
    reg[1] = 0;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, PCA9554_ADDR, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);

    /* clear output register */
    reg[0] = PCA9554_CMD_OUTPUT;
    reg[1] = 0;
    m_xfer_done = false;
    err_code = nrf_drv_twi_tx(&m_twi, PCA9554_ADDR, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);  
}

void pca9554nrf_write(uint8_t out)
{
    ret_code_t err_code;
    uint8_t reg[2];
    /* write to output register */
    reg[0] = PCA9554_CMD_OUTPUT;
    reg[1] = out;
    err_code = nrf_drv_twi_tx(&m_twi, PCA9554_ADDR, reg, sizeof(reg), false);
    APP_ERROR_CHECK(err_code);
    while (m_xfer_done == false);
}