/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_intensity_scaling_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating intensity
 *              scaling kernel into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_intensity_scaling_int.h"
#include "vcop_intensity_scaling_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Intensity_scaling_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Intensity_scaling_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Intensity_scaling_Args *args = (const BAM_Intensity_scaling_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2U*vcop_intensity_scaling_param_count();
#else
    internalBlock[PARAMS_IDX].size = 4U;
#endif

    internalBlock[LUT_IDX].size = NUM_SCALING_TBLS*SCALING_TBL_SIZE;
    internalBlock[LUT_IDX].alignment = 32U;
    internalBlock[LUT_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[LUT_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_IMG_IDX].size = args->blockWidth*args->blockHeight;
    outBlock[OUT_IMG_IDX].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_intensityScalingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Intensity_scaling_Context),
    sizeof(BAM_Intensity_scaling_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 2 */
};

BAM_KernelHelperFuncDef gBAM_TI_intensityScalingHelperFunc =
{ &BAM_Intensity_scaling_getMemRecFunc, NULL};

