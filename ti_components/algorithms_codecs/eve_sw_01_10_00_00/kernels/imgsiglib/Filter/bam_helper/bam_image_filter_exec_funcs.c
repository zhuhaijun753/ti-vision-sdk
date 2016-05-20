/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 ********************************************************************************
 * @file:       bam_image_filter_exec_funcs.c
 *
 * @brief:     This file contains all kernel Exce functions for Bayer to RGB coversion
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
#include "vcop_filter_kernel.h" //makerules should take care of include path

/* Function Prototypes */
static BAM_Status BAM_Image_filter_initFrame(void *kernelContext);
static BAM_Status BAM_Image_filter_computeFrame(void *kernelContext);

/**
 *******************************************************************************
 * @fn        BAM_Image_filter_initFrame
 * @brief     Function for Vloop init
 *
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_filter_initFrame(void *kernelContext)
{
    BAM_Image_filter_Context *context = (BAM_Image_filter_Context *)kernelContext;
/*This is temporary fix for build. This BAM helper doesnt support host emulation */    
#if !VCOP_HOST_EMULATION
    if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == CHAR_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_uchar_char_char_init((unsigned char*)context->pInBlock[0],
                (char*)context->pInternalBlock[COEFFS_IDX],
                (char*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_uchar_char_short_init((unsigned char*)context->pInBlock[0],
                (char*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_ushort_short_short_init((unsigned short*)context->pInBlock[0],
                (short*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == SHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_short_short_short_init((short*)context->pInBlock[0],
                (short*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == USHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_ushort_ushort_short_init((unsigned short*)context->pInBlock[0],
                (unsigned short*)context->pInternalBlock[COEFFS_IDX],
                (short*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == INT_TYPE)
    )
    {
        memcpy(context->pInternalBlock[COEFFS_IDX], context->kernelArgs.filter_coefs, 2*context->kernelArgs.coeff_blk_width*context->kernelArgs.coeff_blk_height);
        vcop_filter_ushort_short_int_init((unsigned short*)context->pInBlock[0],
                (short*)context->pInternalBlock[COEFFS_IDX],
                (int*)context->pOutBlock[0],
                context->kernelArgs.input_blk_width,
                context->kernelArgs.coeff_blk_width,
                context->kernelArgs.coeff_blk_height,
                context->kernelArgs.compute_blk_width,
                context->kernelArgs.compute_blk_height,
                context->kernelArgs.dnSmple_vert,
                context->kernelArgs.dnSmple_horz,
                context->kernelArgs.rnd_shift,
                (uint16_t *)context->pInternalBlock[PARAMS_IDX]
        );
    }
    else
    {
    }
#endif
    return 0;
}

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
static BAM_Status BAM_Image_filter_computeFrame(void *kernelContext)
{
    BAM_Image_filter_Context *context = (BAM_Image_filter_Context *) kernelContext;
/*This is temporary fix for build. This BAM helper doesnt support host emulation */       
#if !VCOP_HOST_EMULATION
    if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == CHAR_TYPE)
    )
    {
        vcop_filter_uchar_char_char_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == UCHAR_TYPE) &&
            (context->kernelArgs.coeff_type  == CHAR_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_uchar_char_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_ushort_short_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == SHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_short_short_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == USHORT_TYPE) &&
            (context->kernelArgs.output_type == SHORT_TYPE)
    )
    {
        vcop_filter_ushort_ushort_short_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else if((context->kernelArgs.input_type  == USHORT_TYPE) &&
            (context->kernelArgs.coeff_type  == SHORT_TYPE) &&
            (context->kernelArgs.output_type == INT_TYPE)
    )
    {
        vcop_filter_ushort_short_int_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
    else
    {
    }
#endif    
    return 0;
}


BAM_KernelExecFuncDef gBAM_TI_filterExecFunc =
{
        NULL,
        &BAM_Image_filter_initFrame,
        &BAM_Image_filter_computeFrame,
        NULL,
        NULL,
        NULL
};

