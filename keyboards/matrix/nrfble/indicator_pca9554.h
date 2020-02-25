/**
 * @file indicator_pca9554.h
 * @brief indicator with pca9554
 */

#pragma once

#include <stdint.h>

void indicator_pca9554_init(void);
void indicator_pca9554_write(uint8_t out);
