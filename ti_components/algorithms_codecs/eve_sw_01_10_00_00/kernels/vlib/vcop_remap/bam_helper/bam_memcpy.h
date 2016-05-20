/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap.h
 *
 *  @brief      This header defines interfaces for integrating Remap kernel
 *              into BAM.
 */

#ifndef BAM_MEMCPY_H_
#define BAM_MEMCPY_H_

#include "remap_common.h"

typedef struct bam_memcpy_args
{
    uint16_t width;
    uint16_t height;
    Format   format;
} BAM_Memcpy_Args;


extern BAM_KernelHelperFuncDef gBAM_TI_memcpyHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_memcpyExecFunc;

extern BAM_KernelInfo gBAM_TI_memcpyKernel;

#define BAM_MEMCPY_INPUT_PORT     (0U)
#define BAM_MEMCPY_OUTPUT_PORT    (0U)


#endif /* BAM_MEMCPY_H_ */

