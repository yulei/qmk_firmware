/**
 * eeprom_stm32f4.h
 */

#pragma once

#include "ch.h"
#include "hal.h"
#include "flash_stm32f4.h"

#if defined(EEPROM_EMU_STM32F411xE)
  #define MCU_STM32F411CE
#else
  #error "not implemented."
#endif

#ifndef EEPROM_SECTOR_INDEX
    #define EEPROM_SECTOR_INDEX     4
#endif

#ifndef EEPROM_SECTOR_SIZE
    #define EEPROM_SECTOR_SIZE      0x10000
#endif


#ifndef EEPROM_START_ADDRESS
    #define EEPROM_START_ADDRESS    0x08010000
#endif

#ifndef EEPROM_PAGE_SIZE
    #define EEPROM_PAGE_SIZE        0x400
#endif

// page's last word will be programmed with this magic
#ifndef EEPROM_EMU_MAGIC
    #define EEPROM_EMU_MAGIC        0xDEADBEAF
#endif

#define EEPROM_PAGE_COUNT       (EEPROM_SECTOR_SIZE/EEPROM_PAGE_SIZE)
#define EEPROM_INVALID_PAGE     0xFFFF
#define EEPROM_USER_SIZE        (EEPROM_PAGE_SIZE-4)

// Use this function to initialize the functionality
uint16_t EEPROM_Init(void);
void EEPROM_Erase (void);
uint16_t EEPROM_WriteDataByte (uint16_t Address, uint8_t DataByte);
uint8_t EEPROM_ReadDataByte (uint16_t Address);
