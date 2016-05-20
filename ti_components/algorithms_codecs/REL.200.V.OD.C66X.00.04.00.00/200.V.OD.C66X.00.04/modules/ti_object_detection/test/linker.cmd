/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

/* Linker for DSP1 instance, not DSP2 */

-stack 0x4000
-heap 0x3000000

-h

MEMORY {
   L1P_SRAM     : origin = 0x00E00000,  len = 0x8000
   L1D_SRAM     : origin = 0x00F00000,  len = 0x6000
   L2_SRAM      : origin = 0x00800000,  len = 0x38000
   SL2_SRAM     : origin = 0x5B000000,  len = 0x40000
   EXT_MEM      : origin = 0x80000000,  len = 0x06000000
   FEAT_DAT     : origin = 0x86000000,  len = 0x01000000
}

SECTIONS
{
    vectors   :> EXT_MEM
    .cinit    :> EXT_MEM
    .cio      :> EXT_MEM
    .bss      :> EXT_MEM
    .init_array :> EXT_MEM
    .text     :> EXT_MEM
    .stack    :> L2_SRAM
    .const    :> EXT_MEM
    .far      :> EXT_MEM
    .fardata  :> EXT_MEM
    .neardata :> EXT_MEM
    .rodata   :> EXT_MEM
    .sysmem   :> EXT_MEM
    .switch   :> EXT_MEM
    .dmemSect :> L2_SRAM
    .featDat  :> FEAT_DAT

}


