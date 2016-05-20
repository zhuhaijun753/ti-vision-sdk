/**
 *  \file     lnk_tda2ex_a15_ocmc.cmd
 *
 *  \brief    This file contains the System Memory Map used by ddr example
 *            for tda2ex SoC.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

 /* ======================================================================
 *  -e Entry
 *   Since we used 'Entry' as the entry-point symbol the compiler issues a
 *   "Entry"). The CCS Version (5.1.0.08000) stops building from command
 *   line when there is a warning. So this warning is suppressed with the
 *   below flag.
 *
 *   --diag_suppress=10063
 * ==================================================================== */

ENTRY(Entry)
MEMORY
{
    IRAM_MEM      : org = 0x402F0000,  len = 0x00010000
    /* SBL Start : SBL will use 256 Bytes of space from address 0x40300000 for
     * while creating tiimage
     * Vector Table will use 256 Bytes of space from address 0x40300100
     */
    OCMCRAM1_1    : org = 0x40300200,  len = (0x00030000 - 0x200)/*OCMC RAM1_1*/
    OCMCRAM1_2    : org = 0x40330000,  len = 0x00010000          /*OCMC RAM1_2*/
    OCMCRAM1_3    : org = 0x40340000,  len = 0x00040000          /*OCMC RAM1_3*/
    /*SBL will use 1 KB of space from address 0x80000000 for EVE */
    DDR3_A15      : org = 0x80000400,  len = (0x0B000000 - 0x400)
    DDR3_DSP      : org = 0x8B000000,  len = 0x02000000
    DDR3_M3VPSS   : org = 0x8D000000,  len = 0x01000000
    DDR3_M3VIDEO  : org = 0x8E000000,  len = 0x01000000
    DDR3_SR0      : org = 0x8F000000,  len = 0x01000000
}




/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{
  .text        : {*(.text)}         > OCMCRAM1_3
  .data        : {*(.data)}         > OCMCRAM1_3
  .bss         : {*(.bss)}          > OCMCRAM1_3
  .const       : {*(.const)}        > OCMCRAM1_3
  .my_sect_ddr : {*(.my_sect_ddr)}  > OCMCRAM1_3
  .            : {*(*)}             > OCMCRAM1_3
  .            : {*(.comment)}      > OCMCRAM1_3
   _stack        = 0x40330000;
  __heap_start__ = 0x40331000;
  __heap_end__   = 0x40339FFF;
  bss_start      = 0x4033A000;
  bss_end        = 0x4033B000;
}