/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_fast9_int.h"
#include "vcop_fast9_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_Fast9_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);


static BAM_Status BAM_Fast9_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    uint16_t          blockWidth;
    uint16_t          blockHeight;
#if (!VCOP_HOST_EMULATION)
    internalBlock[FAST9_PARAMS_IDX].size = 2U*vcop_fast9_param_count();
#else
    /* This field could be any non-zero number for host emulation */
    internalBlock[FAST9_PARAMS_IDX].size = 4U;
#endif

    blockWidth  = FAST9_TI_BLK_WIDTH_MAX;
    blockHeight = FAST9_TI_BLK_HEIGHT_MAX;

    internalBlock[FAST9_SCRATCH_OUT0_PTR_IDX].size = 2U * blockWidth * blockHeight;
    internalBlock[FAST9_SCRATCH_OUT0_PTR_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[FAST9_SCRATCH_OUT0_PTR_IDX].space             = BAM_MEMSPACE_IBUFLA;

    internalBlock[FAST9_SCRATCH_OUT1_PTR_IDX].size = 2U * blockWidth * blockHeight;
    internalBlock[FAST9_SCRATCH_OUT1_PTR_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[FAST9_SCRATCH_OUT1_PTR_IDX].space             = BAM_MEMSPACE_WBUF;

    internalBlock[FAST9_SCRATCH_OUT4_PTR_IDX].size = 2U * blockWidth * blockHeight * sizeof(uint16_t);
    internalBlock[FAST9_SCRATCH_OUT4_PTR_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[FAST9_SCRATCH_OUT4_PTR_IDX].space             = BAM_MEMSPACE_WBUF;

    outBlock[FAST9_OUT_IDX].size = (blockWidth/8U) * blockHeight;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_fast9Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Fast9_Context),
    sizeof(BAM_Fast9_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_fast9HelperFunc =
{ &BAM_Fast9_getMemRecFunc, NULL};

