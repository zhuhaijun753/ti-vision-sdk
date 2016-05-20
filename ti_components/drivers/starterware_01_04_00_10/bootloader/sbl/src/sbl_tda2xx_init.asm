@******************************************************************************
@
@ sbl_init.asm - Init code routines
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
/**
*   Component:        SBL
*
*   Filename:         sbl_init.asm
*
*   Description:
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

@****************************** Global Symbols*******************************
        .global SBL_Start
        .global start_boot
        .global __TI_auto_init
        .global Clear_Bss_Section

        .extern __stack
        .extern bss_start
        .extern bss_end
        .extern start_boot

@************************ Internal Definitions ******************************
@
@ Define the stack sizes for different modes. The user/system mode will use
@ the rest of the total stack size
@

#define UND_STACK_SIZE  0x8
#define ABT_STACK_SIZE  0x8
#define FIQ_STACK_SIZE  0x8
#define IRQ_STACK_SIZE  0x100
#define SVC_STACK_SIZE  0x200

@
@ to set the mode bits in CPSR for different modes
@

#define MODE_USR 0x10
#define MODE_FIQ 0x11
#define MODE_IRQ 0x12
#define MODE_SVC 0x13
#define MODE_ABT 0x17
#define MODE_UND 0x1B
#define MODE_SYS 0x1F

#define I_F_BIT  0xC0

@**************************** Code Seection ***********************************
        .text
@
@ This code is assembled for ARM instructions
@
        .code 32

@******************************************************************************
@
@******************************************************************************
@
@ The reset handler sets up the stack pointers for all the modes. The FIQ and
@ IRQ shall be disabled during this. Then, clearthe BSS sections, switch to the
@  main() function.
@
#if defined (TDA2EX_BUILD)
    .section .sbl_start, "awx"
    .func SBL_Start
#endif
SBL_Start:
@
@ Set up the Stack for Undefined mode
@
         LDR   r0, _stackptr                     @ Read the stack address
         MSR   cpsr_c, #MODE_UND|I_F_BIT       @ switch to undef  mode
         MOV   sp,r0                           @ write the stack pointer
         SUB   r0, r0, #UND_STACK_SIZE         @ give stack space
@
@ Set up the Stack for abort mode
@
         MSR   cpsr_c, #MODE_ABT|I_F_BIT       @ Change to abort mode
         MOV   sp, r0                          @ write the stack pointer
         SUB   r0,r0, #ABT_STACK_SIZE          @ give stack space
@
@ Set up the Stack for FIQ mode
@
         MSR   cpsr_c, #MODE_FIQ|I_F_BIT       @ change to FIQ mode
         MOV   sp,r0                           @ write the stack pointer
         SUB   r0,r0, #FIQ_STACK_SIZE          @ give stack space
@
@ Set up the Stack for IRQ mode
@
         MSR   cpsr_c, #MODE_IRQ|I_F_BIT       @ change to IRQ mode
         MOV   sp,r0                           @ write the stack pointer
         SUB   r0,r0, #IRQ_STACK_SIZE          @ give stack space
@
@ Set up the Stack for USer/System mode
@
         MSR   cpsr_c, #MODE_SYS|I_F_BIT       @ change to system mode
         MOV   sp,r0                           @ write the stack pointer

@
@ Set up the Stack for SVC mode
@
         MSR   cpsr_c, #MODE_SVC|I_F_BIT       @ change to SVC mode
         MOV   sp,r0                           @ write the stack pointer
         SUB   r0,r0, #SVC_STACK_SIZE          @ give stack space

#ifndef BOOTMODE_NOR
         BL    Clear_Bss_Section
#endif

 @   ;; --------------------------------------
 @   ;; ---- I/D CACHE, MMU, BP settings -----
 @   ;; --------------------------------------
    .ifdef ICACHE
            .print "ICache"
            MOV r0, #0
            MCR p15, #0, r0, c7, c5, #0     @; Invalidate entire ICache
                                            @; (not mandatory)
            MRC p15, #0, r1, c1, c0, #0     @; read Control Coprocessor register
            ORR r1, r1, #0x1000             @; Set I Bit
            MCR p15, #0, r1, c1, c0, #0     @; Store new settings
    .endif @; ICACHE

    .ifdef DCACHE
            .print "DCache+MMU"
            SWI #0xF8
            MRC p15, #0, r1, c1, c0, #0    @; read Control Coprocessor register
            ORR r1, r1, #0x4               @; Set C Bit
            MCR p15, #0, r1, c1, c0, #0    @; Store new settings
    .else
    .ifdef MMU
            SWI #0xF8
     .endif @MMU
    .endif @; DCACHE || MMU

    .ifdef BP
        .print "BP"
        MRC p15, #0x0, r1, c1, c0, #0x0   @; read Control Coprocessor register
        ORR r1,r1,#0x800                  @; Set Z Bit
        MCR p15, #0x0, r1, c1, c0, #0x0   @; Store new settings
    .endif   @; BP

    MRC p15, 1, r0, c15, c0, 0    @; Read L2 Auxiliary Control Register
    ORR r0, r0, #0x100            @; Enable hazard detect timeout for A15
    MOV lr, pc                    @; Set correct value in LR
    ADD lr, lr, #0x10
    PUSH {r1-r12, lr}             @; Save registers - ROM code may pollute
                                  @; our registers

    LDR r12, =0x104    @; Set L2 Cache Auxiliary control register - value in R0
    SMC 0x1            @; Call ROM Code API to set control register
    POP {r1-r12, pc}   @; Restore registers

 @  ;; --------------------------------------
 @  ; Initialize internal registers.
 @  ;; --------------------------------------
    MOV r0,  #0

    .ifdef FORCE_BRANCH
        MOV r1,  #0x15 @ ; For linux use. Should not impact other soft.
    .else
        MOV r1,  #0
    .endif

    MOV r2,  #0
    MOV r3,  #0
    MOV r4,  #0
    MOV r5,  #0
    MOV r6,  #0
    MOV r7,  #0
    MOV r8,  #0
    MOV r9,  #0
    MOV r10, #0
    MOV r11, #0
    MOV r12, #0

    .global Jump_main
Jump_main:

    .ifdef LOOP
loop_on_eob:
    B loop_on_eob
    .else @; LOOP
    LDR pc,=main   @; RESET INTERRUPT
    .endif @;!LOOP
@
@ Clear the BSS section here
@
Clear_Bss_Section:
         PUSH  {r0-r2, lr}
         LDR   r0, _bss_start                 @ Start address of BSS
         LDR   r1, _bss_end                   @ End address of BSS
         SUB   r1,r1,#4
         MOV   r2, #0
Loop:
         STR   r2, [r0], #4                    @ Clear one word in BSS
         CMP   r0, r1
         BLE   Loop                            @ Clear till BSS end
         POP   {r0-r2, pc}


_stackptr:
    .word _stack
_bss_start:
    .word bss_start
_bss_end:
    .word bss_end
_main:
    .word main
         .end
