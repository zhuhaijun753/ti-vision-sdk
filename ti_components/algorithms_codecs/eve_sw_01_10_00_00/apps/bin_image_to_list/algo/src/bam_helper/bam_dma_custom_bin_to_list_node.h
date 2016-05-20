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
 *  bam_dma_custom_bin_to_list_node.h
 *
 * @brief
 *
 * @version 0.1 (April 2015) : First version of custom dma node for bin img to list applet
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_H_
#define BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_H_

#include "bam_types.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement.h"
#include "xdais_types.h"


#define NUM_FEATURES  1

typedef struct
{
  uint16_t  maxBlkWidth;
  uint16_t  maxBlkHeight;
  uint8_t   enableMasking;
}BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args;


typedef struct
{
  EDMA_UTILS_autoIncrement_transferProperties inTransferProp[2];
}BAM_DMA_CUSTOM_BIN_TO_LIST_READ_ctrlArgs;



typedef struct
{
  uint8_t   *ptrToXyListBuf;
  uint8_t   *ptrToListSizeBuf;
}BAM_DMA_CUSTOM_BIN_TO_LIST_WRITE_ctrlArgs;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomBinToListNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomBinToListNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomBinToListNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomBinToListNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomBinToListNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomBinToListNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_BIN_TO_LIST_NODE_H_ */

