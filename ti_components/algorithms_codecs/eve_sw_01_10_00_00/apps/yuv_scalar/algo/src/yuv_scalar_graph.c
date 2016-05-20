/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file yuv_scalar_graph.c
 *
 *  @brief  This file implements an applet for yuv_scalar
 *
 *  @author TI
 *
 *  @date   05 Mar 2014
 *
 *  Description
 *    This file contains code to perform yuv_scalar
 */
/*#pragma CHECK_MISRA ("none")*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
/*#pragma RESET_MISRA ("required")*/

#include "yuv_scalar_graph_int.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "iyuv_scalar_ti.h"

#define FIND_BEST_BLOCKDIM

#ifndef NULL
#define NULL        (void *)0 
#endif

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

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamKernelHostDB[] =
{
        { &gBAM_TI_dmaCustomYUVScalarReadNodeKernel,  &gBAM_TI_dmaCustomYUVScalarReadNodeKernelHelperFunc,
          "ti_dma_read_scatterGather", BAM_TI_KERNELID_SCALAR_DMAREAD},
        { &gBAM_TI_yuvScalarKernel, &gBAM_TI_yuvScalarHelperFunc,
          "ti_image_yuv_scalar", BAM_TI_KERNELID_YUV_SCALAR},
        { &gBAM_TI_YUVScalar_DmaAutoIncrementWriteKernel, &gBAM_TI_dmaCustomYUVScalarWriteNodeKernelHelperFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_SCALAR_DMAWRITE_AUTOINCREMENT},
};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaCustomYUVScalarReadNodeKernel,  &gBAM_TI_dmaCustomYUVScalarReadNodeKernelExecFunc,
          "ti_dma_read_scatterGather", BAM_TI_KERNELID_SCALAR_DMAREAD},
        { &gBAM_TI_yuvScalarKernel, &gBAM_TI_yuvScalarExecFunc,
          "ti_image_yuv_scalar", BAM_TI_KERNELID_YUV_SCALAR},
        { &gBAM_TI_YUVScalar_DmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
          "ti_dma_write_autoincrement", BAM_TI_KERNELID_SCALAR_DMAWRITE_AUTOINCREMENT},
};

BAM_KernelDBdef gYUV_SCALAR_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};

static int32_t YUV_SCALAR_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE                  (0)
#define YUV_VERTICAL_SCALE_NODE      (1)
#define YUV_HORIZONTAL_SCALE_NODE    (2)
#define SINK_NODE                    (3)

int32_t YUV_SCALAR_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = YUV_SCALAR_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = YUV_SCALAR_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = YUV_SCALAR_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(YUV_SCALAR_TI_graphArgs) ;
    return 0;
}



int32_t YUV_SCALAR_TI_graphCreate(
        const BAM_GraphMem *graphMem,
        YUV_SCALAR_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    YUV_SCALAR_TI_graphArgs * graphArgs = (YUV_SCALAR_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*
     */

    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,                  BAM_TI_KERNELID_SCALAR_DMAREAD,                    NULL},
            {YUV_VERTICAL_SCALE_NODE,      BAM_TI_KERNELID_YUV_SCALAR,                        NULL},
            {YUV_HORIZONTAL_SCALE_NODE,    BAM_TI_KERNELID_YUV_SCALAR,                        NULL},
            {SINK_NODE,                    BAM_TI_KERNELID_SCALAR_DMAWRITE_AUTOINCREMENT,     NULL},
            {BAM_END_NODE_MARKER,       0,                              NULL},\
    };

    NODELIST[SOURCE_NODE].kernelArgs                    = &graphArgs->dmaReadKernelArgs;
    NODELIST[YUV_VERTICAL_SCALE_NODE].kernelArgs        = &graphArgs->verScaleKernelArgs;
    NODELIST[YUV_HORIZONTAL_SCALE_NODE].kernelArgs      = &graphArgs->horScaleKernelArgs;
    NODELIST[SINK_NODE].kernelArgs                      = &graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},                               {YUV_VERTICAL_SCALE_NODE,      BAM_YUV_SCALAR_INPUT_DATA_PORT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT2},                               {YUV_HORIZONTAL_SCALE_NODE,    BAM_YUV_SCALAR_INPUT_INDEX_PORT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT3},                               {YUV_HORIZONTAL_SCALE_NODE,    BAM_YUV_SCALAR_INPUT_FRAC_COEFF_PORT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT4},                               {YUV_VERTICAL_SCALE_NODE,      BAM_YUV_SCALAR_INPUT_INDEX_PORT}},\
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT5},                               {YUV_VERTICAL_SCALE_NODE ,     BAM_YUV_SCALAR_INPUT_FRAC_COEFF_PORT}},\
            {{YUV_VERTICAL_SCALE_NODE,     BAM_YUV_SCALAR_OUTPUT_DATA_PORT},      {YUV_HORIZONTAL_SCALE_NODE,    BAM_YUV_SCALAR_INPUT_DATA_PORT}},\
            {{YUV_HORIZONTAL_SCALE_NODE,   BAM_YUV_SCALAR_OUTPUT_DATA_PORT},      {SINK_NODE, BAM_SINK_NODE_PORT1}},\
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };


    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    status= BAM_initKernelDB(&gYUV_SCALAR_BAM_kernelDBdef);

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
    graphCreateParams.coreType= BAM_EVE;
    graphCreateParams.kernelDB= &gYUV_SCALAR_BAM_kernelDBdef;
    graphCreateParams.nodeList= (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList= (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem= graphHandle; /* on the stack */
    graphCreateParams.graphMemSize= YUV_SCALAR_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem= graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize= YUV_SCALAR_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem= graphMem->graphcontext; /* passed by the caller, usually in external memory */
    graphCreateParams.extMemSize= YUV_SCALAR_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc= (BOOL)true;
#ifdef FIND_BEST_BLOCKDIM
    graphCreateParams.optimizeBlockDim= (BOOL)true;
#else
    graphCreateParams.optimizeBlockDim= (BOOL)false;
#endif
    graphArgs->createParams= createParams;

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc= &YUV_SCALAR_initArgs;
    graphCreateParams.initKernelsArgsParams= (void*)graphArgs;

    /* Initialize the structure graphCreateParams.blockDimParams that lists the processing block
     * dimensions as well as the step increment sizes used during the block
     * dimension optimization if enabled
     */

    graphCreateParams.blockDimParams.blockWidth= YUV_SCALAR_BLOCK_WIDTH;
    graphCreateParams.blockDimParams.blockHeight= YUV_SCALAR_BLOCK_HEIGHT; 

    graphCreateParams.blockDimParams.blockWidthStep= 32;
    graphCreateParams.blockDimParams.blockHeightStep= 32; 
    graphCreateParams.blockDimParams.blockWidthDivisorOf= 384;
    graphCreateParams.blockDimParams.blockHeightDivisorOf= 64; 

    status = BAM_createGraph(&graphCreateParams, &graphHandle);

    if(status != BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    graphArgs->blockWidth  = graphCreateParams.blockDimParams.blockWidth;
    graphArgs->blockHeight = graphCreateParams.blockDimParams.blockHeight;
    /*-------------------------------------------------------------------------*/
    /* error message handling and return of error code                         */
    /*-------------------------------------------------------------------------*/

    Exit:
    if (status== BAM_E_INVALID_MEM_SIZE) {
        PRINTF("Graph construction failed!!! graphMemSize must be >= %d, onChipScratchMemSize >= %d and extMemSize must be >= %d\n", graphCreateParams.graphMemConsumed, graphCreateParams.onChipScratchMemConsumed, graphCreateParams.extMemConsumed);
    }
    else if (status== BAM_E_BLOCK_DIM_TOO_BIG) {
        PRINTF("Graph construction failed!!! Decrease the value of BLK_WIDTH or BLK_HEIGHT\n");
    } else if (status != BAM_S_SUCCESS)
    {
        PRINTF("Graph construction failed!!!\n");
    }
    else {
        /*BAM_printMemRec(graphCreateParams.memRec, graphCreateParams.numMemRec);*/
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
    param->blkOffset            = 0;
}

/* YUV_SCALAR_initArgs() is callback function that BAM will call to initialize all the kernes' arguments
 * It will be called several times during the search for the best block dimensions
 * */
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t YUV_SCALAR_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams) {
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */

    YUV_SCALAR_TI_graphArgs *graphArgs= (YUV_SCALAR_TI_graphArgs*)initKernelsArgs;

    int16_t blkWidthFinal= 0;
    int16_t blkHeightFinal= 0;

    int32_t status    = BAM_S_SUCCESS;
    int32_t blockIncr = 32;
    uint16_t inBlockWidthOrg  = (uint16_t)((((uint16_t)blockDimParams->blockWidth  * graphArgs->createParams->appCreateParams->scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 4U);
    uint16_t inBlockHeight    = (uint16_t)((((uint16_t)blockDimParams->blockHeight  * graphArgs->createParams->appCreateParams->scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 2U);
    uint16_t  inBlockWidth    = ALIGN_SIZE((uint16_t)inBlockWidthOrg,(uint16_t)blockIncr); 

    blkWidthFinal  = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;

    graphArgs->verScaleKernelArgs.srcBlockWidth  = inBlockWidthOrg; 
    graphArgs->verScaleKernelArgs.srcBlockPitch  = inBlockWidth;
    graphArgs->verScaleKernelArgs.dstBlockWidth  = blkWidthFinal;
    graphArgs->verScaleKernelArgs.dstBlockHeight = blkHeightFinal; 
    graphArgs->verScaleKernelArgs.numTaps        = 2;
    graphArgs->verScaleKernelArgs.fracBits       = graphArgs->createParams->appCreateParams->fracQFmt;


    graphArgs->horScaleKernelArgs.srcBlockWidth  = blkHeightFinal; 
    graphArgs->horScaleKernelArgs.srcBlockPitch  = blkHeightFinal;
    graphArgs->horScaleKernelArgs.dstBlockWidth  = blkHeightFinal;
    graphArgs->horScaleKernelArgs.dstBlockHeight = blkWidthFinal; 
    graphArgs->horScaleKernelArgs.numTaps        = 2;
    graphArgs->horScaleKernelArgs.fracBits       = graphArgs->createParams->appCreateParams->fracQFmt;


    graphArgs->dmaReadKernelArgs.srcBlockWidth   = inBlockWidthOrg; 
    graphArgs->dmaReadKernelArgs.srcBlockPitch   = inBlockWidth;
    graphArgs->dmaReadKernelArgs.srcBlockHeight  = inBlockHeight;
    graphArgs->dmaReadKernelArgs.dstBlockWidth   = blkWidthFinal;
    graphArgs->dmaReadKernelArgs.dstBlockHeight  = blkHeightFinal; 
    graphArgs->dmaReadKernelArgs.numTaps         = 2;

    graphArgs->dmaWriteKernelArgs.numInTransfers  = 0;
    graphArgs->dmaWriteKernelArgs.numOutTransfers = 1;
    graphArgs->dmaWriteKernelArgs.transferType    = EDMA_UTILS_TRANSFER_INOUT;

    assignDMAautoIncrementParams(
            (EDMA_UTILS_autoIncrement_transferProperties *)(void*)&graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            (uint16_t    )blkWidthFinal,                                                              /* roiWidth */
            (uint16_t    )blkHeightFinal,                                                             /* roiHeight */
            (uint16_t    )blkWidthFinal,                                                              /* blkWidth */
            (uint16_t    )blkHeightFinal,                                                             /* blkHeight */
            (uint16_t    )blkWidthFinal,                                                              /* extBlkIncrementX */
            (uint16_t    )blkHeightFinal,                                                             /* extBlkIncrementY */
            (uint16_t    )0,                                                                          /* intBlkIncrementX */
            (uint16_t    )0,                                                                          /* intBlkIncrementY */
            (uint32_t    )0,                                                                          /* roiOffset        */
            (uint8_t    *)NULL,                                                                       /* extMemPtr        */
            (uint16_t    )0,                                                                          /* extMemPtrStride  */
            (uint8_t    *)NULL,                                                                       /* interMemPtr      */
            (uint16_t    )blkWidthFinal,                                                              /* interMemPtrStride */
            (uint8_t     )0);                                                                         /* dmaQueNo          */
    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perform actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t YUV_SCALAR_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs)
{

    BAM_ProcessHints hints;
    int32_t status = BAM_S_SUCCESS;

    /* Specify which processing schedule is the best, unsupported for now */
    hints.priority= BAM_COMPUTE_FIRST;

    status = BAM_process(graphMem->graphObj, inArgs, outArgs, &hints);

    return status;

}
int32_t YUV_SCALAR_TI_kernelControl(const BAM_GraphMem *graphMem, uint8_t  inputDataType, uint16_t scaleRatioQ12)
{
    BAM_yuv_scalar_Ctrl_Args  ctlArg;
    int32_t status = BAM_S_SUCCESS;
    int32_t blockIncr = 32;
    YUV_SCALAR_TI_graphArgs * graphArgs = (YUV_SCALAR_TI_graphArgs *)graphMem->graphArgs;
    uint16_t inBlockWidthOrg  = (uint16_t)(((graphArgs->blockWidth   * scaleRatioQ12) >> Q_FORMATE_SCALE_RATIO) + 4U);
    uint16_t  inBlockWidth     = ALIGN_SIZE((uint16_t)inBlockWidthOrg,(uint16_t)blockIncr); 
    uint16_t blkWidthFinal    = graphArgs->blockWidth  ;
    uint16_t blkHeightFinal   = graphArgs->blockHeight ;
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    ctlArg.srcBlockWidth  = inBlockWidthOrg; 
    ctlArg.srcBlockPitch  = inBlockWidth;
    ctlArg.dstBlockWidth  = blkWidthFinal;
    ctlArg.dstBlockHeight = blkHeightFinal; 
    ctlArg.inputDataType  = inputDataType; 

    status= BAM_controlNode(graphHandle, (uint8_t)YUV_VERTICAL_SCALE_NODE, &ctlArg);
    if (status== BAM_S_SUCCESS) 
    {
      if(inputDataType == 0)
      {
        ctlArg.srcBlockWidth  = blkHeightFinal;  
        ctlArg.srcBlockPitch  = blkHeightFinal;
        ctlArg.dstBlockWidth  = blkHeightFinal;
        ctlArg.dstBlockHeight = blkWidthFinal; 
      }
      else
      {
        ctlArg.srcBlockWidth  = 2U*blkHeightFinal;  
        ctlArg.srcBlockPitch  = 2U*blkHeightFinal;
        ctlArg.dstBlockWidth  = 2U*blkHeightFinal;
        ctlArg.dstBlockHeight = (blkWidthFinal/2U); 
      }

      status= BAM_controlNode(graphHandle, (uint8_t)YUV_HORIZONTAL_SCALE_NODE, &ctlArg);
    }

    return status;
}

int32_t YUV_SCALAR_TI_dmaControl(const BAM_GraphMem *graphMem, BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_ctrl_args  *srcDMACtrlArgs, const IVISION_BufPlanes  ivisionBufPlane[])
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    int32_t status = BAM_S_SUCCESS;
    
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;
    YUV_SCALAR_TI_graphArgs * graphArgs = (YUV_SCALAR_TI_graphArgs *)graphMem->graphArgs;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE |  
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIWIDTH | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_ROIHEGIHT;

    /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
    /* Pointer is used in arithmetic or array index expression */
    /* Deviation allowed since, this same address needs to be accessed with an offset  */
    autoIncCtlArgs.updateParams[0].extMemPtr       = ((uint8_t*)ivisionBufPlane[0].buf + ((ivisionBufPlane[0].frameROI.topLeft.y) * ivisionBufPlane[0].width) +  (ivisionBufPlane[0].frameROI.topLeft.x));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane[0].width;
    autoIncCtlArgs.updateParams[0].roiWidth        = ALIGN_SIZE(ivisionBufPlane[0].frameROI.width, graphArgs->blockWidth );
    autoIncCtlArgs.updateParams[0].roiHeight       = ALIGN_SIZE(ivisionBufPlane[0].frameROI.height,graphArgs->blockHeight);
    
       
    status= BAM_controlNode(graphHandle, (uint8_t)SINK_NODE, &autoIncCtlArgs);
    
    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    status= BAM_controlNode(graphHandle, SOURCE_NODE, srcDMACtrlArgs);
    
    if (status!= BAM_S_SUCCESS) {
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto Exit;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }
  
 Exit:
    return status;
}


