

-stack  0x2800                             /* SOFTWARE STACK SIZE           */
-heap   0x2800                             /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
	IRAM_MEM        : org = 0x40300000  len = 0x1C000       /* RAM 0x1FBFF*/
	MMU_TLB         : org = 0x4031C000  len = 0x00004000    /* IRAM spilt to 112kb and 16kb */
	/*SBL will use 1 KB of space from address 0x80000000 for EVE */
	DDR3_A8         : org = 0x80000400  len = (0x0B000000 - 0x400)     /* 176 MB */
	DDR3_DSP        : org = 0x8B000000  len = 0x02000000    /* 32 MB */
	DDR3_M3VPSS     : org = 0x8D000000  len = 0x01000000    /* 16 MB */
	DDR3_M3VIDEO    : org = 0x8E000000  len = 0x01000000    /* 16 MB */
	DDR3_SR0        : org = 0x8F000000  len = 0x01000000    /* 16 MB */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .init    : load > IRAM_MEM
    .text    : load > IRAM_MEM              /* CODE                         */
    .data    : load > IRAM_MEM              /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > IRAM_MEM              /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > IRAM_MEM              /* GLOBAL CONSTANTS             */
    .cinit   : load > IRAM_MEM
    .stack   : load > IRAM_MEM            /* SOFTWARE SYSTEM STACK        */
    .plt     : load > IRAM_MEM
    .my_sect_ddr : load > IRAM_MEM
    .sysmem : load > IRAM_MEM
}

