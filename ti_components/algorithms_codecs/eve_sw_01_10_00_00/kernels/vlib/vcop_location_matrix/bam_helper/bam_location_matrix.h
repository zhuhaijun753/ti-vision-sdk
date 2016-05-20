/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_location_matrix.h
*
* @brief
*
*
* @version 0.0 (Jan 2014) : Base version.
*/


#ifndef BAM_LOCATION_MATRIX_H_
#define BAM_LOCATION_MATRIX_H_

#include "bam_common.h"


typedef struct
{
    uint16_t blockW;
    uint16_t blockH;
    uint8_t  numBins;
    uint8_t  gradientMagSize; /* Gradient Magnitude size in number of bytes */
} BAM_location_matrix_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_location_matrixHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_location_matrixExecFunc;

extern BAM_KernelInfo gBAM_TI_location_matrixKernel;

#define BAM_LOCATION_MATRIX_INPUT_BLK_PORT    (0)
#define BAM_LOCATION_MATRIX_INPUT_MAG_PORT    (1)

#define BAM_LOCATION_MATRIX_OUTPUT_MATRIX1_PORT (0)
#define BAM_LOCATION_MATRIX_OUTPUT_MATRIX2_PORT (1)

#endif /* BAM_LOCATION_MATRIX_H_ */

