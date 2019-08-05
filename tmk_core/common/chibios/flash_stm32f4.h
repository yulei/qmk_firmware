/**
 * flash_stm32f4.h
 */

#pragma once

#include "ch.h"
#include "hal.h"

typedef enum
    {
    FLASH_BUSY = 1,
    FLASH_ERROR_PG,
    FLASH_ERROR_WRP,
    FLASH_ERROR_OPT,
    FLASH_COMPLETE,
    FLASH_TIMEOUT,
    FLASH_BAD_ADDRESS
    } FLASH_Status;

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x0807FFFF))
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) >= 0) && ((SECTOR) <= 7))

FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
FLASH_Status FLASH_ErasePage(uint32_t Sector);
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);

void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
