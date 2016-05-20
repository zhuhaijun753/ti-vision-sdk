;*******************************************************************************
;
; sbl_m4_init.asm - Initialization code for Cortex M4
;                   (used for tda3xx SBL in all boot modes)
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
        .global stackEnd
;        .global bssStart
;        .global bssEnd
        .global _c_int00

        .sect ".sbl_init"
        .global sbl_start

;******************************* Code Section **********************************
;
; This is SBL start point.
sbl_start:

; Set the Stack Pointer
         LDR  R0, _stackEnd ;Read the stack address
         MOV  SP, R0         ;Write the Stack Pointer

; Auto-inititialization model is ROM. Hence below is not needed
; Clear BSS Section
; clear_bss_section:
;         LDR  R0, _bssStart ;Start address of BSS
;         LDR  R1, _bssEnd   ;End address of BSS
;         SUB  R1, R1, #4
;         MOV  R2, #0
;loop:
;         STR  R2, [R0], #4   ;Clear one word in BSS
;         CMP  R0, R1
;         BLE  loop           ;Clear till BSS end

; Set all registers to 0
         MOV  R0,  #0
         MOV  R1,  #0
         MOV  R2,  #0
         MOV  R3,  #0
         MOV  R4,  #0
         MOV  R5,  #0
         MOV  R6,  #0
         MOV  R7,  #0
         MOV  R8,  #0
         MOV  R9,  #0
         MOV  R10, #0
         MOV  R11, #0
         MOV  R12, #0

; Branch to _c_int00
         B  _c_int00

_stackEnd:
    .word stackEnd
;_bssStart:
;    .word bssStart
;_bssEnd:
;    .word bssEnd
