/**
 * @file eeprom_fds.c
 * @brief fds base eeprom emulation
 *
 */

#include <string.h>
#include "eeprom.h"
#include "fds.h"

#define EE_FILEID 0x6565  //"ee"
static bool ee_callback_registered  = false;
static volatile bool ee_done        = false;
static volatile bool ee_gc_done     = false;
static void ee_evt_handler(fds_evt_t const* p_evt)
{
    switch(p_evt->id) {
    case FDS_EVT_WRITE:
    case FDS_EVT_UPDATE:
        break;
    case FDS_EVT_DEL_RECORD:
    case FDS_EVT_DEL_FILE:
        if (p_evt->del.file_id== EE_FILEID) {
            ee_done = true;
        }
        break;
    case FDS_EVT_GC:
        ee_gc_done = true;
        break;
    case FDS_EVT_INIT:
    default:
        break;
    }
}

void fds_eeprom_init(void)
{
    // fds should be initialized on peer manager
    if (!ee_callback_registered) {
        fds_register(ee_evt_handler);
        ee_callback_registered = true;
    }

    ee_done = false;
    fds_file_delete(EE_FILEID);
    while(!ee_done) { }
}

static uint32_t     ee_data;
static fds_record_t ee_record = {
    .file_id = EE_FILEID,
    .data.p_data = &ee_data,
    .data.length_words = 1,
};

void    fds_eeprom_write_byte(uint16_t addr, uint8_t data)
{
    fds_record_desc_t desc  = {0};
    fds_find_token_t  token = {0};
    ret_code_t        rc    = fds_record_find_by_key(addr, &desc, &token);
    if (rc == NRF_SUCCESS) {
        ee_data = data;
        ee_record.key = addr;
        rc = fds_record_update(&desc, &ee_record);
        if (rc == FDS_ERR_NO_SPACE_IN_FLASH) {
            ee_gc_done = false;
            fds_gc();
            while (!ee_gc_done) {}
            // update again
            rc = fds_record_update(&desc, &ee_record);
        }
    } else {
        ee_data = data;
        ee_record.key = addr;
        rc = fds_record_write(&desc, &ee_record);
        if (rc == FDS_ERR_NO_SPACE_IN_FLASH) {
            ee_gc_done = false;
            fds_gc();
            while (!ee_gc_done) {}
            // write again
            rc = fds_record_write(&desc, &ee_record);
        }
    }

    APP_ERROR_CHECK(rc);
}

uint8_t fds_eeprom_read_byte(uint16_t addr)
{
    fds_record_desc_t desc = {0};
    fds_find_token_t token = {0};
    uint32_t result = 0;
    ret_code_t rc = fds_record_find_by_key(addr, &desc, &token);
    if (rc == NRF_SUCCESS) {
        fds_flash_record_t ee_data = {0};
        fds_record_open(&desc, &ee_data);
        memcpy(&result, ee_data.p_data, sizeof(result));
        fds_record_close(&desc);
    }
    return (uint8_t)result;
}

/*****************************************************************************
 *  Wrap library in AVR style functions.
 *******************************************************************************/
uint8_t eeprom_read_byte(const uint8_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return fds_eeprom_read_byte(p);
}

void eeprom_write_byte(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    fds_eeprom_write_byte(p, Value);
}

void eeprom_update_byte(uint8_t *Address, uint8_t Value) {
    uint16_t p = (uint32_t)Address;
    fds_eeprom_write_byte(p, Value);
}

uint16_t eeprom_read_word(const uint16_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return fds_eeprom_read_byte(p) | (fds_eeprom_read_byte(p + 1) << 8);
}

void eeprom_write_word(uint16_t *Address, uint16_t Value) {
    uint16_t p = (uint32_t)Address;
    fds_eeprom_write_byte(p, (uint8_t)Value);
    fds_eeprom_write_byte(p + 1, (uint8_t)(Value >> 8));
}

void eeprom_update_word(uint16_t *Address, uint16_t Value) {
    uint16_t p = (uint32_t)Address;
    fds_eeprom_write_byte(p, (uint8_t)Value);
    fds_eeprom_write_byte(p + 1, (uint8_t)(Value >> 8));
}

uint32_t eeprom_read_dword(const uint32_t *Address) {
    const uint16_t p = (const uint32_t)Address;
    return fds_eeprom_read_byte(p) | (fds_eeprom_read_byte(p + 1) << 8) | (fds_eeprom_read_byte(p + 2) << 16) | (fds_eeprom_read_byte(p + 3) << 24);
}

void eeprom_write_dword(uint32_t *Address, uint32_t Value) {
    uint16_t p = (const uint32_t)Address;
    fds_eeprom_write_byte(p, (uint8_t)Value);
    fds_eeprom_write_byte(p + 1, (uint8_t)(Value >> 8));
    fds_eeprom_write_byte(p + 2, (uint8_t)(Value >> 16));
    fds_eeprom_write_byte(p + 3, (uint8_t)(Value >> 24));
}

void eeprom_update_dword(uint32_t *Address, uint32_t Value) {
    uint16_t p             = (const uint32_t)Address;
    uint32_t existingValue = fds_eeprom_read_byte(p) | (fds_eeprom_read_byte(p + 1) << 8) | (fds_eeprom_read_byte(p + 2) << 16) | (fds_eeprom_read_byte(p + 3) << 24);
    if (Value != existingValue) {
        fds_eeprom_write_byte(p, (uint8_t)Value);
        fds_eeprom_write_byte(p + 1, (uint8_t)(Value >> 8));
        fds_eeprom_write_byte(p + 2, (uint8_t)(Value >> 16));
        fds_eeprom_write_byte(p + 3, (uint8_t)(Value >> 24));
    }
}

void eeprom_read_block(void *buf, const void *addr, size_t len) {
    const uint8_t *p    = (const uint8_t *)addr;
    uint8_t *      dest = (uint8_t *)buf;
    while (len--) {
        *dest++ = eeprom_read_byte(p++);
    }
}

void eeprom_write_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}

void eeprom_update_block(const void *buf, void *addr, size_t len) {
    uint8_t *      p   = (uint8_t *)addr;
    const uint8_t *src = (const uint8_t *)buf;
    while (len--) {
        eeprom_write_byte(p++, *src++);
    }
}
