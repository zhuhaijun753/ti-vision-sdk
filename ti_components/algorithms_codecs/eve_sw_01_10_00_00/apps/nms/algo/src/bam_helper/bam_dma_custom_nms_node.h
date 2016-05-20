/*
 *******************************************************************************
 *
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bam_dma_custom_nms_node.h
 *
 * @brief
 *
 * @version 0.1 (Aug 2014) : First version of custom dma node for NMS applet
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_CUSTOM_NMS_NODE_H_
#define BAM_DMA_CUSTOM_NMS_NODE_H_

#include "bam_types.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement.h"
#include "xdais_types.h"


#define NUM_FEATURES  1

typedef struct
{
  uint16_t  maxBlkWidth;
  uint16_t  maxBlkHeight;
}BAM_DMA_CUSTOM_NMS_READ_args;


typedef struct
{
  EDMA_UTILS_autoIncrement_transferProperties inTransferProp;
}BAM_DMA_CUSTOM_NMS_READ_ctrlArgs;



typedef struct
{
  uint8_t   *ptrToXyListBuf;
  uint8_t   *ptrToListSizeBuf;
}BAM_DMA_CUSTOM_NMS_WRITE_ctrlArgs;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomNmsNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomNmsNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomNmsNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomNmsNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomNmsNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomNmsNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_NMS_NODE_H_ */

