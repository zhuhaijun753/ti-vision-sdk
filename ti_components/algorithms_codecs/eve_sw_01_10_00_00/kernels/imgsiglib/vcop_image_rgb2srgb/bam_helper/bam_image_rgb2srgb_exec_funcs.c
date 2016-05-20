/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 * @file bam_image_rgb2srgb_exec_funcs.c
 *
 * @brief This file contains all kernel Exce functions for RGB to sRGB coversion
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "vcop_rgb_srgb_kernel.h"
#include "bam_image_rgb2srgb_helper_funcs.h"
#include "edma_utils_memcpy.h"


/* Function Prototypes */
static BAM_Status BAM_Image_rgb2srgb_initFrame(void *kernelContext);
/*static BAM_Status BAM_Image_rgb2srgb_computeFrame(void *kernelContext);*/

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2srgb_initFrame
 * @brief    Function called during graph's instance initialization
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_rgb2srgb_initFrame(void *kernelContext)
{

    BAM_Image_rgb2srgb_Context *context = (BAM_Image_rgb2srgb_Context *) kernelContext;
    /* Sometimes memcpy is faster if number of bytes to transfer is small */
#if 0
    memcpy(context->pInternalBlock[COEFS_IDX], context->kernelArgs.rgb2srgb_coefs, sizeof(short)*25);
#else
    EDMA_UTILS_memcpy2D(context->pInternalBlock[COEFS_IDX], context->kernelArgs.rgb2srgb_coefs, sizeof(short)*25,
        1,0,0);

#endif

    rgb_to_srgb_init((uint16_t *)context->pInBlock[IN_R_IDX],
            (uint16_t *)context->pInBlock[IN_G_IDX],
            (uint16_t *)context->pInBlock[IN_B_IDX],
            (uint16_t *)context->pOutBlock[OUT_R_IDX],
            (uint16_t *)context->pOutBlock[OUT_G_IDX],
            (uint16_t *)context->pOutBlock[OUT_B_IDX],
            context->kernelArgs.blk_width,
            context->kernelArgs.blk_height,
            context->kernelArgs.input_stride,
            context->kernelArgs.output_stride,
            (int16_t *)context->pInternalBlock[COEFS_IDX],
            (uint16_t *)context->pInternalBlock[PARAMS_IDX]
    );

    return 0;
}


/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2srgb_Compute
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
static uint32_t BAM_Image_rgb2srgb_computeFrame
(
        void *kernelContext
)
{
    BAM_Image_rgb2srgb_Context *context = (BAM_Image_rgb2srgb_Context *)kernelContext;

    rgb_to_srgb_vloops(context->pInternalBlock[PARAMS_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_rgb2srgbExecFunc =
{
        NULL,
        &BAM_Image_rgb2srgb_initFrame,
        NULL,/*&BAM_Image_rgb2srgb_computeFrame,*/
        NULL,
        NULL,
        (BAM_KernelCustom)&rgb_to_srgb_vloops
};

