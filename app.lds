OUTPUT_ARCH( "riscv" )

SECTIONS 
{
  . = 0x00001000;
  .text : {
    *(.text._start)
    *(.text)
  }
  . = ALIGN(0x1000);
  .rodata : 
  { 
    *(.rdata)
    *(.rodata)
  }
  .data : { *(.data) }
  .bss : { *(.bss) }
  .debug : { *(.debug) }
  
  . = ALIGN(0x1000);
  .malloc_region : {
    __malloc_start = .;
    . = . + 4096*4;
    __malloc_zone_stop = .;
  }

  _end = .;
}
