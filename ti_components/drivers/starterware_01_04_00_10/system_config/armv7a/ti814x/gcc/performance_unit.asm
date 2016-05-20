@/* ======================================================================
@ *   Copyright (C) 2013 Texas Instruments Incorporated
@ *
@ *   All rights reserved. Property of Texas Instruments Incorporated.
@ *   Restricted rights to use, duplicate or disclose this code are
@ *   granted through contract.
@ *
@ *   The program may not be used without the written permission
@ *   of Texas Instruments Incorporated or against the terms and conditions
@ *   stipulated in the agreement under which this program has been
@ *   supplied.
@ * ==================================================================== */

@*---------------------------------------------------------------------------
@*
@* Functions to Enable, Reset & Read the Cycle Count Register (CCNT)
@*                               
@* CCNT enabled and reset via Performance Monitor Control Register (PMNC)
@* The CCNT is divided by 64 (by setting Bit 3 of PMNC to 1)
@* CCNT is checked for overflow by looking at bit 10 of PMNC
@* Refer ARM1136/A-8 TRM for details
@*---------------------------------------------------------------------------

	.text
	.code 32


.set CCNT_CP1, C9
.set CCNT_CP2, C13
.set PMON_OVF, 3
.set OVERFLOW_MASK, 0x80000000 @ Check Bit 31 for overflow


	.global  ARM_CCNT_Enable
	.global  ARM_CCNT_Reset

ARM_CCNT_Enable:
ARM_CCNT_Reset:
	@ Write Performance Monitor Control Register
	MRC P15, #0, R0, C9, C12, #0

	ORR R0, R0, #0x5
	MCR P15, #0, R0, C9, C12, #0 @ Reset Cycle count register

	MOV R1, #0x80000000
	MCR P15, #0, R1, C9, C12, #1

	BX  LR

	.global  ARM_CCNT_Read
ARM_CCNT_Read:
	MRC P15, #0, R0, C9, C13, #0
	BX  LR

	@ Returns 1 if CCNT overflowed, 0 otherwise
	@ Also resets CCNT overflow bit

	.global  ARM_CCNT_CheckOverflow
ARM_CCNT_CheckOverflow:
	@ Read PMNC
	MRC	P15, #0, R0, C9, C12, #PMON_OVF
	ANDS	R1, R0, #OVERFLOW_MASK
	BICNE	R0, R0, #OVERFLOW_MASK
	MCRNE	P15, #0, R0, C9, C12, #PMON_OVF
	MOVNE	R0, #1
	MOVEQ	R0, #0
	BX  LR


@*---------------------------------------------------------------------------
@*
@* Functions to Enable, Reset & Read the Count Registers
@*
@*---------------------------------------------------------------------------

	.global  ARM_PMN_Enable
@* R0 - counter, R1 - event #
ARM_PMN_Enable:

	MCR P15, #0, R0, C9, C12, #5 @ PMNXSEL:Select counter based on R0
	MCR P15, #0, R1, C9, C13, #1
	MOV R2, #1
	MOV R2, R2, LSL R0
	MCR P15, #0, R2, C9, C12, #1

	BX  LR

	.global  ARM_PMN_Reset
@* R0 - counter
ARM_PMN_Reset:
	MOV R1, #0

	MCR P15, #0, R0, C9, C12, #5 @ PMNXSEL:Select counter based on R0
	MCR P15, #0, R1, C9, C13, #2 @ Write Count Register

	BX  LR

	.global  ARM_PMN_Read
@* R0 - counter, Returns result in R0
ARM_PMN_Read:

	MCR P15, #0, R0, C9, C12, #5 @ PMNXSEL:Select counter based on R0
	MRC P15, #0, R0, C9, C13, #2 @ Read Count Register

	BX  LR


