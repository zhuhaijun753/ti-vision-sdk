/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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
@******************************************************************************
@
@ exceptionhandler.S - Definitions of exception handlers
@
@
@******************************************************************************
@
@ Share header file with assembly source code
@
#include "hw_intc.h"

@************************** Global symbols ************************************
        .global IRQHandler
        .global FIQHandler
        .global AbortHandler
        .global SVCHandler
        .global UndefInstHandler
        .global CPUAbortHandler
        .global fnRAMVectors

@**************************** Text Section ************************************
        .text

@ This source file is assembled for ARM instructions
        .code 32
@******************************************************************************
@*                  Function Definition of SWI Handler
@******************************************************************************
@
@ The SVC Handler switches to system mode if the SVC number is 458752. If the
@ SVC number is different, no mode switching will be done. No other SVC are
@ handled here
@
SVCHandler:
        STMFD    r13!, {r0-r1, r14}       @ Save context in SVC stack
        SUB      r13, r13, #0x4           @ Adjust the stack pointer
        LDR      r0, [r14, #-4]           @ R0 points to SWI instruction
        BIC      r0, r0, #MASK_SVC_NUM    @ Get the SWI number
        CMP      r0, #458752
        MRSEQ    r1, spsr                 @ Copy SPSR
        ORREQ    r1, r1, #0x1F            @ Change the mode to System
        MSREQ    spsr_cf, r1              @ Restore SPSR
        ADD      r13, r13, #0x4           @ Adjust the stack pointer
        LDMFD    r13!, {r0-r1, pc}^       @ Restore registers from IRQ stack

@******************************************************************************
@*                  Function Definition of IRQ Handler
@******************************************************************************
@
@ The IRQ handler jumps to the ISR of highest priority pending IRQ.
@ This handler doesnot support nesting.
@
IRQHandler:
        STMFD    r13!, {r0-r3, r12, r14}  @ Save context in IRQ stack
        LDR      r0, =ADDR_IAR            @ Load IAR address into r0
        LDR      r1, [r0]                 @ Get the Active IRQ
        MOV      r2, r1                   @ save active IRQ in r2
        AND      r1, r1, #IAR_INT_ID_MASK @ Mask the Active IRQ number
        SUB      r1, r1, #PPI_SGI_MASK    @ Get Shared pheriperal int number
        LDR      r3, =fnRAMVectors        @ Load the base of the vector table
        LDR      r0, =argArray            @ Load base of argument
        LDR      r0, [r0, r1, lsl #2]     @ Load argument
        STMFD    r13!, {r2}               @ Save active IRO in stack
        ADD      r14, pc, #0              @ Save return address in LR
        LDR      pc, [r3, r1, lsl #2]     @ Jump to the ISR
        LDMFD    r13!, {r2}               @ Get active IRO from stack
        LDR      r1, =ADDR_EOI            @ Acknowledge the current IRQ
        STR      r2, [r1]
        DMB                               @ Barrier to complete the data write
        LDMFD    r13!, {r0-r3, r12, r14}  @ Restore registers from IRQ stack
        SUBS     pc, r14, #0x4            @ Return to program before IRQ

/*IRQHandler:
        STMFD    r13!, {r0-r3, r12, r14}  ; Save context in IRQ stack
        LDR      r0, ADDR_IAR             ; Get the Active IRQ
        LDR      r1, [r0]
        AND      r1, r1, #IAR_INT_ID_MASK ; Mask the Active IRQ number
        LDR      r0, _fnRAMVectors        ; Load the base of the vector table
        ADD      r14, pc, #0              ; Save return address in LR
        LDR      pc, [r0, r1, lsl #2]     ; Jump to the ISR
        MOV      r0, #NEWIRQAGR           ; Acknowledge the current IRQ
        LDR      r1, ADDR_CONTROL
        STR      r0, [r1]
        DMB                               ; Barrier to complete the data write
        LDMFD    r13!, {r0-r3, r12, r14}  ; Restore registers from IRQ stack
        SUBS     pc, r14, #0x4            ; Return to program before IRQ*/

@******************************************************************************
@*                  Function Definition of FIQ Handler
@******************************************************************************
@
@ The FIQ Handler jumps to the ISR of the highest priority pending FIQ. The
@ pending FIQ. This handler doesnot support nesting
@
FIQHandler:
        STMFD    r13!, {r0-r3, r12, r14}  @ Save context in FIQ stack
        LDR      r0, =ADDR_IAR        @ Get the Active FIQ
        LDR      r1, [r0]
        MOV      r2, r1
        AND      r1, r1, #IAR_INT_ID_MASK @ Mask the Active IRQ number
        SUB      r1, r1, #PPI_SGI_MASK
        LDR      r0, =fnRAMVectors        @ Load the base of the vector table
        ADD      r14, pc, #0              @ Save return address in LR
        LDR      pc, [r0, r1, lsl #2]     @ Jump to the ISR
        LDR      r0, =ADDR_EOI            @ Acknowledge the current IRQ
        STR      r2, [r0]
        DMB                               @ Barrier to complete the data write
        LDMFD    r13!, {r0-r3, r12, r14}  @ Restore registers from IRQ stack
        SUBS     pc, r14, #0x4            @ Return to program before FIQ

@******************************************************************************
@*             Function Definition of Abort Handler
@******************************************************************************
@
@ The Abort handler goes to the C handler of abort mode.
@ if app registers the User defined ISR then will service the ISR else the
@ execution enters infinite loop.
@

AbortHandler:
@
@ Disable all the interrupts
@
        STMFD    r13!, {r0-r3, r12, r14}  @ Save context in stack
        MRS     r0, cpsr                  @ Read from CPSR
        ORR     r0, r0, #0xC0             @ Clear the IRQ and FIQ bits
        MSR     cpsr, r0                  @ Write to CPSR
        ADD     r14, pc, #0               @ Store the return address
        LDR     pc, =CPUAbortHandler      @ Go to C handler
        LDMFD   r13!, {r0-r3, r12, r14}  @ Restore registers from IRQ stack
        SUBS    pc, r14, #0x4             @ Return to program before IRQ

@******************************************************************************
@*             Function Definition of Undef Handler
@******************************************************************************
@ The Undef handler enters infinite loop
@

UndefInstHandler:
@
@ Disable all the interrupts
@
        MRS     r0, cpsr                  @ Read from CPSR
        ORR     r0, r0, #0xC0             @ Clear the IRQ and FIQ bits
        MSR     cpsr, r0                  @ Write to CPSR
        ADD     r14, pc, #0               @ Store the return address
@
@ Go to infinite loop
@
loop0:
        B       loop0
@*****************************************************************************
@
@ End of the file
@
    .end



