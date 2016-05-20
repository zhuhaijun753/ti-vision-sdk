/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_contrast_stretching_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_contrast_stretching_int.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_ContrastStretching_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_ContrastStretching_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_ContrastStretching_Args *args = (const BAM_ContrastStretching_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX].size =
                      sizeof(uint16_t) * vcop_contrast_stretching_param_count();
#else
    internalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    outBlock[BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT].size =
                              ALIGN_2SIMD(args->blkWidth) * args->blkHeight;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_contrastStretchingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_ContrastStretching_Context),
    sizeof(BAM_ContrastStretching_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 2 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_contrastStretchingHelperFunc =
{ &BAM_ContrastStretching_getMemRecFunc, NULL};

