/*
 *******************************************************************************
 *
 * BAM DMA node for Pyramid LK Tracker
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
 */

/**
 *****************************************************************************
 * @file
 *  bam_pyramid_lk_tracker_dma_node.h
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of dma node for pyramid lk tracker
 *
 *****************************************************************************
 */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_PYRAMID_LK_TRACKER_DMA_NODE_H_
#define BAM_PYRAMID_LK_TRACKER_DMA_NODE_H_

#include "bam_types.h"
#include "eve_edma_bam_interface.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_context_size.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"

/*Limited by the number of param entries available for EDMA programming*/
#define VCOP_LK_MAX_NUM_KEY_PER_CALL     (16)
#define NUM_MAX_SCATTER_GATHER_TRANSFERS      (VCOP_LK_MAX_NUM_KEY_PER_CALL*2)
#define VCOP_LK_PATCH_WIDTH          (7) /* 7x7*/

typedef struct
{
  uint8_t *  currBaseAddr;
  uint8_t *  prevBaseAddr;
  uint16_t  imPitch;
  uint16_t  imWidth;
  uint16_t  imHeight;
  uint16_t  numKeyPoints;
  uint16_t  numValidKeyPoints;
  uint8_t   currLevel;
  uint8_t   maxItersLK;
  uint16_t  minErrValue;
  uint8_t   searchRange;
  uint8_t*  srcAddrList[2][2*VCOP_LK_MAX_NUM_KEY_PER_CALL];
  uint8_t *  prevXYAddr[2];
  uint8_t *  cornerListInXY;
  uint8_t *  cornerListOutXY;
  uint8_t *  cornerListErrMeasure;
}EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args;

typedef struct
{
    uint8_t     *extMemPtr;
    uint16_t    extMemPtrStride;
}EDMA_UTILS_pyramidlktracker_transfer_updatePrams;
typedef struct
{
    EDMA_UTILS_pyramidlktracker_transfer_updatePrams updateParams[2];
}EDMA_UTILS_pyramidlktracker_tranfer_params;

typedef struct
{
  uint16_t  imPitch;
  uint16_t  imWidth;
  uint16_t  imHeight;
  uint16_t  numKeyPoints;
  uint16_t  numValidKeyPoints;
  uint8_t   currLevel;
  uint8_t   maxItersLK;
  uint16_t  minErrValue;
  uint8_t   searchRange;
  uint8_t * cornerListInXY;
  uint8_t * cornerListOutXY;
  uint8_t * cornerListErrMeasure;
  EDMA_UTILS_pyramidlktracker_tranfer_params srcNodeParams;
  EDMA_UTILS_pyramidlktracker_tranfer_params sinkNodeParams;
}EDMA_UTILS_pyramidlktracker_dma_ctrl_args;

typedef struct
{
    uint8_t   autoIncrContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    uint8_t   scatterGatherContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];

    uint8_t   numKeyPointsProcessedPerCall;
    uint16_t  totalKeyPointsCompute;
    uint8_t   numScatterGatherTransfers;
    uint16_t  prevFrmblkWidth;
    uint16_t  prevFrmblkHeight;
    uint16_t  prevFrmsrcPtrStride;
    uint16_t  prevFrmdstPtrStride;
    uint16_t  currFrmblkWidth;
    uint16_t  currFrmblkHeight;
    uint16_t  currFrmsrcPtrStride;
    uint16_t  currFrmdstPtrStride;

    uint16_t  blkIdxIn;
    uint16_t  numTotalBlks;

    uint8_t   pingPongFlag;
    uint8_t *  outDataInterMemPtr[2];

    uint8_t  *prevFrmInterMemPtr[1];
    uint8_t  *currFrmInterMemPtr[1];
    uint8_t  *iterativeLoopLAMemPtr[1];
    uint8_t  *iterativeLoopHAMemPtr[1];
    EDMA_UTILS_scattherGather_transferProperties    inBlksScatterGatherTransferContext;
    EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs;
}EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT;

typedef struct
{
    uint8_t     numKeyPointsProcessedPerCall;
    uint16_t    totalKeyPointsCompute;
    uint8_t     numScatterGatherTransfers;
    uint16_t    prevFrmblkWidth;
    uint16_t    prevFrmblkHeight;
    uint16_t    prevFrmsrcPtrStride;
    uint16_t    prevFrmdstPtrStride;
    uint16_t    currFrmblkWidth;
    uint16_t    currFrmblkHeight;
    uint16_t    currFrmsrcPtrStride;
    uint16_t    currFrmdstPtrStride;
    EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs;
}EDMA_UTILS_pyramidlktracker_dmaReadInitParam;

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaReadGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaReadSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_frameInitInChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_frameInitOutChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_dmaReadUpdateDDRptr(void * edmaContext,  void * params);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteUpdateDDRptr(void * edmaContext,  void * params);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_triggerInChannel(void * edmaContext);

int32_t BAM_DMA_PYRAMID_LK_TRACKER_waitInChannel(void * edmaContext);

uint32_t BAM_DMA_PYRAMID_LK_TRACKER_triggerOutChannel(void * edmaContext);

uint32_t BAM_DMA_PYRAMID_LK_TRACKER_waitOutChannel(void * edmaContext);

/**
*  @brief      DMA Read kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaPyramidLKTrackerReadKernel;

/**
*  @brief      DMA Read kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaReadPyramidLKTrackerKernelHelperFunc;

/**
*  @brief      DMA Read kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaReadPyramidLKTrackerKernelExecFunc;

/**
*  @brief      DMA Write kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaPyramidLKTrackerWriteKernel;

/**
*  @brief      DMA Write kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaWritePyramidLKTrackerKernelHelperFunc;

/**
*  @brief      DMA Write kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaWritePyramidLKTrackerKernelExecFunc;

#endif /* BAM_PYRAMID_LK_TRACKER_DMA_NODE_H_ */
