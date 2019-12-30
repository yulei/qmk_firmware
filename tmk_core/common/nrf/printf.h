/**
 * @file printf.h
 */

#pragma once

void nrf_rtt_printf(char *fmt, ...);
#define __xprintf nrf_rtt_printf
