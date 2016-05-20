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
 *  bam_dma_custom_yuv_scalar_node.c
 *
 * @brief
 *
 * @version 0.1 (Jan 2014) : First version of eve edma utils function
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include "evealgframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_autoincrement_1d.h"

#include "edma_utils_scatterGather.h"

#include "bam_dma_autoincrement_node.h"
#include "bam_dma_custom_yuv_scalar_node.h"
#include "bam_common.h"
#include "edma_utils_context_size.h"

#define Q_FORMATE_SCALE_RATIO                   (12)

BAM_Status BAM_DMA_YUV_Scalar_dmaReadGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
#if (!VCOP_HOST_EMULATION)
    const BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args *initParams = edmaArgs;
#else
    const BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args *initParams = (const BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args *)edmaArgs;
#endif
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((initParams==NULL) || (numRecInternal==NULL) || (numRecOutputDataBlock==NULL))
    {
        PRINTF("Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    if(memRecOutputDataBlock==NULL)
    {
        PRINTF("Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
        memRecOutputDataBlock[0].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[0].size = (initParams->srcBlockPitch*initParams->srcBlockHeight);

        memRecOutputDataBlock[1].space = BAM_MEMSPACE_IBUFHA;
        memRecOutputDataBlock[1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[1].size = initParams->numTaps*initParams->dstBlockWidth * sizeof(uint16_t);

        memRecOutputDataBlock[2].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[2].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[2].size = initParams->numTaps*initParams->dstBlockWidth  * sizeof(uint8_t);

        memRecOutputDataBlock[3].space = BAM_MEMSPACE_IBUFHA;
        memRecOutputDataBlock[3].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[3].size = initParams->numTaps*initParams->dstBlockHeight * sizeof(uint16_t);

        memRecOutputDataBlock[4].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[4].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[4].size = initParams->numTaps*initParams->dstBlockHeight * sizeof(uint8_t);

        *numRecOutputDataBlock = 5;
        *numRecInternal = 0;
    }
    return errCode;
}

BAM_Status BAM_DMA_YUV_Scalar_dmaReadSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
#if (!VCOP_HOST_EMULATION)
    const BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args *initParams= edmaArgs;
#else
    const BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args *initParams= (const BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args*)edmaArgs;
#endif

    BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context * context = (BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context *)edmaContext;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    context->nodeArgs = *initParams;
    context->pOutBlock[0]          = (void *)memRecOutputDataBlock[0]->base;
    context->pOutBlock[1]          = (void *)memRecOutputDataBlock[1]->base;
    context->pOutBlock[2]          = (void *)memRecOutputDataBlock[2]->base;
    context->pOutBlock[3]          = (void *)memRecOutputDataBlock[3]->base;
    context->pOutBlock[4]          = (void *)memRecOutputDataBlock[4]->base;

    return errCode;
}

BAM_Status BAM_DMA_YUV_Scalar_frameInitInChannel(void * edmaContext)
{
  BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context * context = (BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context *)edmaContext;
  int32_t                 status = 0;
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint8_t                *srcPtrList[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint8_t                *dstPtrList[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                blkWidth[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                blkHeight[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                srcStride[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                dstStride[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  EDMA_UTILS_scattherGather_transferProperties inBlksScatterGatherTransferContext;

  if (edmaContext==NULL)
  {
    PRINTF("Context Structure pointer is NULL\n");
    errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
  }
  else
  {

    /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();


    /*Populate the scatter gather transfer fields to enable initialization of scatter gather transfer*/
    inBlksScatterGatherTransferContext.dmaQueNo        = 0;
    inBlksScatterGatherTransferContext.srcPtr          = srcPtrList;
    inBlksScatterGatherTransferContext.dstPtr          = dstPtrList;
    inBlksScatterGatherTransferContext.blkWidth        = blkWidth;
    inBlksScatterGatherTransferContext.blkHeight       = blkHeight;
    inBlksScatterGatherTransferContext.srcPtrStride    = srcStride;
    inBlksScatterGatherTransferContext.dstPtrStride    = dstStride;


    srcPtrList[0]  = (uint8_t*)(void*)context->ctrlArgs.imBaseAddr;
    dstPtrList[0]  = (uint8_t*)(void*)context->pOutBlock[0];
    blkWidth  [0]  = context->nodeArgs.srcBlockWidth;
    blkHeight [0]  = context->nodeArgs.srcBlockHeight;
    srcStride [0]  = context->ctrlArgs.imPitch;
    dstStride [0]  = context->nodeArgs.srcBlockPitch;



    srcPtrList[1]  = (uint8_t*)(void*)context->ctrlArgs.xIdxBaseAddr;
    dstPtrList[1]  = (uint8_t*)(void*)context->pOutBlock[1];
    blkWidth  [1]  = 2*(context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType);
    blkHeight [1]  = context->nodeArgs.numTaps;
    srcStride [1]  = 2*context->ctrlArgs.xInfoPitch;
    dstStride [1]  = 2*(context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType);


    srcPtrList[2]  = (uint8_t*)(void*)context->ctrlArgs.xfracBaseAddr;
    dstPtrList[2]  = (uint8_t*)(void*)context->pOutBlock[2];
    blkWidth  [2]  = (context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType);
    blkHeight [2]  = context->nodeArgs.numTaps;
    srcStride [2]  = context->ctrlArgs.xInfoPitch;
    dstStride [2]  = (context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType);


    srcPtrList[3]  = (uint8_t*)(void*)context->ctrlArgs.yIdxBaseAddr;
    dstPtrList[3]  = (uint8_t*)(void*)context->pOutBlock[3];
    blkWidth  [3]  = 2*context->nodeArgs.dstBlockHeight;
    blkHeight [3]  = context->nodeArgs.numTaps;
    srcStride [3]  = 2*context->ctrlArgs.yInfoPitch;
    dstStride [3]  = 2*context->nodeArgs.dstBlockHeight;


    srcPtrList[4]  = (uint8_t*)(void*)context->ctrlArgs.yfracBaseAddr;
    dstPtrList[4]  = (uint8_t*)(void*)context->pOutBlock[4];
    blkWidth  [4]  = context->nodeArgs.dstBlockHeight;
    blkHeight [4]  = context->nodeArgs.numTaps;
    srcStride [4]  = context->ctrlArgs.yInfoPitch;
    dstStride [4]  = context->nodeArgs.dstBlockHeight;

    context->pingPong = 0;


    context->srcAddrList[0][0] = (uint8_t*)(void*)context->ctrlArgs.imBaseAddr;
    context->srcAddrList[0][1] = (uint8_t*)(void*)context->ctrlArgs.xIdxBaseAddr;
    context->srcAddrList[0][2] = (uint8_t*)(void*)context->ctrlArgs.xfracBaseAddr;
    context->srcAddrList[0][3] = (uint8_t*)(void*)context->ctrlArgs.yIdxBaseAddr;
    context->srcAddrList[0][4] = (uint8_t*)(void*)context->ctrlArgs.yfracBaseAddr;


    context->blkIdxX  = 0;
    context->blkIdxY  = 0;

    status = EDMA_UTILS_scattherGather_init(context->scatterGatherContext, &inBlksScatterGatherTransferContext, (uint8_t)NUM_MAX_SCATTER_GATHER_TRANSFERS);
    if ( status != 0 )
    {
      errCode = DMANODE_EDMA_ERR_FAILED;
    }

    EDMA_UTILS_scattherGather_configure(context->scatterGatherContext);
  }
  return errCode;
}

BAM_Status BAM_DMA_YUV_Scalar_triggerInChannel(void * edmaContext)
{
    BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context * context = (BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context *)edmaContext;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Compute the src address*/

    EDMA_UTILS_scattherGather_updateSrcNtrigger(context->scatterGatherContext, (uint8_t *const *)context->srcAddrList[context->pingPong]);

    return errCode;
}

BAM_Status BAM_DMA_YUV_Scalar_waitInChannel(void * edmaContext)
{
    BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context * context = (BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context *)edmaContext;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint16_t srcY, srcX;
    uint32_t offsetY, offsetX;
    context->blkIdxX++;

    if((context->blkIdxX * context->nodeArgs.dstBlockWidth) >= context->ctrlArgs.outWidth)
    {
      context->blkIdxX = 0;
      context->blkIdxY++;
    }

    context->pingPong ^= 1U;
    offsetY = context->ctrlArgs.outStartY *  context->ctrlArgs.scaleRatioQ12;
    offsetY = offsetY >> Q_FORMATE_SCALE_RATIO;

    offsetX = context->ctrlArgs.outStartX *  context->ctrlArgs.scaleRatioQ12;
    offsetX = offsetX >> Q_FORMATE_SCALE_RATIO;

    srcY = (uint16_t)((((context->blkIdxY * context->nodeArgs.dstBlockHeight) + context->ctrlArgs.outStartY) *  context->ctrlArgs.scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO);
    srcY -= (uint16_t)offsetY;
    srcX = (uint16_t)((((context->blkIdxX * (context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType))  + context->ctrlArgs.outStartX) * context->ctrlArgs.scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO);
    srcX -= (uint16_t)offsetX;
    srcX = srcX << context->ctrlArgs.inputDataType;
  
    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    context->srcAddrList[context->pingPong][0] = (uint8_t*)((uint8_t*)context->ctrlArgs.imBaseAddr       + (((uint32_t)srcY*context->ctrlArgs.imPitch)+srcX));
    context->srcAddrList[context->pingPong][1] = (uint8_t*)(void *)(context->ctrlArgs.xIdxBaseAddr   + (context->blkIdxX * (context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType)));
    context->srcAddrList[context->pingPong][2] = (uint8_t*)((uint8_t*)context->ctrlArgs.xfracBaseAddr + (context->blkIdxX * (context->nodeArgs.dstBlockWidth >> context->ctrlArgs.inputDataType)));
    context->srcAddrList[context->pingPong][3] = (uint8_t*)(void *)(context->ctrlArgs.yIdxBaseAddr   + (context->blkIdxY * context->nodeArgs.dstBlockHeight));
    context->srcAddrList[context->pingPong][4] = (uint8_t*)((uint8_t*)context->ctrlArgs.yfracBaseAddr + (context->blkIdxY * context->nodeArgs.dstBlockHeight));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    EDMA_UTILS_scattherGather_wait(context->scatterGatherContext);
    return errCode;
}
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
BAM_Status BAM_DMA_YUV_Scalar_dmaReadUpdateDDRptr(void * edmaContext,  void * params)
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
{
  DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
  BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context * context   = (BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context *)edmaContext;
  context->ctrlArgs = *(BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_ctrl_args*)params;
  return errCode;
}


BAM_Status BAM_YUCScalar_dmaWriteSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
                                                    const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
                                                    uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
#if (!VCOP_HOST_EMULATION)
  const EDMA_UTILS_autoIncrement_initParam *initParams= edmaArgs;
#else
  const EDMA_UTILS_autoIncrement_initParam *initParams= (const EDMA_UTILS_autoIncrement_initParam*)edmaArgs;
#endif

  EDMA_UTILS_autoIncrement_initParam initParamsLocal = *initParams;


  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  int32_t         status = 0;

  if((memRecInputDataBlock !=NULL) && (initParamsLocal.transferType == EDMA_UTILS_TRANSFER_INOUT) )
  {

    initParamsLocal.transferProp[0].interMemPtr = (uint8_t *)(void*)memRecInputDataBlock[0]->base;
  }
  status = EDMA_UTILS_autoIncrement_init(edmaContext, &initParamsLocal);


  if ( status != 0 )
  {
    errCode = DMANODE_EDMA_ERR_FAILED;
  }

  return errCode;
}
BAM_Status BAM_YUVScalar_dmaWriteGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
                                                                 uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
  DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
  *numRecOutputDataBlock = 0;
  *numRecInternal = 0;

  return errCode;
}

BAM_KernelInfo gBAM_TI_dmaCustomYUVScalarReadNodeKernel =
{
    0,                                    /*kernelId*/
    sizeof(BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Context),
    sizeof(BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args),
    BAM_EVE_ARP32,                      /*coreType*/
    BAM_NODE_SOURCE,                    /*nodeType*/
    0,                                  /*numInputDataBlocks */
    MAX_NODE_CHANNELS,                  /*numOutputDataBlocks */
    0                                   /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_dmaCustomYUVScalarReadNodeKernelHelperFunc =
{
    &BAM_DMA_YUV_Scalar_dmaReadGetMemRecFunc, 
    &BAM_DMA_YUV_Scalar_dmaReadSetMemRecFunc
};


BAM_KernelExecFuncDef gBAM_TI_dmaCustomYUVScalarReadNodeKernelExecFunc =
{
    NULL,
     &BAM_DMA_YUV_Scalar_frameInitInChannel,
     &BAM_DMA_YUV_Scalar_triggerInChannel,
     &BAM_DMA_YUV_Scalar_waitInChannel,
     &BAM_DMA_YUV_Scalar_dmaReadUpdateDDRptr,
    NULL
};


BAM_KernelInfo gBAM_TI_YUVScalar_DmaAutoIncrementWriteKernel =
{
    0,                                    /*kernelId*/
    0,
    sizeof(EDMA_UTILS_autoIncrement_initParam),
    BAM_EVE_ARP32,      /*coreType*/
    BAM_NODE_SINK,      /*nodeType*/
    MAX_NODE_CHANNELS,  /*numInputDataBlocks */
    0,                  /*numOutputDataBlocks */
    1                   /*numRecInternal */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaCustomYUVScalarWriteNodeKernelHelperFunc =
{
     &BAM_YUVScalar_dmaWriteGetMemRecFunc, 
     &BAM_YUCScalar_dmaWriteSetMemRecFunc
};

