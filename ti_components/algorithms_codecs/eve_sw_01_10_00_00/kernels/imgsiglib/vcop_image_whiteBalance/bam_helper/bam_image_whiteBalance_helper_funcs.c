/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_whiteBalance_helper_funcs.c
*
* @brief This file contains all kernel helper functions for white balance adjustments
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_image_whiteBalance_helper_funcs.h"
#include "vcop_white_balance_kernel.h"


/* Function Prototypes */
static BAM_Status BAM_Image_whiteBalance_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
);
#if 0
static BAM_Status BAM_Image_whiteBalance_setMemRecFunc
(
    const BAM_MemRec  *internalBlock[],
    const BAM_MemRec  *inBlock[],
    const BAM_MemRec  *outBlock[],
    uint8_t            numInternalBlocks,
    uint8_t            numInBlocks,
    uint8_t            numOutBlocks,
    void              *kernelContext,
    void              *kernelArgs
);
#endif


/**
*******************************************************************************
* @fn        BAM_Image_whiteBalance_getMemRecFunc
* @brief
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  internalBlock :
* @inputs -  outBlock :
* @inputs -  numInternalBlocks :
* @inputs -  numOutBlocks :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
static BAM_Status BAM_Image_whiteBalance_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,           /* generally unused in case of processing node */
    uint8_t      *numOutBlocks     /* generally unused in case of processing node */
)
{
    ISP_BAM_Image_whiteBalance_Args *args = (ISP_BAM_Image_whiteBalance_Args *)kernelArgs;

    internalBlock[PARAMS_IDX].size = 2*vcop_white_balance_BGGR_param_count();

    /*--------------------------------------------------------------------------------------------------*/
    /* Oputput pointer for Bayer data                                                                   */
    /* Here 16 is added for output block width because, actual input block width is                     */
	/* input_blk + horizotal padding size.(Minimum input block width is 16)            */
	/* This padding requires to add this 16(VCOP_2SIMD_WIDTH) for output line, and is independent of input block width  */

	/* 2 is added to block height because vertical padding is required for next module (Bayer2RGB)           */
	/* And is independent of input block height                                                         */
    /*--------------------------------------------------------------------------------------------------*/
    outBlock[0].size = ((args->blk_width +16)* (args->blk_height +2) * sizeof(short));

    return BAM_S_SUCCESS;
}

/* Comment out below function as we are passing NULL as pointer to the setmemRec function in structure BAM_KernelHelperFuncDef
 * BAM automatically copies the different input, output, internal block's pointers into the kernel's context, as well as the arguments.
 */
#if 0
/**
*******************************************************************************
* @fn        BAM_Image_whiteBalance_setMemRecFunc
* @brief    .
*
* @inputs -  internalBlock :
* @inputs -  inBlock :
* @inputs -  outBlock :
* @inputs -  numInternalBlocks :
* @inputs -  numInBlocks :
* @inputs -  numOutBlocks :
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
static BAM_Status BAM_Image_whiteBalance_setMemRecFunc
(
    const BAM_MemRec  *internalBlock[],
    const BAM_MemRec  *inBlock[],
    const BAM_MemRec  *outBlock[],
    uint8_t            numInternalBlocks,
    uint8_t            numInBlocks,
    uint8_t            numOutBlocks,
    void              *kernelContext,
    void              *kernelArgs
)
{
    ISP_BAM_Image_whiteBalance_Args *args = (ISP_BAM_Image_whiteBalance_Args *)kernelArgs;
    BAM_Image_whiteBalance_Context  *context = (BAM_Image_whiteBalance_Context *)kernelContext;

    if(numInternalBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
    }
    if(numInBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
    }
    if(numOutBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
    }

    context->kernelArgs= *args;

    context->pInBlock[0] = inBlock[0]->base;
    context->pOutBlock[0] = outBlock[0]->base;
    context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;

    return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_whiteBalanceKernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_whiteBalance_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_whiteBalance_Args),
    BAM_EVE, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    NUM_INTERNAL_BLOCKS       /*numInternalBlocks */
};

BAM_KernelHelperFuncDef gBAM_TI_whiteBalanceHelperFunc =
{
    &BAM_Image_whiteBalance_getMemRecFunc,
    NULL,/*(BAM_KernelSetMemRecFunc)&BAM_Image_whiteBalance_setMemRecFunc*/
};

