/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_gammaCorrection_helper_funcs.c
*
* @brief This file contains all kernel helper functions for Gamma Correction
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include <vcop.h>
#include "evealgframework.h"
#include "bam_image_gammaCorrection_helper_funcs.h"
#include "vcop_gamma_correction_kernel.h"


/* Function Prototypes */
static BAM_Status BAM_Image_gammaCorrection_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
);

#if 0
static BAM_Status BAM_Image_gammaCorrection_setMemRecFunc
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
* @fn        BAM_Image_rgb2srgb_GetMemRecFunc
* @brief    Function to allocate memory for RGB to sRGB conversion .
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
static BAM_Status BAM_Image_gammaCorrection_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
)
{
    ISP_BAM_Image_gammaCorrection_Args *args = (ISP_BAM_Image_gammaCorrection_Args *)kernelArgs;

    internalBlock[PARAMS_IDX].size = 2*gamma_correction_param_count();

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for R component                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_R_IDX].size = (args->blk_width* args->blk_height *sizeof(short));

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for G component                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_G_IDX].size = (args->blk_width* args->blk_height *sizeof(short));

    /*--------------------------------------------------------------------------*/
    /* Oputput pointer for B component                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[OUT_B_IDX].size = (args->blk_width* args->blk_height *sizeof(short));

    /*--------------------------------------------------------------------------*/
    /* Temp oputput pointer for R component                                     */
    /*--------------------------------------------------------------------------*/
    internalBlock[TEMP_R_IDX].size = (args->blk_width* args->blk_height *sizeof(short));
    internalBlock[TEMP_R_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /*--------------------------------------------------------------------------*/
    /* Temp oputput pointer for G component                                     */
    /*--------------------------------------------------------------------------*/
    internalBlock[TEMP_G_IDX].size = (args->blk_width* args->blk_height *sizeof(short));
    internalBlock[TEMP_G_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /*--------------------------------------------------------------------------*/
    /* Temp oputput pointer for G component                                     */
    /*--------------------------------------------------------------------------*/
    internalBlock[TEMP_B_IDX].size = (args->blk_width* args->blk_height *sizeof(short));
    internalBlock[TEMP_B_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    /*--------------------------------------------------------------------------*/
    /* LUT pointer                                                              */
    /*--------------------------------------------------------------------------*/
    /*1024 - size of LUT table and 4 is table replication number             */
    internalBlock[LUT_IDX].size = 1024*4*sizeof(short); /* TODO : Need to use this pointer for LUT*/

    return BAM_S_SUCCESS;
}

/* Comment out below function as we are passing NULL as pointer to the setmemRec function in structure BAM_KernelHelperFuncDef
 * BAM automatically copies the different input, output, internal block's pointers into the kernel's context, as well as the arguments.
 */
#if 0

/**
*******************************************************************************
* @fn        BAM_Image_gammaCorrection_setMemRecFunc
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
static BAM_Status BAM_Image_gammaCorrection_setMemRecFunc
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
    ISP_BAM_Image_gammaCorrection_Args *args = (ISP_BAM_Image_gammaCorrection_Args *)kernelArgs;
    BAM_Image_gammaCorrection_Context  *context = (BAM_Image_gammaCorrection_Context *)kernelContext;

    if(numInternalBlocks != 5)
    {
        PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
    }
    if(numInBlocks != 3)
    {
        PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
    }
    if(numOutBlocks != 3)
    {
        PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
    }

    context->kernelArgs= *args;

    context->pInBlock[IN_R_IDX]  = inBlock[IN_R_IDX]->base;
    context->pInBlock[IN_G_IDX]  = inBlock[IN_G_IDX]->base;
    context->pInBlock[IN_B_IDX]  = inBlock[IN_B_IDX]->base;
    context->pOutBlock[OUT_R_IDX] = outBlock[OUT_R_IDX]->base;
    context->pOutBlock[OUT_G_IDX] = outBlock[OUT_G_IDX]->base;
    context->pOutBlock[OUT_B_IDX] = outBlock[OUT_B_IDX]->base;

    context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;
    context->pInternalBlock[TEMP_R_IDX] = internalBlock[TEMP_R_IDX]->base;
    context->pInternalBlock[TEMP_G_IDX] = internalBlock[TEMP_G_IDX]->base;
    context->pInternalBlock[TEMP_B_IDX] = internalBlock[TEMP_B_IDX]->base;
    context->pInternalBlock[LUT_IDX]    = internalBlock[LUT_IDX]->base;

    return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_gammaCorrectionKernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_gammaCorrection_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_gammaCorrection_Args),
    BAM_EVE, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,                  /* 3 */
    NUM_OUT_BLOCKS,                 /* 3 */
    NUM_INTERNAL_BLOCKS             /* 5 */
};


BAM_KernelHelperFuncDef gBAM_TI_gammaCorrectionHelperFunc =
{
    &BAM_Image_gammaCorrection_getMemRecFunc,
    NULL/*(BAM_KernelSetMemRecFunc)&BAM_Image_gammaCorrection_setMemRecFunc*/
};

