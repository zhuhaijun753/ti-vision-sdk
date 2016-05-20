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
 *  bam_dma_custom_select_list_elem_node.h
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

#ifndef BAM_DMA_CUSTOM_SELECT_LIST_ELEM_NODE_H_
#define BAM_DMA_CUSTOM_SELECT_LIST_ELEM_NODE_H_

#include "bam_types.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement.h"
#include "xdais_types.h"
#include "edma_utils_autoincrement_1d.h"

#define NUM_FEATURES  1

typedef struct
{
  uint16_t  maxListSize;
}BAM_DMA_CUSTOM_SELECT_LIST_ELEM_READ_args;


typedef struct
{
  EDMA_UTILS_autoIncrement1D_transferProperties inTransferProp;
}BAM_DMA_CUSTOM_SELECT_LIST_ELEM_READ_ctrlArgs;



typedef struct
{
  uint8_t   *ptrToListBuf;
  uint8_t   *ptrToListSizeBuf;
}BAM_DMA_CUSTOM_SELECT_LIST_ELEM_WRITE_ctrlArgs;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomSelectListElemNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomSelectListElemNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomSelectListElemNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomSelectListElemNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomSelectListElemNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomSelectListElemNodeWriteKernelExecFunc;

#endif /* BAM_DMA_CUSTOM_SELECT_LIST_ELEM_NODE_H_ */

