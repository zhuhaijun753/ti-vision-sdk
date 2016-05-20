/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_mag_thresholding_int.h
 *
 *  @brief      This header defines internal structures for Sobel XY magnitude thresholding
 *               kernel.
 */

#ifndef BAM_SOBEL_XY_MAG_THRESHOLDING_INT_H_
#define BAM_SOBEL_XY_MAG_THRESHOLDING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_sobel_xy_mag_thresholding.h"

typedef enum
{
  SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX = 0,
  SOBEL_XY_MAG_THRESHOLDING_INTERNAL_NUM_BLOCK
} eBAM_SOBEL_XY_MAG_THRESHOLDING_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_OUTPUT_BLOCKS];
    BAM_SobelXyMagThresholding_Args kernelInitArgs;
    BAM_SobelXyMagThresholding_CtrlArgs kernelCtrlArgs;
} BAM_SobelXyMagThresholding_Context;

#endif /* BAM_SOBEL_XY_MAG_THRESHOLDING_INT_H_*/

