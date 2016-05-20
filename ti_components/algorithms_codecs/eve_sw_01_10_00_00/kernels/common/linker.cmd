/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
-e _reset_handler
-heap  0x1000
-stack 0x1000

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
      EXTDMEM :    origin = 0x80030000 length = 0x1000000
      L3MEM   :    origin = 0x40300000, length = 0x100000
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
  }>DATMEM PAGE 1

  .const       > DATMEM  PAGE 1
  Adata        > IMEMLA  PAGE 1
  Bdata        > IMEMHA  PAGE 1
  Cdata        > WMEM    PAGE 1
  EOutdata     > DATMEM  PAGE 1
  Sdata        > DATMEM  PAGE 1
  Udata        > WMEM    PAGE 1
  Vdata        > WMEM    PAGE 1
  Ydata        > WMEM    PAGE 1
  .cint        > DATMEM  PAGE 1
  .stack       > DATMEM  PAGE 1
  .sysmem      > DATMEM  PAGE 1
  .cinit       > DATMEM  PAGE 1
  .cio         > DATMEM  PAGE 1
  .far         > DATMEM  PAGE 1
  .fardata     > DATMEM  PAGE 1
  .init_array  > DATMEM  PAGE  1
  .vcop_parameter_block > WMEM PAGE 1
}
