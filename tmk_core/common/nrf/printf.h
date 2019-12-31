/**
 * @file printf.h
 */

#pragma once

void nrf_rtt_printf(char *fmt, ...);

#define printf nrf_rtt_printf
#define sprintf nrf_rtt_printf
