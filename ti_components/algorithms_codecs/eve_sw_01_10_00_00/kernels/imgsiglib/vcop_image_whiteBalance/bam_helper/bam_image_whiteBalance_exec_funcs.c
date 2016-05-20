/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 * @file bam_image_whiteBalance_exec_funcs.c
 *
 * @brief This file contains all kernel Exce functions for white Balance
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "vcop_white_balance_kernel.h"
#include "bam_image_whiteBalance_helper_funcs.h"


/* Function Prototypes */
static BAM_Status BAM_Image_whiteBalance_initFrame(void *kernelContext);
static BAM_Status BAM_Image_whiteBalance_computeFrame(void *kernelContext);


/**
 *******************************************************************************
 * @fn        BAM_Image_whiteBalance_initFrame
 * @brief    Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_whiteBalance_initFrame
(
        void *kernelContext
)
{
    BAM_Image_whiteBalance_Context *context = (BAM_Image_whiteBalance_Context *)kernelContext;

    if(context->kernelArgs.bayerFormat == BGGR)
    {
        vcop_white_balance_BGGR_init((uint16_t *)context->pInBlock[0],
                (uint16_t *)context->pOutBlock[0],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.gain_factor_R,
                context->kernelArgs.gain_factor_Gr,
                context->kernelArgs.gain_factor_Gb,
                context->kernelArgs.gain_factor_B,
                context->kernelArgs.shift_val,
                context->kernelArgs.input_stride,
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == GBRG)
    {
        vcop_white_balance_GBRG_init((uint16_t *)context->pInBlock[0],
                (uint16_t *)context->pOutBlock[0],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.gain_factor_R,
                context->kernelArgs.gain_factor_Gr,
                context->kernelArgs.gain_factor_Gb,
                context->kernelArgs.gain_factor_B,
                context->kernelArgs.shift_val,
                context->kernelArgs.input_stride,
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == GRBG)
    {
        vcop_white_balance_GRBG_init((uint16_t *)context->pInBlock[0],
                (uint16_t *)context->pOutBlock[0],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.gain_factor_R,
                context->kernelArgs.gain_factor_Gr,
                context->kernelArgs.gain_factor_Gb,
                context->kernelArgs.gain_factor_B,
                context->kernelArgs.shift_val,
                context->kernelArgs.input_stride,
                context->kernelArgs.output_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if(context->kernelArgs.bayerFormat == RGGB)
    {
        vcop_white_balance_RGGB_init((uint16_t *)context->pInBlock[0],
                (uint16_t *)context->pOutBlock[0],
                context->kernelArgs.blk_width,
                context->kernelArgs.blk_height,
                context->kernelArgs.gain_factor_R,
                context->kernelArgs.gain_factor_Gr,
                context->kernelArgs.gain_factor_Gb,
                context->kernelArgs.gain_factor_B,
                context->kernelArgs.shift_val,
                context->kernelArgs.input_stride,
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
 * @fn        BAM_Image_whiteBalance_Compute
 * @brief    Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_whiteBalance_computeFrame
(
        void *kernelContext
)
{
    BAM_Image_whiteBalance_Context *context = (BAM_Image_whiteBalance_Context *)kernelContext;

    if(context->kernelArgs.bayerFormat == BGGR)
    {
        vcop_white_balance_BGGR_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == GBRG)
    {
        vcop_white_balance_GBRG_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == GRBG)
    {
        vcop_white_balance_GRBG_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else if(context->kernelArgs.bayerFormat == RGGB)
    {
        vcop_white_balance_RGGB_vloops((uint16_t *)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
    }

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_whiteBalanceExecFunc =
{
        NULL,
        &BAM_Image_whiteBalance_initFrame,
        &BAM_Image_whiteBalance_computeFrame,
        NULL,
        NULL,
        NULL
};

