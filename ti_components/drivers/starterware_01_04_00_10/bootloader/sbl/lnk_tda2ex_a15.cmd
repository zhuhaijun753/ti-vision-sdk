/**
 *  \file     lnk_tda2ex_a15.cmd
 *
 *  \brief    This file contains the System Memory Map used by Secondary
 *            Bootloader (SBL) for QSPI and SD boot mode for tda2ex SoC.
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
ENTRY(SBL_Start)
MEMORY
{
    OCMCRAM1_0 (RIX):   org = 0x40300000, len = 0x00000100
    /* Reserved space for Vector Table */
    OCMCRAM1_1 (RIX):   org = 0x40300100, len = 0x00000100
    OCMCRAM1_2 (RIX):   org = 0x40300200, len = 0x0007FE00
}

/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{
    . = 0x40300000;
    .sbl_start : {*(.sbl_start.*)} > OCMCRAM1_0
    .public    : {*(.public.*)} > OCMCRAM1_2
    .init      : { *(.init.*) } > OCMCRAM1_2
    .text      : { *(.text) ;*(.text.*); } > OCMCRAM1_2
    .data      : { *(.data.*) } > OCMCRAM1_2
    .bss       :
    {
        bss_start = .;
        *(.bss.*) *(COMMON);
        bss_end = .;
    } > OCMCRAM1_2
    .stack     :
    {
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x1000;
        stack_end = .;
    } > OCMCRAM1_2
    .const     : { *(.const.*) } > OCMCRAM1_2
    .rodata    : {*(.rodata.*) } > OCMCRAM1_2
    .cinit     : { *(.cinit.*) } > OCMCRAM1_2
    .cio       : { *(CIO) }

    _stack     = stack_end;
    _text_size = SIZEOF(.text);
    _data_size = SIZEOF(.data);
}
