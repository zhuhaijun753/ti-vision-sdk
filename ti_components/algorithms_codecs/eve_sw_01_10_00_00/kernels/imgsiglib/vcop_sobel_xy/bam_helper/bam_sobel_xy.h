/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy.h
 *
 *  @brief      This header defines interfaces for integrating Sobel X and Y kernels
 *              into BAM.
 */

#ifndef BAM_SOBEL_XY_H_
#define BAM_SOBEL_XY_H_

#include "bam_common.h"

typedef struct
{
  uint16_t  maxBlockWidth;
  uint16_t  maxBlockHeight;
} BAM_SobelXy_Args;

typedef struct
{
  uint16_t  computeWidth;
  uint16_t  computeHeight;
  uint16_t  inputPitch;
  uint16_t  outputPitch;
} BAM_SobelXy_CtrlArgs;


extern BAM_KernelInfo gBAM_TI_sobelXyKernel;
extern BAM_KernelHelperFuncDef gBAM_TI_sobelXyHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_sobelXyExecFunc;

typedef enum
{
  BAM_SOBEL_XY_INPUT_IMAGE_PORT= 0,
  BAM_SOBEL_XY_NUM_INPUT_BLOCKS
} eBAM_SOBEL_XY_INPUT_PORTS;

typedef enum
{
  BAM_SOBEL_XY_OUTPUT_X_PORT = 0,
  BAM_SOBEL_XY_OUTPUT_Y_PORT,
  BAM_SOBEL_XY_NUM_OUTPUT_BLOCKS
} eBAM_SOBEL_XY_OUTPUT_PORTS;

#endif /* BAM_SOBEL_XY_H_ */

