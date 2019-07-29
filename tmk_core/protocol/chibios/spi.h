/**
 * spi.h
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void SPI_init(void);
void SPI_begin(void);
void SPI_end(void);

void SPI_select(void);
void SPI_unselect(void);
void SPI_send(const void* buffer, uint32_t len);
void SPI_recv(void* buffer, uint32_t len);
void SPI_exchange(const void* tx_buf, void* rx_buf, uint32_t len);

#ifdef __cplusplus
}
#endif
