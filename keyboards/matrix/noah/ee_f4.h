/**
 * ee_f4.h
 */

#pragma once

#include <stdint.h>

typedef enum {
  EE_SUCESS,
  EE_ERROR,
  EE_BUSY,
  EE_TIMEOUT,
} eef4_status_t;

#define EE_SECTOR_SIZE 0x4000

#define EE_SECTOR_0_START 0x08008000
#define EE_SECTOR_0_ID 2
#define EE_SECTOR_1_START 0x0800C000
#define EE_SECTOR_1_ID 3
#define EE_MAX_BYTES 1024 //compatible with avr which has 1024 bytes eeprom

void    eef4_init(void);
int32_t eef4_write_byte(uint32_t addr, uint8_t data);
int32_t eef4_read_byte(uint32_t addr, uint8_t* buf);