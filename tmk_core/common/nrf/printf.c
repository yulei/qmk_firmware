/**
 * @file printf.c
 */

#include <stdarg.h>
#include "printf.h"
#include "nrf_log.h"

void xprintf(char* fmt, ...)
{
    va_list args = {0};
    va_start(args, fmt);

    NRF_LOG_INFO(fmt, &args);

    va_end(args);
}


