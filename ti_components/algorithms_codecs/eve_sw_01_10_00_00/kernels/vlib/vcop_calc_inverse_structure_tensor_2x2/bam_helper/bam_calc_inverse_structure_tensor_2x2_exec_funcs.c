/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_inverse_structure_tensor_2x2_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for kernel that computes
 *              inverse of the 2x2 structure tensor into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_calc_inverse_structure_tensor_2x2_int.h"
#include "bam_calc_inverse_structure_tensor_2x2.h"
#include "vcop_calc_inverse_structure_tensor_2x2_kernel.h" /* compiler should take care of include path */
#include "vcop_calc_inverse_structure_tensor_2x2_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame(void *kernelContext);
static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame(void *kernelContext)
{
    BAM_Calc_Inverse_Structure_Tensor_2x2_Context *context = (BAM_Calc_Inverse_Structure_Tensor_2x2_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t qFormatePel = ((uint16_t)VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);

    /* Return error if assumptions in kernel are not satisfied*/
    if(((context->kernelArgs.numKeyPoints) < 1) || ((context->kernelArgs.inputStride) < 1) ||
      ((context->kernelArgs.outputStride) < 1) || ((context->kernelArgs.inputStride) < (context->kernelArgs.numKeyPoints)) ||
      ((context->kernelArgs.outputStride) < (2*context->kernelArgs.numKeyPoints))) {
        status = 1;
    }

    if(status == 0) {
        vcop_calc_inverse_structure_tensor_2x2_init((int32_t*)context->pInBlock[IN_IDX1],
                               (uint16_t*)context->pInBlock[IN_IDX2],
                               (uint32_t*)context->pInBlock[IN_IDX3],
                                (int16_t*)context->pOutBlock[OUT_IDX1],
                               (int32_t*)context->pInternalBlock[SCRATCH_IDX1],
                               (uint32_t*)context->pInternalBlock[SCRATCH_IDX2],
                               context->kernelArgs.inputStride,
                               context->kernelArgs.outputStride,
                               qFormatePel,
                               context->kernelArgs.numKeyPoints,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_computeFrame(void *kernelContext);

static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_computeFrame(void *kernelContext)
{
    BAM_Calc_Inverse_Structure_Tensor_2x2_Context *context = (BAM_Calc_Inverse_Structure_Tensor_2x2_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t qFormatePel = ((uint16_t)VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);

    vcop_calc_inverse_structure_tensor_2x2_cn((int*)context->pInBlock[IN_IDX1],
                           (uint16_t*)context->pInBlock[IN_IDX2],
                           (uint32_t*)context->pInBlock[IN_IDX3],
                            (int16_t*)context->pOutBlock[OUT_IDX1],
                           context->kernelArgs.inputStride,
                           context->kernelArgs.outputStride,
                           qFormatePel,
                           context->kernelArgs.numKeyPoints);

    return status;
}
#endif

static BAM_Status Bam_Calc_Inverse_Structure_Tensor_2x2_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_Calc_Inverse_Structure_Tensor_2x2_Context *context = (BAM_Calc_Inverse_Structure_Tensor_2x2_Context *) kernelContext;
  BAM_Calc_Inverse_Structure_Tensor_2x2_Ctrl_Args *args  = (BAM_Calc_Inverse_Structure_Tensor_2x2_Ctrl_Args *) ctlArg;
  context->kernelArgs.ctrlPtr = *args;
  return status;
}

BAM_KernelExecFuncDef gBAM_TI_calcInverseStructureTensor2x2ExecFunc =
#ifdef NATC
    { NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame, &Bam_Calc_Inverse_Structure_Tensor_2x2_computeFrame, NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_control, NULL };
#else
    { NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_initFrame, NULL, NULL, &Bam_Calc_Inverse_Structure_Tensor_2x2_control, &vcop_calc_inverse_structure_tensor_2x2_vloops };
#endif
