/*
 *******************************************************************************
 *
 * BAM Auto increment DMA node
 *
 *  Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bam_dma_custom_yuv_scalar_node.h
 *
 * @brief
 *
 * @version 0.1 (Nov 2014) : First version of dma node for YUV scalar DMA source
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_YUV_SCALAR_DMA_READ_NODE_H_
#define BAM_DMA_YUV_SCALAR_DMA_READ_NODE_H_

#include "bam_types.h"
#include "eve_edma_bam_interface.h"
#include "edma_utils_context_size.h"

#define NUM_OUT_BLOCKS (5)

typedef struct 
{
  uint16_t srcBlockWidth;       
  uint16_t srcBlockPitch;        
  uint16_t srcBlockHeight;       
  uint16_t dstBlockWidth;       
  uint16_t dstBlockHeight;       
  uint8_t  numTaps;       
} BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args;

typedef struct 
{
  uint8_t  * imBaseAddr;
  uint16_t * xIdxBaseAddr;
  uint8_t  * xfracBaseAddr;
  uint16_t * yIdxBaseAddr;
  uint8_t  * yfracBaseAddr;
  uint16_t   xInfoPitch;
  uint16_t   yInfoPitch;
  uint16_t   imPitch;
  uint16_t   imWidth;
  uint16_t   imHeight;
  uint16_t   outWidth;
  uint16_t   outHeight;
  uint16_t   outStartX;
  uint16_t   outStartY;
  uint16_t   scaleRatioQ12;
  uint8_t    inputDataType;    /*0 --> Luma 1--> UV interleaved         */
}BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_ctrl_args;

#define NUM_MAX_SCATTER_GATHER_TRANSFERS (5)

typedef struct 
{
    uint8_t   autoIncr[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args nodeArgs;
    uint8_t   scatterGatherContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
    uint8_t  pingPong;
    uint16_t blkIdxX;
    uint16_t blkIdxY;
    BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_ctrl_args ctrlArgs;
    uint8_t  *srcAddrList[2][NUM_MAX_SCATTER_GATHER_TRANSFERS];
} BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomYUVScalarReadNodeKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomYUVScalarReadNodeKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomYUVScalarReadNodeKernelExecFunc;
extern BAM_KernelInfo           gBAM_TI_YUVScalar_DmaAutoIncrementWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomYUVScalarWriteNodeKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomYUVScalarWriteNodeKernelExecFunc;

BAM_Status BAM_DMA_YUV_Scalar_dmaReadGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);


BAM_Status BAM_DMA_YUV_Scalar_dmaReadSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);


BAM_Status BAM_DMA_YUV_Scalar_frameInitInChannel(void * edmaContext);


BAM_Status BAM_DMA_YUV_Scalar_triggerInChannel(void * edmaContext);


BAM_Status BAM_DMA_YUV_Scalar_waitInChannel(void * edmaContext);

BAM_Status BAM_DMA_YUV_Scalar_dmaReadUpdateDDRptr(void * edmaContext,  void * params);


BAM_Status BAM_YUCScalar_dmaWriteSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                                                    const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                                                    uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);
BAM_Status BAM_YUVScalar_dmaWriteGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                                                                 uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);


#endif /* BAM_DMA_YUV_SCALAR_DMA_READ_NODE_H_ */

