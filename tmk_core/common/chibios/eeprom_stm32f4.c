/**
 * eeprom_stm32f4.c
 */

#include <stdio.h>
#include <string.h>
#include "eeprom_stm32f4.h"

#define LAST_PAGE   (EEPROM_START_ADDRESS+(EEPROM_PAGE_COUNT-1)*EEPROM_PAGE_SIZE)
#define EMPTY_BYTE  0xFF

static uint32_t FindValidPage(void);
static void SavePage(void*buf , uint32_t page);
static uint32_t WriteDead(uint32_t page);
static uint32_t WriteData(uint32_t page, uint16_t address, uint8_t data);
static uint32_t RestorePage(const void* buf, uint32_t page, uint16_t address);

/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the EEPROM_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

uint8_t DataBuf[EEPROM_PAGE_SIZE];
/*****************************************************************************
*  Delete Flash Space used for user Data, deletes the whole space between
*  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
******************************************************************************/
uint16_t EEPROM_Init(void)
{
    // unlock flash
    FLASH_Unlock();

    // Clear Flags
    //FLASH_ClearFlag(FLASH_SR_EOP|FLASH_SR_PGERR|FLASH_SR_WRPERR);

    return EEPROM_PAGE_SIZE;
}
/*****************************************************************************
*  Erase the whole reserved Flash Space used for user Data
******************************************************************************/
void EEPROM_Erase(void) { FLASH_ErasePage(EEPROM_SECTOR_INDEX); }
/*****************************************************************************
*  Writes once data byte to flash on specified address. If a byte is already
*  written, the whole page must be copied to a buffer, the byte changed and
*  the manipulated buffer written after PageErase.
*******************************************************************************/
uint16_t EEPROM_WriteDataByte (uint16_t Address, uint8_t DataByte) {

    FLASH_Status FlashStatus = FLASH_COMPLETE;

    uint32_t page;

    // exit if desired address is above the limit
    if (Address > EEPROM_USER_SIZE) {
        return 0;
    }

    // find the valid page
    page = FindValidPage();
    if (page == EEPROM_INVALID_PAGE) {
        // can't find a usable page, need to do full erase
        SavePage(DataBuf, page);
        // erase the full page
        FLASH_ErasePage(EEPROM_SECTOR_INDEX);
        // program the desired byte first
        WriteData(page, Address, DataByte);

        // progam the remaining data
        RestorePage(DataBuf, page, Address);
    } else {
        // current destination was empty
        if ((*(__IO uint8_t*)(EEPROM_START_ADDRESS+Address)) == EMPTY_BYTE) {
            FLASH_ProgramByte(EEPROM_START_ADDRESS + Address, DataByte);
        } else {
            if ((*(__IO uint8_t*)(EEPROM_START_ADDRESS+Address)) != DataByte) {
                // need using an new page
                SavePage(DataBuf, page);
                WriteDead(page);
                ++page;
                if (page >= EEPROM_PAGE_COUNT) {
                    // page is full
                    FLASH_ErasePage(EEPROM_SECTOR_INDEX);
                    page = 0;
                }
                WriteData(page, Address, DataByte);
                RestorePage(DataBuf, page, Address);
            }
        }
    }

    return FlashStatus;
}
/*****************************************************************************
*  Read once data byte from a specified address.
*******************************************************************************/
uint8_t EEPROM_ReadDataByte (uint16_t Address) {
    uint32_t page = FindValidPage();
    // Get Byte from specified address
    uint8_t DataByte = (*(__IO uint8_t*)(EEPROM_START_ADDRESS + page*EEPROM_PAGE_SIZE + Address));
    return DataByte;
}

// local helper functions
uint32_t FindValidPage(void)
{
    for (uint32_t i = 0; i < EEPROM_PAGE_COUNT; i++) {
        if ((*((__IO uint32_t*)(EEPROM_START_ADDRESS+i*EEPROM_PAGE_SIZE+EEPROM_USER_SIZE))) != EEPROM_EMU_MAGIC) {
          return i;
        }
    }
    return EEPROM_INVALID_PAGE;
}

void SavePage(void *buf, uint32_t page)
{
    memcpy(buf, (uint32_t *)(EEPROM_START_ADDRESS + page * EEPROM_PAGE_SIZE), EEPROM_PAGE_SIZE);
}

uint32_t WriteDead(uint32_t page)
{
    uint32_t address = EEPROM_START_ADDRESS + page * EEPROM_PAGE_SIZE + EEPROM_USER_SIZE;
    return FLASH_ProgramWord(address, EEPROM_EMU_MAGIC);
}

uint32_t WriteData(uint32_t page, uint16_t offset, uint8_t data)
{
    uint32_t address = EEPROM_START_ADDRESS + page * EEPROM_PAGE_SIZE + offset;
    return FLASH_ProgramByte(address, data);
}

uint32_t RestorePage(const void *buf, uint32_t page, uint16_t address)
{
    FLASH_Status FlashStatus = FLASH_COMPLETE;
    const uint8_t *cur = (const uint8_t *)buf;
    for (uint16_t i = 0; i < EEPROM_USER_SIZE; i++) {
        if (*cur != EMPTY_BYTE && i != address) {
          uint32_t address = EEPROM_START_ADDRESS + page * EEPROM_PAGE_SIZE + i;
          FLASH_ProgramByte(address, *cur);
        }
        cur++;
    }

    return FlashStatus;
}

/*****************************************************************************
 *  Wrap library in AVR style functions.
 *******************************************************************************/
uint8_t eeprom_read_byte(const uint8_t *Address)
{
  const uint16_t p = (const uint32_t)Address;
  return EEPROM_ReadDataByte(p);
}

void eeprom_write_byte (uint8_t *Address, uint8_t Value)
{
    uint16_t p = (uint32_t) Address;
    EEPROM_WriteDataByte(p, Value);
}

void eeprom_update_byte (uint8_t *Address, uint8_t Value)
{
    uint16_t p = (uint32_t) Address;
    EEPROM_WriteDataByte(p, Value);
}

uint16_t eeprom_read_word (const uint16_t *Address)
{
    const uint16_t p = (const uint32_t) Address;
    return EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p+1) << 8);
}

void eeprom_write_word (uint16_t *Address, uint16_t Value)
{
    uint16_t p = (uint32_t) Address;
    EEPROM_WriteDataByte(p, (uint8_t) Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t) (Value >> 8));
}

void eeprom_update_word (uint16_t *Address, uint16_t Value)
{
    uint16_t p = (uint32_t) Address;
    EEPROM_WriteDataByte(p, (uint8_t) Value);
    EEPROM_WriteDataByte(p + 1, (uint8_t) (Value >> 8));
}

uint32_t eeprom_read_dword (const uint32_t *Address)
{
    const uint16_t p = (const uint32_t) Address;
    return EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p+1) << 8)
        | (EEPROM_ReadDataByte(p+2) << 16) | (EEPROM_ReadDataByte(p+3) << 24);
}

void eeprom_write_dword (uint32_t *Address, uint32_t Value)
{
    uint16_t p = (const uint32_t) Address;
    EEPROM_WriteDataByte(p, (uint8_t) Value);
    EEPROM_WriteDataByte(p+1, (uint8_t) (Value >> 8));
    EEPROM_WriteDataByte(p+2, (uint8_t) (Value >> 16));
    EEPROM_WriteDataByte(p+3, (uint8_t) (Value >> 24));
}

void eeprom_update_dword (uint32_t *Address, uint32_t Value)
{
    uint16_t p = (const uint32_t) Address;
    uint32_t existingValue = EEPROM_ReadDataByte(p) | (EEPROM_ReadDataByte(p+1) << 8)
        | (EEPROM_ReadDataByte(p+2) << 16) | (EEPROM_ReadDataByte(p+3) << 24);
    if(Value != existingValue){
      EEPROM_WriteDataByte(p, (uint8_t) Value);
      EEPROM_WriteDataByte(p+1, (uint8_t) (Value >> 8));
      EEPROM_WriteDataByte(p+2, (uint8_t) (Value >> 16));
      EEPROM_WriteDataByte(p+3, (uint8_t) (Value >> 24));
    }
}

void eeprom_read_block(void *buf, const void *addr, uint32_t len) {
    const uint8_t *p = (const uint8_t *)addr;
    uint8_t *dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *p = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *p = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
