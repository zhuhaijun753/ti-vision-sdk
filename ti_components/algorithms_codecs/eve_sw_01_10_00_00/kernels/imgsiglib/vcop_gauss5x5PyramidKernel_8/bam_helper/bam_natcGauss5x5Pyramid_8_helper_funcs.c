/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gauss5x5Pyramid_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating gauss5x5Pyramid into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_gauss5x5Pyramid_8_int.h"
#include "vcop_gauss5x5PyramidKernel_8_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcGauss5x5Pyramid_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_natcGauss5x5Pyramid_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Gauss5x5Pyramid_Args *args = (const BAM_Gauss5x5Pyramid_Args *) kernelArgs;

#if !(VCOP_HOST_EMULATION)
    internalBlock[PARAMS_H_IDX].size = 2u*vcop_gauss5x5PyramidKernel_8_horiz_param_count();
    internalBlock[PARAMS_V_IDX].size = 2u*vcop_gauss5x5PyramidKernel_8_vert_param_count();
    internalBlock[PARAMS_TEMP_IDX].size = args->width*(args->height+ (5u-1u) );
    internalBlock[PARAMS_TEMP_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
#else
    internalBlock[PARAMS_H_IDX].size = 4u;
    internalBlock[PARAMS_V_IDX].size = 4u;
    internalBlock[PARAMS_TEMP_IDX].size = args->width*(args->height+5u-1u);
    internalBlock[PARAMS_TEMP_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
#endif

    /* The size of the output block should be a quarter of the processing block
     * It is expected that the application must have intialized args->out_stride accordingly whereas the height needs to be derived from args->height
     * */
    outBlock[OUT_IDX].size = args->out_stride*(args->height>>1);

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_natcGauss5x5PyramidKernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_Gauss5x5Pyramid_Context),
        sizeof(BAM_Gauss5x5Pyramid_Args),
        BAM_EVE_ARP32,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_natcGauss5x5PyramidHelperFunc =
{ &BAM_natcGauss5x5Pyramid_getMemRecFunc, NULL};

