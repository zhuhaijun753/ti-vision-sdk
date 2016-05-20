@;*******************************************************************************
@;
@; Cache_a15_gcc.asm - A15 Cache assembly code
@;
@;*******************************************************************************
@;
@; Copyright (C) 2015 Texas Instruments Incorporated
@;
@; All rights reserved. Property of Texas Instruments Incorporated.
@; Restricted rights to use, duplicate or disclose this code are
@; granted through contract.
@;
@; The program may not be used without the written permission
@; of Texas Instruments Incorporated or against the terms and conditions
@; stipulated in the agreement under which this program has been
@; supplied.
@;
@;
@;*******************************************************************************

@;****************************** Global Symbols *********************************
        .global CACHEA15GetEnabledASM

@;******************************* Code Section **********************************

@;================ CACHEA15GetEnabledASM ================
        .text
        .func CACHEA15GetEnabledASM

CACHEA15GetEnabledASM:
        mov     r0, #0
        mrc     p15, #0, r1, c1, c0, #0 @ fetch Control Register into r1

        @ Check if program cache enabled
        tst     r1, #0x1000             @ test I bit (bit 12) for program cache
        addne   r0, r0, #5              @ if I bit is true, program caches are
                                        @ enabled

        @ Check if data cache enabled
        tst     r1, #0x0004             @ test C bit (bit 2) for data cache
        addne   r0, r0, #0xa            @ if C bit is true, L1D and unified L2
                                        @ data cache is enabled

        @ Check if all cache enabled
        cmp     r0, #0xf
        movweq  r0, #0x7fff

        bx      lr
        .endfunc

