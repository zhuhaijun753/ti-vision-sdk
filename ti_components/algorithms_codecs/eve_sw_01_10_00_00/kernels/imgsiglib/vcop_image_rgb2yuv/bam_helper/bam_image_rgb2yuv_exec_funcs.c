/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_rgb2yuv_exec_funcs.c
 *
 *  @brief      This file defines functions for integrating rgb2yuv kernels into BAM
 */

/**
 ********************************************************************************
 * @file isp_bam_image_rgb2yuv_Exec_Funcs.c
 *
 * @brief This file contains all kernel Exce functions for Bayer to RGB coversion
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 ********************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_image_rgb2yuv_helper_funcs.h"
#include "vcop_rgb_to_yuv_kernel.h" /* makerules should take care of include path */
#include "edma_utils_memcpy.h"


/* Function Prototypes */
static BAM_Status BAM_Image_rgb2yuv_initFrame(void *kernelContext);
static BAM_Status BAM_Image_rgb2yuv_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2yuv_initFrame
 * @brief    Function called during graph's instance initialization
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_rgb2yuv_initFrame(void *kernelContext)
{

    BAM_Image_rgb2yuv_Context *context = (BAM_Image_rgb2yuv_Context *) kernelContext;
    int16_t *coef= (int16_t*)(context->pInternalBlock[COEFS_IDX]);

    /* Sometimes memcpy is faster if number of bytes to transfer is small */
#if 0
    memcpy(context->pInternalBlock[COEFS_IDX], context->kernelArgs.rgb2yuv_coefs, sizeof(short)*25);
#else
    EDMA_UTILS_memcpy2D(context->pInternalBlock[COEFS_IDX], context->kernelArgs.rgb2yuv_coefs, sizeof(short)*25,
        1,0,0);
#endif



    if(context->kernelArgs.outputFormat == RGB2YUV_OUTPUT_UYVY)
    {
        rgb_to_yuv_UYVY_init((uint16_t *)context->pInBlock[IN_R_IDX],
                (uint16_t *)context->pInBlock[IN_G_IDX],
                (uint16_t *)context->pInBlock[IN_B_IDX],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.input_stride,
                coef[0],
                coef[1],
                coef[2],
                (int16_t *)coef,
                context->kernelArgs.roundingFactor,
                context->kernelArgs.shift_val,
                (uint8_t *)context->pOutBlock[OUT_YUV_IDX],
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else
    {
        rgb_to_yuv_YUYV_init((uint16_t *)context->pInBlock[IN_R_IDX],
                (uint16_t *)context->pInBlock[IN_G_IDX],
                (uint16_t *)context->pInBlock[IN_B_IDX],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.input_stride,
                coef[0],
                coef[1],
                coef[2],
                (int16_t *)coef,
                context->kernelArgs.roundingFactor,
                context->kernelArgs.shift_val,
                (uint8_t *)context->pOutBlock[OUT_YUV_IDX],
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );

    }

    return 0;
}

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2yuv_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_rgb2yuv_computeFrame(void *kernelContext)
{
    BAM_Image_rgb2yuv_Context *context = (BAM_Image_rgb2yuv_Context *) kernelContext;

    if(context->kernelArgs.outputFormat == RGB2YUV_OUTPUT_UYVY)
    {
        rgb_to_yuv_UYVY_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
        rgb_to_yuv_YUYV_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_rgb2yuvExecFunc =
{
        NULL,
        &BAM_Image_rgb2yuv_initFrame,
        &BAM_Image_rgb2yuv_computeFrame,
        NULL,
        NULL,
        NULL
};

