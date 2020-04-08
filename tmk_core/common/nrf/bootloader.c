/**
 * @file bootloader.c
 */

#include "bootloader.h"
#include "nrf.h"
#include "ble_config.h"

void bootloader_jump(void)
{
    NRF_LOG_INFO("RESET button pressed, set bootloader flag and reboot");
    sd_power_gpregret_set(RST_REGISTER, RST_BOOTLOADER);
    sd_nvic_SystemReset();
}
