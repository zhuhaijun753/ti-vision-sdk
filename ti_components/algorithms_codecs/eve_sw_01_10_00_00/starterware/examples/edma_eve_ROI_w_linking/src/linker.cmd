/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
-e _reset_handler
-stack 0x4000
-heap  0x3000

MEMORY
{
    PAGE 0:
      VECMEM  :    origin      = 0x80000000, length = 0x0100
      CMDMEM  :    origin      = 0x80000100, length = 0x1000
      EXTMEM  :    origin      = 0x80001100, length = 0x10000

    PAGE 1:
      DATMEM  :    origin = 0x40020000 length = 0x8000
      WMEM    :    origin = 0x40040000 length = 0x7E00
      IMEMLA  :    origin = 0x40050000 length = 0x4000
      IMEMHA  :    origin = 0x40054000 length = 0x4000
      IMEMLB  :    origin = 0x40070000 length = 0x4000
      IMEMHB  :    origin = 0x40074000 length = 0x4000
      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
      EXTDMEM :    origin = 0x80008000 length = 0x1000000
}

SECTIONS
{
	.intvecs      > VECMEM  PAGE 0
  .inthandler   > CMDMEM  PAGE 0
  .exitlocation > CMDMEM  PAGE 0
  
  .text > EXTMEM   PAGE 0
  {
    *(.text)
	}

   GROUP
   {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
    }>DATMEM  PAGE 1

  .const         load = DATMEM       PAGE 1
  Adata:         load = IMEMLA       PAGE 1
  Bdata:         load = IMEMHA       PAGE 1
  Cdata:         load = WMEM         PAGE 1
  EOutdata:      load = DATMEM       PAGE 1
  Sdata:         load = DATMEM       PAGE 1
  .cint:         load = DATMEM       PAGE 1
  .bss :         load = DATMEM       PAGE 1
  .data:         load = DATMEM       PAGE 1
   SRC_REGION:   load = EXTDMEM      PAGE 1
   DST1_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST2_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST3_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST4_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST5_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST6_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST7_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST8_REGION:  load = GEM0_L2_MEM  PAGE 1
   DST_REGION:   load = DATMEM       PAGE 1

  .cinit:   load = EXTDMEM  PAGE 1
  .ci0:     load = DATMEM   PAGE 1
  .far:     load = DATMEM   PAGE 1
  .fardata: load = DATMEM   PAGE 1
  .stack:   load = EXTDMEM  PAGE 1
  .sysmem:  load = EXTDMEM  PAGE 1

  
   SRC_MEM        > EXTDMEM  PAGE 1
   DST_MEM        > EXTDMEM  PAGE 1
   EXT_MEM        > EXTDMEM  PAGE 1

   IBUFLA         > IMEMLA   PAGE 1
   IBUFHA         > IMEMHA   PAGE 1
   IBUFLB         > IMEMLB   PAGE 1
   IBUFHB         > IMEMHB   PAGE 1
   WBUF           > WMEM     PAGE 1
   .vcop_parameter_block > WMEM PAGE 1


}
