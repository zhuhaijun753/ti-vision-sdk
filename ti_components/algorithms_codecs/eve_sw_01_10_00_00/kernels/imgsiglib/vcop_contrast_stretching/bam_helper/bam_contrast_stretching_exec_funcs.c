/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_contrast_stretching_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_contrast_stretching_int.h"
#include "bam_contrast_stretching.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_ContrastStretching_initFrame(void *kernelContext);
static BAM_Status Bam_ContrastStretching_control(void *kernelContext,
                                                        void * kernelCtlArg);

static BAM_Status Bam_ContrastStretching_initFrame(void *kernelContext)
{
  BAM_ContrastStretching_Context *context = (BAM_ContrastStretching_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;

#if (!VCOP_HOST_EMULATION)
  vcop_contrast_stretching_init(
    context->pInBlock[BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT],
    context->pOutBlock[BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT],
    context->kernelArgs.blkWidth,
    context->kernelArgs.blkHeight,
    context->kernelArgs.inPitch,
    context->kernelArgs.outPitch,
    context->kernelArgs.minVal,
    context->kernelArgs.scaleFactorQ16,
    context->pInternalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX]
  );
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_ContrastStretching_computeFrame(void *kernelContext)
{
    BAM_ContrastStretching_Context *context = (BAM_ContrastStretching_Context *) kernelContext;

#if (!VCOP_HOST_EMULATION)
  vcop_contrast_stretching_vloops(context->pInternalBlock[CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX]);
#else
  vcop_contrast_stretching(
    context->pInBlock[BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT],
    context->pOutBlock[BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT],
    context->kernelArgs.blkWidth,
    context->kernelArgs.blkHeight,
    context->kernelArgs.inPitch,
    context->kernelArgs.outPitch,
    context->kernelArgs.minVal,
    context->kernelArgs.scaleFactorQ16);
#endif
    return 0;
}

#endif

static BAM_Status Bam_ContrastStretching_control(void *kernelContext,
                                                        void * kernelCtlArg)
{
  BAM_Status status = BAM_S_SUCCESS;

  BAM_ContrastStretching_Context *context = (BAM_ContrastStretching_Context *) kernelContext;

  BAM_ContrastStretching_CtrlArgs * args = (BAM_ContrastStretching_CtrlArgs *)kernelCtlArg;

  context->kernelArgs.minVal          = args->minVal;
  context->kernelArgs.scaleFactorQ16  = args->scaleFactorQ16;

  return status;
}

BAM_KernelExecFuncDef gBAM_TI_contrastStretchingExecFunc =
#if (!VCOP_HOST_EMULATION)
{
  NULL,
  &Bam_ContrastStretching_initFrame,
  NULL,
  NULL,
  &Bam_ContrastStretching_control,
  &vcop_contrast_stretching_vloops
};
#else
{
  NULL,
  &Bam_ContrastStretching_initFrame,
  &Bam_ContrastStretching_computeFrame,
  NULL,
  &Bam_ContrastStretching_control,
  NULL
};

#endif

