/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       glcm_graph.c
 *
 *  @brief      This file defines the functions for Gray-level co-occurrence
 *              matrix graph
 *
 *  @version    0.1 (Jan 2014) : Base version.
 */

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* #pragma RESET_MISRA ("required") */

#include "xdais_types.h"
#include "iglcm_ti.h"
#include "glcm_graph_int.h"
#include "edma_utils.h"

static int32_t GLCM_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE               (0U)
#define INTENSITY_SCALING_NODE    (1U)
#define GLCM_NODE                 (2U)
#define SINK_NODE                 (3U)

/**
 * Maximum input block size (height/width) possible for various number of
   angles to be analysed in parallel. This is dictated by scratch_index buffer of
   GLCM kernel. We need to ensure that 2*numRows*ceil(numCols/2)*2*numDirections <= 16kB
   ~ sqrt(16k/(2*numDirections))
 */
static const uint8_t GLCM_TI_gMaxBlkSize[BAM_GLCM_MAX_NUM_DIRECTIONS]  = {90, 63, 52, 44, 40, 36, 34, 31};

typedef enum
{
    BAM_TI_KERNELID_DMAREAD_GLCM          = 0,
    BAM_TI_KERNELID_INTENSITY_SCALING     = 1,
    BAM_TI_KERNELID_GLCM                  = 2,
    BAM_TI_KERNELID_DMAWRITE_GLCM_DUMMY   = 3
} BAM_GLCM_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamGlcmKernelHostDB[] =
{
  { &gBAM_TI_glcmDmaNodeReadKernel, &gBAM_TI_glcmDmaNodeReadKernelHelperFunc,
                        "ti_dma_read_glcm_autoincr", BAM_TI_KERNELID_DMAREAD_GLCM},
  { &gBAM_TI_intensityScalingKernel, &gBAM_TI_intensityScalingHelperFunc,
                        "ti_intensity_scaling", BAM_TI_KERNELID_INTENSITY_SCALING},
  { &gBAM_TI_glcmKernel, &gBAM_TI_glcmHelperFunc,
                        "ti_glcm_compute", BAM_TI_KERNELID_GLCM},
  { &gBAM_TI_glcmDmaNodeWriteKernel, &gBAM_TI_glcmDmaNodeWriteKernelHelperFunc,
                        "ti_dma_write_glcm_dummy", BAM_TI_KERNELID_DMAWRITE_GLCM_DUMMY},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamGlcmKernelExecFuncDB[] =
{
  { &gBAM_TI_glcmDmaNodeReadKernel,  &gBAM_TI_glcmDmaNodeReadKernelExecFunc,
                        "ti_dma_read_glcm_autoincr", BAM_TI_KERNELID_DMAREAD_GLCM},
  { &gBAM_TI_intensityScalingKernel, &gBAM_TI_intensityScalingExecFunc,
                        "ti_intensity_scaling", BAM_TI_KERNELID_INTENSITY_SCALING},
  { &gBAM_TI_glcmKernel, &gBAM_TI_glcmExecFunc,
                        "ti_glcm_compute", BAM_TI_KERNELID_GLCM},
  { &gBAM_TI_glcmDmaNodeWriteKernel, &gBAM_TI_glcmDmaNodeWriteKernelExecFunc,
                        "ti_dma_write_glcm_dummy", BAM_TI_KERNELID_DMAWRITE_GLCM_DUMMY},
};

BAM_KernelDBdef gGlcm_TI_BAM_kernelDBdef =
{
  sizeof(bamGlcmKernelExecFuncDB) / sizeof(bamGlcmKernelExecFuncDB[0]),
  bamGlcmKernelHostDB,
  bamGlcmKernelExecFuncDB
};


int32_t GLCM_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = GLCM_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = GLCM_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = GLCM_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize     = sizeof(GLCM_TI_graphArgs);
  return 0;
}

int32_t GLCM_TI_graphCreate(const BAM_GraphMem * graphMem,
            GLCM_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    GLCM_TI_graphArgs * graphArgs = (GLCM_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]=
    {
        {SOURCE_NODE,               BAM_TI_KERNELID_DMAREAD_GLCM,            NULL},
        {INTENSITY_SCALING_NODE,    BAM_TI_KERNELID_INTENSITY_SCALING,       NULL},
        {GLCM_NODE,                 BAM_TI_KERNELID_GLCM,                    NULL},
        {SINK_NODE,                 BAM_TI_KERNELID_DMAWRITE_GLCM_DUMMY,     NULL},
        {BAM_END_NODE_MARKER,       0,                                       NULL},
    };
    /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
    NODELIST[0].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
    NODELIST[1].kernelArgs = (void *)(&graphArgs->intensityScalingKernelArgs);
    NODELIST[2].kernelArgs = (void *)(&graphArgs->glcmKernelArgs);
    NODELIST[3].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
    BAM_EdgeParams EDGELIST[]=
    {
        {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},             {INTENSITY_SCALING_NODE,  BAM_INTENSITY_SCALING_INPUT_PORT_IMG}},\
        {{INTENSITY_SCALING_NODE, BAM_INTENSITY_SCALING_OUTPUT_PORT_IMG}, {GLCM_NODE, BAM_GLCM_INPUT_PORT}},\
        {{GLCM_NODE, BAM_GLCM_OUTPUT_PORT},                {SINK_NODE, BAM_SINK_NODE_PORT1}},\
        {{BAM_END_NODE_MARKER, 0},                         {BAM_END_NODE_MARKER, 0}},\
    };

  /* Initialize the structure blockDimParams that lists the processing block
  * dimensions as well as the step increment sizes used during the block
  * dimension optimization if enabled
  */
  graphCreateParams.blockDimParams.blockWidth   = GLCM_TI_gMaxBlkSize[0];
  graphCreateParams.blockDimParams.blockHeight  = GLCM_TI_gMaxBlkSize[0];

  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  status= BAM_initKernelDB(&gGlcm_TI_BAM_kernelDBdef);

  if(status != BAM_S_SUCCESS)
  {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
  }

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.coreType             = BAM_EVE;
  graphCreateParams.kernelDB             = &gGlcm_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = GLCM_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = GLCM_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = GLCM_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = (BOOL)true;
  graphCreateParams.optimizeBlockDim     = (BOOL)false;

  graphArgs->createParams = createParams;

   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &GLCM_TI_initKernelsArgs;
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
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
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
    PRINTF("Graph construction failed!!! Decrease the value of blockWidth : %d or blockHeight : %d",
      graphCreateParams.blockDimParams.blockWidth,graphCreateParams.blockDimParams.blockHeight);
  }
  else if (status != BAM_S_SUCCESS)
  {
    PRINTF("Graph construction failed!!!");
  }
  else
  {
    /* This is to prevent MISRA C Issue MISRA.IF.NO_ELSE Rule 14.10. */
  }

  return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to assign DMA parameters to EDMA utilitiy                      */
/*-------------------------------------------------------------------------*/
static void assignDMAautoIncrementParams(
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
        uint8_t     *extMemPtr,
        uint16_t    extMemPtrStride,
        uint8_t     *interMemPtr,
        uint16_t    interMemPtrStride,
        uint8_t     dmaQueNo
);

static void assignDMAautoIncrementParams(
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
    param->extMemPtr            = extMemPtr;
    param->extMemPtrStride      = extMemPtrStride ;
    param->interMemPtr          = interMemPtr ;
    param->interMemPtrStride    = interMemPtrStride;
    param->dmaQueNo             = dmaQueNo;
}


/*-------------------------------------------------------------------------*/
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t GLCM_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;
  uint32_t blockWidth, blockHeight;
  uint32_t n;
  int8_t maxColOffset, minColOffset, maxRowOffset, minRowOffset;
  uint32_t numRows, numCols;

  GLCM_TI_graphArgs *graphArgs = (GLCM_TI_graphArgs*)args;
  GLCM_TI_graphCreateParams *createParams = graphArgs->createParams;
  EDMA_UTILS_autoIncrement_initParam *dmaReadKernelArgs = &(graphArgs->dmaReadKernelArgs);
  BAM_Intensity_scaling_Args *intensityScalingKernelArgs = &(graphArgs->intensityScalingKernelArgs);
  BAM_Glcm_Args *glcmKernelArgs = &(graphArgs->glcmKernelArgs);

  /* Find optimal block dimension */
  blockWidth  = MIN(GLCM_TI_gMaxBlkSize[createParams->numDirections-1], createParams->imageWidth);
  blockHeight = MIN(GLCM_TI_gMaxBlkSize[createParams->numDirections-1], createParams->imageHeight);

  maxColOffset = 0;
  minColOffset = 0;
  maxRowOffset = 0;
  minRowOffset = 0;

  for(n = 0; n < createParams->numDirections; n++) {
    maxColOffset = MAX(maxColOffset, (*createParams->colOffset)[n]);
    minColOffset = MIN(minColOffset, (*createParams->colOffset)[n]);
    maxRowOffset = MAX(maxRowOffset, (*createParams->rowOffset)[n]);
    minRowOffset = MIN(minRowOffset, (*createParams->rowOffset)[n]);
  }
  numCols = blockWidth  - ((uint32_t)maxColOffset - (uint32_t)minColOffset);
  numRows = blockHeight - ((uint32_t)maxRowOffset - (uint32_t)minRowOffset);

  while(((createParams->imageWidth - blockWidth) % numCols) != 0) {
    blockWidth--;
    numCols--;
  }

  while(((createParams->imageHeight - blockHeight) % numRows) != 0) {
    blockHeight--;
    numRows--;
  }

  /*--------------------------------------------------------------------------*/
  /*Params Update for Source DMA node                                         */
  /*--------------------------------------------------------------------------*/
  dmaReadKernelArgs->numInTransfers  = 1;
  dmaReadKernelArgs->transferType    = EDMA_UTILS_TRANSFER_IN;

  assignDMAautoIncrementParams(&dmaReadKernelArgs->transferProp[BAM_SOURCE_NODE_PORT1],
          createParams->imageWidth,            /* roiWidth */
          createParams->imageHeight,           /* roiHeight */
          (uint16_t)blockWidth,                          /* blkWidth */
          (uint16_t)blockHeight,                         /* blkHeight */
          (uint16_t)numCols,                             /* extBlkIncrementX */
          (uint16_t)numRows,                             /* extBlkIncrementY */
          0,                                   /* intBlkIncrementX */
          0,                                   /* intBlkIncrementY */
          0,                                   /* roiOffset        */
          NULL,                                /* extMemPtr        */
          0,                                   /* extMemPtrStride  */
          NULL,                                /* interMemPtr      */
          (uint16_t)blockWidth,                          /* interMemPtrStride */
          0);                                  /* dmaQueNo          */

  /*--------------------------------------------------------------------------*/
  /*Params Update for intensity scaling kernel                                */
  /*--------------------------------------------------------------------------*/
  intensityScalingKernelArgs->blockWidth  = blockWidth;
  intensityScalingKernelArgs->blockHeight = blockHeight;
  intensityScalingKernelArgs->blockStride = blockWidth;
  intensityScalingKernelArgs->loPixelVal  = createParams->loPixelVal;
  intensityScalingKernelArgs->hiPixelVal  = createParams->hiPixelVal;
  intensityScalingKernelArgs->numLevels   = createParams->numLevels;

  /*--------------------------------------------------------------------------*/
  /*Params Update for glcm kernel                                             */
  /*--------------------------------------------------------------------------*/
  glcmKernelArgs->blockWidth  = blockWidth;
  glcmKernelArgs->blockHeight = blockHeight;
  glcmKernelArgs->blockStride = blockWidth;
  glcmKernelArgs->numLevels   = createParams->numLevels;
  glcmKernelArgs->numOffsets  = createParams->numDirections;
  memcpy(glcmKernelArgs->rowOffsets, *(createParams->rowOffset), createParams->numDirections);
  memcpy(glcmKernelArgs->colOffsets, *(createParams->colOffset), createParams->numDirections);

  return (status);

}

/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t GLCM_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority = BAM_COMPUTE_FIRST;

  status = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;

}

int32_t GLCM_TI_dmaControl(const BAM_GraphMem *graphMem, const IVISION_BufDesc *inBufDesc, uint32_t *intGlcmBufAddr)
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;

    const IVISION_BufPlanes * ivisionBufPlane= &inBufDesc->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

    autoIncCtlArgs.updateParams[0].extMemPtr= (uint8_t*)(*((uint8_t (*)[])ivisionBufPlane->buf) +
        (ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x);
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);
    if (status!= BAM_S_SUCCESS) {
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    /* Initialize the control parameters for the SINK custom DMA node for GLCM */
    autoIncCtlArgs.updateParams[0].extMemPtr= (uint8_t *)(void *)intGlcmBufAddr;
    status= BAM_controlNode(graphHandle, SINK_NODE, &autoIncCtlArgs);

 Exit:
    return status;
}
