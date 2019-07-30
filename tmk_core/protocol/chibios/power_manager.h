/**
 * power_manager.h
 * to reduce the power consuming while under battery supply
 */

#pragma once

#include "matrix.h"

typedef enum {
    PWR_VBUS,       // power supply from the usb
    PWR_BATTERY     // power supply from the battery
} power_supply_t;

typedef enum {
    PWR_MODE_RUN,       // system run at full speed, keeping on this mode while VBUS ON or user is typing, scanning on 100Hz
    PWR_MODE_SLEEP,     // VBUS off and user was not typing for a period of time, slowdown the scan frequency to 10Hz
    PWR_MODE_STANDBY,   // VBUS off and no input for a predefined interval, turn ble off
} power_mode_t;

void pwr_init(void);
void pwr_task(void);
void pwr_scan_hook(matrix_row_t* matrix);
