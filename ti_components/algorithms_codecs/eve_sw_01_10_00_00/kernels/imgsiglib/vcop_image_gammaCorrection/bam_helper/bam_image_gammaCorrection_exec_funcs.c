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

#include "vcop_gamma_correction_kernel.h"
#include "bam_image_gammaCorrection_helper_funcs.h"
#include "edma_utils_memcpy.h"

/* Function Prototypes */
static BAM_Status BAM_Image_gammaCorrection_initFrame(void *kernelContext);
/* static BAM_Status BAM_Image_gammaCorrection_computeFrame(void *kernelContext); */

/**
 *******************************************************************************
 * @fn        BAM_Image_rgb2srgb_InitFrame
 * @brief    Function called during graph's instance initialization
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_gammaCorrection_initFrame
(
        void *kernelContext
)
{
    BAM_Image_gammaCorrection_Context *context = (BAM_Image_gammaCorrection_Context *)kernelContext;

    /* Sometimes memcpy is faster if number of bytes to transfer is small */
#if 0
    memcpy(context->pInternalBlock[LUT_IDX], context->kernelArgs.pLUT, 1024*4*sizeof(short));
#else
    EDMA_UTILS_memcpy2D(context->pInternalBlock[LUT_IDX], context->kernelArgs.pLUT, 1024*4*sizeof(short),
        1,0,0);
#endif

    gamma_correction_init((uint16_t *)context->pInBlock[IN_R_IDX],
            (uint16_t *)context->pInBlock[IN_G_IDX],
            (uint16_t *)context->pInBlock[IN_B_IDX],
            (uint16_t *)context->pOutBlock[OUT_R_IDX],
            (uint16_t *)context->pOutBlock[OUT_G_IDX],
            (uint16_t *)context->pOutBlock[OUT_B_IDX],
            context->kernelArgs.blk_width,
            context->kernelArgs.blk_height,
            context->kernelArgs.input_stride,
            context->kernelArgs.output_stride,
            (uint16_t *)context->pInternalBlock[TEMP_R_IDX],
            (uint16_t *)context->pInternalBlock[TEMP_G_IDX],
            (uint16_t *)context->pInternalBlock[TEMP_B_IDX],
            (uint16_t *)context->pInternalBlock[LUT_IDX],
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
static uint32_t BAM_Image_gammaCorrection_computeFrame
(
        void *kernelContext
)
{
    BAM_Image_gammaCorrection_Context *context = (BAM_Image_gammaCorrection_Context *)kernelContext;

    gamma_correction_vloops(context->pInternalBlock[PARAMS_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_gammaCorrectionExecFunc =
{
        NULL,
        &BAM_Image_gammaCorrection_initFrame,
        NULL,/*&BAM_Image_gammaCorrection_computeFrame,*/
        NULL,
        NULL,
        (BAM_KernelCustom)&gamma_correction_vloops
};

