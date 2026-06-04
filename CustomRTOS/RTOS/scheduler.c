#include "rtos.h"

extern TCB_t userTasks[MAX_TASKS];
extern uint8_t currentTask;
extern uint32_t globalTickCount;

/* Cortex-M System Handler Control and State Register */
#define SHCSR (*(volatile uint32_t*)0xE000ED24U)

/* Enable UsageFault, BusFault, MemManage Fault */
void enable_processor_faults(void)
{
    SHCSR |= (1U << 16);
    SHCSR |= (1U << 17);
    SHCSR |= (1U << 18);
}

static inline void disable_irq(void)
{
    __asm volatile ("cpsid i");
}

static inline void enable_irq(void)
{
    __asm volatile ("cpsie i");
}

void init_scheduler_stack(uint32_t schedTopOfStack)
{
    __asm volatile("MSR MSP,%0" : : "r"(schedTopOfStack));
}

void init_tasks_stack(void)
{
    uint32_t *psp;

    psp = (uint32_t*)T1_STACK_START;

    for(int i = 0; i < MAX_TASKS; i++)
    {
        userTasks[i].currentState = TASK_READY_STATE;

        /* xPSR */
        *(--psp) = DUMMY_XPSR;

        /* PC */
        *(--psp) = (uint32_t)userTasks[i].taskHandler;

        /* LR */
        *(--psp) = 0xFFFFFFFD;
        /* R11 */
        *(--psp) = 0;

        /* R10 */
        *(--psp) = 0;

        /* R9 */
        *(--psp) = 0;

        /* R8 */
        *(--psp) = 0;

        /* R7 */
        *(--psp) = 0;

        /* R6 */
        *(--psp) = 0;

        /* R5 */
        *(--psp) = 0;

        /* R4 */
        *(--psp) = 0;

        /* R12 */
        *(--psp) = 0;

        /* R3 */
        *(--psp) = 0;

        /* R2 */
        *(--psp) = 0;

        /* R1 */
        *(--psp) = 0;

        /* R0 */
        *(--psp) = 0;


        userTasks[i].pspValue = (uint32_t)psp;

        /* Move to next task stack (1024 bytes) */
        psp = (uint32_t*)((uint8_t*)psp - SIZE_TASK_STACK);
    }
}

uint32_t get_psp_value(void)
{
    return userTasks[currentTask].pspValue;
}

void save_psp_value(uint32_t currentPspValue)
{
    userTasks[currentTask].pspValue = currentPspValue;
}

void switch_sp_to_psp(void)
{
    __asm volatile(
        "PUSH {LR}        \n"
        "BL get_psp_value \n"
        "MSR PSP,R0       \n"
        "POP {LR}         \n"
        "MOV R0,#0x02     \n"
        "MSR CONTROL,R0   \n"
        "BX LR            \n"
    );
}

void update_next_task(void)
{
    uint8_t state;

    for(uint32_t i = 0; i < MAX_TASKS; i++)
    {
        currentTask++;
        currentTask %= MAX_TASKS;

        state = userTasks[currentTask].currentState;

        if((state == TASK_READY_STATE) && (currentTask != 0))
        {
            break;
        }
    }
}

void task_delay(uint32_t tickCount)
{
    disable_irq();

    if(currentTask)
    {
        userTasks[currentTask].blockCount =
            globalTickCount + tickCount;

        userTasks[currentTask].currentState =
            TASK_BLOCKED_STATE;

        schedule();
    }

    enable_irq();
}

void unblock_tasks(void)
{
    for(int i = 1; i < MAX_TASKS; i++)
    {
        if(userTasks[i].currentState != TASK_READY_STATE)
        {
            if(userTasks[i].blockCount <= globalTickCount)
            {
                userTasks[i].currentState =
                    TASK_READY_STATE;
            }
        }
    }
}

void schedule(void)
{
    INT_CTRL |= PENDSV_SET_BIT;
}