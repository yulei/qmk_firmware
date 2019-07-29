/**
 * power_manager.h
 * to reduce the power consume while under battery supply
 */

#pragma once

#include "matrix.h"

typedef enum {
    PWR_VBUS,       // power supply from the usb
    PWR_BATTERY    // power supply from the battery
} power_supply_t;

typedef enum {
    PWR_MODE_RUN,       // in normal running system, keeping on this mode while VBUS on or user is typing
    PWR_MODE_SLEEP,     // VBUS off, scan frequency under 10Hz
    PWR_MODE_STANDBY,   // VBUS off, no input for a predefined interval, turn ble off
} power_mode_t;

void pwr_init(void);
void pwr_task(void);
void pwr_scan_hook(matrix_row_t* matrix);
