/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_canny_non_maximum_suppression_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Canny NMS
 *               kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_canny_non_maximum_suppression_int.h"
#include "bam_canny_non_maximum_suppression.h"
#include "vcop_canny_non_maximum_suppression_kernel.h" /* compiler should take care of include path */



/***********************************************************************************************/
/*                        Below are the helper  functions related to Canny NMS kernels                                */
/***********************************************************************************************/
static BAM_Status Bam_CannyNonMaximumSuppression_initFrame(void *kernelContext);
static BAM_Status Bam_CannyNonMaximumSuppression_computeFrame(void *kernelContext);

static BAM_Status Bam_CannyNonMaximumSuppression_control(void *kernelContext,
                                            void * kernelCtlArg);

static BAM_Status Bam_CannyNonMaximumSuppression_initFrame(void *kernelContext)
{
  BAM_CannyNonMaximumSuppression_Context *context = (BAM_CannyNonMaximumSuppression_Context *) kernelContext;
  BAM_Status status = BAM_S_SUCCESS;

#if (!VCOP_HOST_EMULATION)
  context->pBlockIndexBinning = (uint16_t *)context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_PARAMS_IDX];
  /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
  /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
  /*  These pointers are derived based on the param block count of individual applet which at compile is unknown , hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
  rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
  context->pBlockMaxCases     =  context->pBlockIndexBinning + vcop_canny_bin_indexing_param_count();
  context->pBlockDoubleThresholding = context->pBlockMaxCases + vcop_canny_nms_max_cases_param_count();
  /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

  vcop_canny_bin_indexing_init(
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_X_PORT],
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_Y_PORT],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->kernelCtrlArgs.computeWidth + 2U,
    context->kernelCtrlArgs.computeHeight + 2U,
    context->kernelCtrlArgs.inBlockPitch,
    context->pBlockIndexBinning );

  vcop_canny_nms_max_cases_init(
      context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_MAG_PORT],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
      context->kernelCtrlArgs.computeWidth,
      context->kernelCtrlArgs.computeHeight,
      context->kernelCtrlArgs.inBlockPitch,
      context->pBlockMaxCases);

  vcop_canny_nms_double_thresholding_init(
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
    context->pOutBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT],
    context->kernelCtrlArgs.lowThreshold,
    context->kernelCtrlArgs.highThreshold,
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inBlockPitch,
    context->kernelCtrlArgs.outBlockPitch,
    context->pBlockDoubleThresholding);

#endif
    return status;
}


static BAM_Status Bam_CannyNonMaximumSuppression_computeFrame(void *kernelContext)
{
    BAM_CannyNonMaximumSuppression_Context *context = (BAM_CannyNonMaximumSuppression_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
   vcop_canny_bin_indexing(
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_X_PORT],
    context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_Y_PORT],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->kernelCtrlArgs.computeWidth + 2U,
    context->kernelCtrlArgs.computeHeight + 2U,
    context->kernelCtrlArgs.inBlockPitch);

  vcop_canny_nms_max_cases(
      context->pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_MAG_PORT],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
      context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
      context->kernelCtrlArgs.computeWidth,
      context->kernelCtrlArgs.computeHeight,
      context->kernelCtrlArgs.inBlockPitch);

  vcop_canny_nms_double_thresholding(
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX],
    context->pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX],
    context->pOutBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT],
    context->kernelCtrlArgs.lowThreshold,
    context->kernelCtrlArgs.highThreshold,
    context->kernelCtrlArgs.computeWidth,
    context->kernelCtrlArgs.computeHeight,
    context->kernelCtrlArgs.inBlockPitch,
    context->kernelCtrlArgs.outBlockPitch);
#else
    /* Param block update to update the radius and current number of edge points */
    vcop_canny_bin_indexing_vloops(context->pBlockIndexBinning);
    vcop_canny_nms_max_cases_vloops(context->pBlockMaxCases);
    vcop_canny_nms_double_thresholding_vloops(context->pBlockDoubleThresholding);

#endif

  return BAM_S_SUCCESS;
}


static BAM_Status Bam_CannyNonMaximumSuppression_control(void *kernelContext,
                                            void * kernelCtlArg)
{
  BAM_CannyNonMaximumSuppression_Context *context = (BAM_CannyNonMaximumSuppression_Context *) kernelContext;

  BAM_CannyNonMaximumSuppression_CtrlArgs * ctrlArgs = (BAM_CannyNonMaximumSuppression_CtrlArgs * )kernelCtlArg;
  BAM_Status status = BAM_S_SUCCESS;

  context->kernelCtrlArgs = *ctrlArgs;

  return status;
}


BAM_KernelExecFuncDef gBAM_TI_cannyNonMaximumSuppressionExecFunc =
{
  NULL,
  &Bam_CannyNonMaximumSuppression_initFrame,
  &Bam_CannyNonMaximumSuppression_computeFrame,
  NULL,
  &Bam_CannyNonMaximumSuppression_control,
  NULL
};


