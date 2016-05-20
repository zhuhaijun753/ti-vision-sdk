/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       feature_matching_graph.c
 *
 *  @brief      This file defines the functions for feature matching graph
 *
 *  @version    0.1 (Aug 2014) : Base version.
 */

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* #pragma RESET_MISRA ("required") */

#include "xdais_types.h"
#include "ifeature_matching_ti.h"
#include "feature_matching_graph_int.h"
#include "edma_utils.h"

static int32_t FEATURE_MATCHING_TI_initKernelsArgs(void *args, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE               (0U)
#define FEATURE_MATCHING_NODE     (1U)
#define SINK_NODE                 (2U)


typedef enum
{
    BAM_TI_KERNELID_DMAREAD_FEAT_MATCH          = 0,
    BAM_TI_KERNELID_FEATURE_MATCHING            = 1,
    BAM_TI_KERNELID_DMAWRITE_FEAT_MATCH_DUMMY   = 2
} BAM_GLCM_TI_KernelID;

/**
 * Kernel Database - used for graph construction. If the application is running others graphs
   that share many common kernels with this local database, it may be worthwhile to move this
   local database into the "master" database defined in kernels/bamdb
 */
static BAM_KernelHostDBdef bamFeatMatchKernelHostDB[] =
{
  { &gBAM_TI_featMatchDmaNodeReadKernel, &gBAM_TI_featMatchDmaNodeReadKernelHelperFunc,
            "ti_dma_read_feat_match_autoincr", BAM_TI_KERNELID_DMAREAD_FEAT_MATCH},
  { &gBAM_TI_featureMatchingKernel, &gBAM_TI_featureMatchingHelperFunc,
            "ti_feature_matching_compute", BAM_TI_KERNELID_FEATURE_MATCHING},
  { &gBAM_TI_featMatchDmaNodeWriteKernel, &gBAM_TI_featMatchDmaNodeWriteKernelHelperFunc,
            "ti_dma_write_feat_match_dummy", BAM_TI_KERNELID_DMAWRITE_FEAT_MATCH_DUMMY},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamFeatMatchKernelExecFuncDB[] =
{
  { &gBAM_TI_featMatchDmaNodeReadKernel,  &gBAM_TI_featMatchDmaNodeReadKernelExecFunc,
                        "ti_dma_read_feat_match_autoincr", BAM_TI_KERNELID_DMAREAD_FEAT_MATCH},
  { &gBAM_TI_featureMatchingKernel, &gBAM_TI_featureMatchingExecFunc,
                        "ti_feature_matching_compute", BAM_TI_KERNELID_FEATURE_MATCHING},
  { &gBAM_TI_featMatchDmaNodeWriteKernel, &gBAM_TI_featMatchDmaNodeWriteKernelExecFunc,
                        "ti_dma_write_feat_match_dummy", BAM_TI_KERNELID_DMAWRITE_FEAT_MATCH_DUMMY},
};

BAM_KernelDBdef gFeatMatch_TI_BAM_kernelDBdef =
{
  sizeof(bamFeatMatchKernelExecFuncDB) / sizeof(bamFeatMatchKernelExecFuncDB[0]),
  bamFeatMatchKernelHostDB,
  bamFeatMatchKernelExecFuncDB
};


int32_t FEATURE_MATCHING_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
  memReq->graphObjSize      = FEATURE_MATCHING_GRAPH_OBJ_SIZE;
  memReq->graphScratchSize  = FEATURE_MATCHING_GRAPH_SCRATCH_SIZE;
  memReq->graphcontextSize  = FEATURE_MATCHING_GRAPH_CONTEXT_SIZE;
  memReq->graphArgsSize     = sizeof(FEATURE_MATCHING_TI_graphArgs);
  return 0;
}

int32_t FEATURE_MATCHING_TI_graphCreate(const BAM_GraphMem * graphMem,
            FEATURE_MATCHING_TI_graphCreateParams * createParams)
{
  BAM_CreateGraphParams graphCreateParams;
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  FEATURE_MATCHING_TI_graphArgs * graphArgs = (FEATURE_MATCHING_TI_graphArgs *)graphMem->graphArgs;
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  /*------------------------------------------------------------------------------*/
  /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
  /*------------------------------------------------------------------------------*/
  BAM_NodeParams NODELIST[]=
  {
    {SOURCE_NODE,            BAM_TI_KERNELID_DMAREAD_FEAT_MATCH,         NULL},
    {FEATURE_MATCHING_NODE,  BAM_TI_KERNELID_FEATURE_MATCHING,           NULL},
    {SINK_NODE,              BAM_TI_KERNELID_DMAWRITE_FEAT_MATCH_DUMMY,  NULL},
    {BAM_END_NODE_MARKER,    0,                                          NULL}
  };
  /* This is done because of build errors, ARP32 compiler doesnt allow below statement */
  NODELIST[0].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);
  NODELIST[1].kernelArgs = (void *)(&graphArgs->featMatchKernelArgs);
  NODELIST[2].kernelArgs = (void *)(&graphArgs->dmaReadKernelArgs);

  BAM_EdgeParams EDGELIST[]=
  {
    {{SOURCE_NODE, BAM_SOURCE_NODE_PORT1},  {FEATURE_MATCHING_NODE, BAM_FEATURE_MATCHING_STRING_1_PORT}},\
    {{SOURCE_NODE, BAM_SOURCE_NODE_PORT2},  {FEATURE_MATCHING_NODE, BAM_FEATURE_MATCHING_STRING_2_PORT}},\
    {{FEATURE_MATCHING_NODE, BAM_FEATURE_MATCHING_OUTPUT_PORT},  {SINK_NODE, BAM_SINK_NODE_PORT1}},\
    {{BAM_END_NODE_MARKER, 0},              {BAM_END_NODE_MARKER, 0}},\
  };

  graphCreateParams.graphMemConsumed = 0;
  graphCreateParams.onChipScratchMemConsumed = 0;
  graphCreateParams.extMemConsumed = 0;

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  status= BAM_initKernelDB(&gFeatMatch_TI_BAM_kernelDBdef);

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if(status != BAM_S_SUCCESS) {
      goto Exit;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  /*---------------------------------------------------------------*/
  /* Initialize Graph creation time parameters                     */
  /*---------------------------------------------------------------*/
  graphCreateParams.coreType             = BAM_EVE;
  graphCreateParams.kernelDB             = &gFeatMatch_TI_BAM_kernelDBdef;
  graphCreateParams.nodeList             = (BAM_NodeParams*)NODELIST;
  graphCreateParams.edgeList             = (BAM_EdgeParams*)EDGELIST;
  graphCreateParams.graphMem             = graphHandle;
  graphCreateParams.graphMemSize         = FEATURE_MATCHING_GRAPH_OBJ_SIZE;
  graphCreateParams.onChipScratchMem     = graphMem->graphScratch;
  graphCreateParams.onChipScratchMemSize = FEATURE_MATCHING_GRAPH_SCRATCH_SIZE;
  graphCreateParams.extMem               = graphMem->graphcontext;
  graphCreateParams.extMemSize           = FEATURE_MATCHING_GRAPH_CONTEXT_SIZE;
  graphCreateParams.useSmartMemAlloc     = (BOOL)true;
  graphCreateParams.optimizeBlockDim     = (BOOL)false;

  graphArgs->createParams = createParams;

   /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  graphCreateParams.initKernelsArgsFunc   = &FEATURE_MATCHING_TI_initKernelsArgs;
  graphCreateParams.initKernelsArgsParams = (void*)graphArgs;

  /*---------------------------------------------------------------*/
  /* Initialize the members related to the  kernels init function  */
  /*---------------------------------------------------------------*/
  status = BAM_createGraph(&graphCreateParams, &graphHandle);
  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  if(status != BAM_S_SUCCESS)
  {
    goto Exit;
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  /*-------------------------------------------------------------------------*/
  /* error message handling and return of error code                         */
  /*-------------------------------------------------------------------------*/
Exit:
  if (status== BAM_E_INVALID_MEM_SIZE)
  {
    PRINTF("Graph construction failed!!! graphMemSize must be >= %d, "
      "onChipScratchMemSize >= %d and extMemSize must be >= %d\n",
      graphCreateParams.graphMemConsumed,
      graphCreateParams.onChipScratchMemConsumed,
      graphCreateParams.extMemConsumed);
  }
  else if (status== BAM_E_BLOCK_DIM_TOO_BIG)
  {
    PRINTF("Graph construction failed!!! Decrease the value of blockWidth "
      "or blockHeight");
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
/* Function to initialize kernel arguments                                 */
/*-------------------------------------------------------------------------*/
static int32_t FEATURE_MATCHING_TI_initKernelsArgs(void *args,
            BAM_BlockDimParams *blockDimParams)
{
  int32_t status = BAM_S_SUCCESS;
  uint16_t numDesc1PerIter, numDesc2PerIter;

  FEATURE_MATCHING_TI_graphArgs *graphArgs = (FEATURE_MATCHING_TI_graphArgs*)args;
  FEATURE_MATCHING_TI_graphCreateParams *createParams = graphArgs->createParams;
  BAM_DMA_NODE_FEAT_MATCH_args *dmaReadKernelArgs = &(graphArgs->dmaReadKernelArgs);
  BAM_featureMatching_Args *featMatchKernelArgs = &(graphArgs->featMatchKernelArgs);

  numDesc1PerIter = (createParams->descriptorLength <= 32) ?
    FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT1 :
    MIN(FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT1,
        16U*((16384U/(2U + createParams->descriptorLength))/16U));

  numDesc2PerIter = (createParams->descriptorLength <= 32) ?
    FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT2 :
    MIN(FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT2,
        2U*((16384U/(64U + createParams->descriptorLength))/2U));

  /*--------------------------------------------------------------------------*/
  /*Params Update for Source & Sink DMA nodes                                 */
  /*--------------------------------------------------------------------------*/
  dmaReadKernelArgs->descriptorLength  = createParams->descriptorLength;
  dmaReadKernelArgs->numDescPerIter1   = numDesc1PerIter;
  dmaReadKernelArgs->numDescPerIter2   = numDesc2PerIter;

  /*--------------------------------------------------------------------------*/
  /*Params Update for feature matching                                        */
  /*--------------------------------------------------------------------------*/
  featMatchKernelArgs->descriptorSize  = createParams->descriptorLength;
  featMatchKernelArgs->descriptorPitch = createParams->descriptorLength;
  featMatchKernelArgs->numDescriptors1 = numDesc1PerIter;
  featMatchKernelArgs->numDescriptors2 = numDesc2PerIter;
  featMatchKernelArgs->mode            = 0;

  return (status);
}


/*-------------------------------------------------------------------------*/
/* Function to populate kernel control parameters                          */
/*-------------------------------------------------------------------------*/
int32_t FEATURE_MATCHING_TI_graphControl(const BAM_GraphMem *graphMem,
                      const FEATURE_MATCHING_TI_graphCtrlArgs *inParams)
{
  BAM_featureMatching_CtlArgs ctlArgs;
  int32_t status = BAM_S_SUCCESS;

  /* initilize the sub-handles inside the main handle */
  BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

  ctlArgs.numDescFullList1  = inParams->numDescriptors1;
  ctlArgs.numDescFullList2  = inParams->numDescriptors2;
  ctlArgs.minDistanceThres  = inParams->minDistanceThres;
  ctlArgs.matchConfidence   = inParams->matchConfidence;
  ctlArgs.numDesc1PerIter   = inParams->numDesc1PerIter;
  ctlArgs.numDesc2PerIter   = inParams->numDesc2PerIter;

  status = BAM_controlNode(graphHandle, FEATURE_MATCHING_NODE, &ctlArgs);

  return status;
}


/*-------------------------------------------------------------------------*/
/* Function to perfrom actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t FEATURE_MATCHING_TI_execute(BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

  BAM_ProcessHints hints;
  int32_t status = BAM_S_SUCCESS;

  /* Specify which processing schedule is the best, unsupported for now */
  hints.priority = BAM_COMPUTE_FIRST;

  status = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

  return status;
}


/*-------------------------------------------------------------------------*/
/* Function to update DMA parameters                                       */
/*-------------------------------------------------------------------------*/
int32_t FEATURE_MATCHING_TI_dmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *in1BufDesc, const IVISION_BufDesc *in2BufDesc,
        const IVISION_BufDesc *outBufDesc, uint16_t numDesc1PerIter,
        uint16_t numDesc2PerIter)
{
    BAM_DMA_NODE_FEAT_MATCH_updateParams dmaCtlArgs;

    const IVISION_BufPlanes *ivisionIn1BufPlane = &in1BufDesc->bufPlanes[0];
    const IVISION_BufPlanes *ivisionIn2BufPlane = &in2BufDesc->bufPlanes[0];
    const IVISION_BufPlanes *ivisionOutBufPlane = &outBufDesc->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /* Initialize the control parameters for the SOURCE custom DMA node */
    dmaCtlArgs.extMemPtrIn1 = (uint8_t*)(*((uint8_t (*)[])ivisionIn1BufPlane->buf) +
      (ivisionIn1BufPlane->frameROI.topLeft.y * ivisionIn1BufPlane->width) +
      ivisionIn1BufPlane->frameROI.topLeft.x);
    dmaCtlArgs.totalNumBytesIn1 = ivisionIn1BufPlane->frameROI.width;

    dmaCtlArgs.extMemPtrIn2 = (uint8_t*)(*((uint8_t (*)[])ivisionIn2BufPlane->buf) +
      (ivisionIn2BufPlane->frameROI.topLeft.y * ivisionIn2BufPlane->width) +
      ivisionIn2BufPlane->frameROI.topLeft.x);
    dmaCtlArgs.totalNumBytesIn2 = ivisionIn2BufPlane->frameROI.width;

    dmaCtlArgs.numDesc1PerIter = numDesc1PerIter;
    dmaCtlArgs.numDesc2PerIter = numDesc2PerIter;

    status= BAM_controlNode(graphHandle, SOURCE_NODE, &dmaCtlArgs);
    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */


    /* Initialize the control parameters for the SINK custom DMA node */
    dmaCtlArgs.extMemPtrOut = (uint8_t*)(*((uint8_t (*)[])ivisionOutBufPlane->buf) +
      (ivisionOutBufPlane->frameROI.topLeft.y * ivisionOutBufPlane->width) +
      ivisionOutBufPlane->frameROI.topLeft.x);

    status= BAM_controlNode(graphHandle, SINK_NODE, &dmaCtlArgs);

 Exit:
    return status;
}
