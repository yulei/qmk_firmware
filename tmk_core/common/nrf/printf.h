/**
 * @file printf.h
 */

#pragma once

void xprintf(char* fmt, ...);

#define printf xprintf
#define sprintf xprintf
