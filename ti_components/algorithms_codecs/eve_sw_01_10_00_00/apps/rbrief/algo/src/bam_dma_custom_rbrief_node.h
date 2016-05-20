/*
 *******************************************************************************
 *
 * BAM Scatter gather DMA node for Fast9 best feature to front applet
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bam_dma_custom_rbrief_node.h
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of custom dma node for rbrief applet
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_CUSTOM_RBRIEF_NODE_H_
#define BAM_DMA_CUSTOM_RBRIEF_NODE_H_

#include "bam_types.h"
#include "eve_edma_bam_interface.h"
#include "edma_utils_context_size.h"
#include "edma_utils_scatterGather.h"
#include "edma_utils_autoincrement_1d.h"
#include "xdais_types.h"
#include "irbrief_ti.h"

#define NUM_FEATURES  1

typedef struct
{
  const IVISION_BufDesc * inBufDesc;
  const IVISION_BufDesc * xyListBufDesc;
  const IVISION_BufDesc * levelListBufDesc;
}BAM_DMA_CUSTOM_RBRIEF_READ_ctrlArgs;


typedef struct
{
  uint8_t   numFeatures;
  uint16_t  maxNumFeatures;
  uint16_t  blockWidth;
  uint16_t  blockHeight;
}BAM_DMA_CUSTOM_RBRIEF_NODE_args;

/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomRbriefNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomRbriefNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomRbriefNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomRbriefNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomRbriefNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomRbriefNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_RBRIEF_NODE_H_ */

