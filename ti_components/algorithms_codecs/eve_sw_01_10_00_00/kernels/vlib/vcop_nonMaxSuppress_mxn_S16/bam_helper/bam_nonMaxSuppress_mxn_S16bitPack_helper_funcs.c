/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S16bitPack_funcs.c
 *
 *  @brief      This file defines interfaces for integrating nonMaxSuppress_mxn_S16bitpack into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack_int.h"
#include "vcop_nonMaxSuppress_mxn_16s_kernel.h"
#include <assert.h>

/* Function Prototypes */
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

#if !(VCOP_HOST_EMULATION)
    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_PARAMS_IDX].size =
                                          sizeof(uint16_t) * vcop_nonMaxSuppress_mxn_16sbitPack_param_count();
#else
    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1].size =
                            sizeof(uint16_t) * BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE;
    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2].size =
                            sizeof(uint16_t) * BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE;
    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2].space = BAM_MEMSPACE_WBUF;


    outBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT].size =
                            (sizeof(uint16_t) * BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE)/ 8U;
    outBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT].space = BAM_MEMSPACE_IBUFHA;


    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S16bitPack_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_NonMaxSuppress_mxn_S16bitPack_Context),
        0,
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NONMAXSUPPRESS_MXN_S16BITPACK_NUM_IN_BLOCKS,/* Num Input Blocks*/
        NONMAXSUPPRESS_MXN_S16BITPACK_NUM_OUT_BLOCKS,/* Num Output Blocks*/
        NONMAXSUPPRESS_MXN_S16BITPACK_NUM_INTERNAL_BLOCKS/* Num Internal Blocks*/
};

BAM_KernelHelperFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_HelperFunc =
{
  &BAM_nonMaxSuppress_mxn_S16bitPack_getMemRecFunc,
  NULL
};

