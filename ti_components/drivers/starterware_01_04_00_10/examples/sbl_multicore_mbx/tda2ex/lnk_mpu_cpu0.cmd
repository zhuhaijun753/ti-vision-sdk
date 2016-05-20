/**
 *  \file     lnk_mpu_cpu0.cmd
 *
 *  \brief    This file contains the System Memory Map used by MPU CPU0 binary
 *            for multicore mailbox app image.
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

ENTRY(Entry)

/* Specify the System Memory Map */
MEMORY
{
    /* Code Section - 20MB */
    /* Data Section - 10MB */
    /* Stack - 5MB */
    /* Heap - 5MB */

    DDR3_MPU_CPU0_CODE  : org = 0x83200000,  len = 0x01400000
    DDR3_MPU_CPU0_DATA  : org = 0x84600000,  len = 0x00A00000
    DDR3_MPU_CPU0_STACK : org = 0x85000000,  len = 0x00500000
    DDR3_MPU_CPU0_HEAP  : org = 0x85500000,  len = 0x00500000

    DDR3_IPU1_CPU0_CODE  : org = 0x86400000, len = 0x01400000
    DDR3_IPU1_CPU0_DATA  : org = 0x87800000, len = 0x00A00000
    DDR3_IPU1_CPU0_STACK : org = 0x88200000, len = 0x00500000
    DDR3_IPU1_CPU0_HEAP  : org = 0x88700000, len = 0x00500000

    DDR3_IPU1_CPU1_CODE  : org = 0x89600000, len = 0x01400000
    DDR3_IPU1_CPU1_DATA  : org = 0x8AA00000, len = 0x00A00000
    DDR3_IPU1_CPU1_STACK : org = 0x8B400000, len = 0x00500000
    DDR3_IPU1_CPU1_HEAP  : org = 0x8B900000, len = 0x00500000

    DDR3_DSP1_CODE  : org = 0x8C800000,      len = 0x01400000
    DDR3_DSP1_DATA  : org = 0x8DC00000,      len = 0x00A00000
    DDR3_DSP1_STACK : org = 0x8E600000,      len = 0x00500000
    DDR3_DSP1_HEAP  : org = 0x8EB00000,      len = 0x00500000
}

/* Specify the Section Allocation into Memory */
SECTIONS
{
    .init        : {*(.init)}        > DDR3_MPU_CPU0_CODE
    .text        : {*(.text)}        > DDR3_MPU_CPU0_CODE /* Code */
    .data        : {*(.data)}        > DDR3_MPU_CPU0_DATA /* Initialized Global and Static variables */
    .bss         : {*(.bss)}         > DDR3_MPU_CPU0_DATA /* Uninitialized or Zero initialized */
                                                          /* Global and Static Variables       */
    .const       : {*(.const)}       > DDR3_MPU_CPU0_DATA /* Global Constants */
    .cinit       : {*(.cinit)}       > DDR3_MPU_CPU0_DATA
    .my_sect_ddr : {*(.my_sect_ddr)} > DDR3_MPU_CPU0_CODE
    .stack :
    {
        stack_start = .;
        *(.stack.*) ;
        . = . + 0x500000;
        stack_end = .;
    }> DDR3_MPU_CPU0_STACK /* Software System Stack */
    .cio         : {*(CIO)}

    _stack = stack_end;
}

