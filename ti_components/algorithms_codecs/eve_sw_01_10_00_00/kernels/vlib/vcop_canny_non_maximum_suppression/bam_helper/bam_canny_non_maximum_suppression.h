/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_canny_non_maximum_suppression.h
 *
 *  @brief      This header defines interfaces for integrating Canny NMS kernels
 *              into BAM.
 */

#ifndef BAM_CANNY_NON_MAXIMUM_SUPPRESSION_H_
#define BAM_CANNY_NON_MAXIMUM_SUPPRESSION_H_

#include "bam_common.h"

typedef struct
{
  uint16_t maxBlockWidth;
  uint16_t maxBlockHeight;
} BAM_CannyNonMaximumSuppression_Args;

typedef struct
{
  uint16_t   computeWidth;
  uint16_t   computeHeight;
  uint16_t   inBlockPitch;
  uint16_t   outBlockPitch;
  uint8_t    lowThreshold;
  uint8_t    highThreshold;
} BAM_CannyNonMaximumSuppression_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_cannyNonMaximumSuppressionHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_cannyNonMaximumSuppressionExecFunc;

extern BAM_KernelInfo gBAM_TI_cannyNonMaximumSuppressionKernel;

typedef enum
{
  BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_X_PORT = 0,
  BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_Y_PORT,
  BAM_CANNY_NON_MAXIMUM_SUPPRESSION_GRAD_MAG_PORT,
  BAM_CANNY_NON_MAXIMUM_SUPPRESSION_NUM_INPUT_BLOCKS
} eBAM_CANNY_NON_MAXIMUM_SUPPRESSION_INPUT_PORTS;

typedef enum
{
  BAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUT_PORT = 0,
  BAM_CANNY_NON_MAXIMUM_SUPPRESSION_NUM_OUTPUT_BLOCKS
} eBAM_CANNY_NON_MAXIMUM_SUPPRESSION_OUTPUT_PORTS;

#endif /* BAM_CANNY_NON_MAXIMUM_SUPPRESSION_H_ */

