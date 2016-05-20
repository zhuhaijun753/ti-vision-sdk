;==========================================================================;
;      Copyright (C) 2009-2012 Texas Instruments Incorporated.             ;
;                      All Rights Reserved                                 ;
;==========================================================================;
	.global	NMI_IRQ_ASM1
NMI_IRQ_ASM1:
    STRF    R7, R0
    MVC    LSA0, R0
    MVC     LEA0, R1
    MVC     LCNT0, R2
    MVC     LSA1, R3
    MVC     LEA1, R4
    MVC     LCNT1, R5
    MVC     LCNT0RLD, R6
    STRF    R6, R0

	.global	NMI_IRQ_ASM2
NMI_IRQ_ASM2:
    LDRF    R0, R6
    MVC     R0, LSA0
    MVC     R1, LEA0
    MVC     R2, LCNT0
    MVC     R3, LSA1
    MVC     R4, LEA1
    MVC     R5, LCNT1
    MVC     R6, LCNT0RLD
    LDRF    R0, R7
    NOP
    NOP
    ADD 4, SP
    BNRP
    NOP
    NOP

