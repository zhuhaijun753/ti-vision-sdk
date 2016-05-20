/*
 *******************************************************************************
 *
 * BAM Auto increment DMA node
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bam_dma_autoincrement_node.h
 *
 * @brief
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Aug 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _BAM_DMA_AUTOINCREMENT_NODE_H_
#define _BAM_DMA_AUTOINCREMENT_NODE_H_

#include "bam_types.h"
#include "eve_edma_bam_interface.h"

/**
 *  @brief   Helper function that BAM will call at graph creation to query about the DMA node's memory requirements
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_getMemRecFunc(const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

/**
 *  @brief   Helper function that BAM will call at graph creation to set the DMA node's memory requirements
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_setMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

/**
 *  @brief   Initialization function that BAM will call at execution time at the beginning of each frame
 *  for input channel.
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_frameInitInChannel(void * edmaContext);

/**
 *  @brief   Initialization function that BAM will call at execution time at the beginning of each frame
 *  for output channels
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_frameInitOutChannel(void * edmaContext);

/**
 *  @brief   Input channel initialization function that BAM will call at execution time, the very first time the DMA node is used.
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_updateDDRptrInChannel(void * edmaContext,
          void *params);

/**
 *  @brief   Output channel initialization function that BAM will call at execution time, the very first time the DMA node is used.
 *
 */
BAM_Status BAM_DMA_AUTOINCREMENT_updateDDRptrOutChannel(void * edmaContext,
          void *params);



#endif /* _BAM_DMA_AUTOINCREMENT_NODE_H_ */

