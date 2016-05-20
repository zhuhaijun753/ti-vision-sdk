;*******************************************************************************
;
; sbl_m4_init_nor.asm - Initialization code for Cortex M4
;                      (used for tda3xx SBL in NOR boot mode)
;
;*******************************************************************************
;
; Copyright (C) 2014 Texas Instruments Incorporated
;
; All rights reserved. Property of Texas Instruments Incorporated.
; Restricted rights to use, duplicate or disclose this code are
; granted through contract.
;
; The program may not be used without the written permission
; of Texas Instruments Incorporated or against the terms and conditions
; stipulated in the agreement under which this program has been
; supplied.
;
;
;*******************************************************************************

;****************************** Global Symbols *********************************

;        .global dataLoadStart
;        .global dataLoadEnd
;        .global dataRunStart
        .global sbl_start
        .global gpmc_config_code
        .global copy_gpmc_config_code

        .sect ".sbl_init"
        .global sbl_nor_start

;***************************** Macro Definitions *******************************
;
SOC_OCMC_RAM1_BASE         .set           0x00300000
SOC_OCMC_RAM1_SIZE         .set           0x00080000
SOC_GPMC_CONF_REGS_BASE    .set           0x50000000
GPMC_CONFIG_1              .set           0x60
GPMC_CONFIG_2              .set           0x64
GPMC_CONFIG_3              .set           0x68
GPMC_CONFIG_4              .set           0x6C
GPMC_CONFIG_5              .set           0x70
GPMC_CONFIG_6              .set           0x74
GPMC_CONFIG_7              .set           0x78
SPANSION_NOR_GPMC_CONFIG_1 .set           0x41041010
SPANSION_NOR_GPMC_CONFIG_2 .set           0x001E1C01
SPANSION_NOR_GPMC_CONFIG_3 .set           0x00000000
SPANSION_NOR_GPMC_CONFIG_4 .set           0x0F071C03
SPANSION_NOR_GPMC_CONFIG_5 .set           0x041B1F1F
SPANSION_NOR_GPMC_CONFIG_6 .set           0x8F070000
SPANSION_NOR_GPMC_CONFIG_7 .set           0x00000C08
CM_L3MAIN1_GPMC_CLKCTRL    .set           0x4A008728
COUNTER_32K_CR             .set           0x4AE04030
SBL_NOR_START_TIME_ADDRESS .set           0x003001C0

;******************************* Code Section **********************************
;
; This is SBL start point in NOR boot mode.
sbl_nor_start:

; Set the Stack Pointer
         LDR  R0, _stackGpmc           ;Read the stack address
         MOV  SP,  R0                  ;Write the Stack Pointer

; Read 32K Counter for SBL start time
         LDR R5, sblCounter32K
         LDR R6, [R5]
         LDR R4, sblStartTimeAddr
         STR R6, [R4]

; Auto-inititialization model is ROM. Hence below is not needed
; Copy the Data Section
;         LDR  R0, _dataLoadStart
;         LDR  R1, _dataLoadEnd
;         LDR  R2, _dataRunStart
;         SUB  R1, R1, #4
;loop1:
;         LDR  R3, [R0], #4
;         STR  R3, [R2], #4
;         CMP  R0, R1
;         BLE  loop1
;         MOV  R0, #0

; Set the GPMC timing parameters and Jump to SBL start
         BL   copy_gpmc_config_code    ;Copy GPMC Config code to OCMC
         LDR  R10, _stackGpmc
         MOV  R0, PC
         ADD  R0, R0, #8               ;8 is for next four instructions
         MOV  LR, R0                   ;GPMC Init code should return to sbl_start
         LDR  R0, gpmcCodeOcmcStart    ;Jump to gpmc_config_code in OCMC
         MOV  PC, R0
         B    sbl_start                ;Branch to sbl_start

; Code for copying GPMC Config code from NOR to OCMC RAM
copy_gpmc_config_code:
         STMFD SP!, {R0-R10}           ;Save the context
         ADR.W R0, gpmc_config_code    ;Get address of GPMC Config code
         MOV  R2, #640                 ;Size of code to be copied
         LDR  R1, gpmcCodeOcmcStart    ;Destination Address
         ADD  R2, R2, R0               ;Source end Address
loop2:
         LDMIA R0!, {R3-R10}           ;Copy from Source Address
         STMIA R1!, {R3-R10}           ;Copy to Destination Address
         CMP  R0, R2                   ;Copy until Source End Address
         BNE  loop2
         LDMFD SP!, {R0-R10}           ;Restore the context
         MOV  PC, LR                   ;Jump back to caller

; Code for configuring GPMC timing parameters
    .align 32
gpmc_config_code:
; Save the context
         MOV  R0, SP
         MOV  SP, R10
         STMFD SP!, {R0-R5}
         STMFD SP!, {IP}

; Bring GPMC out of reset
         LDR  R5, cmL3main1GpmcClkctrlAddress
         MOV  R2, #0x1                 ;Set HW AUTO mode
         STR  R2, [R5]
loop3:
         LDR  R2, [R5]
         ANDS R2, R2, #0x00030000
         CMP  R2, #0
         BNE  loop3

; Disable Chip Select
         LDR  R5, gpmcConfig7Addr
         MOV  R2, #0
         STR  R2, [R5]
; Wait for disable to settle
         MOV  R3, #900
loop4:
         SUB  R3, R3, #1
         CMP  R3, #1
         BNE  loop4

; Set GPMC Timing Parameters
         LDR  R5, gpmcConfig1Addr
         LDR  R2, gpmcConfig1Value
         STR  R2, [R5]
         LDR  R5, gpmcConfig2Addr
         LDR  R2, gpmcConfig2Value
         STR  R2, [R5]
         LDR  R5, gpmcConfig3Addr
         LDR  R2, gpmcConfig3Value
         STR  R2, [R5]
         LDR  R5, gpmcConfig4Addr
         LDR  R2, gpmcConfig4Value
         STR  R2, [R5]
         LDR  R5, gpmcConfig5Addr
         LDR  R2, gpmcConfig5Value
         STR  R2, [R5]
         LDR  R5, gpmcConfig6Addr
         LDR  R2, gpmcConfig6Value
         STR  R2, [R5]
         LDR  R5, gpmcConfig7Addr
         LDR  R2, gpmcConfig7Value
         STR  R2, [R5]

; Enable Chip Select
         LDR  R5, gpmcConfig7Addr
         LDR  R2, gpmcConfig7Value
         ORR  R2, R2, #0x40
         STR  R2, [R5]
; Wait for enable to settle
         MOV  R3, #900
loop5:
         SUB  R3, R3, #1
         CMP  R3, #1
         BNE  loop5

; Restore the context
         LDMFD SP!, {IP}
         LDMFD SP!, {R0-R5}
         MOV  SP, R0
         MOV  PC, LR

; 32K Timer Counter Register
sblCounter32K:
    .word (COUNTER_32K_CR)
; Address where SBL Start Time is Stored
sblStartTimeAddr:
    .word (SBL_NOR_START_TIME_ADDRESS)

gpmcConfig1Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_1)
gpmcConfig2Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_2)
gpmcConfig3Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_3)
gpmcConfig4Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_4)
gpmcConfig5Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_5)
gpmcConfig6Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_6)
gpmcConfig7Addr:
    .word (SOC_GPMC_CONF_REGS_BASE + GPMC_CONFIG_7)

gpmcConfig1Value:
    .word SPANSION_NOR_GPMC_CONFIG_1
gpmcConfig2Value:
    .word SPANSION_NOR_GPMC_CONFIG_2
gpmcConfig3Value:
    .word SPANSION_NOR_GPMC_CONFIG_3
gpmcConfig4Value:
    .word SPANSION_NOR_GPMC_CONFIG_4
gpmcConfig5Value:
    .word SPANSION_NOR_GPMC_CONFIG_5
gpmcConfig6Value:
    .word SPANSION_NOR_GPMC_CONFIG_6
gpmcConfig7Value:
    .word SPANSION_NOR_GPMC_CONFIG_7

; Register for enabling GPMC
cmL3main1GpmcClkctrlAddress:
    .word CM_L3MAIN1_GPMC_CLKCTRL
; GPMC Start Address where GPMC code is copied
gpmcCodeOcmcStart:
    .word (SOC_OCMC_RAM1_BASE + (SOC_OCMC_RAM1_SIZE/2) - 0xC00)
; Stack Pointer Address
_stackGpmc:
    .word (SOC_OCMC_RAM1_BASE + (SOC_OCMC_RAM1_SIZE/2) - 0x4)

;_dataLoadStart:
;    .word dataLoadStart
;_dataLoadEnd:
;    .word dataLoadEnd
;_dataRunStart:
;    .word dataRunStart
