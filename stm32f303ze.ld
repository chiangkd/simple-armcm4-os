/* entry point */
ENTRY(reset_handler)

MEMORY
{
    FLASH (rx): ORIGIN = 0x8000000, LENGTH = 512K
    SRAM (rwx): ORIGIN = 0X20000000, LENGTH = 64K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))  /* vector table */
        *(.text)        /* code section */
        *(.text.*)      /* section merging */
        *(.rodata)
        *(.rodata.*)
        _etext = .;     /* The End of .text section */
    } >FLASH

    .data : AT (_etext)
    {
        _sidata = .;
        *(.data)
        *(.data.*)
        _edata = .;
    } >SRAM 

    .bss :
    {
        _sbss = .;
        *(.bss)
        _ebss = .;
    } > SRAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}