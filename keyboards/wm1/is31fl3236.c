#include <avr/io.h>
#include "i2c_master.h"
#include "is31fl3236.h"

static int is3236_write_register(uint8_t reg_addr, uint8_t reg_data);
/*static uint8_t is3236_index_to_state_register(int index);
static uint8_t is3236_index_to_color_register(int index);
static uint8_t is3236_index_to_pwm_register(int index);
*/
void is3236_init(void)
{
    /**
     * hardware enable
     */
    DDRF |= (1<<0);
    PORTF |= (1<<0);

    /**
     * software enable 
     */
    is3236_write_register(IS3236_REG_SHUTDOWN, 0x01);
}

void is3236_set_led_state(int index, uint8_t on, uint8_t cur)
{
    uint8_t state = on ? 0x10 : 0x00;
    is3236_write_register(IS3236_REG_CTRL_OUT1 + 3*(index-1), state);
    is3236_write_register(IS3236_REG_CTRL_OUT1 + 3*(index-1) + 1, state);
    is3236_write_register(IS3236_REG_CTRL_OUT1 + 3*(index-1) + 2, state);
}

void is3236_set_led_color(int index, uint8_t r, uint8_t g, uint8_t b)
{}

void is3236_set_led_pwm(int index, uint8_t pwm)
{
    is3236_write_register(IS3236_REG_CTRL_OUT1 + 3*(index-1), pwm);
    is3236_write_register(IS3236_REG_CTRL_OUT1 + 3*(index-1) + 1, pwm);
    is3236_write_register(IS3236_REG_CTRL_OUT1 + 3*(index-1) + 2, pwm);
}

void is3236_shutdown(void)
{
    is3236_write_register(IS3236_REG_SHUTDOWN, 0x00);
}

void is3236_update(void)
{
    is3236_write_register(IS3236_REG_UPDATE, 0x00);
}

int is3236_write_register(uint8_t reg_addr, uint8_t reg_data)
{
    i2c_start(IS3236_ADDR|I2C_WRITE);
    i2c_write(reg_addr);
    i2c_write(reg_data);
    i2c_stop();
    return 0;
}

/*
uint8_t is3236_index_to_state_register(int index)
{
    return 0;
}

uint8_t is3236_index_to_color_register(int index)
{
    return 0;
}

uint8_t is3236_index_to_pwm_register(int index)
{
    return 0;
}
*/
