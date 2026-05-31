#include "rtos.h"
#include "gpio.h"

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

TCB_t userTasks[MAX_TASKS];

uint32_t taskStack[MAX_TASKS][SIZE_TASK_STACK];

uint8_t currentTask = 1;
uint32_t globalTickCount = 0;

int main(void)
{
    gpio_init();
    enable_processor_faults();

    //init_scheduler_stack(T1_STACK_START);

    userTasks[0].taskHandler = idle_task;
    userTasks[1].taskHandler = task1_handler;
    userTasks[2].taskHandler = task2_handler;
    userTasks[3].taskHandler = task3_handler;
    userTasks[4].taskHandler = task4_handler;

    init_tasks_stack();

    init_systick_timer(TICK_HZ);

    switch_sp_to_psp();

    task1_handler();

    while(1);
}

void task1_handler(void)
{
    while(1)
    {
        
        gpio_toggle();
        for(uint32_t i = 0; i < 100000; i++);
    }
}

void task2_handler(void)
{
    while(1)
    {
        for(uint32_t i = 0; i < 100000; i++);
    }
}

void task3_handler(void)
{
    while(1)
    {
        for(uint32_t i = 0; i < 100000; i++);
    }
}

void task4_handler(void)
{
    while(1)
    {
        for(uint32_t i = 0; i < 100000; i++);
    }
}

void idle_task(void)
{
    while(1);
}