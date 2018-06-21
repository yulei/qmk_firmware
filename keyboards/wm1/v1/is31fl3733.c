/**
 * is31fl3733.c
 */

#include <avr/io.h>
#include <print.h>
#include "i2c_master.h"
#include "is31fl3733.h"

static int is3733_write_register(uint8_t reg_addr, uint8_t reg_data);

void is3733_init(void)
{
    int ret = 0;
    /*
     * hardware enable
     */
    ret = is3733_write_register(IS3733_REG_WRITELOCK, 0xC5);
    if (ret != 0) 
        print("failed to unlock command register");
    /*
     * set page 3
     */
    ret = is3733_write_register(IS3733_REG_COMMAND, 0x03);
    if (ret !=0 )
        print("failed to set page 3");

    /*
     * enable chip
     */
    ret = is3733_write_register(IS3733_REG_CONFIG, 0x01);
    if (ret !=0)
        print("failed to enable chip");
}

void is3733_set_led_state(int index, uint8_t on, uint8_t cur)
{}
void is3733_set_led_color(int index, uint8_t r, uint8_t g, uint8_t b)
{}
void is3733_set_led_pwm(int index, uint8_t pwm)
{}
void is3733_shutdown(void)
{}

int is3733_write_register(uint8_t reg_addr, uint8_t reg_data)
{
    int ret = 0;
    ret = i2c_start(IS3733_ADDR|I2C_WRITE);
    if (ret!=0)
        return ret;
    ret = i2c_write(reg_addr);
    if (ret!=0)
        return ret;
    ret = i2c_write(reg_data);
    if (ret!=0)
        return ret;
    i2c_stop();
    return ret;
}
