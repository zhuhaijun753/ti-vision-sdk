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

#ifndef BAM_REMAP_H_
#define BAM_REMAP_H_

#include "remap.h"
#include "remap_common.h"


typedef RemapParms BAM_Remap_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_remapHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_remapExecFunc;

extern BAM_KernelInfo gBAM_TI_remapKernel;

#define BAM_REMAP_INPUT_PORT_IMAGE_BLOCK     (0U)
#define BAM_REMAP_INPUT_PORT_LUT             (1U)

#define BAM_REMAP_OUTPUT_PORT                (0U)


#endif /* BAM_REMAP_H_ */

