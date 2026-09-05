ENTRY(Reset_Handler)

MEMORY {
    flash(rx)   : ORIGIN = 0x08000000, LENGTH = 512K
    sram(rwx)   : ORIGIN = 0x20000000, LENGTH = 96K
}

_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS {
    .vector_table   : { KEEP(*(.vector_table)) }    > flash 
    .text           : { *(.text*) }                 > flash
    .rodata         : { *(.rodata*) }               > flash

    .data : {
        _sdata = .;         /* start of .data section */
        *(.first_data)
        *(.data SORT(.data.*))
        _edata = .;         /* end of .data section */
    }   > sram AT > flash

    _sidata = LOADADDR(.data); 

    .bss : {
        _sbss = .;          /* start of .bss section */
        *(.bss SORT(.bss.*) COMMON)
        _ebss = .;          /* end if .bss section */
    } > sram
}
