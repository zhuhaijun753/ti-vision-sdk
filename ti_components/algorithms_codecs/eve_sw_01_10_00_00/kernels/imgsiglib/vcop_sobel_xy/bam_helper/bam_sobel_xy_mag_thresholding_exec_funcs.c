/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_mag_thresholding_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Sobel XY magnitude thresholding
 *              kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_sobel_xy_mag_thresholding_int.h"
#include "bam_sobel_xy_mag_thresholding.h"
#include "vcop_sobel_xy_kernel.h" /* compiler should take care of include path */

/***********************************************************************************************/
/*                        Below are the helper  functions related to Sobel X kernel                                */
/***********************************************************************************************/
static BAM_Status BAM_SobelXyMagThresholding_initFrame(void *kernelContext);
static BAM_Status BAM_SobelXyMagThresholding_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status BAM_SobelXyMagThresholdingBinPack_initFrame(void *kernelContext);


static BAM_Status BAM_SobelXyMagThresholding_initFrame(void *kernelContext)
{
  BAM_SobelXyMagThresholding_Context *context = (BAM_SobelXyMagThresholding_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;


#if !VCOP_HOST_EMULATION
  vcop_sobelXy_3x3_L1_thresholding_init(
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADX_PORT],
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADY_PORT],
    context->pOutBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputPitch,
    context->kernelCtrlArgs.outputPitch,
    context->kernelCtrlArgs.threshold,
    context->pInternalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_SobelXyMagThresholding_computeFrame(void *kernelContext)
{
    BAM_SobelXyMagThresholding_Context *context = (BAM_SobelXyMagThresholding_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_sobelXy_3x3_L1_thresholding(
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADX_PORT],
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADY_PORT],
    context->pOutBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputPitch,
    context->kernelCtrlArgs.outputPitch,
    context->kernelCtrlArgs.threshold);
#endif
  return BAM_S_SUCCESS;
}
#endif

static BAM_Status BAM_SobelXyMagThresholding_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_SobelXyMagThresholding_Context *context = (BAM_SobelXyMagThresholding_Context *) kernelContext;

  BAM_SobelXyMagThresholding_CtrlArgs * ctrlArgs = (BAM_SobelXyMagThresholding_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}

BAM_KernelExecFuncDef BAM_SobelXyMagThresholdingExecFunc =
{
#if !VCOP_HOST_EMULATION
  NULL,
  &BAM_SobelXyMagThresholding_initFrame,
  NULL,
  NULL,
  &BAM_SobelXyMagThresholding_control,
  &vcop_sobelXy_3x3_L1_thresholding_vloops
#else
  NULL,
  &BAM_SobelXyMagThresholding_initFrame,
  &BAM_SobelXyMagThresholding_computeFrame,
  NULL,
  &BAM_SobelXyMagThresholding_control,
  NULL
#endif
};


static BAM_Status BAM_SobelXyMagThresholdingBinPack_initFrame(void *kernelContext)
{
  BAM_SobelXyMagThresholding_Context *context = (BAM_SobelXyMagThresholding_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;


#if !VCOP_HOST_EMULATION
  vcop_sobelXy_3x3_L1_thresholding_binPack_init(
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADX_PORT],
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADY_PORT],
    context->pOutBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputPitch,
    context->kernelCtrlArgs.outputPitch,
    context->kernelCtrlArgs.threshold,
    context->pInternalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_SobelXyMagThresholdingBinPack_computeFrame(void *kernelContext)
{
    BAM_SobelXyMagThresholding_Context *context = (BAM_SobelXyMagThresholding_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_sobelXy_3x3_L1_thresholding_binPack(
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADX_PORT],
    context->pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_GRADY_PORT],
    context->pOutBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputPitch,
    context->kernelCtrlArgs.outputPitch,
    context->kernelCtrlArgs.threshold);
#endif
  return BAM_S_SUCCESS;
}
#endif


BAM_KernelExecFuncDef BAM_SobelXyMagThresholdingBinPackExecFunc =
{
#if !VCOP_HOST_EMULATION
  NULL,
  &BAM_SobelXyMagThresholdingBinPack_initFrame,
  NULL,
  NULL,
  &BAM_SobelXyMagThresholding_control,
  &vcop_sobelXy_3x3_L1_thresholding_binPack_vloops
#else
  NULL,
  &BAM_SobelXyMagThresholdingBinPack_initFrame,
  &BAM_SobelXyMagThresholdingBinPack_computeFrame,
  NULL,
  &BAM_SobelXyMagThresholding_control,
  NULL
#endif
};



