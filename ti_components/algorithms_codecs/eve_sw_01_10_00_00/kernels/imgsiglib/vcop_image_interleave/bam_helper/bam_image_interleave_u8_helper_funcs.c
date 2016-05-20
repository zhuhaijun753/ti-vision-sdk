/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_interleave_u8_exec_funcs.c
 *
 *  @brief       This file implements functions for integrating unsigned 8 bit interleave function into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_image_interleave_u8_int.h"
#include "vcop_image_interleave_kernel.h" /* compiler should take care of include path */


/* Function Prototypes */
static BAM_Status BAM_Image_interleave_u8_getMemRecFunc(const void *kernelArgs, BAM_MemRec *internalBlock,
        BAM_MemRec *outBlock, uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

#if 0
static BAM_Status BAM_Image_interleave_u8_setMemRecFunc(const BAM_MemRec *internalBlock[],
        const BAM_MemRec *inBlock[], const BAM_MemRec *outBlock[], uint8_t numInternalBlocks,
        uint8_t numInBlocks, uint8_t numOutBlocks, void *kernelContext, const void *kernelArgs);
#endif

static BAM_Status BAM_Image_interleave_u8_getMemRecFunc(const void *kernelArgs, BAM_MemRec *internalBlock,
        BAM_MemRec *outBlock, uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    BAM_Image_Interleave_U8_Args *args = (BAM_Image_Interleave_U8_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2 * vcop_image_interleave_u8_param_count();
    outBlock[0].size = (args->inRows) * (args->inCols) * 2;

    return BAM_S_SUCCESS;
}

/* Comment out below function as we are passing NULL as pointer to the setmemRec function in structure BAM_KernelHelperFuncDef
 * BAM automatically copies the different input, output, internal block's pointers into the kernel's context, as well as the arguments.
 */
#if 0
static BAM_Status BAM_Image_interleave_u8_setMemRecFunc(const BAM_MemRec *internalBlock[],
        const BAM_MemRec *inBlock[], const BAM_MemRec *outBlock[], uint8_t numInternalBlocks,
        uint8_t numInBlocks, uint8_t numOutBlocks, void *kernelContext, const void *kernelArgs)
{
    BAM_Image_Interleave_U8_Args *args = (BAM_Image_Interleave_U8_Args *) kernelArgs;
    BAM_Image_Interleave_U8_Context *context = (BAM_Image_Interleave_U8_Context *) kernelContext;

    if (numInternalBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
    }
    if (numInBlocks != 2)
    {
        PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
    }
    if (numOutBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
    }

    context->kernelArgs= *args;

    context->pInBlock[Y_IDX] = inBlock[Y_IDX]->base;
    context->pInBlock[UV_IDX] = inBlock[UV_IDX]->base;
    context->pOutBlock[0] = outBlock[0]->base;
    context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;

    return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_interleaveu8Kernel =
{
    0,                  /* kernelId */
    sizeof(BAM_Image_Interleave_U8_Context),    /* CHECK: kernelContextSize = sizeof(EVE_EDMA_transfer_context) */
    sizeof(BAM_Image_Interleave_U8_Args),
    BAM_EVE, /*coreType */
    BAM_NODE_COMPUTE,   /* nodeType */
    NUM_IN_BLOCKS,                  /* 2 */
    NUM_OUT_BLOCKS,                 /* 1 */
    NUM_INTERNAL_BLOCKS             /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_interleaveu8HelperFunc =
{ &BAM_Image_interleave_u8_getMemRecFunc, /*&BAM_Image_interleave_u8_setMemRecFunc*/ };
