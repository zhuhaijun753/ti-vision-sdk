/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
-e _reset_handler
-w
-stack 0x1000
--heap_size=0x800

MEMORY
{
  PAGE 0:
    VECMEM:  origin 	 = 0x80000000, length = 0x0100
    CMDMEM:  origin 	 = 0x80000100, length = 0x0e00
    DDR_CODE: origin     = 0x80001000, length = 0x7000
  PAGE 1:
    DATMEM      : origin = 0x40020000, length = 0x6000
    RES_SET_LOC : origin = 0x40026000, length = 0x0200
    STACKS:  origin 	 = 0x40027000, length = 0x1000
    IMEML :  origin      = 0x40050000, length = 0x4000
    IMEMH :  origin      = 0x40054000, length = 0x4000
    WMEM  :  origin      = 0x40040000, length = 0x8000
    OCMCRAM: origin 	 = 0x40300000, length = 0x0007fe00
    GEM1L2: origin 	     = 0x40810000, length = 0x00010000
    SYNC_AREA: origin 	 = 0x4037fe00, length = 0x00000100
    DDR: origin 	     = 0x80030000, length = 0x00100000
}



SECTIONS
{
	.intvecs	> VECMEM PAGE 0
	.inthandler	> CMDMEM PAGE 0
	.exitlocation	> CMDMEM PAGE 0
	.text: 		> DDR_CODE  PAGE 0
	{
         
	  *.obj(.text)
        }

  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1

  .far         > DATMEM  PAGE 1
  .fardata     > DATMEM  PAGE 1
  .cio         > DATMEM  PAGE 1
  .cinit       > DATMEM  PAGE 1

  Adata:    load = IMEML  PAGE 1
  Bdata:    load = IMEML  PAGE 1
  Cdata:    load = IMEMH  PAGE 1
  Pdata:    load = WMEM   PAGE 1
  Sdata:    > DATMEM      PAGE 1
  EOutdata: > DATMEM       PAGE 1
  res_set_sect: > RES_SET_LOC PAGE 1
  .cint:    > DATMEM PAGE 1
  .bss :    > DATMEM PAGE 1
  .const:   > DATMEM PAGE 1
  .data:    > DATMEM PAGE 1
  .sysmem:  > DATMEM PAGE 1
  .stack:   > STACKS PAGE 1
  .dmem_int_sec > DATMEM PAGE 1
  SectionSync:  load = SYNC_AREA PAGE 1
  DDRData:  > DDR PAGE 1
  OCMCRam_data: > OCMCRAM PAGE 1
  GEM1L2_data: > GEM1L2 PAGE 1
}

