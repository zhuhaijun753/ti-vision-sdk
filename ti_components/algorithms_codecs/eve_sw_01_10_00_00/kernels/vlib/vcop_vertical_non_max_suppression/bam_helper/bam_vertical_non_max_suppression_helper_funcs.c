/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vertical_nms_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating vertical nms
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_vertical_non_max_suppression_int.h"
#include "vcop_vertical_non_max_suppression_kernel.h" /* compiler should take care of include path */

const uint8_t IN_ID_IDX[8] = {1, 2, 3, 4, 5, 6, 7, 8};


/* Function Prototypes */
static BAM_Status BAM_Vertical_Non_Max_Suppression_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Vertical_Non_Max_Suppression_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Vertical_Non_Max_Suppression_Args *args = (const BAM_Vertical_Non_Max_Suppression_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_vertical_non_max_suppression_kernel_param_count();
#else
    internalBlock[PARAMS_IDX].size = 16U;
#endif

    internalBlock[ID_IDX].size = 8U*sizeof(uint8_t);
    internalBlock[ID_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    internalBlock[NMS_ID_IDX].size = args->max_corners * sizeof(uint16_t);
    internalBlock[NMS_ID_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    
    internalBlock[NMS_Y_SCORE_IDX].size = args->max_corners * sizeof(uint16_t);
    internalBlock[NMS_Y_SCORE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    outBlock[BAM_VERTICAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_XY].size = (args->max_corners + (2U*VCOP_SIMD_WIDTH)) * (sizeof(uint32_t));

    outBlock[BAM_VERTICAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_SCORE].size = (args->max_corners + (2U*VCOP_SIMD_WIDTH)) * (sizeof(uint32_t));

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_verticalnonmaxsuppressionKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Vertical_Non_Max_Suppression_Context),
    sizeof(BAM_Vertical_Non_Max_Suppression_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 3 */
    NUM_OUT_BLOCKS,                         /* 2 */
    NUM_INTERNAL_BLOCKS                     /* 2 */
};

BAM_KernelHelperFuncDef gBAM_TI_verticalnonmaxsuppressionHelperFunc =
{ &BAM_Vertical_Non_Max_Suppression_getMemRecFunc, NULL};

