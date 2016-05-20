/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_horizontal_nms_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating horizontal nms
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_horizontal_non_max_suppression_int.h"
#include "vcop_horizontal_non_max_suppression_kernel.h" /* compiler should take care of include path */

const uint8_t ID_EXT_IDX[8] = {1, 2, 3, 4, 5, 6, 7, 8};

/* Function Prototypes */
static BAM_Status BAM_Horizontal_Non_Max_Suppression_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Horizontal_Non_Max_Suppression_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Horizontal_Non_Max_Suppression_Args *args = (const BAM_Horizontal_Non_Max_Suppression_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U * vcop_horizontal_non_max_suppression_param_count();
#else
    internalBlock[PARAMS_IDX].size = 16U;
#endif

    internalBlock[ID_IDX].size = sizeof(ID_EXT_IDX);
    internalBlock[ID_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[ID_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_XY].size = (args->max_corners + 8U) * sizeof(uint32_t);
    outBlock[BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_XY].space = BAM_MEMSPACE_IBUFHA;

    outBlock[BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_SCORE].size = (args->max_corners + 8U) * sizeof(uint16_t);
    outBlock[BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_SCORE].space = BAM_MEMSPACE_WBUF ;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_horizontalnonmaxsuppressionKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Horizontal_Non_Max_Suppression_Context),
    sizeof(BAM_Horizontal_Non_Max_Suppression_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 2 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_horizontalnonmaxsuppressionHelperFunc =
{ &BAM_Horizontal_Non_Max_Suppression_getMemRecFunc, NULL};

