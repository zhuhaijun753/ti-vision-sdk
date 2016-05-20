/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
-e _reset_handler
-w
-stack 0x1000
--heap_size=0x800
-x

MEMORY
{
    PAGE 0:
    VECMEM:          origin      = 0x80000000, length = 0x0100

    PAGE 1:
    DATMEM_CHECK:    origin      = 0x40020000, length = 0x0100
    DMEM_DATA:       origin      = 0x40020100, length = 0x0e00
    RES_SET_LOC :    origin      = 0x40026000, length = 0x0200
    DATMEM:          origin      = 0x40025000, length = 0x1000
    STACKS:          origin      = 0x40027000, length = 0x1000
    WMEM  :          origin      = 0x40040000, length = 0x8000
    IMEMLA:          origin      = 0x40050000, length = 0x4000
    IMEMHA:          origin      = 0x40054000, length = 0x4000
    IMEMLB:          origin      = 0x40070000, length = 0x4000
    IMEMHB:          origin      = 0x40074000, length = 0x4000
    OCMCRAM:         origin      = 0x40300000, length = 0x0007fe00
    SYNC_AREA:       origin      = 0x4037fe00, length = 0x00000100
    DDR:             origin      = 0x80000100, length = 0x1000000
}



SECTIONS
{
  .intvecs      > VECMEM  PAGE 0
  .inthandler   > DDR     PAGE 1
  .exitlocation > DDR     PAGE 1

  GROUP (my_funcs)  
  { 
      .text:test_main
      .text:prefetch_cache
      .text:eve_array_add_uns_char_init
      .text:eve_array_add_uns_char_vloops
      .text:eve_array_add_uns_char
  } align = 0x8000 > DDR PAGE 1

    .text:         > DDR PAGE 1
    {
      boot_arp32.obj(.inthandler)
      rtsarp32_v200.lib<boot.obj>(.text)
      rtsarp32_v200.lib<autoinit.obj>(.text) 
      rtsarp32_v200.lib<exit.obj> (.text)
      rtsarp32_v200.lib<args_main.obj> (.text)
      rtsarp32_v200.lib<memcpy.obj> (.text)
      rtsarp32_v200.lib<_lock.obj> (.text)
      rtsarp32_v200.lib<pre_init.obj> (.text)
   }
  
  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1


  .vcop_parameter_block   > WMEM   PAGE 1
  .const                  > DATMEM  PAGE 1

  Adata:    load = IMEMLA  PAGE 1
  Bdata:    load = IMEMLA  PAGE 1
  Cdata:    load = IMEMHA  PAGE 1
  Pdata:    load = WMEM  PAGE 1
  Sdata:    > DATMEM_CHECK  PAGE 1
  EOutdata: > DATMEM  PAGE 1
  res_set_sect: > RES_SET_LOC  PAGE 1
  .cint:    > DATMEM  PAGE 1
  .bss :    > DATMEM  PAGE 1
  .data:    > DATMEM  PAGE 1
  .sysmem:  > DATMEM PAGE 1
  .stack:   > STACKS PAGE 1
  SectionSync:  load = SYNC_AREA PAGE 1
  DDRData:  > DDR  PAGE 1
  OCMCRam_data: > OCMCRAM  PAGE 1
  .cio:  > DDR PAGE 1
 .far:       load = DDR  PAGE 1
 .fardata:   load = DDR  PAGE 1
}

