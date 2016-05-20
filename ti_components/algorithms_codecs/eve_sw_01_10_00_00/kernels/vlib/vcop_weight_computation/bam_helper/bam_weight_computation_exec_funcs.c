/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_weight_computation_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for weight computation
 *              kernel function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_weight_computation_int.h"
#include "bam_weight_computation.h"
#include "vcop_weight_computation_kernel.h" /* compiler should take care of include path */
#include "vcop_weight_computation_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Weight_Computation_initFrame(void *kernelContext);
static BAM_Status Bam_Weight_Computation_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_Weight_Computation_initFrame(void *kernelContext)
{
    BAM_Weight_Computation_Context *context = (BAM_Weight_Computation_Context *) kernelContext;
    BAM_Status status = 0;
    uint32_t qFormatePel = ((uint32_t)VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);
    uint32_t qFormatMaxFactor = ((uint32_t)1 << qFormatePel);
    uint16_t truncateBits = qFormatePel <= 8U ? 0 : (2U*(qFormatePel-8U));
    qFormatMaxFactor--;
    /* Return error if assumptions in kernel are not satisfied*/
    if((context->kernelArgs.outputStride < context->kernelArgs.numKeyPoints) ||
        ((context->kernelArgs.numKeyPoints) < 1) || ((context->kernelArgs.outputStride) < 1) ||
        ((qFormatMaxFactor) < 1U)) {
        status = 1;
    }

    if(status == 0) {
        vcop_weight_computation_init((uint16_t*)context->pInBlock[IN_IDX],
                               (uint16_t*)context->pOutBlock[OUT_IDX],
                               context->kernelArgs.numKeyPoints,
                               (uint16_t)qFormatMaxFactor,
                               truncateBits,
                               context->kernelArgs.outputStride,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Weight_Computation_computeFrame(void *kernelContext);

static BAM_Status Bam_Weight_Computation_computeFrame(void *kernelContext)
{
    BAM_Weight_Computation_Context *context = (BAM_Weight_Computation_Context *) kernelContext;
    BAM_Status status = 0;
    uint32_t qFormatePel = (VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);
    uint32_t qFormatMaxFactor = ((1 << qFormatePel) - 1);
    uint16_t truncateBits = qFormatePel <= 8 ? 0 : (2*(qFormatePel-8));

    vcop_weight_computation_cn((uint16_t*)context->pInBlock[IN_IDX],
                           (uint16_t*)context->pOutBlock[OUT_IDX],
                           context->kernelArgs.numKeyPoints,
                           qFormatMaxFactor,
                           truncateBits,
                           context->kernelArgs.outputStride);

    return status;
}
#endif

static BAM_Status Bam_Weight_Computation_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_Weight_Computation_Context *context = (BAM_Weight_Computation_Context *) kernelContext;
  BAM_Weight_Computation_Ctrl_Args *args  = (BAM_Weight_Computation_Ctrl_Args *) ctlArg;
  context->kernelArgs.ctrlPtr = *args;
  return status;
}

BAM_KernelExecFuncDef gBAM_TI_weightComputationExecFunc =
#ifdef NATC
    { NULL, &Bam_Weight_Computation_initFrame, &Bam_Weight_Computation_computeFrame, NULL, &Bam_Weight_Computation_control, NULL };
#else
    { NULL, &Bam_Weight_Computation_initFrame, NULL, NULL, &Bam_Weight_Computation_control, &vcop_weight_computation_vloops };
#endif

