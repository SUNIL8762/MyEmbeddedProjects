#include <stdint.h>

extern int main(void);

extern uint32_t _estack;

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void Default_Handler(void);

void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

__attribute__((used,section(".isr_vector")))
const uint32_t vector_table[] =
{
    (uint32_t)&_estack,            /* 0 Initial MSP */
    (uint32_t)Reset_Handler,       /* 1 Reset */

    (uint32_t)Default_Handler,     /* 2 NMI */
    (uint32_t)HardFault_Handler,   /* 3 HardFault */
    (uint32_t)MemManage_Handler,   /* 4 MemManage */
    (uint32_t)BusFault_Handler,    /* 5 BusFault */
    (uint32_t)UsageFault_Handler,  /* 6 UsageFault */

    0,                             /* 7 Reserved */
    0,                             /* 8 Reserved */
    0,                             /* 9 Reserved */
    0,                             /* 10 Reserved */

    (uint32_t)SVC_Handler,         /* 11 SVCall */
    (uint32_t)DebugMon_Handler,    /* 12 Debug Monitor */
    0,                             /* 13 Reserved */

    (uint32_t)PendSV_Handler,      /* 14 PendSV */
    (uint32_t)SysTick_Handler      /* 15 SysTick */
};

void Reset_Handler(void)
{
    uint32_t *pSrc;
    uint32_t *pDst;

    /* Copy .data from FLASH to SRAM */
    pSrc = &_sidata;
    pDst = &_sdata;

    while(pDst < &_edata)
    {
        *pDst++ = *pSrc++;
    }

    /* Clear .bss */
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

void HardFault_Handler(void)
{
    while(1);
}

void MemManage_Handler(void)
{
    while(1);
}

void BusFault_Handler(void)
{
    while(1);
}

void UsageFault_Handler(void)
{
    while(1);
}
void SVC_Handler(void)
{
    Default_Handler();
}

void DebugMon_Handler(void)
{
    Default_Handler();
}