/**
 * @file bootloader.c
 */

#include "bootloader.h"

void bootloader_jump(void) { NVIC_SystemReset(); }
