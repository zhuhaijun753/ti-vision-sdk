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

    .ref NMI_IRQ
    .ref SWI_IRQ
    .ref INTH_IRQ4
    .ref INTH_IRQ5
    .ref INTH_IRQ6
    .ref INTH_IRQ7

;******************************************************************************
;* Interrupt Service Table (IST)                                              *
;******************************************************************************
    .sect ".intvecs"

_vec_table:
    .word _reset_handler      ; RESET
    .word NMI_IRQ             ; NMI
    .word SWI_IRQ             ; SWI
    .word _dummy_handler      ; Reserved
    .word INTH_IRQ4           ; INT4
    .word INTH_IRQ5           ; INT5
    .word INTH_IRQ6           ; INT6
    .word INTH_IRQ7           ; INT7
    .word _dummy_handler      ; UNDEF
    .word _dummy_handler      ; -----


;******************************************************************************
;* Reset handler                                                              *
;******************************************************************************
    .sect ".inthandler"

_reset_handler:
  	MVC	   1,         CSR     ; enable GIE
	MVC	   0xF3,      IER     ; 
	MVC	   _my_stack, SP
	MVCH   _my_stack, SP
	CALL	_c_int00
	NOP
	CALL	exit
	NOP
	MVK	    _vec_table, R7
	MVK	    main, R6
	MVK	    _reset_handler, R6

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

