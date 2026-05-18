OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
  . = 0x400000;

  .text : {
    *(.text .text.*)
  }

  . = ALIGN(0x1000);
  .rodata : {
    . = ALIGN(16);
    *(.rodata .rodata.*)
  }

  . = ALIGN(0x1000);
  .data : {
    . = ALIGN(16);
    *(.data .data.*)
  }

  .bss : {
    . = ALIGN(16);
    *(.bss .bss.*)
    *(COMMON)
  }
}