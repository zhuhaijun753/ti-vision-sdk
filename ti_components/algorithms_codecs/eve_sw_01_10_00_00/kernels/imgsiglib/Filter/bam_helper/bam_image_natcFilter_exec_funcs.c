/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 ********************************************************************************
 * @file:       bam_image_natcFilter_exec_funcs.c
 *
 * @brief:     This file contains all kernel Exce functions for the natural C version of the filter kernek
 *
 * @author:  Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version:  0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_image_filter_helper_funcs.h"
#include "../inc/vcop_filter_cn.h"

/* Function Prototypes */
static BAM_Status BAM_Image_natcFilter_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn:        BAM_Image_filter_Compute
 * @brief      Function to call Vloop
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_natcFilter_computeFrame(void *kernelContext)
{
    BAM_Image_filter_Context *context = (BAM_Image_filter_Context *)kernelContext;

    if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == CHAR_TYPE)
    )
    {
        filter_uchar_cn((unsigned char*)context->pInBlock[0],
                (char*)context->kernelArgs.filter_coefs,
                (unsigned char*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                0,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_uchar_cn((unsigned char*)context->pInBlock[0],
                (char*)context->kernelArgs.filter_coefs,
                (unsigned char*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == SHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == USHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == INT_TYPE)
    )
    {
        filter_cn((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->kernelArgs.filter_coefs,
                (unsigned short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                1,
                context->kernelArgs.rnd_shift
        );
    }
    else
    {
    }

    return 0;
}


BAM_KernelExecFuncDef gBAM_TI_natcFilterExecFunc =
{
        NULL,
        NULL,
        &BAM_Image_natcFilter_computeFrame,
        NULL,
        NULL,
        NULL
};

