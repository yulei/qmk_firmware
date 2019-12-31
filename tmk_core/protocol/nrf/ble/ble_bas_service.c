/*
Copyright (C) 2018,2019 Jim Jiang <jim@lotlab.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "ble_bas_service.h"
#include <string.h>

#include "app_timer.h"
#include "ble_config.h"
#include "ble_bas.h"

#define __STATIC_INLINE static inline
#include "nrf_drv_saadc.h"
#include "nrfx_saadc.h"

#define BATTERY_LEVEL_MEAS_INTERVAL APP_TIMER_TICKS(2000) /**< Battery level measurement interval (ticks). */
#define SAMPLES_IN_BUFFER 5

static nrf_saadc_value_t m_buffer_pool[2][SAMPLES_IN_BUFFER];

struct BatteryInfo battery_info;

APP_TIMER_DEF(m_battery_timer_id); /**< Battery timer. */
BLE_BAS_DEF(m_bas); /**< Structure used to identify the battery service. */

/**@brief Function for performing a battery measurement, and update the Battery Level characteristic in the Battery Service.
 */
static void battery_level_update(uint8_t battery_level)
{
    ret_code_t err_code;

    err_code = ble_bas_battery_level_update(&m_bas, battery_level, BLE_CONN_HANDLE_ALL);
    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY) && (err_code != NRF_ERROR_RESOURCES) && (err_code != NRF_ERROR_FORBIDDEN) && (err_code != NRF_ERROR_INVALID_STATE) && (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)) {
        APP_ERROR_HANDLER(err_code);
    }
}

/**@brief Function for handling the Battery measurement timer timeout.
 *
 * @details This function will be called each time the battery level measurement timer expires.
 *
 * @param[in]   p_context   Pointer used for passing some arbitrary information (context) from the
 *                          app_start_timer() call to the timeout handler.
 */
static void battery_level_meas_timeout_handler(void* p_context)
{
    UNUSED_PARAMETER(p_context);
    nrfx_saadc_sample();
}

/**@brief Init battery measurement timer.
 */
static void battery_timer_init(void)
{
    ret_code_t err_code;
    // Create battery timer.
    err_code = app_timer_create(&m_battery_timer_id,
        APP_TIMER_MODE_REPEATED,
        battery_level_meas_timeout_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing Battery Service.
 */
static void bas_init(void)
{
    ret_code_t err_code;
    ble_bas_init_t bas_init_obj;

    memset(&bas_init_obj, 0, sizeof(bas_init_obj));

    bas_init_obj.evt_handler = NULL;
    bas_init_obj.support_notification = true;
    bas_init_obj.p_report_ref = NULL;
    bas_init_obj.initial_batt_level = 100;

    bas_init_obj.bl_rd_sec = SEC_CURRENT;
    bas_init_obj.bl_cccd_wr_sec = SEC_CURRENT;
    bas_init_obj.bl_report_rd_sec = SEC_CURRENT;

    err_code = ble_bas_init(&m_bas, &bas_init_obj);
    APP_ERROR_CHECK(err_code);
}

void battery_timer_start(void)
{
    ret_code_t err_code;

    err_code = app_timer_start(m_battery_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

static void calculate_battery_persentage(struct BatteryInfo * info) {
    if (info->voltage >= 4100)
        info->percentage = 100;
    else if (info->voltage >= 3335)
        info->percentage = 15 + (info->voltage - 3335) / 9;
    else if (info->voltage >= 2900)
        info->percentage = (info->voltage - 2900) / 29;
    else
        info->percentage = 0;
}

static void adc_result_handler(nrf_saadc_value_t value)
{
    // RESULT = [V(P) – V(N) ] * GAIN/REFERENCE * 2 ^ (RESOLUTION - m)
    // value  = V_in / 1.2 * 1024
    // V_in   = V_bat * 2.2 / 12.2
    battery_info.voltage = (uint32_t)value * 1200 * 122 / 1024 / 22;
    calculate_battery_persentage(&battery_info);
    battery_level_update(battery_info.percentage);
}

static const nrfx_saadc_config_t config = NRFX_SAADC_DEFAULT_CONFIG;

static void saadc_callback(nrf_drv_saadc_evt_t const* p_event)
{
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE) {
        ret_code_t err_code;

        nrf_saadc_value_t value = 0;
        for (uint8_t i = 0; i < p_event->data.done.size; i++) {
            value += p_event->data.done.p_buffer[i];
        }
        value /= p_event->data.done.size;
        adc_result_handler(value);

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
        APP_ERROR_CHECK(err_code);
    }
}

static void adc_init(void)
{
    ret_code_t err_code;

    nrf_saadc_channel_config_t channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(BATTERY_ADC_PIN);
    channel_config.gain = NRF_SAADC_GAIN1_2;

    err_code = nrfx_saadc_init(&config, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrfx_saadc_channel_init(0, &channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrfx_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrfx_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);
}

void battery_service_init(void)
{
    adc_init();
    battery_timer_init();
    bas_init();
}
