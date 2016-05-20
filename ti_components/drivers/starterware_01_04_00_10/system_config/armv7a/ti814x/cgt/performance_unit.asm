;/* ======================================================================
; *   Copyright (C) 2013 Texas Instruments Incorporated
; *
; *   All rights reserved. Property of Texas Instruments Incorporated.
; *   Restricted rights to use, duplicate or disclose this code are
; *   granted through contract.
; *
; *   The program may not be used without the written permission
; *   of Texas Instruments Incorporated or against the terms and conditions
; *   stipulated in the agreement under which this program has been
; *   supplied.
; * ==================================================================== */

;*---------------------------------------------------------------------------
;*
;* Functions to Enable, Reset & Read the Cycle Count Register (CCNT)
;*
;* CCNT enabled and reset via Performance Monitor Control Register (PMNC)
;* The CCNT is divided by 64 (by setting Bit 3 of PMNC to 1)
;* CCNT is checked for overflow by looking at bit 10 of PMNC
;* Refer ARM1136/A-8 TRM for details
;*---------------------------------------------------------------------------

	.text
	.state32

	.if __TI_TMS470_V7__
CCNT_CP1	.set    C9
CCNT_CP2	.set    C13
PMON_OVF	.set    3
OVERFLOW_MASK	.set	0x80000000 ; Check Bit 31 for overflow
	.else
CCNT_CP1	.set    C15
CCNT_CP2	.set    C12
PMON_OVF	.set    0
OVERFLOW_MASK	.set	0x400      ; Check Bit 10 for overflow
	.endif

	.global  ARM_CCNT_Enable
	.armfunc ARM_CCNT_Enable
	.global  ARM_CCNT_Reset
	.armfunc ARM_CCNT_Reset
ARM_CCNT_Enable:
ARM_CCNT_Reset:
	; Write Performance Monitor Control Register
	MRC P15, #0, R0, CCNT_CP1, C12, #0
	; ORR R0, R0, #0xD
	ORR R0, R0, #0x5
	MCR P15, #0, R0, CCNT_CP1, C12, #0 ; Reset Cycle count register
	.if __TI_TMS470_V7__
	MOV R1, #0x80000000
	MCR P15, #0, R1, CCNT_CP1, C12, #1
	.endif
	BX  LR

	.global  ARM_CCNT_Read
	.armfunc ARM_CCNT_Read
ARM_CCNT_Read:
	.if __TI_TMS470_V7__
	MRC P15, #0, R0, CCNT_CP1, CCNT_CP2, #0
	.else
	MRC P15, #0, R0, CCNT_CP1, CCNT_CP2, #1
	.endif
	BX  LR

	; Returns 1 if CCNT overflowed, 0 otherwise
	; Also resets CCNT overflow bit

	.global  ARM_CCNT_CheckOverflow
	.armfunc ARM_CCNT_CheckOverflow
ARM_CCNT_CheckOverflow:
	; Read PMNC
	MRC	P15, #0, R0, CCNT_CP1, C12, #PMON_OVF
	ANDS	R1, R0, #OVERFLOW_MASK
	BICNE	R0, R0, #OVERFLOW_MASK
	MCRNE	P15, #0, R0, CCNT_CP1, C12, #PMON_OVF
	MOVNE	R0, #1
	MOVEQ	R0, #0
	BX  LR


;*---------------------------------------------------------------------------
;*
;* Functions to Enable, Reset & Read the Count Registers
;*
;*---------------------------------------------------------------------------

	.global  ARM_PMN_Enable
	.armfunc ARM_PMN_Enable
;* R0 - counter, R1 - event #
ARM_PMN_Enable:
	.if __TI_TMS470_V7__
	MCR P15, #0, R0, CCNT_CP1, C12, #5 ; PMNXSEL:Select counter based on R0
	MCR P15, #0, R1, CCNT_CP1, CCNT_CP2, #1
	MOV R2, #1
	MOV R2, R2, LSL R0
	MCR P15, #0, R2, CCNT_CP1, C12, #1
	.else
	MRC P15, #0, R2, CCNT_CP1, CCNT_CP2, #0
	ORR R2, R2, #0x3
	CMP R0, #0
	BICEQ R2, R2, #0xff00000
	BICNE R2, R2, #0xff000
	ORREQ R2, R2, R1, LSL #20
	ORRNE R2, R2, R1, LSL #12
	MCR P15, #0, R2, CCNT_CP1, CCNT_CP2, #0
	.endif
	BX  LR

	.global  ARM_PMN_Reset
	.armfunc ARM_PMN_Reset
;* R0 - counter
ARM_PMN_Reset:
	MOV R1, #0
	.if __TI_TMS470_V7__
	MCR P15, #0, R0, CCNT_CP1, C12, #5 ; PMNXSEL:Select counter based on R0
	MCR P15, #0, R1, CCNT_CP1, CCNT_CP2, #2 ; Write Count Register
	.else
	CMP R0, #0
	MCREQ P15, #0, R1, CCNT_CP1, CCNT_CP2, #2 ; Write Count Register 0
	MCRNE P15, #0, R1, CCNT_CP1, CCNT_CP2, #3 ; Write Count Register 1
	.endif
	BX  LR

	.global  ARM_PMN_Read
	.armfunc ARM_PMN_Read
;* R0 - counter, Returns result in R0
ARM_PMN_Read:
	.if __TI_TMS470_V7__
	MCR P15, #0, R0, CCNT_CP1, C12, #5 ; PMNXSEL:Select counter based on R0
	MRC P15, #0, R0, CCNT_CP1, CCNT_CP2, #2 ; Read Count Register
	.else
	CMP R0, #0
	MRCEQ P15, #0, R0, CCNT_CP1, CCNT_CP2, #2 ; Read Count register 0
	MRCNE P15, #0, R0, CCNT_CP1, CCNT_CP2, #3 ; Read Count Register 1
	.endif
	BX  LR

