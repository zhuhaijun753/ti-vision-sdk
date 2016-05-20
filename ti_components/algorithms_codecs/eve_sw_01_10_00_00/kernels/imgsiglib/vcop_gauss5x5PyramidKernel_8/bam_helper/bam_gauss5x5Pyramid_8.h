/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gauss5x5Pyramid_8.h
 *
 *  @brief      This header defines interfaces for integrating Gauss  pyramid into BAM.
 */

#ifndef BAM_GAUSS5x5_PYRAMID_H_
#define BAM_GAUSS5x5_PYRAMID_H_

#include <stdint.h>
#include "evealgframework.h"

typedef struct
{
    uint16_t width; /* Must be multiple fo 16 */
    uint16_t height; /* Must be multiple fo 2 */
    uint16_t in_stride;
    uint16_t out_stride;
} BAM_Gauss5x5Pyramid_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_gauss5x5PyramidHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_gauss5x5PyramidExecFunc;

extern BAM_KernelInfo gBAM_TI_gauss5x5PyramidKernel;

#define BAM_GAUSS5x5PYRAMID_INPUT_PORT      0
#define BAM_GAUSS5x5PYRAMID_OUTPUT_PORT     0

#endif /* BAM_GAUSSPYRAMID_H_ */
