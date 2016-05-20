/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*
 *******************************************************************************
 *
 * BAM DMA node for Gray-level Co-occurrence matrix applet
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  glcm_bam_dma_node.h
 *
 * @brief
 *
 * @version 0.1 (Jan 2014) : First version of custom dma node for glcm applet
 *
 *****************************************************************************
*/

#ifndef GLCM_BAM_DMA_NODE_H_
#define GLCM_BAM_DMA_NODE_H_

#include "bam_types.h"
#include "bam_glcm.h"

/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_glcmDmaNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_glcmDmaNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_glcmDmaNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_glcmDmaNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_glcmDmaNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_glcmDmaNodeWriteKernelExecFunc;

#endif /* GLCM_BAM_DMA_NODE_H_ */

