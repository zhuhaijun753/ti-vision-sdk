/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_binary_masking_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating binary Masking
 *              kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_binary_masking_int.h"
#include "bam_binary_masking.h"
#include "vcop_binary_masking_kernel.h" /* compiler should take care of include path */




/***********************************************************************************************/
/*                        Below are the helper  functions related to Sobel X kernel                                */
/***********************************************************************************************/
static BAM_Status Bam_BinaryMasking_initFrame(void *kernelContext);

static BAM_Status Bam_BinaryMasking_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_BinaryMasking_initFrame(void *kernelContext)
{
  BAM_BinaryMasking_Context *context = (BAM_BinaryMasking_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;


#if !VCOP_HOST_EMULATION
  vcop_binary_masking_init(
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BYTE_DATA_IMAGE_PORT],
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BIT_DATA_IMAGE_PORT],
    context->pOutBlock[BAM_BINARY_MASKING_OUTPUT_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputByteDataPitch,
    context->kernelCtrlArgs.inputBitDataPitch,
    context->kernelCtrlArgs.outputPitch,
    context->pInternalBlock[BINARY_MASKING_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_BinaryMasking_computeFrame(void *kernelContext)
{
    BAM_BinaryMasking_Context *context = (BAM_BinaryMasking_Context *)kernelContext;

    vcop_binary_masking(
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BYTE_DATA_IMAGE_PORT],
    context->pInBlock[BAM_BINARY_MASKING_INPUT_BIT_DATA_IMAGE_PORT],
    context->pOutBlock[BAM_BINARY_MASKING_OUTPUT_PORT],
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inputByteDataPitch,
    context->kernelCtrlArgs.inputBitDataPitch,
    context->kernelCtrlArgs.outputPitch);

  return BAM_S_SUCCESS;
}
#endif

static BAM_Status Bam_BinaryMasking_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_BinaryMasking_Context *context = (BAM_BinaryMasking_Context *) kernelContext;

  BAM_BinaryMasking_CtrlArgs * ctrlArgs = (BAM_BinaryMasking_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  if ( ( ctrlArgs->computeWidth * ctrlArgs->computeHeight )  <= (context->kernelInitArgs.maxBlockWidth * context->kernelInitArgs.maxBlockHeight) )
  {
    context->kernelCtrlArgs = *ctrlArgs;
  }
  else
  {
    status = BAM_E_FAIL;
  }

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_binaryMaskingExecFunc =
{
#if !VCOP_HOST_EMULATION
  NULL,
  &Bam_BinaryMasking_initFrame,
  NULL,
  NULL,
  &Bam_BinaryMasking_control,
  &vcop_binary_masking_vloops
#else
  NULL,
  &Bam_BinaryMasking_initFrame,
  &Bam_BinaryMasking_computeFrame,
  NULL,
  &Bam_BinaryMasking_control,
  NULL
#endif
};

