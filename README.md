# Custom Preemptive RTOS Kernel | ARM Cortex-M4

A bare-metal custom preemptive Real-Time Operating System (RTOS) kernel developed from scratch for ARM Cortex-M4 microcontrollers without using vendor HAL libraries or third-party RTOS frameworks.

This project demonstrates low-level RTOS internals including task scheduling, context switching, ARM exception handling, startup initialization, linker configuration, and peripheral driver development using direct register-level programming.

---

## Key Features

### RTOS Kernel

- Preemptive round-robin scheduler
- SysTick-based task scheduling
- PendSV-based context switching
- Task Control Block (TCB) management
- Separate stack allocation for each task
- Process Stack Pointer (PSP) and Main Stack Pointer (MSP) switching
- Task delay and blocking mechanism
- Idle task implementation
- ARM exception-based context save and restore

### ARM Cortex-M4 Internals

- SysTick timer configuration
- PendSV exception handling
- NVIC interrupt priority management
- Exception stack frame management
- Context switching using hardware and software stacking
- ARM startup sequence implementation

### Peripheral Drivers

Developed using direct register-level programming:

- GPIO Driver
- UART Driver
- SPI Driver
- I2C Driver
- CAN Driver

No STM32 HAL or vendor abstraction libraries are used.

---

## System Architecture

```text
+---------------------------------------------------+
|                Application Layer                  |
|---------------------------------------------------|
| Task1 | Task2 | Task3 | Task4 | Idle Task         |
+---------------------------------------------------+
|                 RTOS Kernel Layer                 |
|---------------------------------------------------|
| Scheduler                                         |
| Task Manager                                      |
| Context Switch Engine                             |
| Delay Manager                                     |
| Tick Manager                                      |
+---------------------------------------------------+
|            Cortex-M Exception Layer               |
|---------------------------------------------------|
| SysTick Handler                                   |
| PendSV Handler                                    |
| Fault Handlers                                    |
+---------------------------------------------------+
|               Driver Layer                        |
|---------------------------------------------------|
| GPIO | UART | SPI | I2C | CAN                     |
+---------------------------------------------------+
|           ARM Cortex-M4 Hardware                  |
+---------------------------------------------------+
```

---

## Context Switching Flow

```text
Task Running
      |
      V
SysTick Interrupt
      |
      V
Tick Counter Update
      |
      V
PendSV Triggered
      |
      V
Save Current Task Context
(R4-R11 + PSP)
      |
      V
Select Next Ready Task
      |
      V
Restore Next Task Context
      |
      V
Resume Execution
```

---

## ARM Cortex-M4 Context Management

### Hardware Automatically Saves

When an exception occurs, Cortex-M4 automatically pushes:

```text
R0
R1
R2
R3
R12
LR
PC
xPSR
```

### Software Saves

PendSV handler additionally saves:

```text
R4
R5
R6
R7
R8
R9
R10
R11
```

This ensures complete CPU context preservation during task switches.

---

## Startup and Memory Initialization

Custom startup implementation performs:

1. Vector table initialization
2. Stack pointer initialization
3. Copying `.data` section from Flash to RAM
4. Clearing `.bss` section
5. System initialization
6. Jump to `main()`

---

## Custom Linker Script

The project uses a custom linker script to define:

- Flash memory layout
- RAM memory layout
- Code section placement
- Data section placement
- BSS section placement
- Stack memory allocation

### Memory Layout

```text
FLASH
---------------------------------
| Vector Table                  |
| Application Code              |
| Read Only Data                |
---------------------------------

RAM
---------------------------------
| .data                         |
| .bss                          |
| Task Stacks                   |
| Scheduler Stack               |
---------------------------------
```

---

## Project Structure

```text
CustomRTOS/
│
├── Core/
│   ├── main.c
│   ├── startup_stm32f4xx.s
│   └── linker.ld
│
├── RTOS/
│   ├── scheduler.c
│   ├── systick.c
│   ├── pendsv_handler.c
│   ├── task.c
│   └── rtos.h
│
├── Drivers/
│   ├── gpio.c
│   ├── uart.c
│   ├── spi.c
│   ├── i2c.c
│   └── can.c
│
├── Debug/
│
└── README.md
```

---

## Development Environment

| Component | Details |
|------------|----------|
| MCU | STM32F4 Series |
| Core | ARM Cortex-M4 |
| Architecture | ARMv7E-M |
| Language | C, ARM Assembly |
| Compiler | arm-none-eabi-gcc |
| Debugger | GDB |
| Debug Interface | JTAG / SWD |
| Programmer | ST-Link |

---

## Debugging and Validation

Validated using:

- GDB register inspection
- SWD debugging
- Context switch verification
- PSP/MSP transition verification
- Scheduler execution tracing
- Interrupt priority validation
- Task stack analysis

---

## Technical Concepts Demonstrated

### RTOS

- Scheduler Design
- Task Management
- Context Switching
- Tick Management
- Stack Management
- ARM Exception Handling

### Embedded Systems

- Bare-Metal Development
- Register-Level Programming
- Linker Scripts
- Startup Assembly
- Interrupt Handling
- Memory Mapping

### Communication Protocols

- SPI
- I2C
- UART
- CAN

---

## Future Enhancements

Planned improvements include:

- Priority-based scheduling
- Semaphores
- Mutexes
- Message queues
- Event groups
- Software timers
- Dynamic task creation
- Memory pool allocator
- Stack overflow detection
- MPU support
- Tickless idle mode

---

## Learning Outcomes

This project provides hands-on experience with:

- RTOS kernel internals
- ARM Cortex-M architecture
- Scheduler implementation
- Context switching mechanisms
- Startup code development
- Linker script development
- Embedded memory architecture
- Low-level debugging techniques
- Real-time embedded systems design

---

## Highlights

- Developed a custom preemptive RTOS kernel for ARM Cortex-M4 from scratch.
- Implemented SysTick and PendSV-based task scheduling and context switching.
- Developed custom startup assembly and linker scripts.
- Performed low-level debugging using GDB and SWD/JTAG interfaces.
- Built SPI, I2C, UART, and CAN drivers using direct register-level programming.
- Gained deep understanding of ARM exception handling, memory architecture, and RTOS internals.