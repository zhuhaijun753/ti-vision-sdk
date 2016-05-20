/*
 *******************************************************************************
 *
 * BAM One shot DMA node
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bam_dma_one_shot_node.h
 *
 * @brief
 *  This file interfaces with the BAM dma node that triggers EDMA only one time
 *  when a specific triggerBlockId is reached.
 *  So to trigger at the beginning of the frame, set it to 0 and at the end, set it to the
 *  N-1 when N is the total number of blocks in the frame.
 *
 * @version 0.1 (Dec 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_ONESHOT_NODE_H_
#define BAM_DMA_ONESHOT_NODE_H_

#include "bam_types.h"
#include "edma_utils_autoincrement.h"
#include "eve_edma_bam_interface.h"

typedef struct {
    uint16_t    blkWidth;
    uint16_t    blkHeight;
    uint8_t     *extMemPtr;
    uint8_t     *interMemPtr;
    uint16_t    extMemPtrStride;
    uint16_t    interMemPtrStride;
} BAM_DMA_OneShot_transferProperties;

/**
*  @brief      DMA argument structure used to initialize the EDMA parameters
*/
typedef struct
{
    uint8_t    transferType;
    uint8_t    numInTransfers;
    uint8_t    numOutTransfers;
    int32_t    triggerBlockId;
    uint32_t   numTotalBlocksInFrame;  /* required because if it is a sink node because the scheduler needs to know when to stop */
    BAM_DMA_OneShot_transferProperties transferProp[NUM_MAX_TRANSFER_AUTOINCREMENT];
} BAM_DMA_OneShot_Args;

/**
*  @brief      Control structure used to pass new pointer and new stride in external memory after graph creation, before each execution.
*/
typedef struct
{
    uint8_t numTransfers;
    uint8_t *extMemPtr[NUM_MAX_TRANSFER_AUTOINCREMENT];
    uint16_t extMemPtrStride[NUM_MAX_TRANSFER_AUTOINCREMENT];
} BAM_DMA_OneShot_CtlArgs;

/**
*  @brief      DMA Read kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaOneShotReadKernel;

/**
*  @brief      DMA Read kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaReadOneShotKernelHelperFunc;

/**
*  @brief      DMA Read kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaReadOneShotKernelExecFunc;

/**
*  @brief      DMA Write kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaOneShotWriteKernel;

/**
*  @brief      DMA Write kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaWriteOneShotKernelHelperFunc;

/**
*  @brief      DMA Write kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaWriteOneShotKernelExecFunc;

#endif /* BAM_DMA_ONESHOT_NODE_H_ */

