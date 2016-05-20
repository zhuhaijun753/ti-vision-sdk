/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/****************************************************************************/
/* LNK32.CMD - v4.5.0 COMMAND FILE FOR LINKING TMS470 32BIS C/C++ PROGRAMS  */
/*                                                                          */
/*   Usage:  lnk470 <obj files...>    -o <out file> -m <map file> lnk32.cmd */
/*           cl470 <src files...> -z -o <out file> -m <map file> lnk32.cmd  */
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


ENTRY(SBL_Start)
MEMORY
{

	/*----------------------------------------------------------------------------------*/
    /*  NCS0:  BOOTROM/SECURERAM/EXTERNAL SLOW                                          */
    /*----------------------------------------------------------------------------------*/

    PUBROM   (RIX)	: org = 0x40038000 ,  len = 0x0000C000
    SECRAM   (RIX) : org = 0x402F0000  , len = 0x00010000  /* Internal SRAM      (TDA2XX 64 KB)  */
    OCMCRAM1 (RWIX): org = 0x40300000  , len = 0x00080000  /* OCMC RAM        */
    OCMCRAM3 (RWIX): org = 0x40500000 ,  len = 0x00100000  /* OCMC RAM        */
    LPDDR2   (RWIX): org = 0x9F001000 ,  len = 0x00004000  /* LPDDR2 CA part  ( 512 Mbytes)  */
    SBL_REG_LOG_BFR_SEG  : org = 0x40590000 , len = 0x100  /* SBL Regression test log buffer*/
    PUBROM_EXE      (RIX) : org = 0x00038000  , len = 0x0000C000  /* BootRom Public  (TDA2XX 48 KB)  */
}




/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{
    . = 0x40300000;
  .public  : {*(.public.*)} > OCMCRAM1   /* Public boot code */
  .init : { *(.init.*) }  > OCMCRAM1
  .text : { *(.text) ;*(.text.*); }  > OCMCRAM1
  .data : { *(.data.*) }	> OCMCRAM1
  .bss : { bss_start = . ; *(.bss.*) *(COMMON); bss_end = . ;}	> OCMCRAM1
  .stack :
  {
    stack_start = .;
    *(.stack.*) ;
   . = . + 0x1000;
   stack_end = .;
  }	> OCMCRAM1

  .const : { *(.const.*) }	> OCMCRAM1
  .rodata : {*(.rodata.*) } > OCMCRAM1
  .cinit : { *(.cinit.*) }	> OCMCRAM1
  .cio : { *(CIO) }

  _stack = stack_end;
  _text_size = SIZEOF(.text);
  _data_size = SIZEOF(.data);
  SBL_REGRESSION_LOG_BFR_SEG = 0x40590000;
}










