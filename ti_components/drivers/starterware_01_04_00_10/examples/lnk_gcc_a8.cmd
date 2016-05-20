/****************************************************************************/
/* lnk_gcc_a8.cmd -COMMAND FILE FOR LINKING Linaro ToolChain C/CPPPROGRAMS  */
/*                                                                          */
/****************************************************************************/

/*-stack  0x2800                              SOFTWARE STACK SIZE           */
/*-heap   0x2800                              HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */


ENTRY(Entry)
MEMORY
 {

    IRAM_MEM        : org = 0x40300000,  len = 0x1C000            /* RAM 0x1FBFF*/
    MMU_TLB		: org = 0x4031C000,  len = 0x4000
	/*SBL will use 1 KB of space from address 0x80000000 for EVE */
    DDR3_A8		:org = 0x80000400, len = (0x0B000000 - 0x400)    /* 176 MB */
	DDR3_DSP	:org = 0x8B000000, len = 0x02000000    /* 32 MB */
	DDR3_M3VPSS 	:org = 0x8D000000, len = 0x01000000    /* 16 MB */
	DDR3_M3VIDEO	:org = 0x8E000000, len = 0x01000000    /* 16 MB */
	DDR3_SR0	:org = 0x8F000000, len = 0x01000000    /* 16 MB */
 }
/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

 SECTIONS
 {

    .init    : {*(.init)} > DDR3_A8


    .text    : {*(.text)} > DDR3_A8              /* CODE                         */
    .data    : {*(.data)} > DDR3_A8              /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
	.bss ALIGN(0x4):
    {
		bss_start = . ;
		*(.bss.*) *(COMMON);
		bss_end = . ;
    } 	> DDR3_A8              /* UNINITIALIZED OR ZERO INITIALIZED */
                                             /* GLOBAL & STATIC VARIABLES.   */
	. = ALIGN(4);
	_end = .;
	PROVIDE (end = .);

	.stack ALIGN(0x4):
	{
		stack_start = .;
		*(.stack.*) ;
		. = . + 0x1000;
		stack_end = .;
	}	> DDR3_A8

	. = ALIGN(4);
	__exidx_start = .;
	PROVIDE(__exidx_start = __exidx_start);

	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*);
	} > DDR3_A8

	. = ALIGN(4);
	__exidx_end = .;
	PROVIDE(__exidx_end = __exidx_end);
    .const  ALIGN(0x4):  {*(.const)} > DDR3_A8              /* GLOBAL CONSTANTS             */
	.my_sect_ddr ALIGN(0x4): {*(.my_sect_ddr)} > DDR3_A8
	_stack = stack_end;
 }
