/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_binary_masking_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating binary Masking
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_binary_masking_int.h"
#include "vcop_binary_masking_kernel.h" /* compiler should take care of include path */


static BAM_Status BAM_BinaryMasking_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_BinaryMasking_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    BAM_BinaryMasking_Args *args = (BAM_BinaryMasking_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[BINARY_MASKING_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * vcop_binary_masking_param_count();
#else
    internalBlock[BINARY_MASKING_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    outBlock[BAM_BINARY_MASKING_OUTPUT_PORT].size = (args->maxBlockWidth / 8U) * args->maxBlockHeight;
    outBlock[BAM_BINARY_MASKING_OUTPUT_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_BINARY_MASKING_OUTPUT_PORT].space = BAM_MEMSPACE_WBUF;


    return BAM_S_SUCCESS;
}


/* For Compute Hough Space index BAM node */
BAM_KernelInfo gBAM_TI_binaryMaskingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_BinaryMasking_Context),
    sizeof(BAM_BinaryMasking_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_BINARY_MASKING_NUM_INPUT_BLOCKS,
    BAM_BINARY_MASKING_NUM_OUTPUT_BLOCKS,
    BINARY_MASKING_INTERNAL_NUM_BLOCK
};

BAM_KernelHelperFuncDef gBAM_TI_binaryMaskingHelperFunc =
{ &BAM_BinaryMasking_getMemRecFunc,
  NULL};

