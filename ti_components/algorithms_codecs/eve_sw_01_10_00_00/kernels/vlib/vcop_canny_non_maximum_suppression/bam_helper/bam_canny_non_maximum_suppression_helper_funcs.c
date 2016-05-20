/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_canny_non_maximum_suppression_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Canny NMS
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_canny_non_maximum_suppression_int.h"
#include "vcop_canny_non_maximum_suppression_kernel.h" /* compiler should take care of include path */

static BAM_Status BAM_CannyNonMaximumSuppression_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_CannyNonMaximumSuppression_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_CannyNonMaximumSuppression_Args *args = (const BAM_CannyNonMaximumSuppression_Args *) kernelArgs;


#if !VCOP_HOST_EMULATION
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) *
                      ( vcop_canny_bin_indexing_param_count() +
                      vcop_canny_nms_max_cases_param_count() +
                      vcop_canny_nms_double_thresholding_param_count());
#else
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX].size = args->maxBlockWidth *
                                                                          args->maxBlockHeight *
                                                                          sizeof(uint8_t);
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX].size = args->maxBlockWidth *
                                                                          args->maxBlockHeight *
                                                                          sizeof(uint16_t);
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX].size = args->maxBlockWidth *
                                                                          args->maxBlockHeight *
                                                                          sizeof(uint16_t);
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX].space = BAM_MEMSPACE_WBUF;


    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX].size = args->maxBlockWidth *
                                                                          args->maxBlockHeight *
                                                                          sizeof(uint16_t);
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX].space = BAM_MEMSPACE_WBUF;


    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX].size = args->maxBlockWidth *
                                                                          args->maxBlockHeight *
                                                                          sizeof(uint16_t);
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX].space = BAM_MEMSPACE_WBUF;


    outBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT].size = args->maxBlockWidth *
                                                                          args->maxBlockHeight *
                                                                          sizeof(uint8_t);
    outBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}

/* For Compute Hough Space index BAM node */
BAM_KernelInfo gBAM_TI_cannyNonMaximumSuppressionKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_CannyNonMaximumSuppression_Context),
    sizeof(BAM_CannyNonMaximumSuppression_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_CANNY_NON_MAXIMUM_SUPPRESSION_NUM_INPUT_BLOCKS,
    BAM_CANNY_NON_MAXIMUM_SUPPRESSION_NUM_OUTPUT_BLOCKS,
    CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_NUM_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_cannyNonMaximumSuppressionHelperFunc =
{ &BAM_CannyNonMaximumSuppression_getMemRecFunc,
  NULL};

