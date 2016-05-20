/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_harrisScore_32_7x7_.h
 *
 *  @brief      This header defines interfaces for integrating harris score into BAM.
 */

#ifndef BAM_HARRISSCORE_U32_7x7_H_
#define BAM_HARRISSCORE_U32_7x7_H_

typedef struct
{
    uint16_t width; /* width * height must be multiple of 16 */
    uint16_t height;
    uint16_t inStride;
    uint16_t outStride;
    uint16_t scaling;
    uint8_t  windowSize;
} BAM_HarrisScore_32_7x7_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_harrisScore_32_7x7_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_harrisScore_32_7x7_ExecFunc;

extern BAM_KernelInfo gBAM_TI_harrisScore_32_7x7_Kernel;

/* Harris Score Method B shares the same arguments as harris score original method
hence reuse it*/
extern BAM_KernelHelperFuncDef gBAM_TI_harrisScore_32_methodB_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_harrisScore_32_methodB_ExecFunc;

extern BAM_KernelInfo gBAM_TI_harrisScore_32_methodB_Kernel;

typedef enum
{
  BAM_HARRISSCORE_32_INPUT_GRADX_PORT,
  BAM_HARRISSCORE_32_INPUT_GRADY_PORT,
  BAM_HARRISSCORE_32_INPUT_BLOCKS
} BAM_HARRISSCORE_32_METHOD_B_INPUT_PORTS;

typedef enum
{
  BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT,
  BAM_HARRISSCORE_32_OUTPUT_BLOCKS
} BAM_HARRISSCORE_32_METHOD_B_OUTPUT_PORTS;

#endif /* BAM_HARRISSCORE_U32_7x7_H_ */

