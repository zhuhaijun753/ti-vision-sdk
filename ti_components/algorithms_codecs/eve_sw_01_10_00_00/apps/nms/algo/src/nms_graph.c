/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file      nms_graph.c
 *
 *  @brief      This file defines the functions for graph for NMS applet
 *
 *  @version 0.0 (Aug 2014) : Base version.
 */


/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "xdais_types.h"
#include "inms_ti.h"

#include "nms_alg_int.h"

#include "nms_graph_int.h"

#include "edma_utils.h"
#include "bam_dma_autoincrement_node.h"

static int32_t NMS_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);


#define SOURCE_NODE         (0)
#define NMS_TO_LIST_NODE    (1U)
#define SINK_NODE           (2U)


typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_CUSTOM_NMS_DMAREAD_NODE,
    BAM_TI_KERNELID_NMS_16S_TO_LIST,
    BAM_TI_KERNELID_CUSTOM_NMS_DMAWRITE_NODE
} BAM_NMS_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamNmsKernelHostDB[] =
{
    { &gBAM_TI_dmaCustomNmsNodeReadKernel, &gBAM_TI_dmaCustomNmsNodeReadKernelHelperFunc,
            "ti_custom_nms_dma_read", BAM_TI_KERNELID_CUSTOM_NMS_DMAREAD_NODE},

    { &gBAM_TI_nms16sToListKernel, &gBAM_TI_nms16sToListHelperFunc,
            "ti_nms_to_list_kernel", BAM_TI_KERNELID_NMS_16S_TO_LIST },


    { &gBAM_TI_dmaCustomNmsNodeWriteKernel, &gBAM_TI_dmaCustomNmsNodeWriteKernelHelperFunc,
            "ti_custom_nms_dma_write", BAM_TI_KERNELID_CUSTOM_NMS_DMAWRITE_NODE},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamNmsKernelExecFuncDB[] =
{
    { &gBAM_TI_dmaCustomNmsNodeReadKernel, &gBAM_TI_dmaCustomNmsNodeReadKernelExecFunc,
            "ti_custom_nms_dma_read", BAM_TI_KERNELID_CUSTOM_NMS_DMAREAD_NODE},

    { &gBAM_TI_nms16sToListKernel, &gBAM_TI_nms16sToListExecFunc,
              "ti_nms_to_list_kernel", BAM_TI_KERNELID_NMS_16S_TO_LIST},

    { &gBAM_TI_dmaCustomNmsNodeWriteKernel, &gBAM_TI_dmaCustomNmsNodeWriteKernelExecFunc,
            "ti_custom_nms_dma_write", BAM_TI_KERNELID_CUSTOM_NMS_DMAWRITE_NODE},
};


BAM_KernelDBdef gNms_BAM_TI_kernelDBdef =
{
    sizeof(bamNmsKernelExecFuncDB) / sizeof(bamNmsKernelExecFuncDB[0]),
    bamNmsKernelHostDB,
    bamNmsKernelExecFuncDB
};



int32_t NMS_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = NMS_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = NMS_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = NMS_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(NMS_TI_graphArgs) ;
  return 0;
}

int32_t NMS_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      NMS_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    NMS_TI_graphArgs * graphArgs = (NMS_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]= {\
            {SOURCE_NODE,           BAM_TI_KERNELID_CUSTOM_NMS_DMAREAD_NODE,  NULL},\
            {NMS_TO_LIST_NODE,      BAM_TI_KERNELID_NMS_16S_TO_LIST,          NULL},\
            {SINK_NODE,             BAM_TI_KERNELID_CUSTOM_NMS_DMAWRITE_NODE, NULL},\
            {BAM_END_NODE_MARKER,   0,                                        NULL},\
    };

    /* This is done to avoid build errors because of --gcc flag not being enable as per MISRA C */
    NODELIST[SOURCE_NODE].kernelArgs      = (void *)&graphArgs->dmaReadKernelArgs;

    BAM_EdgeParams EDGELIST[]= {\
            {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},
                            {NMS_TO_LIST_NODE, BAM_NMS_MXN_S16_TO_LIST_INPUT_BLOCK_PORT}},\

            {{NMS_TO_LIST_NODE, BAM_NMS_MXN_S16_TO_LIST_OUTPUT_XY_LIST_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT1}},\

            {{NMS_TO_LIST_NODE, BAM_NMS_MXN_S16_TO_LIST_OUTPUT_LIST_SIZE_PORT},
                            {SINK_NODE, BAM_SINK_NODE_PORT2}},\

            {{BAM_END_NODE_MARKER, 0},
                            {BAM_END_NODE_MARKER, 0}},\
    };

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    status= BAM_initKernelDB(&gNms_BAM_TI_kernelDBdef);

    if(status != BAM_S_SUCCESS)
    {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType             = BAM_EVE;
    graphCreateParams.kernelDB             = &gNms_BAM_TI_kernelDBdef;
    graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem             = graphHandle;
    graphCreateParams.graphMemSize         = NMS_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize = NMS_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem               = graphMem->graphcontext;
    graphCreateParams.extMemSize           = NMS_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc     = (BOOL)true;
    graphCreateParams.optimizeBlockDim     = (BOOL)false;

    graphArgs->createParams = createParams;

     /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc   = &NMS_TI_initKernelsArgs;
    graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    status = BAM_createGraph(&graphCreateParams, &graphHandle);
    if(status != BAM_S_SUCCESS)
    {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    /*-------------------------------------------------------------------------*/
    /* error message handling and return of error code                         */
    /*-------------------------------------------------------------------------*/
  Exit:
    if (status== BAM_E_INVALID_MEM_SIZE)
    {
      PRINTF("NMS : Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
        graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
    {
      PRINTF("NMS  : Graph construction failed!!! Decrease the value of blockWidth : or blockHeight :");
    }
    else if (status != BAM_S_SUCCESS)
    {
      PRINTF("NMS  : Graph construction failed!!!");
    }
    else
    {
      /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
    }

    return (status);
}

/*-------------------------------------------------------------------------*/
/* Function to assign DMA parameters to EDMA utilitiy                      */
/*-------------------------------------------------------------------------*/
static inline void assignDMAautoIncrementParams(
  EDMA_UTILS_autoIncrement_transferProperties * param,
  uint16_t    roiWidth,
  uint16_t    roiHeight,
  uint16_t    blkWidth,
  uint16_t    blkHeight,
  uint16_t    extBlkIncrementX,
  uint16_t    extBlkIncrementY,
  uint16_t    intBlkIncrementX,
  uint16_t    intBlkIncrementY,
  uint32_t    roiOffset,
  uint32_t    blockOffset,
  uint8_t     *extMemPtr,
  uint16_t    extMemPtrStride,
  uint8_t     *interMemPtr,
  uint16_t    interMemPtrStride,
  uint8_t     dmaQueNo
)
{
  param->roiWidth             = roiWidth;
  param->roiHeight            = roiHeight;
  param->blkWidth             = blkWidth;
  param->blkHeight            = blkHeight;
  param->extBlkIncrementX     = extBlkIncrementX;
  param->extBlkIncrementY     = extBlkIncrementY;
  param->intBlkIncrementX     = intBlkIncrementX;
  param->intBlkIncrementY     = intBlkIncrementY;
  param->roiOffset            = roiOffset;
  param->blkOffset            = blockOffset;
  param->extMemPtr            = extMemPtr;
  param->extMemPtrStride      = extMemPtrStride ;
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t NMS_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;

  NMS_TI_graphArgs              *graphArgs          = (NMS_TI_graphArgs*)args;
  BAM_DMA_CUSTOM_NMS_READ_args  *dmaReadKernelArgs  = &(graphArgs->dmaReadKernelArgs);


  NMS_TI_graphCreateParams      *createParams       = graphArgs->createParams;

  /* allocate maximum input block size */
  dmaReadKernelArgs->maxBlkWidth    = BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE *
                              createParams->inmsCreateParams->inputByteDepth;
  dmaReadKernelArgs->maxBlkHeight   = 1U;

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t NMS_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  status  = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;

}

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */


int32_t NMS_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  const NMS_TI_InArgs * inArgs,
                                  uint16_t imageWidth,
                                  uint8_t  inElemSize,
                                  uint16_t computeWidth,
                                  uint16_t computeHeight
                                  )
{
  int32_t status = BAM_S_SUCCESS;
  BAM_Nms_16s_to_list_CtrlArgs controlArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
  uint16_t        effOutImageWidth;
  uint16_t        actualImageWidth;

  actualImageWidth  = imageWidth / inElemSize;

  effOutImageWidth = CEIL(actualImageWidth - ((uint16_t)inArgs->windowWidth - (uint16_t)1) ,computeWidth);

  controlArgs.binToImgListKernelArgs.blkWidth       = actualImageWidth - ((uint16_t)inArgs->windowWidth - (uint16_t)1);
  controlArgs.binToImgListKernelArgs.blkHeight      = computeHeight;
  controlArgs.binToImgListKernelArgs.blkStride      = effOutImageWidth;
  controlArgs.binToImgListKernelArgs.frameStartX    = 0;
  controlArgs.binToImgListKernelArgs.frameStartY    = 0;
  controlArgs.binToImgListKernelArgs.outputQformat  = 0;
  controlArgs.binToImgListKernelArgs.xyOrder        = BAM_BIN_IMAGE_TO_LIST_XY;

  controlArgs.nmsMxnS16bitPackKernelArgs.computeWidth   = computeWidth;
  controlArgs.nmsMxnS16bitPackKernelArgs.computeHeight  = computeHeight;
  controlArgs.nmsMxnS16bitPackKernelArgs.winW           = inArgs->windowWidth;
  controlArgs.nmsMxnS16bitPackKernelArgs.winH           = inArgs->windowHeight;
  controlArgs.nmsMxnS16bitPackKernelArgs.inStride       = computeWidth + ((uint16_t)inArgs->windowWidth - (uint16_t)1);
  controlArgs.nmsMxnS16bitPackKernelArgs.outStride      = CEIL(effOutImageWidth, 8U);
  controlArgs.nmsMxnS16bitPackKernelArgs.threshold      = inArgs->nmsThreshold;

  status = BAM_controlNode( graphHandle, 1U, &controlArgs);

  return status;
}




int32_t NMS_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint8_t winWidth,
                                uint8_t winHeight,
                                uint8_t inElemSize,
                                uint16_t computeWidth,
                                uint16_t computeHeight,
                                const IVISION_BufDesc *inBufDesc,
                                const IVISION_BufDesc *outBufDesc,
                                uint8_t * ptrToListSize
                                )

{
    BAM_DMA_CUSTOM_NMS_READ_ctrlArgs dmaReadUpdateParams;
    BAM_DMA_CUSTOM_NMS_WRITE_ctrlArgs dmaWriteUpdateParams;
    const IVISION_BufPlanes * ivisionBufPlane;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    uint16_t effImageWidth;
    uint16_t effImageHeight;
    uint16_t blockWidth;
    uint16_t blockHeight;
    uint16_t imgWidth;
    uint16_t imgHeight;
    uint8_t * extMemPtr;

    ivisionBufPlane = &inBufDesc->bufPlanes[0];

    blockWidth  = computeWidth;
    blockHeight = computeHeight;

    imgWidth  = (uint16_t)ivisionBufPlane->frameROI.width / inElemSize;
    imgHeight = (uint16_t)ivisionBufPlane->frameROI.height;

    effImageWidth  = CEIL(imgWidth - (winWidth  - (uint16_t)1), blockWidth) + (winWidth  - (uint16_t)1);
    effImageHeight = CEIL(imgHeight - (winHeight - (uint16_t)1), blockHeight) + (winHeight - (uint16_t)1);

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    extMemPtr = (uint8_t*)ivisionBufPlane->buf + ((ivisionBufPlane->frameROI.topLeft.y) * ivisionBufPlane->width) +
                                            (ivisionBufPlane->frameROI.topLeft.x);
    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    assignDMAautoIncrementParams(&dmaReadUpdateParams.inTransferProp,
      effImageWidth * inElemSize,/* roiWidth : This will come during Process call via bufDesc */
      effImageHeight,/* roiHeight : This will come during Process call via bufDesc */
      (blockWidth  + ((uint16_t)winWidth  - (uint16_t)1U)) * inElemSize,/*blkWidth */
      blockHeight + ((uint16_t)winHeight - (uint16_t)1U),/*blkHeight*/
      blockWidth * inElemSize,/* extBlkIncrementX */
      blockHeight,/* extBlkIncrementY */
      0,/* intBlkIncrementX */
      0,/* intBlkIncrementY */
      0,/* roiOffset */
      0,/*blockOffset */
      extMemPtr,/* extMemPtr : This will come during process call */
      ivisionBufPlane->width,/* extMemPtrStride */
      NULL,/*Int Mem Ptr DMA node will be populating this field */
      (blockWidth  + ((uint16_t)winWidth  - (uint16_t)1U)) * inElemSize,/* interMemPtrStride */
      0 /* dmaQueNo */
      );


    status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaReadUpdateParams);

    if (status!= BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    ivisionBufPlane= &outBufDesc->bufPlanes[0];

    /* CHECK_MISRA("-17.1")  -> Disable rule 17.1  */
    /* MISRA.PTR.ARITH :  Pointer is used in arithmetic or array index expression  */
    /*  These pointers are allocated from the user outside this applet hence we cannot check if we are accessing beyond. The harmful side effect of voilating this
        rule (accessing outside valid memory) shall be checked by another code checker like Klocwork     */
    dmaWriteUpdateParams.ptrToXyListBuf = (uint8_t*)ivisionBufPlane->buf +
                          (ivisionBufPlane->frameROI.topLeft.y *
                          ivisionBufPlane->width) +
                          ivisionBufPlane->frameROI.topLeft.x;

    /*RESET_MISRA("17.1")  -> Reset rule 17.1 for MISRA.PTR.ARITH */

    dmaWriteUpdateParams.ptrToListSizeBuf = ptrToListSize;

    status= BAM_controlNode(graphHandle, SINK_NODE, &dmaWriteUpdateParams);


 Exit:
    return status;
}

