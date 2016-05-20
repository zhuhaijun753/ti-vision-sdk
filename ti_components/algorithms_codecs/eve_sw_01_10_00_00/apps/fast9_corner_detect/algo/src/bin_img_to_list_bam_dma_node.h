/*
 *******************************************************************************
 *
 * BAM DMA node for Binary image to list applet
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bin_img_to_list_bam_dma_node.h
 *
 * @brief
 *
 * @author: Anoop K P (a-kp@ti.com)
 * @version 0.1 (Dec 2013) : First version of eve edma utils function
 *
 *****************************************************************************
*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BIN_IMG_TO_LIST_BAM_DMA_NODE_H_
#define BIN_IMG_TO_LIST_BAM_DMA_NODE_H_

#include "bam_types.h"
#include "eve_edma_bam_interface.h"

typedef struct
{
  uint8_t * dstPtr;
  uint32_t * pListSize;
} BAM_DMA_CUSTOM_BINIMG2LIST_WRITENODE_ctrlArgs;

/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_binImg2ListReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaReadBinImg2ListHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaReadBinImg2ListExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_binImg2ListWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaWriteBinImg2ListHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaWriteBinImg2ListExecFunc;


#endif /* _BIN_IMG_TO_LIST_BAM_DMA_NODE_H_ */

