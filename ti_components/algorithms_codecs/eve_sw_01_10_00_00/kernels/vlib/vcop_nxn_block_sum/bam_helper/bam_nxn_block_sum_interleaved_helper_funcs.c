/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_nxn_block_sum_interleaved_helper_funcs.c
*
* @brief    This file contains all kernel helper functions for nxn_block_sum_interleaved
*           kernel
*
* @author Anshu Jain(anshu.jain@ti.com)
*
* @version 0.0 (Nov 2013) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_nxn_block_sum_interleaved_helper_funcs.h"
#include "vcop_nxn_block_sum_kernel.h"

#define NUM_BINS 6
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */	
#define ALIGN_SIZE(x,y) ((((x) + ((y)-(1U))) / (y)) * (y)) 
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */
BAM_Status BAM_nxn_block_sum_interleaved_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);
/**
*******************************************************************************
* @fn        BAM_nxn_block_sum_interleaved_getMemRecFunc
* @brief
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  memRecInternal :
* @inputs -  memRecOutputDataBlock :
* @inputs -  numRecInternal :
* @inputs -  numRecOutputDataBlock :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_nxn_block_sum_interleaved_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{
    const BAM_nxn_block_sum_interleaved_Args *args = (const BAM_nxn_block_sum_interleaved_Args *)kernelArgs;
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t scratchBufSize;
    uint32_t nxnOutBufSize;
    uint32_t alignedWidth;
    uint32_t alignedHeight;
    if ( args->numBins == NUM_BINS)
    {
    alignedWidth  = ALIGN_SIZE(args->blockW,(args->nValue*VCOP_SIMD_WIDTH));
    alignedHeight = ALIGN_SIZE(args->blockH,(args->nValue*VCOP_SIMD_WIDTH));
    scratchBufSize =  (((((alignedWidth * alignedHeight)/(args->nValue))/(VCOP_SIMD_WIDTH * VCOP_SIMD_WIDTH)) *
                      VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1U) * sizeof(uint32_t)) +
                      ((((alignedWidth * alignedHeight)/(args->nValue * args->nValue))/
                      (VCOP_SIMD_WIDTH * VCOP_SIMD_WIDTH))* VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1U) *
                      sizeof(uint32_t)));
    nxnOutBufSize = (((args->blockW * args->blockH) / (args->nValue * args->nValue))* sizeof(uint16_t));

#if (!VCOP_HOST_EMULATION)
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*(vcop_nxn_sum_interleaved_param_count());
#else
    /* This field could be any non-zero number for host emulation, its not really used for host emualtion */
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].size = 4;
#endif
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;

    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX].size = scratchBufSize;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX].space = BAM_MEMSPACE_WBUF;

    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX].size = scratchBufSize;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX].space = BAM_MEMSPACE_IBUFLA;

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX].size = nxnOutBufSize ;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX].space = BAM_MEMSPACE_IBUFLA;

    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX].size = nxnOutBufSize;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX].space = BAM_MEMSPACE_IBUFHA;

    }
    return status;
}

BAM_KernelInfo gBAM_TI_nxn_block_sum_interleavedKernel =
{
    0,  /*kernelId */
    sizeof(BAM_nxn_block_sum_interleaved_Context),/*kernelContextSize*/
    sizeof(BAM_nxn_block_sum_interleaved_Args),
    BAM_EVE, /* Core Type */
    BAM_NODE_COMPUTE, /*nodeType */
    NXN_BLOCK_SUM_INTERLEAVED_NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    NXN_BLOCK_SUM_INTERLEAVED_NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    NXN_BLOCK_SUM_INTERLEAVED_NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_nxn_block_sum_interleavedHelperFunc =
{
    &BAM_nxn_block_sum_interleaved_getMemRecFunc,
    NULL
};

