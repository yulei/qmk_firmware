/**
 * @file bootloader.c
 */

#include "bootloader.h"
#include "nrf.h"

void bootloader_jump(void) { NVIC_SystemReset(); }
