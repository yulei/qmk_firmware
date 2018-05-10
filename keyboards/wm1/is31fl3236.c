#include <avr/io.h>
#include "i2c.h"
#include "is31fl3236.h"

static int is3236_write_register(uint8_t reg_addr, uint8_t reg_data);

void is3236_init(void)
{
    i2c_master_start(0);

    is3236_write_register(IS3236_REG_SHUTDOWN, 0x01);
}

void is3226_set_led_state(int index, uint8_t on, uint8_t cur)
{}

void is3236_set_led_color(int index, uint8_t r, uint8_t g, uint8_t b)
{}

void is3236_set_led_pwm(int index, uint8_t pwm)
{}

void is3236_shutdown(void)
{}

int is3236_write_register(uint8_t reg_addr, uint8_t reg_data)
{
    return -1;
}
