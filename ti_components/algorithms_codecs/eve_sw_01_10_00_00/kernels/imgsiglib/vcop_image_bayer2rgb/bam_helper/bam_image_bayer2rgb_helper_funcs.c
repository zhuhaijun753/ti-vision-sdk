/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       bam_image_bayer2rgb_helper_funcs.c
 *
 *  @brief      This file contains all kernel helper functions for Bayer to RGB coversion
 *  @author     Gajanan Ambi(gajanan.ambi@ti.com)
 *  @version    0.0 (November 2012) : Base version.
 */

/**
 ********************************************************************************
 * @file isp_bam_image_bayer2rgb_Helper_Funcs.c
 *
 * @brief This file contains all kernel helper functions for Bayer to RGB coversion
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 ********************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_image_bayer2rgb_helper_funcs.h"
#include "vcop_BayerCFA_interpolate_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Image_bayer2rgb_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t *numInternalBlocks,
    uint8_t *numOutBlocks
);
#if 0
static BAM_Status BAM_Image_bayer2rgb_setMemRecFunc
(
    const BAM_MemRec *internalBlock[],
    const BAM_MemRec *inBlock[],
    const BAM_MemRec *outBlock[],
    uint8_t numInternalBlocks,
    uint8_t numInBlocks,
    uint8_t numOutBlocks,
    void *kernelContext,
    void *kernelArgs
);
#endif
/**
 *******************************************************************************
 * @fn        BAM_Image_bayer2rgb_GetMemRecFunc
 * @brief    Function to allocate memory for Bayer to RGB conversion .
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
static BAM_Status BAM_Image_bayer2rgb_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t *numInternalBlocks,
    uint8_t *numOutBlocks
)
{
    ISP_BAM_Image_Bayer2rgb_Args *args = (ISP_BAM_Image_Bayer2rgb_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2 * vcop_BayerCFA_interpolate_short_BGGR_param_count();

    /*--------------------------------------------------------------------------------*/
    /* Oputput pointer for R component                                                */
	/* Minimum block width supported is VCOP_2SIMD_WIDTH, for padded pixel extraction */
	/* extra 16 memory locations are required. similarly 4 extra line are required    */
	/* at the block end to extract verticaly padded pixels.                           */
	/* These extra memory locations are required internaly and is independent of      */
	/* block width and height                                                         */
    /*--------------------------------------------------------------------------------*/
    outBlock[OUT_R_IDX].size = ((args->blk_width  + 16) * (args->blk_height + 2) * sizeof(short));

    /*--------------------------------------------------------------------------------*/
    /* Oputput pointer for G component                                                */
	/* Minimum block width supported is VCOP_2SIMD_WIDTH, for padded pixel extraction */
	/* extra 16 memory locations are required. similarly 4 extra line are required    */
	/* at the block end to extract verticaly padded pixels.                           */
	/* These extra memory locations are required internaly and is independent of      */
	/* block width and height                                                         */
    /*--------------------------------------------------------------------------------*/
    outBlock[OUT_G_IDX].size = ((args->blk_width + 16) * (args->blk_height + 2) * sizeof(short));

    /*--------------------------------------------------------------------------------*/
    /* Oputput pointer for B component                                                */
	/* Minimum block width supported is VCOP_2SIMD_WIDTH, for padded pixel extraction */
	/* extra 16 memory locations are required. similarly 4 extra line are required    */
	/* at the block end to extract verticaly padded pixels.                           */
	/* These extra memory locations are required internaly and is independent of      */
	/* block width and height                                                         */
    /*--------------------------------------------------------------------------------*/
    outBlock[OUT_B_IDX].size = ((args->blk_width + 16) * (args->blk_height + 2) * sizeof(short));

    return BAM_S_SUCCESS;
}

/* Comment out below function as we are passing NULL as pointer to the setmemRec function in structure BAM_KernelHelperFuncDef
 * BAM automatically copies the different input, output, internal block's pointers into the kernel's context, as well as the arguments.
 */
#if 0
/**
 *******************************************************************************
 * @fn        BAM_Image_bayer2rgb_SetMemRecFunc
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
static BAM_Status BAM_Image_bayer2rgb_setMemRecFunc
(
    const BAM_MemRec *internalBlock[],
    const BAM_MemRec *inBlock[],
    const BAM_MemRec *outBlock[],
    uint8_t numInternalBlocks,
    uint8_t numInBlocks,
    uint8_t numOutBlocks,
    void *kernelContext,
    void *kernelArgs
)
{
    ISP_BAM_Image_Bayer2rgb_Args *args = (ISP_BAM_Image_Bayer2rgb_Args *) kernelArgs;
    BAM_Image_bayer2rgb_Context *context = (BAM_Image_bayer2rgb_Context *) kernelContext;

    if (numInternalBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
    }
    if (numInBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
    }
    if (numOutBlocks != 3)
    {
        PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
    }

    context->kernelArgs= *args;

    context->pInBlock[IN_IDX] = inBlock[IN_IDX]->base;
    context->pOutBlock[OUT_R_IDX]  = outBlock[OUT_R_IDX]->base;
    context->pOutBlock[OUT_G_IDX]  = outBlock[OUT_G_IDX]->base;
    context->pOutBlock[OUT_B_IDX]  = outBlock[OUT_B_IDX]->base;
    context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;

    return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_bayer2rgbKernel =
{
    0, /*kernelId */
    sizeof(BAM_Image_bayer2rgb_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_Bayer2rgb_Args),
    BAM_EVE, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS, /*1*/
    NUM_OUT_BLOCKS, /*3 */
    NUM_INTERNAL_BLOCKS /*1 */
};

BAM_KernelHelperFuncDef gBAM_TI_bayer2rgbHelperFunc =
{
    &BAM_Image_bayer2rgb_getMemRecFunc,
    NULL/*(BAM_KernelSetMemRecFunc)&BAM_Image_bayer2rgb_setMemRecFunc*/
};

