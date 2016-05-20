

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
	MMU_TLB : org = 0x4031C000,len = 0x000004000
	/*CODE SECTION - 20MB*/
	/*DATA SECTION - 10MB*/
	/*STACK - 5MB*/
	/*HEAP - 5MB*/
	DDR3_MPU_CPU0_CODE : org = 0x90000000,len = 0x01400000
	DDR3_MPU_CPU0_DATA :  org = 0x91400000, len = 0x00A00000
	DDR3_MPU_CPU0_STACK : org = 0x91E00000, len = 0x00500000
	DDR3_MPU_CPU0_HEAP :  org = 0x92300000, len = 0x00500000

	DDR3_IPU1_CPU0_CODE : org = 0x93200000,len = 0x01400000
	DDR3_IPU1_CPU0_DATA :  org = 0x94600000, len = 0x00A00000
	DDR3_IPU1_CPU0_STACK : org = 0x95000000, len = 0x00500000
	DDR3_IPU1_CPU0_HEAP :  org = 0x95500000, len = 0x00500000

	DDR3_IPU1_CPU1_CODE : org = 0x96400000,len = 0x01400000
	DDR3_IPU1_CPU1_DATA :  org = 0x97800000,len = 0x00A00000
	DDR3_IPU1_CPU1_STACK : org = 0x98200000,len = 0x00500000
	DDR3_IPU1_CPU1_HEAP :  org = 0x98700000,len = 0x00500000

	DDR3_IPU2_CPU0_CODE : org = 0x99600000,len = 0x01400000
	DDR3_IPU2_CPU0_DATA :  org = 0x9AA00000,len = 0x00A00000
	DDR3_IPU2_CPU0_STACK : org = 0x9B400000,len = 0x00500000
	DDR3_IPU2_CPU0_HEAP :  org = 0x9B900000,len = 0x00500000

	DDR3_IPU2_CPU1_CODE : org = 0x9C800000,len = 0x01400000
	DDR3_IPU2_CPU1_DATA :  org = 0x9DC00000,len = 0x00A00000
	DDR3_IPU2_CPU1_STACK : org = 0x9E600000,len = 0x00500000
	DDR3_IPU2_CPU1_HEAP :  org = 0x9EB00000,len = 0x00500000

	DDR3_DSP1_CODE : org = 0x83200000,len = 0x01400000
	DDR3_DSP1_DATA : org = 0x84600000, len = 0x00A00000
	DDR3_DSP1_STACK :org = 0x85000000, len = 0x00500000
	DDR3_DSP1_HEAP : org = 0x85500000, len = 0x00500000

	DDR3_DSP2_CODE : org = 0x86400000,len = 0x01400000
	DDR3_DSP2_DATA :  org = 0x87800000,len = 0x00A00000
	DDR3_DSP2_STACK : org = 0x88200000,len = 0x00500000
	DDR3_DSP2_HEAP :  org = 0x88700000,len = 0x00500000

	DDR3_EVE1_CODE : org = 0x89000000,len = 0x01400000
	DDR3_EVE1_DATA :  org = 0x8AA00000,len = 0x00A00000
	DDR3_EVE1_STACK : org = 0x8B400000,len = 0x00500000
	DDR3_EVE1_HEAP :  org = 0x8B900000,len = 0x00500000

	DDR3_MPU_CPU1_CODE : org = 0x8C800000,len = 0x01400000
	DDR3_MPU_CPU1_DATA :  org = 0x8DC00000,len = 0x00A00000
	DDR3_MPU_CPU1_STACK : org = 0x8E600000,len = 0x00500000
	DDR3_MPU_CPU1_HEAP :  org = 0x8EB00000,len = 0x00500000
}




/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{
  .init : { *(.init) }  > DDR3_MPU_CPU1_CODE
  .text : { *(.text) }  > DDR3_MPU_CPU1_CODE
  .data : { *(.data) }	> DDR3_MPU_CPU1_DATA
  .bss ALIGN(0x4):
  {
    bss_start = . ;
    *(.bss.*) *(COMMON);
    bss_end = . ;
  }	> DDR3_MPU_CPU1_DATA
  .const : { *(.const) }	> DDR3_MPU_CPU1_DATA
  .cinit : { *(.cinit) }	> DDR3_MPU_CPU1_DATA
  .stack : { *(.stack) }	> DDR3_MPU_CPU1_STACK
  .my_sect_ddr : { *(.my_sect_ddr) }	> DDR3_MPU_CPU1_DATA
  .cio : { *(CIO) }

  _stack = 0x00500000;

}


