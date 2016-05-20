/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_mag_thresholding.h
 *
 *  @brief      This header defines interfaces for integrating Sobel XY magnitude thresholding kernels
 *              into BAM.
 */

#ifndef BAM_SOBEL_XY_MAG_THRESHOLDING_H_
#define BAM_SOBEL_XY_MAG_THRESHOLDING_H_

#include "bam_common.h"

typedef struct
{
  uint16_t  maxBlockWidth;
  uint16_t  maxBlockHeight;
} BAM_SobelXyMagThresholding_Args;

typedef struct
{
  uint16_t  computeWidth;
  uint16_t  computeHeight;
  uint16_t  inputPitch;
  uint16_t  outputPitch;
  uint16_t  threshold;
} BAM_SobelXyMagThresholding_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_sobelXyMagThresholdingHelperFunc;
extern BAM_KernelExecFuncDef BAM_SobelXyMagThresholdingExecFunc;
extern BAM_KernelInfo BAM_SobelXyMagThresholdingKernel;

extern BAM_KernelHelperFuncDef gBAM_TI_sobelXyMagThresholdingBinPackHelperFunc;
extern BAM_KernelExecFuncDef BAM_SobelXyMagThresholdingBinPackExecFunc;
extern BAM_KernelInfo BAM_SobelXyMagThresholdingBinPackKernel;

typedef enum
{
  BAM_SOBEL_XY_MAG_THRESHOLDING_GRADX_PORT= 0,
  BAM_SOBEL_XY_MAG_THRESHOLDING_GRADY_PORT,
  BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_INPUT_BLOCKS
} eBAM_SOBEL_XY_MAG_THRESHOLDING_INPUT_PORTS;

typedef enum
{
  BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT = 0,
  BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_OUTPUT_BLOCKS
} eBAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_PORTS;

#endif /* BAM_SOBEL_XY_MAG_THRESHOLDING_H_ */

