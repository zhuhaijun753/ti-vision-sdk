/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file blockSort_u32_graph.c
 *
 *  @brief  This file implements an applet for block sort
 *
 *  @author TI
 *
 *  @date   19 Dec 2013
 *
 *  Description
 *    This file contains code to perform block sort on every block of a frame
 *    Contains implementation of BLOCK_SORT_U8_TI_graphCreate() and BLOCK_SORT_U8_TI_execute()
 *    at the frame level.
 */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "blockSort_u32_graph_int.h"

#include "bam_blockSortU32.h"
#include "bam_natcBlockSortU32.h"

#include "edma_utils.h"

#include "iBlockSort_u32_ti.h"

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

#ifndef NULL
#define NULL        (void *)0
#endif

/**
 * Kernel Database - used for graph construction
 */
static BAM_KernelHostDBdef bamKernelHostDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelHelperFunc,
        "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_blockSortU32Kernel, &gBAM_TI_blockSortU32HelperFunc,
        "ti_image_blockSortU32", BAM_TI_KERNELID_BLOCK_SORTU32},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc,
        "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_natcBlockSortU32Kernel, &gBAM_TI_natcBlockSortU32HelperFunc,
        "ti_image_natcBlockSortU32", BAM_TI_KERNELID_NATCBLOCK_SORTU32 }

};

/**
 * Kernel Database - used for graph execution
 */
static BAM_KernelExecFuncDBdef bamKernelExecFuncDB[] =
{
        { &gBAM_TI_dmaAutoIncrementReadKernel,  &gBAM_TI_dmaReadAutoIncrementKernelExecFunc,
        "ti_dma_read_autoincrement", BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT},
        { &gBAM_TI_blockSortU32Kernel, &gBAM_TI_blockSortU32ExecFunc,
        "ti_image_blockSortU32", BAM_TI_KERNELID_BLOCK_SORTU32},
        { &gBAM_TI_dmaAutoIncrementWriteKernel, &gBAM_TI_dmaWriteAutoIncrementKernelExecFunc,
        "ti_dma_write_autoincrement", BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT},
        { &gBAM_TI_natcBlockSortU32Kernel, &gBAM_TI_natcBlockSortU32ExecFunc,
        "ti_image_natcBlockSortU32", BAM_TI_KERNELID_NATCBLOCK_SORTU32 }
};

/* CHECK_MISRA("-8.7")  -> Disable rule 8.7 */
/* Name visibility is too wide */
/* Deviation is allowed because we use static keyword to make it local to the file */
static BAM_KernelDBdef gBLOCK_SORT_U32_TI_BAM_kernelDBdef =
{
        sizeof(bamKernelExecFuncDB) / sizeof(bamKernelExecFuncDB[0]),
        bamKernelHostDB,
        bamKernelExecFuncDB
};
/*RESET_MISRA("8.7")  -> Reset rule 8.7*/

static int32_t BLOCK_SORT_U32_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams);

#define SOURCE_NODE 0
#define SORT_NODE   1
#define SINK_NODE   2

int32_t BLOCK_SORT_U32_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
{
    memReq->graphObjSize      = BLOCK_SORT_GRAPH_OBJ_SIZE     ;
    memReq->graphScratchSize  = BLOCK_SORT_GRAPH_SCRATCH_SIZE ;
    memReq->graphcontextSize  = BLOCK_SORT_GRAPH_CONTEXT_SIZE ;
    memReq->graphArgsSize    = sizeof(BLOCK_SORT_U32_TI_graphArgs) ;
    return 0;
}



int32_t BLOCK_SORT_U32_TI_graphCreate(
        const BAM_GraphMem *graphMem,
        BLOCK_SORT_U32_TI_graphCreateParams * createParams)
{
    BAM_CreateGraphParams graphCreateParams;
    int32_t status = BAM_S_SUCCESS;

    /* initilize the sub-handles inside the main handle */
    BLOCK_SORT_U32_TI_graphArgs * graphArgs = (BLOCK_SORT_U32_TI_graphArgs *)graphMem->graphArgs;
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /*------------------------------------------------------------------------------*/
    /* Create NODELIST and EDGE LIST. It should be derived from the algorithm graph */
    /*------------------------------------------------------------------------------*/

    BAM_NodeParams NODELIST[]={\
            {SOURCE_NODE,   BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT,      NULL},
            {SORT_NODE,     BAM_TI_KERNELID_BLOCK_SORTU32,              NULL},
            {SINK_NODE,     BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT,     NULL},
            {BAM_END_NODE_MARKER,       0,                              NULL},\
    };

    NODELIST[SOURCE_NODE].kernelArgs= &graphArgs->dmaReadKernelArgs;
    NODELIST[SORT_NODE].kernelArgs= &graphArgs->sortKernelArgs;
    NODELIST[SINK_NODE].kernelArgs= &graphArgs->dmaWriteKernelArgs;

    BAM_EdgeParams EDGELIST[]= {
            {{SOURCE_NODE,  BAM_SOURCE_NODE_PORT1},             {SORT_NODE,  BAM_BLOCKSORTU32_INPUT_PORT}},\
            {{SORT_NODE,    BAM_BLOCKSORTU32_OUTPUT_PORT},      {SINK_NODE, BAM_SINK_NODE_PORT1}},\
            {{BAM_END_NODE_MARKER, 0},                          {BAM_END_NODE_MARKER, 0}},\
    };

    assert((createParams->blockWidth *  createParams->blockHeight) <= BLOCKSORTU32_MAX_ELEMTS);

    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    status= BAM_initKernelDB(&gBLOCK_SORT_U32_TI_BAM_kernelDBdef);

	if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }
	
    /*---------------------------------------------------------------*/
    /* Initialize Graph creation time parameters                     */
    /*---------------------------------------------------------------*/
    graphCreateParams.coreType= BAM_EVE;
    graphCreateParams.kernelDB= &gBLOCK_SORT_U32_TI_BAM_kernelDBdef;
    graphCreateParams.nodeList= (BAM_NodeParams*)NODELIST;
    graphCreateParams.edgeList= (BAM_EdgeParams*)EDGELIST;
    graphCreateParams.graphMem= graphHandle; /* on the stack */
    graphCreateParams.graphMemSize= BLOCK_SORT_GRAPH_OBJ_SIZE;
    graphCreateParams.onChipScratchMem= graphMem->graphScratch;
    graphCreateParams.onChipScratchMemSize= BLOCK_SORT_GRAPH_SCRATCH_SIZE;
    graphCreateParams.extMem= graphMem->graphcontext; /* passed by the caller, usually in external memory */
    graphCreateParams.extMemSize= BLOCK_SORT_GRAPH_CONTEXT_SIZE;
    graphCreateParams.useSmartMemAlloc= (BOOL)true;
    graphCreateParams.optimizeBlockDim= (BOOL)false;

    graphArgs->createParams= createParams;

    /*---------------------------------------------------------------*/
    /* Initialize the members related to the  kernels init function  */
    /*---------------------------------------------------------------*/
    graphCreateParams.initKernelsArgsFunc= &BLOCK_SORT_U32_TI_initArgs;
    graphCreateParams.initKernelsArgsParams= (void*)graphArgs;

    /* Initialize the structure graphCreateParams.blockDimParams that lists the processing block
     * dimensions as well as the step increment sizes used during the block
     * dimension optimization if enabled
     */
    graphCreateParams.blockDimParams.blockWidth= createParams->blockWidth;
    graphCreateParams.blockDimParams.blockHeight= createParams->blockHeight;
    graphCreateParams.blockDimParams.blockWidthStep= 0;
    graphCreateParams.blockDimParams.blockHeightStep= 0;
    graphCreateParams.blockDimParams.blockWidthDivisorOf= createParams->imgFrameWidth;
    graphCreateParams.blockDimParams.blockHeightDivisorOf= createParams->imgFrameHeight;

    status = BAM_createGraph(&graphCreateParams, &graphHandle);

    if(status != BAM_S_SUCCESS) {
        goto Exit;
    }

    /*
     * We check whether one-block processing of input data in internal memory needs to be enabled by checking if the processing block dimensions
     * are equal to the frame's width and height. We also check if the pointers createParams->srcImBuf and createParams->dstImBuf
     * are indeed already in VCOP's internal memory acceptable range.
     * If all of these conditions are true, then we override the sort node's input and output block's pointer values (derived by BAM during BAM_createGraph()) with the ones
     * contained in createParams->srcImBuf and createParams->dstImBuf. For that, we use the BAM_controlNode() function as these arguments
     * are not exposed in the sort kernel's BAM_BlockSortU32_Args structure, used at create time.
     */
    if ((createParams->blockWidth== createParams->imgFrameWidth) && (createParams->blockHeight== createParams->imgFrameHeight)
#if (!VCOP_HOST_EMULATION)
            && (createParams->srcImBuf>= (uint32_t*)ibufla) && (createParams->srcImBuf<= (uint32_t*)ibufha) && (createParams->dstImBuf >=  (uint32_t*)ibufha) && (createParams->dstImBuf <= (uint32_t*)ibuflb)) {
#else
        ) {
#endif
            BAM_BlockSortU32_CtlArgs blockSortCtlArgs;
            
            blockSortCtlArgs.ctlCmdId= BAM_BLOCKSORT_U32_CMD_SET_PTR;
            blockSortCtlArgs.inputPtr= (void*)createParams->srcImBuf;
            blockSortCtlArgs.outputPtr= (void*)createParams->dstImBuf;
            status= BAM_controlNode(graphHandle, (uint8_t)SORT_NODE, &blockSortCtlArgs);

            if (status!= BAM_S_SUCCESS) {
                goto Exit;
            }
    }

    createParams->blockWidth= graphCreateParams.blockDimParams.blockWidth;
    createParams->blockHeight= graphCreateParams.blockDimParams.blockHeight;

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
    param->blkOffset            = 0;
    param->extMemPtr            = extMemPtr;
    param->extMemPtrStride      = extMemPtrStride ;
    param->interMemPtr          = interMemPtr ;
    param->interMemPtrStride    = interMemPtrStride;
    param->dmaQueNo             = dmaQueNo;
}

/* BLOCK_SORT_U32_initArgs() is callback function that BAM will call to initialize all the kernes' arguments
 * It will be called several times during the search for the best block dimensions
 * */
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter blockDimParams is not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type BAM_InitkernelsArgsFunc in order to be passed to structure BAM_CreateGraphParams */
static int32_t BLOCK_SORT_U32_TI_initArgs(void *initKernelsArgs, BAM_BlockDimParams *blockDimParams) {
/* RESET_MISRA("16.7")  -> Reset rule 16.7  */
    int32_t status = BAM_S_SUCCESS;
    BLOCK_SORT_U32_TI_graphArgs *graphArgs= (BLOCK_SORT_U32_TI_graphArgs*)initKernelsArgs;

    int16_t blkWidthFinal= 0;
    int16_t blkHeightFinal= 0;

    blkWidthFinal = blockDimParams->blockWidth;
    blkHeightFinal = blockDimParams->blockHeight;

    assert((graphArgs->createParams->imgFrameWidth % blkWidthFinal) == 0);
    assert((graphArgs->createParams->imgFrameHeight % blkHeightFinal) == 0);

    graphArgs->sortKernelArgs.numElmts= blkWidthFinal*blkHeightFinal;

    graphArgs->dmaReadKernelArgs.numInTransfers                                           = 1;
    graphArgs->dmaReadKernelArgs.transferType                                             = EDMA_UTILS_TRANSFER_IN;

    assignDMAautoIncrementParams(
            &graphArgs->dmaReadKernelArgs.transferProp[BAM_SOURCE_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth*sizeof(uint32_t), /* roiWidth */
            graphArgs->createParams->imgFrameHeight, /* roiHeight */
            (uint16_t)blkWidthFinal*sizeof(uint32_t),                         /* blkWidth */
            (uint16_t)blkHeightFinal,                                           /* blkHeight */
            (uint16_t)blkWidthFinal*sizeof(uint32_t),                                              /* extBlkIncrementX */
            (uint16_t)blkHeightFinal,                                                             /* extBlkIncrementY */
            0,                                                                          /* intBlkIncrementX */
            0,                                                                          /* intBlkIncrementY */
            0,                                                                          /* roiOffset        */
            NULL,                                                                       /* extMemPtr        */
            0,                                                                          /* extMemPtrStride  */
            NULL,                                                                       /* interMemPtr      */
            (uint16_t)blkWidthFinal*sizeof(uint32_t),                                             /* interMemPtrStride */
            0);                                                                         /* dmaQueNo          */

    graphArgs->dmaWriteKernelArgs.numOutTransfers = 1;
    graphArgs->dmaWriteKernelArgs.transferType    = EDMA_UTILS_TRANSFER_OUT;

    assignDMAautoIncrementParams(
            &graphArgs->dmaWriteKernelArgs.transferProp[BAM_SINK_NODE_PORT1],
            graphArgs->createParams->imgFrameWidth*sizeof(uint32_t), /* roiWidth */
            graphArgs->createParams->imgFrameHeight, /* roiHeight */
            (uint16_t)blkWidthFinal*sizeof(uint32_t),                         /* blkWidth */
            (uint16_t)blkHeightFinal,                                           /* blkHeight */
            (uint16_t)blkWidthFinal*sizeof(uint32_t),                                              /* extBlkIncrementX */
            (uint16_t)blkHeightFinal,                                                             /* extBlkIncrementY */
            0,                                                                          /* intBlkIncrementX */
            0,                                                                          /* intBlkIncrementY */
            0,                                                                          /* roiOffset        */
            NULL,                                                                       /* extMemPtr        */
            0,                                                                          /* extMemPtrStride  */
            NULL,                                                                       /* interMemPtr      */
            (uint16_t)blkWidthFinal*sizeof(uint32_t),                                             /* interMemPtrStride */
            1U);                                                                         /* dmaQueNo          */

    return status;
}

/*-------------------------------------------------------------------------*/
/* Function to perform actual execution                                    */
/*-------------------------------------------------------------------------*/
int32_t BLOCK_SORT_U32_TI_execute(
        BAM_GraphMem * graphMem,
        const BAM_InBufs *inBufs, const BAM_OutBufs *outBufs,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs, const BAM_ProcessHints *hints)
{
    int32_t status = BAM_S_SUCCESS;

    if ((hints->priority== BAM_SINGLE_BLOCK_NO_EDMA) || (hints->priority== BAM_SINGLE_BLOCK)) {
        BAM_processSingleBlock(graphMem->graphObj, inBufs, outBufs, inArgs, outArgs, hints);
    }
    else {
        BAM_process(graphMem->graphObj, inArgs, outArgs, hints);
    }

    return status;

}

int32_t BLOCK_SORT_U32_TI_dmaControl(const BAM_GraphMem *graphMem, const IVISION_BufDesc *inBufDesc, const IVISION_BufDesc *outBufDesc)
{
    EDMA_UTILS_autoIncrement_updateParams autoIncCtlArgs;
    uint8_t (*buf)[];
    const IVISION_BufPlanes * ivisionBufPlane= &inBufDesc->bufPlanes[0];
    int32_t status = BAM_S_SUCCESS;
    
    /* initilize the sub-handles inside the main handle */
    BAM_GraphHandle graphHandle = (BAM_GraphHandle)graphMem->graphObj;

    /* Initialize the control parameters for the SOURCE auto-increment DMA node */
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

    buf= (uint8_t (*)[])ivisionBufPlane->buf;
    autoIncCtlArgs.updateParams[0].extMemPtr= &(*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x];
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;
    
    status= BAM_controlNode(graphHandle, SOURCE_NODE, &autoIncCtlArgs);
    
    if (status!= BAM_S_SUCCESS) {
        goto Exit;
    }
    
    /* Initialize the control parameters for the SINK auto-increment DMA node */
    ivisionBufPlane= &outBufDesc->bufPlanes[0];
    buf= (uint8_t (*)[])ivisionBufPlane->buf;
    
    autoIncCtlArgs.updateMask= EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR | EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;
    
    autoIncCtlArgs.updateParams[0].extMemPtr= &(*buf)[(ivisionBufPlane->frameROI.topLeft.y * ivisionBufPlane->width) + ivisionBufPlane->frameROI.topLeft.x];
    autoIncCtlArgs.updateParams[0].extMemPtrStride = ivisionBufPlane->width;

    status= BAM_controlNode(graphHandle, (uint8_t)SINK_NODE, &autoIncCtlArgs);

 Exit:
    return status;
}




