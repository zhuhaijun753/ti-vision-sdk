/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Sobel X and Y
 *              kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_sobel_xy_int.h"
#include "bam_sobel_xy.h"
#include "vcop_sobel_xy_kernel.h" /* compiler should take care of include path */

/***********************************************************************************************/
/*                        Below are the helper  functions related to Sobel X kernel                                */
/***********************************************************************************************/
static BAM_Status Bam_SobelXy_initFrame(void *kernelContext);
static BAM_Status Bam_SobelXy_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_SobelXy_initFrame(void *kernelContext)
{
  BAM_SobelXy_Context *context = (BAM_SobelXy_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;


#if !VCOP_HOST_EMULATION
  vcop_sobelXY_3x3_separable_uchar_init(
    context->pInBlock[BAM_SOBEL_XY_INPUT_IMAGE_PORT],
    context->pInternalBlock[SOBEL_XY_INTERNAL_SCRATCH_X_IDX],
    context->pInternalBlock[SOBEL_XY_INTERNAL_SCRATCH_Y_IDX],
    context->pOutBlock[BAM_SOBEL_XY_OUTPUT_X_PORT],
    context->pOutBlock[BAM_SOBEL_XY_OUTPUT_Y_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputPitch,
    context->kernelCtrlArgs.outputPitch,
    3U,
    context->pInternalBlock[SOBEL_XY_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_SobelXy_computeFrame(void *kernelContext)
{
    BAM_SobelXy_Context *context = (BAM_SobelXy_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_sobelXY_3x3_separable_uchar(
    context->pInBlock[BAM_SOBEL_XY_INPUT_IMAGE_PORT],
    context->pInternalBlock[SOBEL_XY_INTERNAL_SCRATCH_X_IDX],
    context->pInternalBlock[SOBEL_XY_INTERNAL_SCRATCH_Y_IDX],
    context->pOutBlock[BAM_SOBEL_XY_OUTPUT_X_PORT],
    context->pOutBlock[BAM_SOBEL_XY_OUTPUT_Y_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputPitch,
    context->kernelCtrlArgs.outputPitch,
    3U);
#endif
  return BAM_S_SUCCESS;
}
#endif

static BAM_Status Bam_SobelXy_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_SobelXy_Context *context = (BAM_SobelXy_Context *) kernelContext;

  BAM_SobelXy_CtrlArgs * ctrlArgs = (BAM_SobelXy_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_sobelXyExecFunc =
{
#if !VCOP_HOST_EMULATION
  NULL,
  &Bam_SobelXy_initFrame,
  NULL,
  NULL,
  &Bam_SobelXy_control,
  &vcop_sobelXY_3x3_separable_uchar_vloops
#else
  NULL,
  &Bam_SobelXy_initFrame,
  &Bam_SobelXy_computeFrame,
  NULL,
  &Bam_SobelXy_control,
  NULL
#endif
};

