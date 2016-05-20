 @******************************************************************************
@* initmmu v#####                                                               *
@* Copyright (c) 2008@%%%% Texas Instruments Incorporated                     *
@* Author: Jay Shastry: Modified the original SDO code for cortex A8 on OMAP3 *
@* device																	  *
@******************************************************************************

        .text
	.code 32
	.align 4

#define Fault     00B             @ constant defines for level 1 pagetable
#define Section           0x02
#define B                 0x04
#define C                 0x08
#define TTBit             0x010
@Domain            111100000B
#define Domain            0x0
#define FullAccess        0x0C00

@ttb_first_level .field 0x80000000
@ttb_first_level .field 0x4020C000
#define ttb_first_level 0x4031C000
#define domain_val      0xffffffff
#define loop_count      0xfff
@ added by P.Aberl
@loop_count_2    .field 0x6FF, 32
#define loop_count_2    0x5FF

        .global  ARM_InitMMUentry
@        .armfunc ARM_InitMMUentry

ARM_InitMMUentry: 

@ if MMU/MPU enabled - disable it (useful for ARMulator tests)
@ also disable the caches and and invalidate the TLBs
@ NOTE: this would not be required from a cold reset
         
        MRC     p15, #0, r0, c1, c0, #0     @ read CP15 register 1 into r0
        BIC     r0, r0, #0x1                @ clear bit 0
        MCR     p15, #0, r0, c1, c0, #0     @ write value back

        MOV     r0, #0
        MCR     p15, #0, r0, c7, c5, #0     @ invalidate caches jay

        MRC   p15, #0, R0, c1, c0, #1       @    /* Read Auxiliary Control Register */
        MOV   R1, #0x3D                     @
        AND   R0, R1, R0                        @               /* Clear L2EN bit */
        MCR   p15, #0, R0, c1, c0, #1       @    /* Disable L2$ */

        MCR     p15, #0, r0, c8, c7, #0     @ invalidate TLBs
@ Cortex-A8 supports two translation tables
        @ Configure translation table base (TTB) control register cp15,c2
        @ to a value of all zeros, indicates we are using TTB register 0.
 
        MOV     r0,#0x0
        MCR     p15, #0, r0, c2, c0, #2
        

        LDR     r0, =ttb_first_level         @ set start of Translation Table
					    @ base (16k Boundary)
        MCR     p15, #0, r0, c2, c0, #0     @ write to CP15 register 2

@ Create translation table for flat mapping
@ Top 12 bits of VA is pointer into table
@ Create 4096 entries from 000xxxxx to fffxxxxx


        LDR     r1,= loop_count               @ loop counter
@        MOV     r2, #(TTBit | Section)      @ build descriptor pattern in reg
        MOV     r2, #(Section)
        ORR     r2, r2, #(Domain | FullAccess)

_init_ttb_1:
        ORR     r3, r2, r1, LSL #20         @ use loop counter to create
					    @ individual table entries
        ORR     r3,r3,#0x0C @1100B                @ set cachable and bufferable
					    @ attributes for section 0 (3:2)
        STR     r3, [r0, r1, LSL #2]        @ str r3 at TTB base + loopcount*4
        SUBS    r1, r1, #1                  @ decrement loop counter
        BPL     _init_ttb_1

@************************************************************************************
@ added by P. Aberl
@ clear cachable bit for memory regions incorporating system and peripheral registers
@ 0x48000000 - 0x6FFFFFFF
        LDR     r1,= loop_count_2             @ loop counter
        MOV     r2, #(TTBit | Section)      @ build descriptor pattern in reg
        ORR     r2, r2, #(Domain | FullAccess)

_init_ttb_2:
        ORR     r3, r2, r1, LSL #20         @ use loop counter to create
					    @ individual table entries
        ORR     r3,r3,#0x04 @0100B                @ set  bufferable  only
@        ORR     r3,r3,#0000B                @ set  strongly ordered
					    @ attributes for section 0 (3:2)
        STR     r3, [r0, r1, LSL #2]        @ str r3 at TTB base + loopcount*4
        SUBS    r1, r1, #1                  @ decrement loop counter
		CMP		r1, #0x440
        BPL     _init_ttb_2

@===================================================================
@ Setup domain control register - Enable all domains to client mode
@===================================================================

        MRC     p15, #0, r0, c3, c0, #0     @ Read Domain Access Control Register
        LDR     r0, = domain_val           @ Initialize every domain entry to b01 (client)
        MCR     p15, #0, r0, c3, c0, #0     @ Write Domain Access Control Register

@ enable MMU
        MRC     p15, #0, r0, c1, c0, #0     @ read CP15 register 1 into r0
        BIC     r0, r0, #(0x1  <<12)        @ ensure I Cache disabled
        BIC     r0, r0, #(0x1  <<2)         @ ensure D Cache disabled
        ORR     r0, r0, #0x1                @ enable MMU before scatter loading
        MCR     p15, #0, r0, c1, c0, #0     @ write CP15 register 1

@ Now the MMU is enabled, virtual to physical address translations will
@ occur and effect the next instruction fetch. Even if this module is
@ remapped, the branch instruction should be safe as it is
@ contained in the pipeline.  However, this should not be relied upon
@ (as this file stands, it flat-maps
@ the entire address space, so there is no problem.

    	BX	LR
@		MOV R15,lr
		
