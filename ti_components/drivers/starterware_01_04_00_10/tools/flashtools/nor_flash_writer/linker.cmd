/*
 * TI Booting and Flashing Utilities
 *
 * Copyright 2007 by Spectrum Digital Incorporated.
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 *  Linker command file
 *
 */
/* -l rtsv5_A_le_eabi.lib */
/*-l rts32e.lib */

-stack          0x00004000      /* Stack Size */
-heap           0x00004000      /* Heap Size */

/* __S_STACK_SIZE = 0x80;      *//* SUPERVISOR Stack */

MEMORY
{
   DRAM:        o = 0x80500000  l = 0x0100000 
   GPMC_NOR:    o = 0x08000000  l = 0x04000000 /* 64 MB */
}

SECTIONS
{
    .bss        >   DRAM
    .cinit      >   DRAM 
    .cio        >   DRAM
    .const      >   DRAM 
    .stack      >   DRAM 
    .sysmem     >   DRAM 
    .text       >   DRAM 
    .DRAM       >   DRAM 
	.far		>	DRAM	
	.switch		> 	DRAM	
	.data		>  	DRAM 
	.gpmc_mem	>	GPMC_NOR
}
