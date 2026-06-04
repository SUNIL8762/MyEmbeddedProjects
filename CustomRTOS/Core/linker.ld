ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Initial MSP value */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    /* Vector table */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Code + constants */
    .text :
    {
        . = ALIGN(4);

        *(.text*)
        *(.rodata*)

        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /* Initialized variables in RAM */
    .data :
    {
        . = ALIGN(4);

        _sdata = .;

        *(.data*)

        . = ALIGN(4);
        _edata = .;

    } > SRAM AT > FLASH

    /* Flash address of .data image */
    _sidata = LOADADDR(.data);

    /* Zero initialized variables */
    .bss :
    {
        . = ALIGN(4);

        _sbss = .;

        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;

    } > SRAM

    /* End of RAM used by program */
    _end = .;
}