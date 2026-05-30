#ifndef RTOS_H
#define RTOS_H

#include <stdint.h>

#define MAX_TASKS              5
#define DUMMY_XPSR             0x01000000U
#define SIZE_TASK_STACK        1024U
#define TICK_HZ                1000U

#define TASK_READY_STATE       0x00
#define TASK_BLOCKED_STATE     0xFF

#define SYST_CSR               (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR               (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR               (*(volatile uint32_t*)0xE000E018)

#define INT_CTRL               (*(volatile uint32_t*)0xE000ED04)
#define SHPR3                  (*(volatile uint32_t*)0xE000ED20)

#define PENDSV_SET_BIT         (1 << 28)

#define NVIC_PENDSV_PRI        0xFF
#define NVIC_SYSTICK_PRI       0xFE

#define SRAM_START             0x20000000U
#define SRAM_SIZE              (128 * 1024)
#define SRAM_END               ((SRAM_START) + (SRAM_SIZE))

#define T1_STACK_START         SRAM_END
#define T2_STACK_START         (SRAM_END - SIZE_TASK_STACK)
#define T3_STACK_START         (SRAM_END - (2 * SIZE_TASK_STACK))
#define T4_STACK_START         (SRAM_END - (3 * SIZE_TASK_STACK))
#define IDLE_STACK_START       (SRAM_END - (4 * SIZE_TASK_STACK))


typedef struct
{
    uint32_t pspValue;
    uint32_t blockCount;
    uint8_t currentState;
    void (*taskHandler)(void);

}TCB_t;

void init_scheduler_stack(uint32_t schedTopOfStack);
void init_tasks_stack(void);
void switch_sp_to_psp(void);
void enable_processor_faults(void);
void systick_timer_init(uint32_t tickHz);
void schedule(void);
void task_delay(uint32_t tickCount);
void update_next_task(void);
void init_systick_timer(uint32_t tickHz);
void idle_task(void);

#endif