/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_subSampling_exec_funcs.c
*
* @brief This file contains all kernel Exce functions for Bayer to RGB coversion
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "vcop_bayer_subsampling_kernel.h"
#include "bam_image_subSampling_helper_funcs.h"


/* Function Prototypes */
static BAM_Status BAM_Image_subSampling_initFrame(void *kernelContext);
/*static BAM_Status BAM_Image_subSampling_computeFrame(void *kernelContext);*/


/**
*******************************************************************************
* @fn        BAM_Image_subSampling_initFrame
* @brief     Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
static BAM_Status BAM_Image_subSampling_initFrame
(
    void *kernelContext
)
{
    BAM_Image_subSampling_Context *context = (BAM_Image_subSampling_Context *)kernelContext;

    bayer_subSampling_init((uint16_t *)context->pInBlock[0],
                           (uint16_t *)context->pOutBlock[0],
                           context->kernelArgs.blk_width,
                           context->kernelArgs.blk_height,
                           context->kernelArgs.input_stride,
                           context->kernelArgs.output_stride,
                           context->kernelArgs.subSample_X,
                           context->kernelArgs.subSample_Y,
                           context->kernelArgs.numOfSample,
                           (uint16_t *)context->pInternalBlock[PARAMS_IDX]
                          );

    return 0;
}


/**
*******************************************************************************
* @fn        BAM_Image_subSampling_Compute
* @brief    Function to call Vloop
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
/* No need to implement wrapper, the framework will call the vloop directly */
#if 0
static BAM_Status BAM_Image_subSampling_computeFrame
(
    void *kernelContext
)
{
    BAM_Image_subSampling_Context *context = (BAM_Image_subSampling_Context *)kernelContext;

    bayer_subSampling_vloops(context->pInternalBlock[PARAMS_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_subSamplingExecFunc =
{
    NULL,
    &BAM_Image_subSampling_initFrame,
    NULL,/*&BAM_Image_subSampling_computeFrame,*/
    NULL,
    NULL,
    (BAM_KernelCustom)&bayer_subSampling_vloops
};

