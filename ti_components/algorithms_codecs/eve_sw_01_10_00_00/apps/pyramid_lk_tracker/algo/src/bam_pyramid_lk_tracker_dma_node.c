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
 *  bam_pyramid_lk_tracker_dma_node.c
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of dma node for pyramid lk tracker
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

#include "edma_utils_scatterGather.h"
#include "bam_pyramid_lk_tracker_dma_node.h"
#include "bam_common.h"

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaReadGetMemRecFunc(const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
#if (!VCOP_HOST_EMULATION)
    const EDMA_UTILS_pyramidlktracker_dmaReadInitParam *initParams = edmaArgs;
#else
    const EDMA_UTILS_pyramidlktracker_dmaReadInitParam *initParams = (const EDMA_UTILS_pyramidlktracker_dmaReadInitParam *)edmaArgs;
#endif

    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((initParams==NULL) || (numRecInternal==NULL) || (numRecOutputDataBlock==NULL))
    {
        PRINTF("Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    else if(memRecOutputDataBlock==NULL)
    {
        PRINTF("Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    else if(initParams->numScatterGatherTransfers > NUM_MAX_SCATTER_GATHER_TRANSFERS)
    {
        PRINTF("Num of transfer Requested(= %d) is greater than max number \n",initParams->numScatterGatherTransfers);
        errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
    }

    else /* if(errCode == DMANODE_EDMA_ERR_SUCCESS)*/
    {
        /*Request memory in image buffers for holding input blocks from previous frame*/
        memRecOutputDataBlock[0].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[0].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[0].size = (initParams->numKeyPointsProcessedPerCall)*(initParams->prevFrmblkWidth*initParams->prevFrmblkHeight);

        /*Request memory in image buffers for holding input blocks from current frame*/
        memRecOutputDataBlock[1].space = BAM_MEMSPACE_IBUFHA;
        memRecOutputDataBlock[1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[1].size = (initParams->numKeyPointsProcessedPerCall)*(initParams->currFrmblkWidth*initParams->currFrmblkHeight);

        /*Request internal memory for holding the previous frame XY coordinates*/
        memRecOutputDataBlock[2].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[2].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[2].size = initParams->numKeyPointsProcessedPerCall*4;

        /*Request scratch memory in IBUFLA to be used by the iterative LK loop*/
        memRecOutputDataBlock[3].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[3].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[3].size = 2048;

        /*Request scratch memory in IBUFLA to be used by the iterative LK loop*/
        memRecOutputDataBlock[4].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[4].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[4].size = 2048;

        *numRecOutputDataBlock = 5;
        *numRecInternal = 0;
    }
    return errCode;
}

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaReadSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
#if (!VCOP_HOST_EMULATION)
    const EDMA_UTILS_pyramidlktracker_dmaReadInitParam *initParams= edmaArgs;
#else
    const EDMA_UTILS_pyramidlktracker_dmaReadInitParam *initParams= (const EDMA_UTILS_pyramidlktracker_dmaReadInitParam*)edmaArgs;
#endif
  
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext==NULL)
    {
        PRINTF("Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }
    else if (memRecOutputDataBlock == NULL)
    {
       errCode = DMANODE_EDMA_ERR_FAILED;
    }
    else /* (errCode == DMANODE_EDMA_ERR_SUCCESS) */ 
    {
        /* Reset globalStateStruct for the first time for IN channels before configuring EDMA */
        EDMA_UTILS_globalReset();
        
        context->numKeyPointsProcessedPerCall   = initParams->numKeyPointsProcessedPerCall;
        context->totalKeyPointsCompute          = initParams->totalKeyPointsCompute;
        context->numScatterGatherTransfers      = initParams->numScatterGatherTransfers;
        context->prevFrmblkWidth                = initParams->prevFrmblkWidth;
        context->prevFrmblkHeight               = initParams->prevFrmblkHeight;
        context->prevFrmsrcPtrStride            = initParams->prevFrmsrcPtrStride;
        context->prevFrmdstPtrStride            = initParams->prevFrmdstPtrStride;
        context->currFrmblkWidth                = initParams->currFrmblkWidth;
        context->currFrmblkHeight               = initParams->currFrmblkHeight;
        context->currFrmsrcPtrStride            = initParams->currFrmsrcPtrStride;
        context->currFrmdstPtrStride            = initParams->currFrmdstPtrStride;
        context->ctrlArgs                       = initParams->ctrlArgs;


        context->prevFrmInterMemPtr[0]          = (uint8_t *)memRecOutputDataBlock[0]->base;
        context->currFrmInterMemPtr[0]          = (uint8_t *)memRecOutputDataBlock[1]->base;
        context->ctrlArgs->prevXYAddr[0]        = (uint8_t *)memRecOutputDataBlock[2]->base;
        context->iterativeLoopLAMemPtr[0]       = (uint8_t *)memRecOutputDataBlock[3]->base;
        context->iterativeLoopHAMemPtr[0]       = (uint8_t *)memRecOutputDataBlock[4]->base;
#if (!VCOP_HOST_EMULATION)
        /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
        /* Pointer is used in arithmetic or array index expression */
        /* Deviation allowed since, this same address needs to be accessed with an offset  */
        context->ctrlArgs->prevXYAddr[1]        = (context->ctrlArgs->prevXYAddr[0] + 0x20000U);
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
#else
        context->ctrlArgs->prevXYAddr[1]        = context->ctrlArgs->prevXYAddr[0];
#endif
    }
    return errCode;
}

int32_t BAM_DMA_PYRAMID_LK_TRACKER_frameInitInChannel(void * edmaContext)
{
  EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
  int32_t                 status = 0;
  uint32_t                transferCnt = 0;
  int32_t                errCode = DMANODE_EDMA_ERR_SUCCESS;
  uint8_t                *dstPtrList[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                blkWidth[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                blkHeight[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                srcStride[NUM_MAX_SCATTER_GATHER_TRANSFERS];
  uint16_t                dstStride[NUM_MAX_SCATTER_GATHER_TRANSFERS];

  uint16_t currBlkTfrWidth;
  uint16_t currBlkTfrHeight;

  currBlkTfrWidth     = (context->ctrlArgs->searchRange*2U) + (uint16_t)VCOP_LK_PATCH_WIDTH;
  currBlkTfrWidth     = (uint16_t)((currBlkTfrWidth + 1U) & (uint16_t)(~1U));
  currBlkTfrHeight    = (context->ctrlArgs->searchRange*2U) + (uint16_t)VCOP_LK_PATCH_WIDTH;


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
    context->inBlksScatterGatherTransferContext.dmaQueNo        = 0;
    context->inBlksScatterGatherTransferContext.srcPtr          = (uint8_t **)(context->ctrlArgs->srcAddrList[0]);
    context->inBlksScatterGatherTransferContext.dstPtr          = dstPtrList;
    context->inBlksScatterGatherTransferContext.blkWidth        = blkWidth;
    context->inBlksScatterGatherTransferContext.blkHeight       = blkHeight;
    context->inBlksScatterGatherTransferContext.srcPtrStride    = srcStride;
    context->inBlksScatterGatherTransferContext.dstPtrStride    = dstStride;

    for(transferCnt = 0 ; transferCnt < context->numKeyPointsProcessedPerCall; transferCnt++)
    {
      /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
      /* Pointer is used in arithmetic or array index expression */
      /* Deviation allowed since, this same address needs to be accessed with an offset  */
      dstPtrList[transferCnt] = (context->prevFrmInterMemPtr[0] + (transferCnt * context->prevFrmblkWidth));
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
      blkWidth[transferCnt]   = context->prevFrmblkWidth;
      blkHeight[transferCnt]  = context->prevFrmblkHeight;
      srcStride[transferCnt]  = context->prevFrmsrcPtrStride;
      dstStride[transferCnt]  = context->prevFrmdstPtrStride;
    }

    for(transferCnt = context->numKeyPointsProcessedPerCall ; transferCnt < context->numScatterGatherTransfers; transferCnt++)
    {
      /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
      /* Pointer is used in arithmetic or array index expression */
      /* Deviation allowed since, this same address needs to be accessed with an offset  */
      dstPtrList[transferCnt] = (context->currFrmInterMemPtr[0] + ((transferCnt - context->numKeyPointsProcessedPerCall) * context->currFrmdstPtrStride * context->currFrmblkHeight));
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
      blkWidth[transferCnt]   = currBlkTfrWidth; 
      blkHeight[transferCnt]  = currBlkTfrHeight; 
      srcStride[transferCnt]  = context->currFrmsrcPtrStride;
      dstStride[transferCnt]  = context->currFrmdstPtrStride;
    }

    /* Reset internal variables of context */
    context->pingPongFlag = 0;
    context->blkIdxIn = 0;
    context->numTotalBlks = (context->totalKeyPointsCompute/context->numKeyPointsProcessedPerCall);

    status = EDMA_UTILS_scattherGather_init(context->scatterGatherContext, &context->inBlksScatterGatherTransferContext, context->numScatterGatherTransfers);
    if ( status != 0 )
    {
      errCode = DMANODE_EDMA_ERR_FAILED;
    }
    status = EDMA_UTILS_scattherGather_configure(context->scatterGatherContext);
  }


  return errCode;
}

int32_t BAM_DMA_PYRAMID_LK_TRACKER_triggerInChannel(void * edmaContext)
{
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    int32_t         errCode = DMANODE_EDMA_ERR_SUCCESS;

    EDMA_UTILS_scattherGather_updateSrcNtrigger(context->scatterGatherContext, context->inBlksScatterGatherTransferContext.srcPtr);

    return errCode;
}

int32_t BAM_DMA_PYRAMID_LK_TRACKER_waitInChannel(void * edmaContext)
{
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    int32_t         errCode = DMANODE_EDMA_ERR_SUCCESS;

    EDMA_UTILS_scattherGather_wait(context->scatterGatherContext);
    context->blkIdxIn++;
    context->inBlksScatterGatherTransferContext.srcPtr = ((uint8_t **)(context->ctrlArgs->srcAddrList[context->blkIdxIn&1U]));

    return errCode;
}

int32_t BAM_DMA_PYRAMID_LK_TRACKER_dmaReadUpdateDDRptr(void * edmaContext,  void * params)
{
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    EDMA_UTILS_pyramidlktracker_dmaReadNode_ctrl_args * ctrlArgs = context->ctrlArgs;
    int32_t         errCode = DMANODE_EDMA_ERR_SUCCESS;
    EDMA_UTILS_pyramidlktracker_dma_ctrl_args *bam_ctrl_args = (EDMA_UTILS_pyramidlktracker_dma_ctrl_args*) params;
    if (edmaContext==NULL)
    {
        PRINTF("Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }
    else
    {
      context->currFrmsrcPtrStride   = bam_ctrl_args->srcNodeParams.updateParams[0].extMemPtrStride;
      context->prevFrmsrcPtrStride   = bam_ctrl_args->srcNodeParams.updateParams[1].extMemPtrStride;
      ctrlArgs->currBaseAddr         = (uint8_t *)bam_ctrl_args->srcNodeParams.updateParams[0].extMemPtr;
      ctrlArgs->prevBaseAddr         = (uint8_t *)bam_ctrl_args->srcNodeParams.updateParams[1].extMemPtr;

      ctrlArgs->imPitch              = bam_ctrl_args->imPitch             ;
      ctrlArgs->imWidth              = bam_ctrl_args->imWidth             ;
      ctrlArgs->imHeight             = bam_ctrl_args->imHeight            ;
      ctrlArgs->numKeyPoints         = bam_ctrl_args->numKeyPoints        ;
      ctrlArgs->numValidKeyPoints    = bam_ctrl_args->numValidKeyPoints   ;
      ctrlArgs->currLevel            = bam_ctrl_args->currLevel           ;
      ctrlArgs->maxItersLK           = bam_ctrl_args->maxItersLK          ;
      ctrlArgs->minErrValue          = bam_ctrl_args->minErrValue         ;
      ctrlArgs->searchRange          = bam_ctrl_args->searchRange         ;
      ctrlArgs->cornerListInXY       = bam_ctrl_args->cornerListInXY      ;
      ctrlArgs->cornerListOutXY      = bam_ctrl_args->cornerListOutXY     ;
      ctrlArgs->cornerListErrMeasure = bam_ctrl_args->cornerListErrMeasure;
    }

    return errCode;
}

/*Output DMA Write Node Functions*/
/*getMemRecFunc & setMemRecFunc implementations for DMA Write Node which is using 1D auto increment*/
BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteGetMemRecFunc(const void *edmaArgs, BAM_MemRec *memRecInternal, BAM_MemRec *memRecOutputDataBlock,
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
#if (!VCOP_HOST_EMULATION)
    const EDMA_UTILS_autoIncrement_initParam *initParams = edmaArgs;
#else
    const EDMA_UTILS_autoIncrement_initParam *initParams = (const EDMA_UTILS_autoIncrement_initParam *)edmaArgs;
#endif
    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;
    uint32_t        numTransfer = 0;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((initParams==NULL) || (numRecInternal==NULL) || (numRecOutputDataBlock==NULL))
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    else if((memRecOutputDataBlock==NULL))
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Argument pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
    }

    else if (initParams->transferType != EDMA_UTILS_TRANSFER_INOUT )
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Transfer Types!!\n");
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    else if(initParams->numOutTransfers > MAX_NODE_CHANNELS)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Num of transfer Requested(= %d) is greater than max number \n",numTransfer);
        errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
    }

    else  /* (errCode == DMANODE_EDMA_ERR_SUCCESS) */
    {
        numTransfer = initParams->numOutTransfers;
        for(transferCnt = 0 ; ((transferCnt < numTransfer) && (errCode == DMANODE_EDMA_ERR_SUCCESS)); transferCnt++)
        {
            if( (initParams->transferProp[transferCnt].roiWidth <= 0U) ||
                (initParams->transferProp[transferCnt].roiHeight <= 0U) )
            {
                PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Image Dimentions!!\n");
                errCode = DMANODE_EDMA_ERR_INVALID_IMAGE_DIM;
            }

            if( (initParams->transferProp[transferCnt].blkWidth <= 0U) ||
                (initParams->transferProp[transferCnt].blkHeight <= 0U) )
            {
                PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Invalid Image Dimentions!!\n");
                errCode = DMANODE_EDMA_ERR_INVALID_BLOCK_DIM;
            }
        }

        if(errCode == DMANODE_EDMA_ERR_SUCCESS)
        {
            *numRecOutputDataBlock = 0;
            *numRecInternal = 0;
        }
    }

    return errCode;
}

BAM_Status BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteSetMemRecFunc(const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
#if (!VCOP_HOST_EMULATION)
    const EDMA_UTILS_autoIncrement_initParam *initParams= edmaArgs;
#else
    const EDMA_UTILS_autoIncrement_initParam *initParams= (const EDMA_UTILS_autoIncrement_initParam*)edmaArgs;
#endif
    EDMA_UTILS_autoIncrement_initParam initParamsLocal = *initParams;

    BAM_Status errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t        transferCnt = 0;
    int32_t         status = 0;
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;


    if (edmaContext==NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    if(errCode == DMANODE_EDMA_ERR_SUCCESS)
    {
        if( (memRecInputDataBlock!=NULL) && (initParamsLocal.transferType == EDMA_UTILS_TRANSFER_INOUT) )
        {
            if(initParamsLocal.numOutTransfers > 2)
            {
                PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Not enough channels available for transfer\n");
                errCode = DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS;
            }

            if(errCode == DMANODE_EDMA_ERR_SUCCESS)
            {
                for(transferCnt = 0 ; transferCnt < initParamsLocal.numOutTransfers; transferCnt++)
                {
                    /* ------------------------------------------------------------- */
                    /* Set internal memory pointers                                  */
                    /* ------------------------------------------------------------- */
                    if(memRecInputDataBlock[transferCnt]->base==NULL)
                    {
                        errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
                        break;
                    }
                    initParamsLocal.transferProp[transferCnt].interMemPtr = (uint8_t *)memRecInputDataBlock[transferCnt]->base;
                    context->outDataInterMemPtr[transferCnt] = (uint8_t *)memRecInputDataBlock[transferCnt]->base;
                }
            }
        }
        else
        {
            errCode = DMANODE_EDMA_ERR_FAILED;
        }
    }
    if ( errCode == DMANODE_EDMA_ERR_SUCCESS )
    {
        status = EDMA_UTILS_autoIncrement_init(edmaContext, &initParamsLocal);
    }

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;
}

int32_t BAM_DMA_PYRAMID_LK_TRACKER_frameInitOutChannel(void * edmaContext)
{
    int32_t                 status = 0;
    int32_t         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (edmaContext==NULL)
    {
        PRINTF("BAM_DMA_AUTOINCREMENT ERROR : Context Structure pointer is NULL\n");
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
    }

    status = EDMA_UTILS_autoIncrement_configure(edmaContext, EDMA_UTILS_TRANSFER_INOUT);

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }

    return errCode;
}

uint32_t BAM_DMA_PYRAMID_LK_TRACKER_triggerOutChannel(void * edmaContext)
{
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    uint32_t         errCode = DMANODE_EDMA_ERR_SUCCESS;

    errCode = (uint32_t)EDMA_UTILS_autoIncrement_triggerOutChannel((void *)context->autoIncrContext);

    return errCode;
}

uint32_t BAM_DMA_PYRAMID_LK_TRACKER_waitOutChannel(void * edmaContext)
{
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    uint32_t         errCode = DMANODE_EDMA_ERR_SUCCESS;

    EDMA_UTILS_autoIncrement_waitOutChannel((void *)context->autoIncrContext);

    return errCode;
}

int32_t BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteUpdateDDRptr(void * edmaContext,  void * params)
{
    EDMA_UTILS_pyramidlktracker_dma_ctrl_args *bam_ctrl_args = (EDMA_UTILS_pyramidlktracker_dma_ctrl_args*) params;
    EDMA_UTILS_autoIncrement_initParam                       dmaWriteKernelArgs;
    EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT * context = (EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT *)edmaContext;
    int32_t         status = 0;
    int32_t errCode = DMANODE_EDMA_ERR_SUCCESS;

    dmaWriteKernelArgs.transferType           = EDMA_UTILS_TRANSFER_INOUT;
    dmaWriteKernelArgs.numInTransfers         = 0;
    dmaWriteKernelArgs.numOutTransfers        = 2;
    dmaWriteKernelArgs.transferProp[0].roiWidth            = 4*context->numKeyPointsProcessedPerCall;
    dmaWriteKernelArgs.transferProp[0].roiHeight           = context->ctrlArgs->numKeyPoints/context->numKeyPointsProcessedPerCall;
    dmaWriteKernelArgs.transferProp[0].blkWidth            = 4*context->numKeyPointsProcessedPerCall;
    dmaWriteKernelArgs.transferProp[0].blkHeight           = 1;
    dmaWriteKernelArgs.transferProp[0].extBlkIncrementX    = 0;
    dmaWriteKernelArgs.transferProp[0].extBlkIncrementY    = 1;
    dmaWriteKernelArgs.transferProp[0].intBlkIncrementX    = 0;
    dmaWriteKernelArgs.transferProp[0].intBlkIncrementY    = 0;
    dmaWriteKernelArgs.transferProp[0].roiOffset           = 0;
    dmaWriteKernelArgs.transferProp[0].extMemPtr           = (uint8_t *)bam_ctrl_args->sinkNodeParams.updateParams[0].extMemPtr;
    dmaWriteKernelArgs.transferProp[0].extMemPtrStride     = context->numKeyPointsProcessedPerCall*4;
    dmaWriteKernelArgs.transferProp[0].interMemPtr         = context->outDataInterMemPtr[0];
    dmaWriteKernelArgs.transferProp[0].interMemPtrStride   = context->numKeyPointsProcessedPerCall*4;
    dmaWriteKernelArgs.transferProp[0].dmaQueNo            = 0;

    dmaWriteKernelArgs.transferProp[1].roiWidth            = 2*context->numKeyPointsProcessedPerCall;
    dmaWriteKernelArgs.transferProp[1].roiHeight           = context->ctrlArgs->numKeyPoints/context->numKeyPointsProcessedPerCall;
    dmaWriteKernelArgs.transferProp[1].blkWidth            = 2*context->numKeyPointsProcessedPerCall;
    dmaWriteKernelArgs.transferProp[1].blkHeight           = 1;
    dmaWriteKernelArgs.transferProp[1].extBlkIncrementX    = 0;
    dmaWriteKernelArgs.transferProp[1].extBlkIncrementY    = 1;
    dmaWriteKernelArgs.transferProp[1].intBlkIncrementX    = 0;
    dmaWriteKernelArgs.transferProp[1].intBlkIncrementY    = 0;
    dmaWriteKernelArgs.transferProp[1].roiOffset           = 0;
    dmaWriteKernelArgs.transferProp[1].extMemPtr           = (uint8_t *)bam_ctrl_args->sinkNodeParams.updateParams[1].extMemPtr;
    dmaWriteKernelArgs.transferProp[1].extMemPtrStride     = context->numKeyPointsProcessedPerCall*2;
    dmaWriteKernelArgs.transferProp[1].interMemPtr         = context->outDataInterMemPtr[1];
    dmaWriteKernelArgs.transferProp[1].interMemPtrStride   = context->numKeyPointsProcessedPerCall*2;
    dmaWriteKernelArgs.transferProp[1].dmaQueNo            = 0;


    status = EDMA_UTILS_autoIncrement_init(edmaContext, &dmaWriteKernelArgs);

    if ( status != 0 )
    {
        errCode = DMANODE_EDMA_ERR_FAILED;
    }
    return errCode;
}

BAM_KernelInfo gBAM_TI_dmaPyramidLKTrackerReadKernel =
{
    0,                                    /*kernelId*/
    sizeof(EDMA_UTILS_PYRAMID_LK_TRACKER_CONTEXT),
    sizeof(EDMA_UTILS_pyramidlktracker_dmaReadInitParam),
    BAM_EVE_ARP32,                      /*coreType*/
    BAM_NODE_SOURCE,                    /*nodeType*/
    0,                                  /*numInputDataBlocks */
    MAX_NODE_CHANNELS,                  /*numOutputDataBlocks */
    1                                   /*numRecInternal */
};

BAM_KernelInfo gBAM_TI_dmaPyramidLKTrackerWriteKernel =
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

BAM_KernelHelperFuncDef gBAM_TI_dmaReadPyramidLKTrackerKernelHelperFunc =
{
     &BAM_DMA_PYRAMID_LK_TRACKER_dmaReadGetMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_PYRAMID_LK_TRACKER_dmaReadSetMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelHelperFuncDef gBAM_TI_dmaWritePyramidLKTrackerKernelHelperFunc =
{
     &BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteGetMemRecFunc, /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
     &BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteSetMemRecFunc /* function to get kernel’s memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

BAM_KernelExecFuncDef gBAM_TI_dmaReadPyramidLKTrackerKernelExecFunc =
{
    NULL, &BAM_DMA_PYRAMID_LK_TRACKER_frameInitInChannel,  &BAM_DMA_PYRAMID_LK_TRACKER_triggerInChannel,
     &BAM_DMA_PYRAMID_LK_TRACKER_waitInChannel,  &BAM_DMA_PYRAMID_LK_TRACKER_dmaReadUpdateDDRptr,
    NULL
};

BAM_KernelExecFuncDef gBAM_TI_dmaWritePyramidLKTrackerKernelExecFunc =
{
    NULL, &BAM_DMA_PYRAMID_LK_TRACKER_frameInitOutChannel , &EDMA_UTILS_autoIncrement_triggerOutChannel,
    &EDMA_UTILS_autoIncrement_waitOutChannel,  &BAM_DMA_PYRAMID_LK_TRACKER_dmaWriteUpdateDDRptr,
    NULL
};
