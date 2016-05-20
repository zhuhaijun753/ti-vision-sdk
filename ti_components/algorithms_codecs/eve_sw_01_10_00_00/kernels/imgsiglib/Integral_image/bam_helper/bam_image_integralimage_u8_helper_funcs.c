/*
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
* @file bam_image_integraiImage_u8_helper_funcs.c
*
* @brief This file contains all kernel helper functions for Gamma Correction
*
* @author Kumar Desappan(kumar.desappan@ti.com)
*
* @version 0.0 (Jul 2013) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_image_integralimage_u8_helper_funcs.h"
#include "eve_integral_image_kernel.h"

BAM_Status BAM_Image_integralImage_u8_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);

/**
*******************************************************************************
* @fn        BAM_Image_integralImage_u8_getMemRecFunc
* @brief    Function to allocate memory for RGB to sRGB conversion .
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  memRecInternal :
* @inputs -  memRecOutputDataBlock :
* @inputs -  numRecInternal :
* @inputs -  numRecOutputDataBlock :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_Image_integralImage_u8_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{

#if (!VCOP_HOST_EMULATION)
    const BAM_Image_integralImage_u8_Args *args = kernelArgs;
    memRecInternal[PARAMS_IDX].size = 2u*eve_integral_image_u8_int_int_param_count();
    memRecInternal[PARAMS_RESET_ACCV_IDX].size = 2u*eve_integral_image_reset_accv_param_count();
#else
    const BAM_Image_integralImage_u8_Args *args = (const BAM_Image_integralImage_u8_Args *)kernelArgs;
    memRecInternal[PARAMS_IDX].size = 16;
    memRecInternal[PARAMS_RESET_ACCV_IDX].size = 16;
#endif

    memRecInternal[SCRATCH_VER_ACC_IDX].size =  sizeof(int32_t)*  args->blk_height;
    
    memRecInternal[SCRATCH_B0_IDX].size = sizeof(int32_t)*  (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_B0_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_B0_IDX].space = BAM_MEMSPACE_WBUF;
    
    memRecInternal[SCRATCH_B1_IDX].size = sizeof(int32_t)*  (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_B1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_B1_IDX].space = BAM_MEMSPACE_WBUF;
    
    memRecInternal[SCRATCH_C0_IDX].size = sizeof(int32_t)*  (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_C0_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_C0_IDX].space = BAM_MEMSPACE_ANY_VCOPBUF;
    
    memRecInternal[SCRATCH_C1_IDX].size = sizeof(int32_t)* (args->blk_width/16)*9*args->blk_height;
    memRecInternal[SCRATCH_C1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[SCRATCH_C1_IDX].space = BAM_MEMSPACE_ANY_VCOPBUF;
    
    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[OUT_INTG_IMG_IDX].size = sizeof(int32_t) * ( args->blk_width * args->blk_height );
    memRecOutputDataBlock[OUT_INTG_IMG_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[OUT_INTG_IMG_IDX].space = BAM_MEMSPACE_IBUFHA;

    memRecOutputDataBlock[OUT_HOR_ACC_IDX].size = sizeof(int32_t) * args->blk_width;
    memRecOutputDataBlock[OUT_HOR_ACC_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[OUT_HOR_ACC_IDX].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_integralImage_u8Kernel =
{
    0,  /*kernelId */
    sizeof(BAM_Image_integralImage_u8_Context),/*kernelContextSize*/
    sizeof(BAM_Image_integralImage_u8_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE, /*nodeType */
    NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_integralImage_u8HelperFunc =
{
    &BAM_Image_integralImage_u8_getMemRecFunc,
    NULL
};

