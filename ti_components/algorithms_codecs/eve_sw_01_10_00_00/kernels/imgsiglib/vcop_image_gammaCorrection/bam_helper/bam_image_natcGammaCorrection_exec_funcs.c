/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 * @file bam_image_gammaCorrection_exec_funcs.c
 *
 * @brief This file contains all kernel Exec functions for gamma correction
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../src_C/vcop_gammaCorrection_cn.h"
#include "vcop_gamma_correction_kernel.h"
#include "bam_image_gammaCorrection_helper_funcs.h"
#include "edma_utils_memcpy.h"

/* Function Prototypes */
static BAM_Status BAM_Image_natcGammaCorrection_initFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2srgb_InitInstance
 * @brief    Function called during graph's instance initialization
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_natcGammaCorrection_initFrame
(
        void *kernelContext
)
{
    BAM_Image_gammaCorrection_Context *context = (BAM_Image_gammaCorrection_Context *)kernelContext;

    EDMA_UTILS_memcpy2D(context->pInternalBlock[LUT_IDX], context->kernelArgs.pLUT, 1024*4*sizeof(short),
            1,0,0);
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
#if 1
static BAM_Status BAM_Image_natcGammaCorrection_computeFrame
(
        void *kernelContext
)
{
    BAM_Image_gammaCorrection_Context *context = (BAM_Image_gammaCorrection_Context *)kernelContext;

    natc_gamma_correction
    (
            (uint16_t *)context->pInBlock[IN_R_IDX],
            (uint16_t *)context->pInBlock[IN_G_IDX],
            (uint16_t *)context->pInBlock[IN_B_IDX],
            (uint16_t *)context->pOutBlock[OUT_R_IDX],
            (uint16_t *)context->pOutBlock[OUT_G_IDX],
            (uint16_t *)context->pOutBlock[OUT_B_IDX],
            context->kernelArgs.blk_width,
            context->kernelArgs.blk_height,
            context->kernelArgs.input_stride,
            context->kernelArgs.output_stride,
            (int16_t *)context->pInternalBlock[LUT_IDX]
    );

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_natcGammaCorrectionExecFunc =
{
        NULL,
        &BAM_Image_natcGammaCorrection_initFrame,
        &BAM_Image_natcGammaCorrection_computeFrame,
        NULL,
        NULL,
        NULL
};

