#include "rtos.h"

extern uint32_t get_psp_value(void);
extern void save_psp_value(uint32_t currentPspValue);
extern void update_next_task(void);

__attribute__((naked)) void PendSV_Handler(void)
{
    __asm volatile(

        "MRS R0,PSP                 \n"
        "STMDB R0!,{R4-R11}         \n"
        "PUSH {LR}                  \n"
        "BL save_psp_value          \n"
        "BL update_next_task        \n"
        "BL get_psp_value           \n"
        "LDMIA R0!,{R4-R11}         \n"
        "MSR PSP,R0                 \n"
        "POP {LR}                   \n"
        "BX LR                      \n"
    );
}