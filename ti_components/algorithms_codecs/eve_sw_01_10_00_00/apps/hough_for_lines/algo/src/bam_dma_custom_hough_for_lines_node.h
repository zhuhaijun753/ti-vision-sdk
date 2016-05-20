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
 *  bam_dma_custom_hough_for_lines_node.h
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

#ifndef BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_H_
#define BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_H_

#include "bam_types.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement_1d.h"
#include "xdais_types.h"


#define NUM_FEATURES  1

typedef struct
{
  uint8_t * ptrToList;
  uint8_t * ptrToVotedRhoThetaSpace;
  uint16_t   listSize;
  uint16_t  thetaStart;
  uint16_t  thetaEnd;
  uint16_t  thetaStepSize;
  uint16_t  rhoMaxLength;
}BAM_DMA_CUSTOM_HOUGH_FOR_LINES_READ_ctrlArgs;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomHoughForLinesNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomHoughForLinesNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomHoughForLinesNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomHoughForLinesNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomHoughForLinesNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomHoughForLinesNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_HOUGH_FOR_LINES_NODE_H_ */

