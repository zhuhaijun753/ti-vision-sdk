/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*
 *****************************************************************************
 *
 * BAM DMA node for feature matching applet
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *****************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  feature_matching_bam_dma_node.h
 *
 * @brief
 *
 * @version 0.1 (Aug 2014) : First version of custom dma node for feature
 *                           matching applet
 *
 *****************************************************************************
*/

#ifndef FEATURE_MATCHING_BAM_DMA_NODE_H_
#define FEATURE_MATCHING_BAM_DMA_NODE_H_

#include "bam_types.h"

typedef struct
{
  uint16_t  descriptorLength;
  uint16_t  numDescPerIter1;
  uint16_t  numDescPerIter2;
} BAM_DMA_NODE_FEAT_MATCH_args;

typedef struct
{
  uint32_t totalNumBytesIn1;
  uint32_t totalNumBytesIn2;
  uint16_t numDesc1PerIter;
  uint16_t numDesc2PerIter;
  uint8_t *extMemPtrIn1;
  uint8_t *extMemPtrIn2;
  uint8_t *extMemPtrOut;
} BAM_DMA_NODE_FEAT_MATCH_updateParams;

/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_featMatchDmaNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_featMatchDmaNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_featMatchDmaNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_featMatchDmaNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_featMatchDmaNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_featMatchDmaNodeWriteKernelExecFunc;

#endif /* FEATURE_MATCHING_BAM_DMA_NODE_H_ */

