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
static BAM_Status BAM_Image_natcGammaCorrection_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
);


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
static BAM_Status BAM_Image_natcGammaCorrection_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   *internalBlock,
    BAM_MemRec   *outBlock,
    uint8_t      *numInternalBlocks,
    uint8_t      *numOutBlocks
)
{
    ISP_BAM_Image_gammaCorrection_Args *args = (ISP_BAM_Image_gammaCorrection_Args *)kernelArgs;

    internalBlock[PARAMS_IDX].size = 2;
    internalBlock[PARAMS_IDX].space= BAM_MEMSPACE_DMEM;

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


BAM_KernelInfo gBAM_TI_natcGammaCorrectionKernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_gammaCorrection_Context),/*kernelContextSize*/
    sizeof(ISP_BAM_Image_gammaCorrection_Args),
    BAM_EVE_ARP32, /*coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,                  /* 3 */
    NUM_OUT_BLOCKS,                 /* 3 */
    NUM_INTERNAL_BLOCKS             /* 5 */
};


BAM_KernelHelperFuncDef gBAM_TI_natcGammaCorrectionHelperFunc =
{
    &BAM_Image_natcGammaCorrection_getMemRecFunc,
    NULL
};

