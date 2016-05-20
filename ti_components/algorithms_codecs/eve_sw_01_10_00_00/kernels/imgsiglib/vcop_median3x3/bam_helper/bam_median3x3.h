/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median3x3.h
 *
 *  @brief      This header defines interfaces for integrating 3x3 median filter
 *              into BAM.
 */

#ifndef BAM_MEDIAN_3x3_H_
#define BAM_MEDIAN_3x3_H_

typedef struct
{
    uint16_t  blockWidth;
    uint16_t  blockHeight;
} BAM_Median3x3_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_median3x3HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_median3x3ExecFunc;

extern BAM_KernelInfo gBAM_TI_median3x3Kernel;

typedef enum
{
  BAM_MEDIAN_3x3_INPUT_PORT  =  0,
  BAM_MEDIAN_3x3_NUM_INPUT_BLOCKS
} eBAM_MEDIAN_3x3_INPUT_PORTS;

typedef enum
{
  BAM_MEDIAN_3x3_OUTPUT_PORT  =  0,
  BAM_MEDIAN_3x3_NUM_OUTPUT_BLOCKS
} eBAM_MEDIAN_3x3_OUTPUT_PORTS;

#endif /* BAM_MEDIAN_3x3_H_ */

