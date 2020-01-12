/**
 * @file ble_adv_service.h
 * @brief ble advertising service
 */

#pragma once

#include "ble_config.h"

void ble_advs_init(void);
void ble_advs_start(bool erase_bonds);
