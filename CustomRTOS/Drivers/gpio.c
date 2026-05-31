#include <stdint.h>

#define RCC_AHB1ENR      (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER      (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR        (*(volatile uint32_t*)0x40020014)

void gpio_init(void)
{
    RCC_AHB1ENR |= (1 << 0);

    GPIOA_MODER |= (1 << 10);
}

void gpio_toggle(void)
{
    GPIOA_ODR ^= (1 << 5);
}

