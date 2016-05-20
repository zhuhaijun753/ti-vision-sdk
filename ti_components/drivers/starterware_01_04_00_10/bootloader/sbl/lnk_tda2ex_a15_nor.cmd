/**
 *  \file     lnk_tda2ex_a15_nor.cmd
 *
 *  \brief    This file contains the System Memory Map used by Secondary
 *            Bootloader (SBL) for NOR boot mode for tda2ex SoC.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
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

/* SPECIFY THE SYSTEM MEMORY MAP */
ENTRY(nor_lowlevel_init)
MEMORY
{
    OCMCRAM1_0 (RIX):   org = 0x40300000, len = 0x00000100
    /* Reserved space for Vector Table */
    OCMCRAM1_1 (RIX):   org = 0x40300100, len = 0x00000100
    OCMCRAM1_2 (RIX):   org = 0x40300200, len = 0x0007FE00
    NOR_MEM0 (RWIX) :   org = 0x08000000, len = 0x00000300
    NOR_MEM1 (RWIX) :   org = 0x08000300, len = 0x03FFFD00
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    . = 0x08000000;
	.sbl_start : {*(.sbl_start.*)} > NOR_MEM0
    .public    : {*(.public.*)} > NOR_MEM1
    .init      : { *(.init.*) } > NOR_MEM1
    .text      : { *(.text) ;*(.text.*); }  > NOR_MEM1
    .data      :
    {
        data_start = .;
        *(.data.*);
        data_end = .;
    } > OCMCRAM1_2 AT>NOR_MEM1
    .bss       :
    {
        bss_start = .;
        *(.bss.*) *(COMMON);
        bss_end = .;
    } > OCMCRAM1_2 AT>NOR_MEM1
    .stack     :
    {
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x1000;
        stack_end = .;
    } > OCMCRAM1_2
    .const     : { *(.const.*) } > NOR_MEM1
    .rodata    : {*(.rodata.*) } > NOR_MEM1

    data_start_ldr = LOADADDR(.data);
    _stack = stack_end;
    _text_size = SIZEOF(.text);
    _data_size = SIZEOF(.data);
}
