#include <stdint.h>

#define I2C1_CR1       (*(volatile uint32_t*)0x40005400)
#define I2C1_DR        (*(volatile uint32_t*)0x40005410)
#define I2C1_SR1       (*(volatile uint32_t*)0x40005414)

void i2c_init(void)
{
    I2C1_CR1 |= (1 << 0);
}

void i2c_start(void)
{
    I2C1_CR1 |= (1 << 8);
}

void i2c_write(uint8_t data)
{
    while(!(I2C1_SR1 & (1 << 7)));

    I2C1_DR = data;
}