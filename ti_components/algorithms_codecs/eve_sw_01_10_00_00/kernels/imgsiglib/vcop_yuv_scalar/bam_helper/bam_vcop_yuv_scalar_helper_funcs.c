/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_yuv_scalar_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV Scalar
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_yuv_scalar_int.h"
#include "vcop_yuv_scalar_kernel.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */	
#define ALIGN_SIZE(x,y) ((((x) + ((y)-1U)) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

static BAM_Status BAM_YUV_Scalar_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks);


static BAM_Status BAM_YUV_Scalar_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks)
{
  const BAM_yuv_scalar_Args * args = (const BAM_yuv_scalar_Args *)kernelArgs;
  uint16_t transposeBlkWidth    = ALIGN_SIZE((uint16_t)args->dstBlockHeight,(uint16_t)4);
  if((transposeBlkWidth % 8U) == 0)
  {
    transposeBlkWidth += 4U;
  }

#if (!VCOP_HOST_EMULATION)
  internalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_0].size = 2U *
                               yuv_scalar_pixels_look_up_kernel_param_count();
  internalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_1].size = 2U *
                               yuv_scalar_interpolation_kernel_param_count();
  internalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2].size =
    yuv_scalar_luma_copy_kernel_param_count() > yuv_scalar_chroma_copy_kernel_param_count() ?  
    2U * yuv_scalar_luma_copy_kernel_param_count() : 2U* yuv_scalar_chroma_copy_kernel_param_count();
#else
  /* This field could be any non-zero number for host emulation */
  internalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_0].size = 4;
  internalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_1].size = 4;
  internalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2].size = 4;
#endif

  internalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX].size                    = (args->srcBlockPitch *args->dstBlockHeight * sizeof(uint8_t));
  internalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX].attrs.memAttrs          =  BAM_MEMATTRS_SCRATCH;
  internalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX].space                   = BAM_MEMSPACE_WBUF;

  internalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX].size            = (ALIGN_SIZE((uint16_t)args->srcBlockWidth,(uint16_t)16) * transposeBlkWidth * sizeof(uint8_t));
  internalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX].attrs.memAttrs  =  BAM_MEMATTRS_SCRATCH;
  internalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX].space           = BAM_MEMSPACE_IBUFHA;

  internalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX].size            = (ALIGN_SIZE((uint16_t)args->srcBlockWidth,(uint16_t)16) * transposeBlkWidth * sizeof(uint8_t));
  internalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX].attrs.memAttrs  =  BAM_MEMATTRS_SCRATCH;
  internalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX].space           = BAM_MEMSPACE_IBUFHA;

  internalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX].size                    = (8 * sizeof(uint16_t));
  internalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX].attrs.memAttrs          = BAM_MEMATTRS_PERSIST;
  internalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX].space                   = BAM_MEMSPACE_WBUF;

  outBlock[YUV_SCALAR_OUT_IDX].size              = ALIGN_SIZE(args->srcBlockWidth,2U) * args->dstBlockHeight;
  outBlock[YUV_SCALAR_OUT_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
  outBlock[YUV_SCALAR_OUT_IDX].space             = BAM_MEMSPACE_IBUFLA;


  return BAM_S_SUCCESS;
}




BAM_KernelInfo gBAM_TI_yuvScalarKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_YUV_Scalar_Context),
    sizeof(BAM_yuv_scalar_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_yuvScalarHelperFunc =
{ &BAM_YUV_Scalar_getMemRecFunc, NULL};




