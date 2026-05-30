#include "rtos.h"

extern uint32_t globalTickCount;

void init_systick_timer(uint32_t tickHz)
{
    uint32_t countValue;

    countValue = (16000000 / tickHz) - 1;

    SYST_RVR = countValue;

    SYST_CVR = 0;

    SYST_CSR |= (1 << 1);
    SYST_CSR |= (1 << 0);
    SYST_CSR |= (1 << 2);

    SHPR3 |= (NVIC_PENDSV_PRI << 16);
    SHPR3 |= (NVIC_SYSTICK_PRI << 24);
}

void SysTick_Handler(void)
{
    globalTickCount++;

    unblock_tasks();

    schedule();
}