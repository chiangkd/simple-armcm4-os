/* entry point */
ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx): ORIGIN = 0x8000000, LENGTH = 512K
    SRAM (rwx): ORIGIN = 0X20000000, LENGTH = 64K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .text :
    {
        *(.isr_vector)  /* vector table */
        *(.text)        /* code section */
        *(.text.*)      /* section merging */
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
        _etext = .;     /* The End of .text section */
    }> FLASH

    .data :
    {
        _sidata = LOADADDR(.data);
        _sdata = .; /* Location counter always tracks VMA of the section */
                    /* in which it is being used (_sdata = 0x20000000) */
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT> FLASH

    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
        . = ALIGN(4);
        end = .;
        __end__ = .;
    } > SRAM
}