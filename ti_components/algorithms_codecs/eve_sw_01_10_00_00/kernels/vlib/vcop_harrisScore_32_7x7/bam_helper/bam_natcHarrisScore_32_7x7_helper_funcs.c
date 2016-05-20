/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcHarrisScore_32_7x7_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating harrisScore_32_7x7 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_harrisScore_32_7x7_int.h"
#include "vcop_harrisScore_32_7x7_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcHarrisScore_32_7x7_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_natcHarrisScore_32_7x7_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if !(VCOP_HOST_EMULATION)
    const BAM_HarrisScore_32_7x7_Args *args = kernelArgs;
    internalBlock[PARAMS_IDX_1].size = 2u*vcop_harrisScore_32_7x7_1_param_count();
    internalBlock[PARAMS_IDX_2].size = 2u*vcop_harrisScore_32_7x7_2_param_count();
#else
    const BAM_HarrisScore_32_7x7_Args *args = (const BAM_HarrisScore_32_7x7_Args *)kernelArgs;
    internalBlock[PARAMS_IDX_1].size = 4u;
    internalBlock[PARAMS_IDX_2].size = 4u;

#endif
    internalBlock[XX_IDX].size = sizeof(uint32_t)*(ALIGN_SIMD(args->width)*(args->height+1u));
    internalBlock[XX_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[YY_IDX].size = sizeof(uint32_t)*(ALIGN_SIMD(args->width)*(args->height+1u));
    internalBlock[YY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[XY_IDX].size = sizeof(uint32_t)*(ALIGN_SIMD(args->width)*(args->height+1u));
    internalBlock[XY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[DETL_IDX].size = sizeof(uint32_t)*(args->outStride*(args->height - (args->windowSize - 1u))+VCOP_SIMD_WIDTH); /* we add VCOP_SIMD_WIDTH of guard band because the function rounds the loop counter so a multiple of 16 elements is processed every row */
    internalBlock[DETL_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[DETH_IDX].size = sizeof(uint32_t)*(args->outStride*(args->height - (args->windowSize - 1u))+VCOP_SIMD_WIDTH);
    internalBlock[DETH_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    outBlock[OUT_IDX].size = sizeof(uint32_t)*(args->outStride*(args->height - (args->windowSize - 1u))+VCOP_SIMD_WIDTH);
    /* During performance fine-tuning of harris-corner applet, we concluded that larger blocks can be allocated if this output memory record goes to WBUF
     * This improvement may only be meaningful in the case of harris-corner applet. For other applet, try first with the below line removed.
     * */
    outBlock[OUT_IDX].space= BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_natcHarrisScore_32_7x7_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_HarrisScore_32_7x7_Context),
        sizeof(BAM_HarrisScore_32_7x7_Args),
        BAM_EVE_ARP32,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 2 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 7 */
};

BAM_KernelHelperFuncDef gBAM_TI_natcHarrisScore_32_7x7_HelperFunc =
{ &BAM_natcHarrisScore_32_7x7_getMemRecFunc, NULL};

