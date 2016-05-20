/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_rgb2yuv_helper_funcs.c
 *
 *  @brief      This file defines functions for integrating rgb2yuv kernels into BAM
 */

/**
 ********************************************************************************
 * @file isp_bam_image_rgb2yuv_Helper_Funcs.c
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
#include "bam_image_rgb2yuv_helper_funcs.h"
#include "vcop_rgb_to_yuv_kernel.h" /* makerules should take care of include path */


/* Function Prototypes */
static BAM_Status BAM_Image_rgb2yuv_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t *numInternalBlocks,
    uint8_t *numOutBlocks
);

#if 0
static BAM_Status BAM_Image_rgb2yuv_setMemRecFunc
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
 * @fn        BAM_Image_rgb2yuv_GetMemRecFunc
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
static BAM_Status BAM_Image_rgb2yuv_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t *numInternalBlocks,
    uint8_t *numOutBlocks
)
{
    ISP_BAM_Image_rgb2yuv_Args *args = (ISP_BAM_Image_rgb2yuv_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2 * rgb_to_yuv_UYVY_param_count();

    internalBlock[COEFS_IDX].size = sizeof(short)*25; /* 25 - size of coef table*/

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for yuv output                                           */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_YUV_IDX].size = 2 * ((args->blk_width) * (args->blk_height));

    return 0;
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
static BAM_Status BAM_Image_rgb2yuv_setMemRecFunc
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
    BAM_Image_rgb2yuv_Context *context = (BAM_Image_rgb2yuv_Context *) kernelContext;
    ISP_BAM_Image_rgb2yuv_Args *args = (ISP_BAM_Image_rgb2yuv_Args *) kernelArgs;

    if (numInternalBlocks != 2)
    {
        PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
    }
    if (numInBlocks != 3)
    {
        PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
    }
    if (numOutBlocks != 1)
    {
        PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
    }

    context->kernelArgs= *args;

    context->pInBlock[IN_R_IDX]  = inBlock[IN_R_IDX]->base;
    context->pInBlock[IN_G_IDX]  = inBlock[IN_G_IDX]->base;
    context->pInBlock[IN_B_IDX]  = inBlock[IN_B_IDX]->base;
    context->pOutBlock[OUT_YUV_IDX] = outBlock[OUT_YUV_IDX]->base;

    context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;
    context->pInternalBlock[COEFS_IDX] = internalBlock[COEFS_IDX]->base;


    return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_rgb2yuvKernel =
{
    0, /*kernelId */
    sizeof(BAM_Image_rgb2yuv_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_rgb2yuv_Args),
    BAM_EVE, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,          /*3*/
    NUM_OUT_BLOCKS,         /*1 */
    NUM_INTERNAL_BLOCKS     /*2 */
};

BAM_KernelHelperFuncDef gBAM_TI_rgb2yuvHelperFunc =
{
    &BAM_Image_rgb2yuv_getMemRecFunc,
    NULL /*(BAM_KernelSetMemRecFunc)&BAM_Image_rgb2yuv_setMemRecFunc*/
};
