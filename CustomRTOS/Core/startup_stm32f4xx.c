#include <stdint.h>

extern int main(void);

extern uint32_t _estack;

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((used,section(".isr_vector")))
const uint32_t vector_table[] =
{
    (uint32_t)&_estack,        // Initial MSP
    (uint32_t)Reset_Handler,   // Reset
    (uint32_t)Default_Handler, // NMI
    (uint32_t)Default_Handler, // HardFault
    (uint32_t)Default_Handler, // MemManage
    (uint32_t)Default_Handler, // BusFault
    (uint32_t)Default_Handler, // UsageFault
};

void Reset_Handler(void)
{
    uint32_t *pSrc;
    uint32_t *pDst;

    /* Copy .data from FLASH to SRAM */
    pSrc = &_etext;
    pDst = &_sdata;

    while(pDst < &_edata)
    {
        *pDst++ = *pSrc++;
    }

    /* Zero initialize .bss */
    pDst = &_sbss;

    while(pDst < &_ebss)
    {
        *pDst++ = 0;
    }

    main();

    while(1);
}

void Default_Handler(void)
{
    while(1);
}