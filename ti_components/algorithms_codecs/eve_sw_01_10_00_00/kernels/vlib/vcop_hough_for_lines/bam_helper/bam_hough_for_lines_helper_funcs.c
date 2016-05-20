/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_hough_for_lines_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hough for lines
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_hough_for_lines_int.h"
#include "vcop_hough_for_lines_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_HoughForLines_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_HoughForLines_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    uint16_t      transposeStride;
    uint32_t      transposeBufSize;
    uint32_t      interimArraySize;
#if !VCOP_HOST_EMULATION
    internalBlock[HOUGH_FOR_LINES_INTERNAL_PARAMS_IDX].size =
                      (sizeof(uint16_t) * vcop_hough_for_lines_param_count()) +
                      (sizeof(uint16_t) * vcop_merge_voted_rho_array_param_count());
#else
    internalBlock[HOUGH_FOR_LINES_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    transposeStride = ((( ( (uint16_t)HOUGH_FOR_LINES_RHO_MAX_LENGTH * sizeof(uint16_t)) / 2U ) / 4U) + 1U ) * 4U;

    interimArraySize = HOUGH_FOR_LINES_MAX_LIST_SIZE * sizeof(uint16_t);
    transposeBufSize = 8U * (uint32_t)transposeStride ;

    /* This buffer is reused for second kernel of merging 8copy to single copy also ,
       hence maximum of  of it should be transposeBufSize  and  listSize*/

    internalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX].size = max(transposeBufSize , interimArraySize);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX].space = BAM_MEMSPACE_IBUFHA;


    internalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX].size = 8U * HOUGH_FOR_LINES_RHO_MAX_LENGTH *
                                                                      sizeof(uint16_t);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX].space = BAM_MEMSPACE_WBUF;


    internalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX].size = transposeStride * 8U;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX].size = 8U * sizeof(uint16_t);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX].size = 2U  * sizeof(uint16_t);
    internalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_houghForLinesKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_HoughForLines_Context),
    NULL,
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,
    NUM_OUT_BLOCKS,
    NUM_INTERNAL_BLOCKS
};

BAM_KernelHelperFuncDef gBAM_TI_houghForLinesHelperFunc =
{ &BAM_HoughForLines_getMemRecFunc,
  NULL};


