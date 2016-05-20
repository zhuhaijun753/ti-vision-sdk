/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_harrisScore_32_methodB_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating harrisScore_32_methodB into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_harrisScore_32_methodB_int.h"
#include "vcop_harrisScore_32_7x7_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_harrisScore_32_methodB_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_harrisScore_32_methodB_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_HarrisScore_32_7x7_Args *args = (const BAM_HarrisScore_32_7x7_Args *) kernelArgs;

#if !(VCOP_HOST_EMULATION)
    internalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_PARAM_IDX].size = sizeof(uint16_t)* vcop_harrisScore_32_methodB_param_count();
#else
    internalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_PARAM_IDX].size = 4u;
#endif
    internalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHXX_IDX].size = (uint32_t)sizeof(uint32_t)*(ALIGN_SIMD(args->width)*(args->height+1u));
    internalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHXX_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHYY_IDX].size = (uint32_t)sizeof(uint32_t)*(ALIGN_SIMD(args->width)*(args->height+1u));
    internalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHYY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    outBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT].size = (uint32_t)sizeof(uint32_t)*((args->outStride*(args->height - (args->windowSize - 1u)))+(uint32_t)VCOP_SIMD_WIDTH);
    /* During performance fine-tuning of harris-corner applet, we concluded that larger blocks can be allocated if this output memory record goes to WBUF
     * This improvement may only be meaningful in the case of harris-corner applet. For other applet, try first with the below line removed.
     * */
    outBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT].space= BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_harrisScore_32_methodB_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_HarrisScore_32_methodB_Context),
        sizeof(BAM_HarrisScore_32_7x7_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 2 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 7 */
};

BAM_KernelHelperFuncDef gBAM_TI_harrisScore_32_methodB_HelperFunc =
{ &BAM_harrisScore_32_methodB_getMemRecFunc, NULL};

