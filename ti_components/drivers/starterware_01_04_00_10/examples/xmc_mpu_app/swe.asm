;
; \file swe.asm
;
; \brief Implement APIs to switch DSP CPU mode
;
;

; ======================================================================
;   Copyright (C) 2014 Texas Instruments Incorporated
;
;   All rights reserved. Property of Texas Instruments Incorporated.
;   Restricted rights to use, duplicate or disclose this code are
;   granted through contract.
;
;   The program may not be used without the written permission
;   of Texas Instruments Incorporated or against the terms and conditions
;   stipulated in the agreement under which this program has been
;   supplied.
; ====================================================================


; BIOS does not support SWE - it justs returns back without any handler support
; Instead we are using SWENR, which is similar to SWE
; SWENR jumps to a location which is given by REP register. This is set up at
; before BIOS_start() when CPU is in supervisor mode. swenr_rep_setup() API is
; used for this purpose.
; In SWENR, NRP is not populated and hence the return address is manually set up
; in the handler (swenr_handler)
; SWENR handler changes the NTSR register as per the function arguments to
; return with the requested CPU mode

       .if __TI_EABI__
       .global  swenr_handler
       .global  swenr_rep_setup
       .global  switchCpuMode_asm
       .else
       .global  _swenr_handler
       .global  _swenr_rep_setup
       .global  _switchCpuMode_asm
       .endif
       .clink

; \brief ASM function from do a CPU mode switch.
;        Switch to USER if (A4 = 1)
;        Switch to SUPERVISOR if (A4 = 0)
       .if __TI_EABI__
switchCpuMode_asm:    .asmfunc
       .else
_switchCpuMode_asm:   .asmfunc
       .endif
    SWENR
swenr_return:
    NOP           5
    RETNOP.S2     B3, 5
    NOP           4
    .endasmfunc

; \brief SWENR handler to change CPU mode
;        Switch to USER if (A4 = 1)
;        Switch to SUPERVISOR if (A4 = 0)
       .if __TI_EABI__
swenr_handler:    .asmfunc
       .else
_swenr_handler:   .asmfunc
       .endif
    STW.D2T2      B0,*B15--[1]
    STW.D2T2      B1,*B15--[1]

    ;Set return pointer
    MVKL          swenr_return, B0
    MVKH          swenr_return, B0
    MVC           B0, NRP

    ;Set CXM (bit 6) for USER (A4 = 1)
    ;Clr CXM (bit 6) for SUPERVISOR (A4 = 0)
    MVC           NTSR, B0
    MVK.S2        0xffffff0f, B1
    MVKH.S2       0xffff0000, B1
    AND           B0, B1, B0
    SHL           A4, 6, A4 ;Argument is A4
    OR            B0, 9, B0 ;Set XEN/GIE bit
    OR            B0, A4, B0
    MVC           B0, NTSR

    LDW.D2T2      *++B15[1],B1
    LDW.D2T2      *++B15[1],B0
    B             NRP
    NOP           5
    .endasmfunc


; \brief ASM function to setup SWENR handler to swenr_handler
       .if __TI_EABI__
swenr_rep_setup:    .asmfunc
       .else
_swenr_rep_setup:   .asmfunc
       .endif
    STW.D2T2      B0,*B15--[1]
    MVKL          swenr_handler, B0
    MVKH          swenr_handler, B0
    MVC           B0, REP
    LDW.D2T2      *++B15[1],B0
    RETNOP.S2     B3, 5
    NOP           4
    .endasmfunc

