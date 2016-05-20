

/****************************************************************************/
/* LNK32.CMD - v4.5.0 COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS  */
/*                                                                          */
/*   Usage:  armlnk <obj files...>    -o <out file> -m <map file> lnk32.cmd */
/*           armcl <src files...> -z -o <out file> -m <map file> lnk32.cmd  */
/*                                                                          */
/*   Description: This file is a sample command file that can be used       */
/*                for linking programs built with the TMS470 C/C++          */
/*                Compiler.   Use it as a guideline; you may want to change */
/*                the allocation scheme according to the size of your       */
/*                program and the memory layout of your target system.      */
/*                                                                          */
/*   Notes: (1)   You must specify the directory in which run-time support  */
/*                library is located.  Either add a "-i<directory>" line to */
/*                this file, or use the system environment variable C_DIR   */
/*                to specify a search path for libraries.                   */
/*                                                                          */
/*          (2)   If the run-time support library you are using is not      */
/*                named below, be sure to use the correct name here.        */
/*                                                                          */
/****************************************************************************/
/*-stack  0x0800                              SOFTWARE STACK SIZE           */
/*-heap   0x2000                              HEAP AREA SIZE                */
/*-e Entry*/
/* Since we used 'Entry' as the entry-point symbol the compiler issues a    */
/* warning (#10063-D: entry-point symbol other than "_c_int00" specified:   */
/* "Entry"). The CCS Version (5.1.0.08000) stops building from command      */
/* line when there is a warning. So this warning is suppressed with the     */
/* below flag. */

/*--diag_suppress=10063*/


ENTRY(Entry)
MEMORY
{
	
	IRAM_MEM : org = 0x40300000,len = 0x1C000
	OCMC_RAM2 : org = 0x40400000,len = 0x100000
	MMU_TLB : org = 0x4031C000,len = 0x000004000
	DDR3_A8 : org = 0x80000000,len = 0x0B000000
	DDR3_DSP : org = 0x8B000000,len = 0x02000000
	DDR3_M3VPSS : org = 0x8D000000,len = 0x01000000
	DDR3_M3VIDEO : org = 0x8E000000,len = 0x01000000
	DDR3_SR0 : org = 0x8F000000,len = 0x01000000
	GPMC_NOR :    org = 0x08000000, len = 0x04000000 
}




/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{
 
  . = 0x40400000;
  .init : { *(.init) }  > OCMC_RAM2
  .text : { *(.text) }  > OCMC_RAM2
  .data : { *(.data) }	> OCMC_RAM2
  .bss : { *(.bss) }	> OCMC_RAM2
  .const : { *(.const) }	> OCMC_RAM2
  .cinit : { *(.cinit) }	> OCMC_RAM2
  .stack : { *(.stack) }	> OCMC_RAM2
  .cio : { *(CIO) }

 
  _stack = 0x800;
  __heap_start__ = 0x40500000;
  __heap_end__ = 0x40528FFF;
  __TI_STACK_BASE = 0x4052FFFF;
  __TI_STACK_SIZE = 0x8000;
  stack_start = 0x40301000;  
  bss_start      = 0x80343000;
  bss_end        = 0x80344000;
  end = 0x0;
}


 
 







