/**
 * @file ble_bat_service.h
 * @brief ble battery service
 */

#include "ble_bas.h"
#include "sensorsim.h"

#include "ble_bat_service.h"

APP_TIMER_DEF(m_battery_timer_id);                                  /**< Battery timer. */
BLE_BAS_DEF(m_bas);                                                 /**< Structure used to identify the battery service. */

static sensorsim_cfg_t   m_battery_sim_cfg;                         /**< Battery Level sensor simulator configuration. */
static sensorsim_state_t m_battery_sim_state;                       /**< Battery Level sensor simulator state. */

static void sensor_simulator_init(void);
static void battery_level_update(void);
static void battery_level_meas_timeout_handler(void* p_context);

void ble_bat_service_init(void) {
    ret_code_t     err_code;
    ble_bas_init_t bas_init_obj;

    memset(&bas_init_obj, 0, sizeof(bas_init_obj));

    bas_init_obj.evt_handler          = NULL;
    bas_init_obj.support_notification = true;
    bas_init_obj.p_report_ref         = NULL;
    bas_init_obj.initial_batt_level   = 100;

    bas_init_obj.bl_rd_sec        = SEC_JUST_WORKS;
    bas_init_obj.bl_cccd_wr_sec   = SEC_JUST_WORKS;
    bas_init_obj.bl_report_rd_sec = SEC_JUST_WORKS;

    err_code = ble_bas_init(&m_bas, &bas_init_obj);
    APP_ERROR_CHECK(err_code);

    // Create battery timer.
    err_code = app_timer_create(&m_battery_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                battery_level_meas_timeout_handler);
    APP_ERROR_CHECK(err_code);

    sensor_simulator_init();
}

void ble_bat_service_start(void) {
    ret_code_t     err_code;
    err_code = app_timer_start(m_battery_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for performing a battery measurement, and update the Battery Level characteristic in the Battery Service.
 */
static void battery_level_update(void) {
    ret_code_t err_code;
    uint8_t  battery_level;

    battery_level = (uint8_t)sensorsim_measure(&m_battery_sim_state, &m_battery_sim_cfg);

    err_code = ble_bas_battery_level_update(&m_bas, battery_level, BLE_CONN_HANDLE_ALL);
    if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_BUSY) &&
        (err_code != NRF_ERROR_RESOURCES) &&
        (err_code != NRF_ERROR_FORBIDDEN) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
       ) {
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
static void battery_level_meas_timeout_handler(void * p_context) {
    UNUSED_PARAMETER(p_context);
    battery_level_update();
}

/**@brief Function for initializing the battery sensor simulator.
 */
static void sensor_simulator_init(void) {
    m_battery_sim_cfg.min          = MIN_BATTERY_LEVEL;
    m_battery_sim_cfg.max          = MAX_BATTERY_LEVEL;
    m_battery_sim_cfg.incr         = BATTERY_LEVEL_INCREMENT;
    m_battery_sim_cfg.start_at_max = true;

    sensorsim_init(&m_battery_sim_state, &m_battery_sim_cfg);
}
