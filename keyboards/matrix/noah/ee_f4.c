/**
 * ee_f4.c
 *   @author yulei, yuleiz@gmail.com
 */

#include <string.h>
#include "ee_f4.h"
#include "hal.h"

#define IS_VALID_ADDRESS(ADDRESS) (((ADDRESS) >= 0) && ((ADDRESS) < EE_MAX_BYTES))
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) >= EE_SECTOR_0_ID) && ((SECTOR) <= EE_SECTOR_1_ID))
#define EraseTimeout ((uint32_t)0x00000FFF)
#define ProgramTimeout ((uint32_t)0x0000001F)

#define FLASH_PSIZE_BYTE 0
#define FLASH_PSIZE_HFWORD FLASH_CR_PSIZE_0
#define FLASH_PSIZE_WORD FLASH_CR_PSIZE_1
#define FLASH_CR_SNB_Pos 3
#define FLASH_KEY1_F4 0x45670123
#define FLASH_KEY2_F4 0xCDEF89AB

#define FLASH_MAGIC_ADDR 0
#define FLASH_SECTOR_ACTIVE 0xBEEFBEEF  // magic number to mark this page was used currently
#define FLASH_SECTOR_EMPTY 0xFFFFFFFF
#define FLASH_SECTOR_FULL 0xDEADDEAD
#define FLASH_INVALID_ADDR 0xFFFFFFFF

#define DATA_VALID_MASK 0x8000
#define DATA_VALID_ADDR 0xFFFF
typedef union {
    struct {
        uint16_t addr;
        uint8_t  pad;
        uint8_t  val;
    } flash;
    uint32_t value;
} __attribute__((packed)) flash_data_t;

static uint8_t current_sector = 0;

static void Flash_Delay(void) {
    __IO uint32_t i = 0;
    for (i = 0xFF; i != 0; i--) {
    }
}

static eef4_status_t FLASH_GetStatus(void) {
    if ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY) return EE_BUSY;

    if ((FLASH->SR & (FLASH_SR_PGSERR | FLASH_SR_PGPERR | FLASH_SR_PGAERR)) != 0) return EE_ERROR;

    if ((FLASH->SR & FLASH_SR_WRPERR) != 0) return EE_ERROR;

    if ((FLASH->SR & FLASH_SR_SOP) != 0) return EE_ERROR;

    return EE_SUCESS;
}

static eef4_status_t FLASH_WaitForLastOperation(uint32_t timeout) {
    /* Check for the Flash Status */
    eef4_status_t status = FLASH_GetStatus();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == EE_BUSY) && (timeout != 0x00)) {
        Flash_Delay();
        status = FLASH_GetStatus();
        timeout--;
    }

    if (timeout == 0) status = EE_TIMEOUT;

    return status;
}

static eef4_status_t FLASH_UnlockF4(void) {
    FLASH->KEYR = FLASH_KEY1_F4;
    FLASH->KEYR = FLASH_KEY2_F4;
    return EE_SUCESS;
}

static eef4_status_t FLASH_LockF4(void) {
    FLASH->CR |= FLASH_CR_LOCK;
    return EE_SUCESS;
}

static eef4_status_t FLASH_EraseSectorF4(uint32_t sector) {
    eef4_status_t status = EE_SUCESS;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    FLASH_UnlockF4();
    if (status == EE_SUCESS) {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CR |= FLASH_CR_SER | (sector << FLASH_CR_SNB_Pos);
        FLASH->CR |= FLASH_CR_STRT;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if (status != EE_TIMEOUT) {
            /* if the erase operation is completed, disable the PER Bit */
            FLASH->CR &= ~FLASH_CR_SNB;
            FLASH->CR &= ~FLASH_CR_SER;
        }

        FLASH->SR = (FLASH_SR_EOP | FLASH_SR_SOP | FLASH_SR_WRPERR);
    }
    FLASH_LockF4();
    /* Return the Erase Status */
    return status;
}

static eef4_status_t FLASH_ProgramWordF4(uint32_t address, uint32_t data) {
    eef4_status_t status = EE_ERROR;
    if (address % sizeof(uint32_t) != 0) {
        // address not aligned
        return EE_ERROR;
    }
    if (IS_VALID_ADDRESS(address)) {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        FLASH_UnlockF4();
        if (status == EE_SUCESS) {
            // set size to halfword
            FLASH->CR &= ~FLASH_CR_PSIZE;
            FLASH->CR |= FLASH_PSIZE_WORD;
            FLASH->CR |= FLASH_CR_PG;

            *(__IO uint32_t *)address = data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            if (status != EE_TIMEOUT) {
                /* if the program operation is completed, disable the PG Bit */
                FLASH->CR &= ~FLASH_CR_PG;
            }
            FLASH->SR = (FLASH_SR_EOP | FLASH_SR_SOP | FLASH_SR_PGSERR | FLASH_SR_PGPERR | FLASH_SR_PGAERR | FLASH_SR_WRPERR);
        }
        FLASH_LockF4();
    }
    return status;
}

void eef4_init(void) {
    // get the current working sector
    if (*((uint32_t *)EE_SECTOR_0_START) == FLASH_SECTOR_ACTIVE) {
        current_sector = EE_SECTOR_0_ID;
    } else if (*((uint32_t *)EE_SECTOR_1_START) == FLASH_SECTOR_ACTIVE) {
        current_sector = EE_SECTOR_1_ID;
    } else /* not active setting, find one empty sector as active*/ {
        if (*((uint32_t *)EE_SECTOR_0_START) == FLASH_SECTOR_EMPTY) {
            current_sector = EE_SECTOR_0_ID;
            FLASH_ProgramWordF4(EE_SECTOR_0_START, FLASH_SECTOR_ACTIVE);
        } else if (*((uint32_t *)EE_SECTOR_1_START) == FLASH_SECTOR_EMPTY) {
            current_sector = EE_SECTOR_1_ID;
            FLASH_ProgramWordF4(EE_SECTOR_1_START, FLASH_SECTOR_ACTIVE);
        } else {
            // none can be used, erase all
            FLASH_EraseSectorF4(EE_SECTOR_0_ID);
            current_sector = EE_SECTOR_0_ID;
            FLASH_ProgramWordF4(EE_SECTOR_0_START, FLASH_SECTOR_ACTIVE);
            FLASH_EraseSectorF4(EE_SECTOR_1_ID);
        }
    }
}

static uint32_t sector_addr(uint32_t sector) {
    if (sector == EE_SECTOR_0_ID) return EE_SECTOR_0_START;
    if (sector == EE_SECTOR_1_ID) return EE_SECTOR_1_START;

    return FLASH_INVALID_ADDR;
}

static bool sector_empty(uint32_t sector) {
    uint32_t addr = sector_addr(sector);
    uint32_t end  = addr + EE_SECTOR_SIZE;
    if (addr == FLASH_INVALID_ADDR) {
        return false;
    }
    while (addr < end) {
        if ((*(uint32_t *)addr) != FLASH_SECTOR_EMPTY) {
            return false;
        }
        addr += 4;
    }
    return true;
}

static eef4_status_t prepare_sector(uint32_t sector) {
    eef4_status_t status = EE_SUCESS;
    if (!sector_empty(sector)) {
        status = FLASH_EraseSectorF4(sector);
    }
    return status;
}

static eef4_status_t mark_active_sector(uint32_t sector) {
    uint32_t      addr   = sector_addr(sector);
    eef4_status_t status = FLASH_ProgramWordF4(addr, FLASH_SECTOR_ACTIVE);
    return status;
}

static eef4_status_t mark_full_sector(uint32_t sector) {
    uint32_t      addr   = sector_addr(sector) + EE_SECTOR_SIZE - 4;
    eef4_status_t status = FLASH_ProgramWordF4(addr, FLASH_SECTOR_FULL);
    return status;
}

static eef4_status_t switch_sector(void) {
  eef4_status_t   status = EE_SUCESS;
  static uint16_t flash_buf[EE_MAX_BYTES];
  uint32_t        start       = sector_addr(current_sector);
  uint32_t        end         = start + EE_SECTOR_SIZE - 4;
  uint32_t        next_sector = current_sector == EE_SECTOR_0_ID ? EE_SECTOR_1_ID : EE_SECTOR_0_ID;
  // save valid data first
  memset(&flash_buf[0], 0, sizeof(flash_buf));
  while (end >= start + 4) {
    flash_data_t *data = (flash_data_t *)end;

    if (data->flash.addr < EE_MAX_BYTES) {
      // valid data
      if ((flash_buf[data->flash.addr] & DATA_VALID_MASK) == 0) {
        flash_buf[data->flash.addr] = DATA_VALID_MASK | data->flash.val;
      }
      end -= 4;
    }
  }
  // write valid data
  if (prepare_sector(next_sector) == EE_SUCESS) {
    uint32_t addr = sector_addr(next_sector) + 4;
    for (uint32_t i = 0; i < EE_MAX_BYTES; i++) {
      if (flash_buf[i] & DATA_VALID_MASK) {
        flash_data_t data = {.flash = {i, 0, flash_buf[i] & ~DATA_VALID_MASK}};
        status            = FLASH_ProgramWordF4(addr, data.value);
        if (status != EE_SUCESS) {
          return status;
        }
        addr += 4;
      }
    }
    status = mark_active_sector(next_sector);
    if (status != EE_SUCESS) {
      return status;
    }
    status         = mark_full_sector(current_sector);
    current_sector = next_sector;
    return status;
  } else {
    return EE_ERROR;
  }
}
static uint32_t find_valid_addr(void) {
    uint32_t start = sector_addr(current_sector);
    uint32_t end   = start + EE_SECTOR_SIZE;
    start += 4;  // bypass the sector header
    while (start < end) {
        flash_data_t *data = (flash_data_t *)start;
        if (data->flash.addr == DATA_VALID_ADDR) {
            return start;
        } else {
            start += 4;
        }
    }
    return FLASH_INVALID_ADDR;
}

int32_t eef4_write_byte(uint32_t addr, uint8_t val) {
    uint32_t valid_addr = find_valid_addr();
    if (valid_addr == FLASH_INVALID_ADDR) {
        switch_sector();
        valid_addr = find_valid_addr();
    }
    if (valid_addr != FLASH_INVALID_ADDR) {
        flash_data_t data = {.flash = {addr, 0, val}};
        return FLASH_ProgramWordF4(valid_addr, data.value);
    }
    return EE_ERROR;
}

int32_t eef4_read_byte(uint32_t addr, uint8_t *buf) {
    uint32_t start = sector_addr(current_sector);
    uint32_t end   = start + EE_SECTOR_SIZE;
    end -= 4;
    while (end >= start + 4) {
        flash_data_t *data = (flash_data_t *)end;
        if (data->flash.addr == (uint16_t)addr) {
            *buf = data->flash.val;
            return EE_SUCESS;
        }
        end -= 4;
    }
    return EE_ERROR;
}

/*****************************************************************************
 *  Wrap library in AVR style functions.
 *******************************************************************************/
/*uint8_t eeprom_read_byte(const uint8_t *Address) {
    const uint32_t addr = (const uint32_t)Address;
    uint8_t        data = 0;
    eef4_read_byte(addr, &data);
    return data;
}

void eeprom_write_byte(uint8_t *Address, uint8_t Value) {
    uint32_t addr = (uint32_t)Address;
    eef4_write_byte(addr, Value);
}

void eeprom_update_byte(uint8_t *Address, uint8_t Value) {
    uint32_t addr = (uint32_t)Address;
    eef4_write_byte(addr, Value);
}

uint16_t eeprom_read_word(const uint16_t *Address) {
    const uint8_t *p = (const uint8_t *)Address;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8);
}

void eeprom_write_word(uint16_t *Address, uint16_t Value) {
    uint32_t p = (uint32_t)Address;
    eef4_write_byte(p, (uint8_t)Value);
    eef4_write_byte(p + 1, (uint8_t)(Value >> 8));
}

void eeprom_update_word(uint16_t *Address, uint16_t Value) {
    uint32_t p = (uint32_t)Address;
    eef4_write_byte(p, (uint8_t)Value);
    eef4_write_byte(p + 1, (uint8_t)(Value >> 8));
}

uint32_t eeprom_read_dword(const uint32_t *Address) {
    uint8_t *p = (uint8_t *)Address;
    return eeprom_read_byte(p) | (eeprom_read_byte(p + 1) << 8) | (eeprom_read_byte(p + 2) << 16) | (eeprom_read_byte(p + 3) << 24);
}

void eeprom_write_dword(uint32_t *Address, uint32_t Value) {
    uint32_t p = (uint32_t)Address;
    eef4_write_byte(p, (uint8_t)Value);
    eef4_write_byte(p + 1, (uint8_t)(Value >> 8));
    eef4_write_byte(p + 2, (uint8_t)(Value >> 16));
    eef4_write_byte(p + 3, (uint8_t)(Value >> 24));
}

void eeprom_update_dword(uint32_t *Address, uint32_t Value) {
    uint32_t p             = (const uint32_t)Address;
    uint32_t existingValue = eeprom_read_dword(Address);
    if (Value != existingValue) {
        eef4_write_byte(p, (uint8_t)Value);
        eef4_write_byte(p + 1, (uint8_t)(Value >> 8));
        eef4_write_byte(p + 2, (uint8_t)(Value >> 16));
        eef4_write_byte(p + 3, (uint8_t)(Value >> 24));
    }
}

void eeprom_read_block(void *buf, const void *addr, uint32_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_block(const void *buf, void *addr, uint32_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}*/