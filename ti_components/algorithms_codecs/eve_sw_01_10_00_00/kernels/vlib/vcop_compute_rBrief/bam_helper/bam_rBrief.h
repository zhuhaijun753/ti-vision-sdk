/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_rBrief.h
 *
 *  @brief      This header defines interfaces for integrating rBrief into BAM.
 */

#ifndef BAM_RBRIEF_H_
#define BAM_RBRIEF_H_

typedef struct
{
  const int8_t (*orbPattern)[1024];
} BAM_rBrief_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_rBriefHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_rBriefExecFunc;

extern BAM_KernelInfo gBAM_TI_rBriefKernel;

#define BAM_RBRIEF_INPUT_IMG_PORT      (0)

#define BAM_RBRIEF_OUTPUT_PORT          (0)

#endif /* BAM_RBRIEF_H_ */
