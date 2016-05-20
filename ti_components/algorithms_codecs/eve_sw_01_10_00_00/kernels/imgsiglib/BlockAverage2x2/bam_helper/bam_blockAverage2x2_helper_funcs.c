/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockAverage2x2_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating blockAverage2x2 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_blockAverage2x2_int.h"
#include "vcop_blockAverage2x2_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_blockAverage2x2_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_blockAverage2x2_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_BlockAverage2x2_Args *args = (const BAM_BlockAverage2x2_Args *) kernelArgs;

#if !(VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2u*vcop_blockAverage2x2_uchar_param_count();
#else
    internalBlock[PARAMS_IDX].size = 4u;
#endif

    /* The size of the output block should be a quarter of the processing block
     * It is expected that the application must have intialized args->out_stride accordingly whereas the height needs to be derived from args->height
     * */
    outBlock[OUT_IDX].size = args->out_stride*(args->height>>1);

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_blockAverage2x2Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_BlockAverage2x2_Context),
        sizeof(BAM_BlockAverage2x2_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_blockAverage2x2HelperFunc =
{ &BAM_blockAverage2x2_getMemRecFunc, NULL};

