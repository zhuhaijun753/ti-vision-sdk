/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_disparityHamDist_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hamming-based disparity calculation kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_disparityHamDist_int.h"
#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_postprocess_kernel.h"
#include "init_disparity_hammingDistance_row_params.h"
#include "vcop_disparity_hammingDistance_row_cn.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

/* Function Prototypes */
static BAM_Status BAM_DisparityHamDist_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter kernelArgs is not used to modify the addressed object but is not declared as a pointer to const */
/* Must be a false positive because it is declared as pointer to const void here */
static BAM_Status BAM_DisparityHamDist_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7 */

    uint16_t scratchBufferSize, allCostOutputBufferSize;
    uint32_t pScatterStride;
    BAM_Status status= BAM_S_SUCCESS;
    /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
    /* Cast operation removes const or volatile modifier from a pointer or reference */
    /* Doesn't seem it is an issue here, probably a false positive */
    const BAM_DisparityHamDist_Args *args= (const BAM_DisparityHamDist_Args*)kernelArgs;
    /*RESET_MISRA("11.8")  -> Reset rule 11.8 for GOTO */
    
    /* Make sure that codeWordByteLen is 4, currently only 32-bits hamming distance is supported */
    if (args->codeWordByteLen != 4) {
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* Make sure that out_pitch is multiple of 4 but not multiple of 32 */
    if ((args->allCostOutputStride < (args->width*SIZE_COST)) || ((args->allCostOutputStride & 3U)!=0) || ((args->allCostOutputStride & 31U)==0)) {
        status= BAM_E_FAIL;
        goto Exit;
    }

    /* Two lines below are extracted from init_disparity_hammingDistance_row_params(). Calculate size of one line used in the first p-scatter, need to be (n*8 + 1) banks or (n*8*4 + 4)=  n*32 + 4 bytes) wide to avoid p-scatter error*/
    /*pScatterStride= (uint16_t)((((uint32_t)args->numDisparities/(uint32_t)args->disparityStep)*(uint32_t)SIZE_COST + 31UL) & (uint32_t)(~31UL)) + 4UL ;*/ /* Round up to next multiple of 32 and then add 4 bytes */ 
    pScatterStride= (((uint32_t)args->numDisparities/(uint32_t)args->disparityStep)*(uint32_t)SIZE_COST) + 31UL;
    pScatterStride= ((uint32_t)pScatterStride & 0xFFFFFFE0U);
    pScatterStride+= 4UL;

    scratchBufferSize= (uint16_t)pScatterStride*args->width;

    /* Return the allCostOutput buffer size that needs to be allocated */
    allCostOutputBufferSize= (uint16_t)args->allCostOutputStride*(uint16_t)(2U + ((uint32_t)args->numDisparities/(uint32_t)args->disparityStep)); /* The +2 is a requirement from  vcop_disparity_genPrevAndNextMinCost()  */

#if (!VCOP_HOST_EMULATION)
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].size = (uint32_t)DISPARITY_HAMDIST_PARAMS_SIZE;
#else
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].size = (uint32_t)DISPARITY_HAMDIST_PARAMS_SIZE;
#endif
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[DISPARITY_HAMDIST_PARAMS_IDX].space             = BAM_MEMSPACE_IBUFLA;

    /*
     * Will contain one byte of value 0x80 used as 'collate mask' and 32 bytes used for p-scatter's osffsets.
     */
    internalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX].size = 34U;
    internalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX].attrs.memAttrs    = BAM_MEMATTRS_CONST;
    internalBlock[DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX].space             = BAM_MEMSPACE_WBUF;

    /* Size of scratch should be scratchBufferSize 
     */
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].size = (uint32_t)scratchBufferSize;
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].space             = BAM_MEMSPACE_IBUFHA;
    internalBlock[DISPARITY_HAMDIST_SCRATCH0_IDX].alignment         = 32;

    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].size = (uint32_t)scratchBufferSize;
    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].space             = BAM_MEMSPACE_WBUF;
    internalBlock[DISPARITY_HAMDIST_SCRATCH1_IDX].alignment         = 32;

    /* Don't support for now
    if (args->extraRLdisparities== 1) {
        internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].size = MAX((args->numDisparities / args->disparityStep) * SIZE_COST * (args->width + args->numDisparities - 1), allCostOutputBufferSize);
    }
    else {
        internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].size = allCostOutputBufferSize;
    }
    */
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].size = allCostOutputBufferSize;
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].space             = BAM_MEMSPACE_IBUFLA;
    internalBlock[DISPARITY_HAMDIST_SCRATCH2_IDX].alignment         = 32;

    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].size = allCostOutputBufferSize;
    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].space= BAM_MEMSPACE_WBUF;
    internalBlock[DISPARITY_HAMDIST_ALLCOST_IDX].alignment= 32;

    outBlock[DISPARITY_HAMDIST_DISP_OUT_IDX].size = args->width;
    outBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX].size = 2*args->width;
    outBlock[DISPARITY_HAMDIST_CARRYOVER_OUT_IDX].size = 2*(args->numDisparities/args->disparityStep);
    
    if (args->adjacentCosts== 1) {
        outBlock[DISPARITY_HAMDIST_PREV_ADJ_COST].size = 2*args->width;
        outBlock[DISPARITY_HAMDIST_NEXT_ADJ_COST].size = 2*args->width;
    }
    else {
        outBlock[DISPARITY_HAMDIST_PREV_ADJ_COST].size = 4;
        outBlock[DISPARITY_HAMDIST_NEXT_ADJ_COST].size = 4;
    }
    
    /* Don't support for now
    if (args->extraRLdisparities== 1) {
        outBlock[DISPARITY_HAMDIST_RL_DISP_OUT_IDX].size = ALIGN_2SIMD(args->width + args->numDisparities - 1);
        outBlock[DISPARITY_HAMDIST_RL_MINCOST_OUT_IDX].size = SIZE_COST * ALIGN_2SIMD(args->width + args->numDisparities - 1);
    }
    else {
        outBlock[DISPARITY_HAMDIST_RL_DISP_OUT_IDX].size = 4;
        outBlock[DISPARITY_HAMDIST_RL_MINCOST_OUT_IDX].size = 4;
    }
    */

    Exit:
    return status;
}


BAM_KernelInfo gBAM_TI_disparityHamDist_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_DisparityHamDist_Context),
        sizeof(BAM_DisparityHamDist_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 3 */
        NUM_OUT_BLOCKS,                         /* 5 */
        NUM_INTERNAL_BLOCKS                     /* 8 */
};

BAM_KernelHelperFuncDef gBAM_TI_disparityHamDist_HelperFunc =
{ &BAM_DisparityHamDist_getMemRecFunc, NULL};

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */


