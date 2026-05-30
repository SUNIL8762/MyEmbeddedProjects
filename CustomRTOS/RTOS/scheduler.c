#include "rtos.h"
    __asm volatile(
        "PUSH {LR}             \n"
        "BL get_psp_value      \n"
        "MSR PSP,R0            \n"
        "POP {LR}              \n"
        "MOV R0,#0x02          \n"
        "MSR CONTROL,R0        \n"
        "BX LR                 \n"
    );
}

uint32_t get_psp_value(void)
{
    return userTasks[currentTask].pspValue;
}

void save_psp_value(uint32_t currentPspValue)
{
    userTasks[currentTask].pspValue = currentPspValue;
}

void update_next_task(void)
{
    uint8_t state = TASK_BLOCKED_STATE;

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
    __disable_irq();

    if(currentTask)
    {
        userTasks[currentTask].blockCount = globalTickCount + tickCount;
        userTasks[currentTask].currentState = TASK_BLOCKED_STATE;

        schedule();
    }

    __enable_irq();
}

void unblock_tasks(void)
{
    for(int i = 1; i < MAX_TASKS; i++)
    {
        if(userTasks[i].currentState != TASK_READY_STATE)
        {
            if(userTasks[i].blockCount == globalTickCount)
            {
                userTasks[i].currentState = TASK_READY_STATE;
            }
        }
    }
}

void schedule(void)
{
    INT_CTRL |= PENDSV_SET_BIT;
}