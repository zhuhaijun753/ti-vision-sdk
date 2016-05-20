/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 * @file bam_image_whiteBalance_exec_funcs.c
 *
 * @brief This file contains all kernel Exce functions for the natural C version of white Balance
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../src_C/vcop_bayer_white_balance_cn.h"
#include "vcop_white_balance_kernel.h"
#include "bam_image_whiteBalance_helper_funcs.h"


/* Function Prototypes */
static BAM_Status BAM_Image_natcWhiteBalance_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_whiteBalance_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_natcWhiteBalance_computeFrame
(
        void *kernelContext
)
{
    BAM_Image_whiteBalance_Context *context = (BAM_Image_whiteBalance_Context *)kernelContext;

    natc_bayer_white_balance
    (
            (unsigned short*)context->pInBlock[0],
            (unsigned short*)context->pOutBlock[0],
            context->kernelArgs.blk_width,
            context->kernelArgs.blk_height,
            context->kernelArgs.gain_factor_R,
            context->kernelArgs.gain_factor_Gr,
            context->kernelArgs.gain_factor_Gb,
            context->kernelArgs.gain_factor_B,
            context->kernelArgs.shift_val,
            context->kernelArgs.input_stride,
            context->kernelArgs.output_stride,
            context->kernelArgs.bayerFormat
    );

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_natcWhiteBalanceExecFunc =
{
        NULL,
        NULL,
        &BAM_Image_natcWhiteBalance_computeFrame,
        NULL,
        NULL,
        NULL
};

