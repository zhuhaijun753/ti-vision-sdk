

-stack  0x20000                            /* SOFTWARE STACK SIZE           */
-heap   0x20000                            /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    IRAM_MEM:     org = 0x00000000 len = 0x00001000  /* RAM 0x1FBFF */
	/*SBL will use 1 KB of space from address 0x80000000 for EVE */
    DDR3_M3VPSS:  org = 0x80000400 len = (0x04000000 - 0x400)  /* 64 MB       */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs : load > IRAM_MEM
    .init    : load > DDR3_M3VPSS
              
    .text    : load > DDR3_M3VPSS /* CODE                         */
    .data    : load > DDR3_M3VPSS /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > DDR3_M3VPSS /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end) 
    .const   : load > DDR3_M3VPSS              /* GLOBAL CONSTANTS             */
    .cinit   : load > DDR3_M3VPSS
    .stack   : load > DDR3_M3VPSS            /* SOFTWARE SYSTEM STACK        */
    .plt     : load > DDR3_M3VPSS
    .sysmem  : load > DDR3_M3VPSS
	.my_sect_ddr : load > DDR3_M3VPSS

}

