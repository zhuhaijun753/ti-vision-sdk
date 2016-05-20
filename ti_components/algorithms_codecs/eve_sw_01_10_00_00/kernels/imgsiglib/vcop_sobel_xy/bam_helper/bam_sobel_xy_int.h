/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_int.h
 *
 *  @brief      This header defines internal structures for Sobel X and Y
 *               kernel.
 */

#ifndef BAM_SOBEL_XY_INT_H_
#define BAM_SOBEL_XY_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_sobel_xy.h"

typedef enum
{
  SOBEL_XY_INTERNAL_PARAMS_IDX = 0,
  SOBEL_XY_INTERNAL_SCRATCH_X_IDX,
  SOBEL_XY_INTERNAL_SCRATCH_Y_IDX,
  SOBEL_XY_INTERNAL_NUM_BLOCK
} eBAM_SOBEL_XY_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[SOBEL_XY_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_SOBEL_XY_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_SOBEL_XY_NUM_OUTPUT_BLOCKS];
    BAM_SobelXy_Args     kernelInitArgs;
    BAM_SobelXy_CtrlArgs kernelCtrlArgs;
} BAM_SobelXy_Context;

#endif /* BAM_SOBEL_XY_INT_H_*/

