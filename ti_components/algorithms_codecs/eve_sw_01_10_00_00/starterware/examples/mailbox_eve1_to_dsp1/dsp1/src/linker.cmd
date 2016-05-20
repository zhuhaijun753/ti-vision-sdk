/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
--heap_size=0x800

MEMORY {
        L2ROM:		o = 0x007E0000, l = 0x4000
        L1PRAM:		o = 0x00E00000, l = 0x8000
        L1DRAM :	o = 0x00F00000, l = 0x8000
        L2RAM:		o = 0x00800000, l = 0x10000
        L2DATA:		o = 0x00810000, l = 0x10000

	OCMCRAM:	o = 0x40300000, l = 0x0007fe00
	SYNC_AREA	o = 0x4037fe00, l = 0x00000100
	DDR		o = 0x80000000, l = 0x80000000
}

SECTIONS
{
    GROUP
    {
        .vects:      {. = align(8);}
	    .l2_int:     {. = align(8);}
        .switch:     {. = align(8);}	
        .const:      {. += 0x100;}	
        .text:       {. = align(4);}   
        .int_code:   {. = align(4);}   
        .lib_code:   {. = align(4);}   
        .sysinit:    {. = align(4);}   
        .syssaram:   {. = align(4);}   
        .cinit:	     {. = align(4);}
        .pinit:	     {. = align(4);}
        .data16:     {. = align(2);}
        .data:       {. = align(2);} 
        .bss:	     {. = align(8);} 
        .far:	     {. = align(8);} 
	    .sysmem:     {. = align(16);}
	     gem_l2ram_usr_init:   {. = align(8);}
	     gem_l2ram_usr_uninit: {. = align(8);}
        .stack:	     {. = align(8);}
        .sysstack:   {. = align(8);}
        .cio:        {. = align(8);}
   } > L2RAM

   SectionSync:  load = SYNC_AREA
   GEM1L2_data: > L2DATA
}
