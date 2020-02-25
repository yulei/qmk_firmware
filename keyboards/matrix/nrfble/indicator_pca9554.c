/**
 * @file indicator_pca9554.c
 */

#include "indicator_pca9554.h"
#include "i2c_master.h"

#define PCA9554_ADDR            0x20
#define PCA9554_CMD_INPUT       0
#define PCA9554_CMD_OUTPUT      1
#define PCA9554_CMD_POLARITY    2
#define PCA9554_CMD_CONFIG      3

void indicator_pca9554_init(void)
{
    uint8_t reg[2];

    /* set to output mode */
    reg[0] = PCA9554_CMD_CONFIG;
    reg[1] = 0;
    i2c_transmit(PCA9554_ADDR, reg, sizeof(reg), 0);

    /* clear output register */
    reg[0] = PCA9554_CMD_OUTPUT;
    reg[1] = 0;
    i2c_transmit(PCA9554_ADDR, reg, sizeof(reg), 0);
}

void indicator_pca9554_write(uint8_t out)
{
    uint8_t reg[2];
    /* write to output register */
    reg[0] = PCA9554_CMD_OUTPUT;
    reg[1] = out;

    i2c_transmit(PCA9554_ADDR, reg, sizeof(reg), 0);
}
