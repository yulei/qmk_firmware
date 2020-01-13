/**
 * @file ble_hid_service.h
 * @brief defined the hid service related part
 */

#pragma once

#include "ble_config.h"

void ble_hid_service_init(void);
void ble_hid_service_start(void);
void ble_hid_service_send_report(uint8_t report_id, uint8_t* report_data);
void ble_hid_service_flush(bool send);
