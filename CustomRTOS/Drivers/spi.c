#include <stdint.h>

#define SPI1_CR1       (*(volatile uint32_t*)0x40013000)
#define SPI1_SR        (*(volatile uint32_t*)0x40013008)
#define SPI1_DR        (*(volatile uint32_t*)0x4001300C)

void spi_init(void)
{
    SPI1_CR1 |= (1 << 2);
    SPI1_CR1 |= (1 << 6);
}

void spi_send(uint8_t data)
{
    while(!(SPI1_SR & (1 << 1)));

    SPI1_DR = data;

    while(SPI1_SR & (1 << 7));
}