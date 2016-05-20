;/*==========================================================================*/
;/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
;/*                      All Rights Reserved                                 */
;/*==========================================================================*/

;******************************************************************************
;* asm directives                                                             *
;******************************************************************************

    .data
    .global _my_stack
_my_stack:
    .word 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0

    .text   
	.global	main
	.global	_c_int00
	.global exit
	.global _vec_table
	.global _reset_handler
	.global _dummy_handler

;******************************************************************************
;* Interrupt Service Table (IST)                                              *
;******************************************************************************
    .sect ".intvecs"

_vec_table:
    .word _reset_handler          ; RESET
    ;.word 0x20 ; RESET;
    .word _dummy_handler          ; NMI
    .word _dummy_handler          ; SWI
    .word _dummy_handler          ; Reserved
    .word _dummy_handler          ; INT4
    .word _dummy_handler          ; INT5
    .word _dummy_handler          ; INT6
    .word _dummy_handler          ; INT7
    .word _dummy_handler          ; UNDEF
    .word _dummy_handler          ; -----



;******************************************************************************
;* Reset handler                                                              *
;******************************************************************************
    .sect ".inthandler"

_reset_handler:
; 	MVC	1, CSR
; 	MVC	19, IER
	MVC	   _my_stack, SP
	MVCH   _my_stack, SP
	CALL	_c_int00
	NOP
	CALL	exit
	NOP
	MVK	_vec_table, R7
	MVK	main, R6
	MVK	_reset_handler, R6

;******************************************************************************
;* Dummy handler                                                              *
;******************************************************************************
    .sect ".inthandler"
_dummy_handler:
	NOP
	NOP
	B	_dummy_handler
	NOP

;----------------------------------------------------------------------
; Exit simulation
;----------------------------------------------------------------------
	.sect	".exitlocation"
	.global	end_of_test
	        NOP       ; -- 0x100
    
	        NOP       ; -- 0x104
	        NOP       ; -- 0x108
end_of_test: 
	        MVKS	-1, R0       
	        MVKS	-1, R1       
	        MVKS	-1, R2       
	        MVKS	-1, R3       
	        MVKS	-1, R4       
	        MVKS	-1, R5       
	        MVKS	-1, R6       
	        MVKS	-1, R7      
	        
;----------------------------------------------------------------------

