/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_extract_bit_field_u32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating extract
 *              bit field function into BAM
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_extract_bit_field_u32_int.h"
#include "vcop_extract_bit_field_u32_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Extract_Bit_Field_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Extract_Bit_Field_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Extract_Bit_Field_Args *args = (const BAM_Extract_Bit_Field_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_extract_bit_field_u32_param_count();
#else
    /* This field could be any non-zero number for host emulation */
    internalBlock[PARAMS_IDX].size = 4U;
#endif

    outBlock[OUT_LIST_IDX].size = args->length;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_extract_bit_field_u32Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Extract_Bit_Field_Context),
    sizeof(BAM_Extract_Bit_Field_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_extract_bit_field_u32HelperFunc =
{ &BAM_Extract_Bit_Field_getMemRecFunc, NULL};
