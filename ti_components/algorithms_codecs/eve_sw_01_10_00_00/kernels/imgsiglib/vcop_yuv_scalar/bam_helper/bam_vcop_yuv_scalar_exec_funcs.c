/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file       bam_vcop_yuv_scalar_exec_funcs.cc
*
*  @brief      This file defines interfaces for integrating YUV Scalar
*              into BAM
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_yuv_scalar_int.h"
#include "bam_yuv_scalar.h"
#include "vcop_yuv_scalar_kernel.h"
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */	
#define ALIGN_SIZE(x,y) ((((x) + ((y)-1U)) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

static BAM_Status BAM_YUV_Scalar_compute(void *kernelContext);
static BAM_Status BAM_YUV_Scalar_control(void *kernelContext, void *ctlArg);
static BAM_Status BAM_YUV_Scalar_initFrame(void *kernelContext);

static BAM_Status BAM_YUV_Scalar_initFrame(void *kernelContext)
{
  BAM_YUV_Scalar_Context *context = (BAM_YUV_Scalar_Context *) kernelContext;
  uint32_t i;
  BAM_Status status = 0;
  uint16_t transposeBlkWidth    = ALIGN_SIZE((uint16_t)context->ctrlArgs.dstBlockHeight,(uint16_t)4);

  uint16_t (*offsetPtr)[8] ;
  if((transposeBlkWidth % 8U) == 0)
  {
    transposeBlkWidth += 4U;
  }
  context->transposeBlkWidth = transposeBlkWidth;
  offsetPtr = (uint16_t (*)[8])(void*)context->pInternalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX];
  for(i = 0; i < 8U; i++)
  {
    (*offsetPtr)[i] = i*context->transposeBlkWidth;
  }

#if (!VCOP_HOST_EMULATION)
         yuv_scalar_pixels_look_up_kernel_init((uint32_t*)context->pInBlock[YUV_SCALAR_IN_IDX], 
                                              (uint16_t*)context->pInBlock[YUV_SCALAR_INDEX_IDX], 
                                              (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX], 
                                              context->kernelArgs.numTaps, 
                                              context->ctrlArgs.srcBlockPitch, 
                                              context->ctrlArgs.dstBlockHeight,
                                              context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_0]);

        yuv_scalar_interpolation_kernel_init((uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX],
                                        (uint8_t*)context->pInBlock[YUV_SCALAR_FRAC_IDX], 
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX], 
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX], 
                                        (uint16_t *)context->pInternalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX],  
                                        context->transposeBlkWidth, 
                                        context->kernelArgs.fracBits, 
                                        context->kernelArgs.numTaps, 
                                        context->ctrlArgs.srcBlockWidth, 
                                        context->ctrlArgs.srcBlockPitch, 
                                        context->ctrlArgs.dstBlockHeight,
                                        context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_1]);

        if(context->ctrlArgs.inputDataType == 0)
        {
          yuv_scalar_luma_copy_kernel_init((uint32_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX], 
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX], 
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX], 
                                    context->transposeBlkWidth, 
                                    context->ctrlArgs.srcBlockWidth, 
                                    context->ctrlArgs.dstBlockHeight,
                                    context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2]);
            /* CHECK_MISRA("-11.1")  -> Disable rule 11.1     */
            /* This is auto generated fucntion by VCOP compiler tool */	
          context->scalarCopyKenel = (BAM_KernelCustom)&yuv_scalar_luma_copy_kernel_vloops;
            /* RESET_MISRA("11.1")  -> Reset rule 11.1     */
        }
        else
        {
          yuv_scalar_chroma_copy_kernel_init((uint8_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX], 
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX], 
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX], 
                                    context->transposeBlkWidth, 
                                    context->ctrlArgs.srcBlockWidth, 
                                    context->ctrlArgs.dstBlockHeight,
                                    context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2]);
            /* CHECK_MISRA("-11.1")  -> Disable rule 11.1     */
            /* This is auto generated fucntion by VCOP compiler tool */	
          context->scalarCopyKenel = (BAM_KernelCustom)&yuv_scalar_chroma_copy_kernel_vloops;
            /* RESET_MISRA("11.1")  -> Reset rule 11.     */
        }
#endif

  return status;
}

static BAM_Status BAM_YUV_Scalar_compute(void *kernelContext)
{
  BAM_YUV_Scalar_Context *context = (BAM_YUV_Scalar_Context *) kernelContext;
  BAM_Status status = 0;

#if (VCOP_HOST_EMULATION)
        yuv_scalar_pixels_look_up_kernel((uint32_t*)context->pInBlock[YUV_SCALAR_IN_IDX], 
                                              (uint16_t*)context->pInBlock[YUV_SCALAR_INDEX_IDX], 
                                              (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX], 
                                              context->kernelArgs.numTaps, 
                                              context->ctrlArgs.srcBlockPitch, 
                                              context->ctrlArgs.dstBlockHeight);

        yuv_scalar_interpolation_kernel((uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_LUT_OUT_IDX],
                                        (uint8_t*)context->pInBlock[YUV_SCALAR_FRAC_IDX], 
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX], 
                                        (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX], 
                                        (uint16_t *)context->pInternalBlock[YUV_SCALAR_INTERNAL_OFFSETS_IDX],  
                                        context->transposeBlkWidth, 
                                        context->kernelArgs.fracBits, 
                                        context->kernelArgs.numTaps, 
                                        context->ctrlArgs.srcBlockWidth, 
                                        context->ctrlArgs.srcBlockPitch, 
                                        context->ctrlArgs.dstBlockHeight);

        if(context->ctrlArgs.inputDataType == 0)
        {
          yuv_scalar_luma_copy_kernel((uint32_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX], 
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX], 
                                    (uint32_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX], 
                                    context->transposeBlkWidth, 
                                    context->ctrlArgs.srcBlockWidth, 
                                    context->ctrlArgs.dstBlockHeight);
        }
        else
        {
          yuv_scalar_chroma_copy_kernel((uint8_t*)context->pOutBlock[YUV_SCALAR_OUT_IDX], 
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_0_IDX], 
                                    (uint8_t*)context->pInternalBlock[YUV_SCALAR_INTERNAL_TRANSPOSE_OUT_1_IDX], 
                                    context->transposeBlkWidth, 
                                    context->ctrlArgs.srcBlockWidth, 
                                    context->ctrlArgs.dstBlockHeight);
        }
#else
        yuv_scalar_pixels_look_up_kernel_vloops(context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_0]);
        yuv_scalar_interpolation_kernel_vloops(context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_1]);
        context->scalarCopyKenel(context->pInternalBlock[YUV_SCALAR_INTERNAL_PARAMS_IDX_2]);

#endif

  return status;
}


static BAM_Status BAM_YUV_Scalar_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_YUV_Scalar_Context *context = (BAM_YUV_Scalar_Context *) kernelContext;
  BAM_yuv_scalar_Ctrl_Args *args  = (BAM_yuv_scalar_Ctrl_Args *) ctlArg;
  context->ctrlArgs = *args;
  return status;
}


BAM_KernelExecFuncDef gBAM_TI_yuvScalarExecFunc =
{ 
  NULL,
  &BAM_YUV_Scalar_initFrame,
  &BAM_YUV_Scalar_compute,
  NULL,
  &BAM_YUV_Scalar_control,
  NULL 
};



