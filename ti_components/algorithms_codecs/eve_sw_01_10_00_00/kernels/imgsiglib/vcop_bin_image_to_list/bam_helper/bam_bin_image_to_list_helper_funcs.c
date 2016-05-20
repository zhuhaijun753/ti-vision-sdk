/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_bin_image_to_list_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating binary image to
 *              (X, Y) co-ordinate list creation into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_bin_image_to_list_int.h"
#include "vcop_bin_image_to_list_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Bin_image_to_list_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Bin_image_to_list_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2U * vcop_bin_image_to_list_param_count();
#else
    internalBlock[PARAMS_IDX].size = 16U;
#endif
    internalBlock[STARTXY_IDX].size = 4U;
    internalBlock[STARTXY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[STARTXY_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[XSEQ_IDX].size = 4U * 8U *((BIN_IMAGE_TO_LIST_MAX_BLK_WIDTH+7U)/8U);
    internalBlock[XSEQ_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[XSEQ_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_XY_IDX].size = 4U * BIN_IMAGE_TO_LIST_MAX_PIXELS;
    outBlock[OUT_XY_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_SIZE_IDX].size = 4U * 8U;
    outBlock[OUT_SIZE_IDX].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_binImageToListKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Bin_image_to_list_Context),
    sizeof(BAM_Bin_image_to_list_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_BIN_IMAGE_TO_LIST_NUM_IN_BLOCKS,                          /* 1 */
    BAM_BIN_IMAGE_TO_LIST_NUM_OUT_BLOCKS,                         /* 2 */
    BAM_BIN_IMAGE_TO_LIST_NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_binImageToListHelperFunc =
{ &BAM_Bin_image_to_list_getMemRecFunc, NULL};

