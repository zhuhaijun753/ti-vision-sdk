@*******************************************************************************
@
@ sbl_tda2ex_nor_init.asm - Initialization code for Cortex A15
@                      (used for tda2ex SBL in NOR boot mode)
@
@*******************************************************************************
@
@ Copyright (C) 2015 Texas Instruments Incorporated
@
@ All rights reserved. Property of Texas Instruments Incorporated.
@ Restricted rights to use, duplicate or disclose this code are
@ granted through contract.
@
@ The program may not be used without the written permission
@ of Texas Instruments Incorporated or against the terms and conditions
@ stipulated in the agreement under which this program has been
@ supplied.
@
@
@*******************************************************************************


@****************************** Global Symbols *********************************

        .global SBL_Start
        .global gSetVoltRailsStatus
        .global SBLConfigAllVotageRails
        .global nor_lowlevel_init
        .global cpy_nor_gpmc_code
        .global nor_gpmc_init
        .global Clear_Bss_Section

@***************************** Macro Definitions *******************************
@

#define SOC_CORE_CM_CORE_BASE          (0x4a008700)
#define SOC_GPMC_CONF_REGS_BASE        (0x50000000)
#define SOC_OCMC_RAM1_BASE             (0x40300000)
#define SOC_OCMC_RAM1_BASE_SIZE        (0x80000)

#define CM_L3MAIN1_CLKSTCTRL           (0x0)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL   (0x50)
#define CM_L3MAIN1_GPMC_CLKCTRL        (0x28)

#define GPMC_CONFIG1_N(n)              (0x60+ (n * 48))
#define GPMC_CONFIG2_N(n)              (0x64+ (n * 48))
#define GPMC_CONFIG3_N(n)              (0x68+ (n * 48))
#define GPMC_CONFIG4_N(n)              (0x6c+ (n * 48))
#define GPMC_CONFIG5_N(n)              (0x70+ (n * 48))
#define GPMC_CONFIG6_N(n)              (0x74+ (n * 48))
#define GPMC_CONFIG7_N(n)              (0x78+ (n * 48))

#define SPNOR_GPMC_CONFIG1             (0x41041010)
#define SPNOR_GPMC_CONFIG2             (0x001E1C01)
#define SPNOR_GPMC_CONFIG3             (0x00000000)
#define SPNOR_GPMC_CONFIG4             (0x0F071C03)
#define SPNOR_GPMC_CONFIG5             (0x041B1F1F)
#define SPNOR_GPMC_CONFIG6             (0x8F070000)
#define SPNOR_GPMC_CONFIG7             (0x00000C08)


@******************************* Code Section **********************************
@
@ This is SBL start point in NOR boot mode.
    .section .sbl_start, "awx"
nor_lowlevel_init:
    @; Initialize the Stack pointer
    ldr   r0, sram_stack_gpmc   @; Read the stack address
    mov   sp,r0                 @; Write the stack pointer
    bl ocmc_init_start          @; Initialize the OCMC0
    @; Copy the data section
    LDR   r0, _data_start_ldr   @; SRC address of DATA - FLASH location
    LDR   r1, _data_start       @; DST address of DATA - RAM location
    LDR   r3,_data_end          @; DSR END address of DATA - RAM location
    SUB   r3,r3,#4              @; size -1

Loop_data_section:
    LDR   r4,[r0], #4    @ Read the data from src location & increment pointer
    STR   r4, [r1], #4   @ Store the data into dst location & increment pointer
    CMP   r1, r3
    BLE   Loop_data_section
    BL    Clear_Bss_Section         @; Initialization of BSS done
    MOV   R0, #0                    @; Initialize the gSetVoltRailsStatus before
                                    @; starting voltage rail configuration.
    LDR   R1, =gSetVoltRailsStatus  @; read addr of gSetVoltRailsStatus into R1
    STR   R0, [R1]                  @; store new value into globvar
    bl    SBLConfigAllVotageRails   @; Call AVS Class 0 & ABB Config function
    @; Branch to nor_init_start
    bl   nor_init_start

@; /****************************************************************************
@ ; * OCMC RAM Init
@ ; *
@ ; ***************************************************************************/
ocmc_init_start:
@   ; /**** enable ocmc 0 ****/
@   ; /* CLKSTCTRL - Automatic transition*/
    ldr r5, cm_l3main1_clkstctrl_addr
    mov r2, #0x3
    str r2, [r5]
    @; /* wait for interface clk to settle */
ocmc0_wait0:
    ldr r2, [r5]
    ands r2, r2, #0x00000100
    cmp r2, #0x00000100
    bne ocmc0_wait0
    @; /* OCMC1 CLKCTRL */
    ldr r5, cm_l3main1_ocmc_ram1_clkctrl_addr
    mov r2, #0x1
    str r2, [r5]
    @; /* wait for module mode to functional*/
ocmc0_wait1:
    ldr r2, [r5]
    ands r2, r2, #0x00030000
    cmp r2, #0
    bne ocmc0_wait1
    mov pc, lr          @;/* back to caller */

@; /****************************************************************************
@ ; * NOR Initialization
@ ; ***************************************************************************/
nor_init_start:
    @; /* gpmc init */

    bl  cpy_nor_gpmc_code @;/* copy nor gpmc init code to sram */
    ldr r10, sram_stack_gpmc
    mov r0, pc
    add r0, r0, #12  @;/* 12 is for next three instructions */
    mov lr, r0   @;/* gpmc init code in sram should return to s_init_start */
    ldr r0, sram_pc_start
    mov pc, r0  @;/* transfer ctrl to nor_gpmc_init() in sram */
    b SBL_Start ;/* and jump to s_init */

@; /**************************************************************************
@ ; * cpy_nor_gpmc_code: relocates nor gpmc init code into ocmc0 where its
@ ; * safer to execute
@ ; * R2 is loaded wtih size of data to be copied, this should be calculated
@ ; * if we are modifying nor_gpmc_init()
 ; *************************************************************************/
    .section .sbl_start, "awx"
cpy_nor_gpmc_code:
    stmfd sp!, {r0 - r10}
    @;/* Copy NOR GPMC init code into SRAM */
    adr r0, nor_gpmc_init     @;/*r0 src addr - get addr of nor gpmc init code*/
    @ ;mov r0, pc
    @ ;add r0, r0, #36          @;/*TODO: Replace it with ADR */
    mov r2, #640    @;/* r2 <- copy size(% by 32 bytes:r3-r10 (8) regs used) */
    ldr r1, sram_pc_start     @;/* r1 <- dest address (passed in) */
    add r2, r2, r0      @;/* r2 <- source end address */
next2:
    ldmia   r0!, {r3 - r10}     @;/* copy from source address [r0] */
    stmia   r1!, {r3 - r10}     @;/* copy to   target address [r1] */
    cmp r0, r2          @;/* until source end address [r2] */
    bne next2
    ldmfd sp!, {r0 - r10}
    mov pc, lr          @;/* back to caller */

@; /****************************************************************************
@ ; *  nor_gpmc_init: - Init GPMC for NOR on CS0, executed from SRAM.
@ ; *
@ ; *  R0 - used for saving SP, hence do not use it anywhere
@ ; ***************************************************************************/
    .section .sbl_start, "awx"
nor_gpmc_init:
    mov r0, sp
    @;ldr sp, SRAM_STACK_GPMC
    mov sp,r10
    @;ldr sp, #0x4031b7fc
    stmfd sp!, {r0 - r5}
    stmfd sp!, {ip}

    @;/****** GPMC out of reset ******/
    ldr r5, cm_l3main1_gpmc_clkctrl_addr
    mov r2, #0x1     @ check for the module mode value - Auto
    str r2, [r5]
    @;/* wait for gpmc enable to settle */
gpmc_next_wait0:
    ldr r2, [r5]
    ands r2, r2, #0x00030000
    cmp r2, #0
    bne gpmc_next_wait0

    @;/***** GPMC CS0 init ******/
    @;/* disable CS0*/
    ldr r5, gpmc_cfg7_addr
    mov r2, #0
    str r2, [r5]
    ;/* wait for disable to settle */
    mov r3, #0x900
gpmc_next_wait1:
    sub r3, r3, #1
    cmp r3, #1
    bne gpmc_next_wait1

    ;/* set gpmc config registers */
    ldr r5, gpmc_cfg1_addr
    ldr r2, gpmc_cfg1_val
    str r2, [r5]
    ldr r5, gpmc_cfg2_addr
    ldr r2, gpmc_cfg2_val
    str r2, [r5]
    ldr r5, gpmc_cfg3_addr
    ldr r2, gpmc_cfg3_val
    str r2, [r5]
    ldr r5, gpmc_cfg4_addr
    ldr r2, gpmc_cfg4_val
    str r2, [r5]
    ldr r5, gpmc_cfg5_addr
    ldr r2, gpmc_cfg5_val
    str r2, [r5]
    ldr r5, gpmc_cfg6_addr
    ldr r2, gpmc_cfg6_val
    str r2, [r5]
    ldr r5, gpmc_cfg7_addr
    ldr r2, gpmc_cfg7_val
    str r2, [r5]

    ;/* enable CS0 */
    ldr r5, gpmc_cfg7_addr
    ldr r2, gpmc_cfg7_val
    orr r2, r2, #0x40
    str r2, [r5]

    ;/* wait for enable to settle */
    mov r3, #0x900
gpmc_next_wait2:
    sub r3, r3, #1
    cmp r3, #1
    bne gpmc_next_wait2

    ldmfd sp!, {ip}
    ldmfd sp!, {r0 - r5}
    mov sp, r0
    mov pc, lr      ;/* back to caller*/

; /* these constants need to be close for PIC code */
; /* The Nor has to be in the Flash Base CS0 for this condition to happen */

cm_l3main1_ocmc_ram1_clkctrl_addr:
    .word   (SOC_CORE_CM_CORE_BASE+CM_L3MAIN1_OCMC_RAM1_CLKCTRL)
cm_l3main1_clkstctrl_addr:
    .word   (SOC_CORE_CM_CORE_BASE+CM_L3MAIN1_CLKSTCTRL)
cm_l3main1_gpmc_clkctrl_addr:
    .word   (SOC_CORE_CM_CORE_BASE+CM_L3MAIN1_GPMC_CLKCTRL)

sram_pc_start:
    .word (SOC_OCMC_RAM1_BASE + SOC_OCMC_RAM1_BASE_SIZE - 0xC00)
sram_stack_gpmc:
    .word (SOC_OCMC_RAM1_BASE + SOC_OCMC_RAM1_BASE_SIZE - 4)


gpmc_cfg1_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG1_N(0))
gpmc_cfg2_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG2_N(0))
gpmc_cfg3_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG3_N(0))
gpmc_cfg4_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG4_N(0))
gpmc_cfg5_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG5_N(0))
gpmc_cfg6_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG6_N(0))
gpmc_cfg7_addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG7_N(0))

gpmc_cfg1_val:
    .word SPNOR_GPMC_CONFIG1
gpmc_cfg2_val:
    .word SPNOR_GPMC_CONFIG2
gpmc_cfg3_val:
    .word SPNOR_GPMC_CONFIG3
gpmc_cfg4_val:
    .word SPNOR_GPMC_CONFIG4
gpmc_cfg5_val:
    .word SPNOR_GPMC_CONFIG5
gpmc_cfg6_val:
    .word SPNOR_GPMC_CONFIG6
gpmc_cfg7_val:
    .word SPNOR_GPMC_CONFIG7

_data_start_ldr:
    .word data_start_ldr
 _data_start:
    .word data_start
_data_end:
    .word data_end