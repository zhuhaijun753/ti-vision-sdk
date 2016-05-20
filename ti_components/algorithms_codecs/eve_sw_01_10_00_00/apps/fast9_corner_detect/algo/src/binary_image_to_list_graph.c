/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file      binary_image_to_list_graph.c
 *
 *  @brief      This file defines the functions for binary image to list graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/* #pragma RESET_MISRA ("required") */

#include "binary_image_to_list_graph_int.h"

static int32_t BIN_IMAGE_TO_LIST_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

#define MAX_KERNEL_ID (255)

typedef enum _bam_ti_kernelid
{
    BAM_TI_KERNELID_UNDEFINED = -1,

    BAM_TI_KERNELID_DMAREAD_AUTOINCR       = 0,
    BAM_TI_KERNELID_BIN_IMAGE_TO_LIST      = 1,
    BAM_TI_KERNELID_DMAWRITE_SCATTERGATHER = 2,
    BAM_TI_KERNELID_MAX = MAX_KERNEL_ID
} BAM_TI_KernelID;


/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamKernelHostDB_binToList[] =
{
    { &gBAM_TI_binImg2ListReadKernel,  &gBAM_TI_dmaReadBinImg2ListHelperFunc,  "ti_dma_read_autoincrement",  BAM_TI_KERNELID_DMAREAD_AUTOINCR},
    { &gBAM_TI_binImageToListKernel,   &gBAM_TI_binImageToListHelperFunc,      "ti_image_bin_img_to_list",   BAM_TI_KERNELID_BIN_IMAGE_TO_LIST },
    { &gBAM_TI_binImg2ListWriteKernel, &gBAM_TI_dmaWriteBinImg2ListHelperFunc, "ti_dma_write_scattergather", BAM_TI_KERNELID_DMAWRITE_SCATTERGATHER},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB_binToList[] =
{
    { &gBAM_TI_binImg2ListReadKernel,  &gBAM_TI_dmaReadBinImg2ListExecFunc,  "ti_dma_read_autoincrement",  BAM_TI_KERNELID_DMAREAD_AUTOINCR},
    { &gBAM_TI_binImageToListKernel,   &gBAM_TI_binImageToListExecFunc,      "ti_image_bin_img_to_list",   BAM_TI_KERNELID_BIN_IMAGE_TO_LIST },
    { &gBAM_TI_binImg2ListWriteKernel, &gBAM_TI_dmaWriteBinImg2ListExecFunc, "ti_dma_write_scattergather", BAM_TI_KERNELID_DMAWRITE_SCATTERGATHER},

};

BAM_KernelDBdef gBAM_TI_kernelDBdef_binToList =
{
    sizeof(bamKernelExecFuncDB_binToList) / sizeof(bamKernelExecFuncDB_binToList[0]),
    bamKernelHostDB_binToList,
    bamKernelExecFuncDB_binToList
};

#define SOURCE_NODE         0U
#define BIN_TO_LIST_NODE    1U
#define SINK_NODE           2U


int32_t BIN_IMAGE_TO_LIST_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = BIN_IMAGE_TO_LIST_GRAPH_OBJ_SIZE     ;
  memReq->graphScratchSize  = BIN_IMAGE_TO_LIST_GRAPH_SCRATCH_SIZE ;
  memReq->graphcontextSize  = BIN_IMAGE_TO_LIST_GRAPH_CONTEXT_SIZE ;
  memReq->graphArgsSize    = sizeof(BIN_IMAGE_TO_LIST_TI_graphArgs) ;
  return 0;
}

int32_t BIN_IMAGE_TO_LIST_TI_graphCreate(const BAM_GraphMem* graphMem, BIN_IMAGE_TO_LIST_TI_graphArgs * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BIN_IMAGE_TO_LIST_TI_graphArgs * graphArgs = (BIN_IMAGE_TO_LIST_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]={
            {SOURCE_NODE,          BAM_TI_KERNELID_DMAREAD_AUTOINCR,           NULL},
            {BIN_TO_LIST_NODE,     BAM_TI_KERNELID_BIN_IMAGE_TO_LIST,          NULL},
            {SINK_NODE,            BAM_TI_KERNELID_DMAWRITE_SCATTERGATHER,     NULL},
            {BAM_END_NODE_MARKER,  0,                                          NULL}
    };

    NODELIST[1].kernelArgs = (void *)(&graphArgs->binToListKernelArgs);

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,          BAM_SOURCE_NODE_PORT1},                  {BIN_TO_LIST_NODE,  BAM_BIN_IMAGE_TO_LIST_INPUT_PORT_IMG}},
            {{BIN_TO_LIST_NODE,     BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_XY},   {SINK_NODE, BAM_SINK_NODE_PORT1}},
            {{BIN_TO_LIST_NODE,     BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_SIZE}, {SINK_NODE, BAM_SINK_NODE_PORT2}},
            {{BAM_END_NODE_MARKER, 0},                                       {BAM_END_NODE_MARKER, 0}}
    };

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  status= BAM_initKernelDB(&gBAM_TI_kernelDBdef_binToList);

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
  graphCreateParams.kernelDB             = &gBAM_TI_kernelDBdef_binToList;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = BIN_IMAGE_TO_LIST_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = BIN_IMAGE_TO_LIST_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = BIN_IMAGE_TO_LIST_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = (BOOL)true;
  graphCreateParams.optimizeBlockDim     = (BOOL)false;


   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &BIN_IMAGE_TO_LIST_TI_initKernelsArgs;
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
    PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
      graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
  }
  else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
  {
    PRINTF("Graph construction failed!!! Decrease the value of blockWidth or blockHeight");
  }
  else if (status != BAM_S_SUCCESS)
  {
    PRINTF("Graph construction failed!!!");
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
  uint32_t    blkOffset,
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
  param->blkOffset            = blkOffset;
  param->extMemPtr            = extMemPtr;
  param->extMemPtrStride      = extMemPtrStride ;
  param->interMemPtr          = interMemPtr ;
  param->interMemPtrStride    = interMemPtrStride;
  param->dmaQueNo             = dmaQueNo;
}

/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t BIN_IMAGE_TO_LIST_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{

    int32_t status = BAM_S_SUCCESS;

    return (status);
}


int32_t BIN_IMAGE_TO_LIST_TI_graphControl(
        const BAM_GraphMem *graphMem,
        BAM_Bin_image_to_list_ctrlArgs * binToImgListCtrlArgs
        )
{
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    status = BAM_controlNode(graphHandle, BIN_TO_LIST_NODE, binToImgListCtrlArgs);

    return status;
}
int32_t BIN_IMAGE_TO_LIST_TI_graphDmaControl(
              const BAM_GraphMem *graphMem,
              const IVISION_BufDesc *inBufDesc,
              const IVISION_BufDesc *outBufDesc,
              const BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs * dmaCtrlParams)
{
    const IVISION_BufPlanes * ivisionBufPlane;
    EDMA_UTILS_autoIncrement_updateParams updateParams;
    BAM_DMA_CUSTOM_BINIMG2LIST_WRITENODE_ctrlArgs ctrlArgs;
    int32_t status = BAM_S_SUCCESS;
    uint8_t                 *extMemPtr;
    uint16_t                effectiveX;
    uint16_t                effectiveY;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    ivisionBufPlane = &inBufDesc->bufPlanes[0];

    updateParams.transferType = EDMA_UTILS_TRANSFER_IN;

    updateParams.updateMask =
            EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ALL &
              (~(EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_INTERMEMPTR));


    effectiveX = ivisionBufPlane->frameROI.topLeft.x +
                    dmaCtrlParams->dx;

    effectiveY = ivisionBufPlane->frameROI.topLeft.y +
                    dmaCtrlParams->dy;

    /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
    /* Pointer arithmetic is needed here to update the output pointer */
    /* The harmful side effect of voilating this rule (accessing outside valid memory) */
    /* shall be checked by another code checker like Klocwork */
    extMemPtr = ((uint8_t*)ivisionBufPlane->buf) + (((effectiveY * dmaCtrlParams->imgPitch) + effectiveX)/8U);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

    assignDMAautoIncrementParams(&(updateParams.updateParams[0]),
      (dmaCtrlParams->imgWidth+7U)/8U,          /* roiWidth */
      dmaCtrlParams->imgHeight,                 /* roiHeight */
      (dmaCtrlParams->blkWidth +7U)/8U,         /* blkWidth */
      dmaCtrlParams->blkHeight,                 /* blkHeight */
      0U,                                       /* extBlkIncrementX */
      dmaCtrlParams->blkHeight,                 /* extBlkIncrementY */
      0U,                                       /* intBlkIncrementX */
      0U,                                       /* intBlkIncrementY */
      0U,                                       /* roiOffset */
      0U,                                       /* blkOffset */
      extMemPtr,                                /* extMemPtr */
      (dmaCtrlParams->imgPitch+7U)/8U,          /* extMemPtrStride */
      NULL,                                     /* interMemPtr */
      (dmaCtrlParams->blkWidth+7U)/8U,          /* interMemPtrStride */
      0U                                         /* dmaQueNo */
      );

    status = BAM_controlNode(graphHandle, SOURCE_NODE, &updateParams);

    if (status != BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    ivisionBufPlane= &outBufDesc->bufPlanes[dmaCtrlParams->level];

    /* External memory pointer for out transfer */
    /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
    /* Pointer arithmetic is needed here to update the output pointer */
    /* The harmful side effect of voilating this rule (accessing outside valid memory) */
    /* shall be checked by another code checker like Klocwork */
    extMemPtr = (uint8_t*)ivisionBufPlane->buf +
                        ((ivisionBufPlane->frameROI.topLeft.y *
                        ivisionBufPlane->width) +
                        ivisionBufPlane->frameROI.topLeft.x);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

    ctrlArgs.dstPtr     = extMemPtr;
    ctrlArgs.pListSize  = dmaCtrlParams->pListSize;


    status= BAM_controlNode(graphHandle, SINK_NODE, &ctrlArgs);

 Exit:
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t BIN_IMAGE_TO_LIST_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority= BAM_COMPUTE_FIRST;

  BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;
}
