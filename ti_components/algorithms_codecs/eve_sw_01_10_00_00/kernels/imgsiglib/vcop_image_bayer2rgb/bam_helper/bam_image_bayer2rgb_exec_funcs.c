/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 * @file isp_bam_image_bayer2rgb_Exec_Funcs.c
 *
 * @brief This file contains all kernel Exce functions for Bayer to RGB coversion
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 * @version 0.0 (November 2012) : Base version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "vcop_BayerCFA_interpolate_kernel.h"
#include "bam_image_bayer2rgb_helper_funcs.h"

/* Function Prototypes */
static BAM_Status BAM_Image_bayer2rgb_initFrame(void *kernelContext);
static BAM_Status BAM_Image_bayer2rgb_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_bayer2rgb_initFrame
 * @brief    Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_bayer2rgb_initFrame(void *kernelContext)
{
    BAM_Image_bayer2rgb_Context *context = (BAM_Image_bayer2rgb_Context *) kernelContext;

    if(context->kernelArgs.bayerFormat == BGGR)
    {
        vcop_BayerCFA_interpolate_short_BGGR_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == GBRG)
    {
        vcop_BayerCFA_interpolate_short_GBRG_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == GRBG)
    {
        vcop_BayerCFA_interpolate_short_GRBG_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == RGGB)
    {
        vcop_BayerCFA_interpolate_short_RGGB_init((uint16_t *)context->pInBlock[IN_IDX],
                context->kernelArgs.input_stride,
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                (uint16_t *)context->pOutBlock[OUT_R_IDX],
                (uint16_t *)context->pOutBlock[OUT_G_IDX],
                (uint16_t *)context->pOutBlock[OUT_B_IDX],
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else
    {
    }

    return 0;
}

/**
 *******************************************************************************
 * @fn        BAM_Image_bayer2rgb_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_bayer2rgb_computeFrame(void *kernelContext)
{
    BAM_Image_bayer2rgb_Context *context = (BAM_Image_bayer2rgb_Context *) kernelContext;

    if(context->kernelArgs.bayerFormat == BGGR)
    {
        vcop_BayerCFA_interpolate_short_BGGR_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == GBRG)
    {
        vcop_BayerCFA_interpolate_short_GBRG_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == GRBG)
    {
        vcop_BayerCFA_interpolate_short_GRBG_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == RGGB)
    {
        vcop_BayerCFA_interpolate_short_RGGB_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
    }

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_bayer2rgbExecFunc =
{
        NULL,
        &BAM_Image_bayer2rgb_initFrame,
        &BAM_Image_bayer2rgb_computeFrame,
        NULL,
        NULL,
        NULL
};

