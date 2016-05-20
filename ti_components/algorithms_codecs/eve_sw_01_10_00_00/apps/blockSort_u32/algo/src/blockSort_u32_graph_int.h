/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       blockSort_u32_graph_int.h
 *
 *  @brief      This file defines the interface for fast9 corner detect graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef BLOCK_SORT_U32_TI_GRAPH_INT_H
#define BLOCK_SORT_U32_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "bam_blockSortU32.h"
#include "bam_natcBlockSortU32.h"

#include "edma_utils_autoincrement.h"

#include "iBlockSort_u32_ti.h"

#define MAX_KERNEL_ID (255)

typedef enum
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT=0,
    BAM_TI_KERNELID_BLOCK_SORTU32=1,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT=2,
    BAM_TI_KERNELID_NATCBLOCK_SORTU32=3,
    BAM_TI_KERNELID_MAX = MAX_KERNEL_ID
} BAM_TI_KernelID;

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#if (VCOP_HOST_EMULATION)
#define BLOCK_SORT_GRAPH_OBJ_SIZE             (2664)
#else
#define BLOCK_SORT_GRAPH_OBJ_SIZE             (2460)
#endif
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define BLOCK_SORT_GRAPH_SCRATCH_SIZE         (884)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define BLOCK_SORT_GRAPH_CONTEXT_SIZE         (3324)

/** ========================================================
 *  @name   BLOCK_SORT_U32_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          harris corner detect graph
 *
 * @param  imgFrameWidth
 *         Width in bytes for the input image
 *
 * @param  imgFrameHeight
 *         height in number of lines for the input image
 *
 * @param  activeImgWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
 *                          For this function, it should always be equal to (createParams->imgFrameWidth)
 *
 * @param  activeImgHeight   Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
 *                           For this function, it should always be equal to (createParams->imgFrameHeight)
 *
 * @param  blockWidth
 *         Width of each block to be sorted
 *
 * @param  blockheight
 *         Height of each block to be sorted
 *
 * @param  srcImBuf
 *         This an output parameter filled by BLOCK_SORT_U32_TI_graphCreate(). It is used in one block mode, in case the function is called to process one block of elements, it can directly write the input data to the address returned in this member srcImBuf
 *
 * @param  dstImBuf
 *         This an output parameter filled by BLOCK_SORT_U32_TI_graphCreate(). It is used in one block mode, in case the function is called to process one block of elements, it can directly read the output data from the address returned in this member dstImBuf
 *
 *  ===============================================================
 */
typedef struct
{
    uint16_t      imgFrameWidth;
    uint16_t      imgFrameHeight;

    uint16_t      activeImgWidth;
    uint16_t      activeImgHeight;

    uint16_t      blockWidth;
    uint16_t      blockHeight;

    uint32_t     *srcImBuf;
    uint32_t     *dstImBuf;

}BLOCK_SORT_U32_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct BLOCK_SORT_U32_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  BAM_BlockSortU32_Args   Parameters for block sorting kernel
  @param  createParams            Creation time parameters
 */
typedef struct
{
    EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
    EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
    BAM_BlockSortU32_Args           sortKernelArgs;
    BLOCK_SORT_U32_TI_graphCreateParams *createParams;
} BLOCK_SORT_U32_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_blockSort_u32
 *  @func          BLOCK_SORT_U32_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_SORT_U32_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockSort_u32
 *  @func          BLOCK_SORT_U32_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           BLOCK_SORT_U32_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_SORT_U32_TI_graphCreate(const BAM_GraphMem * graphMem,
        BLOCK_SORT_U32_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_blockSort_u32
 *  @func          BLOCK_SORT_U32_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BLOCK_SORT_U32_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inBufs  : Pointer to graph memory structure
 *  @param [in]    outBufs : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_SORT_U32_TI_execute(BAM_GraphMem *graphMem,
        const BAM_InBufs *inBufs, const BAM_OutBufs *outBufs,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs, const BAM_ProcessHints *hints);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockSort_u32
 *  @func          BLOCK_SORT_U32_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before BLOCK_SORT_32_TI_execute()
 *                 to control the source and sink node's parameters. 
 *  @pre           BLOCK_SORT_U32_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inBufs  : Pointer to input buffer's descriptions
 *  @param [in]    outBufs : Pointer to output buffer's descriptions
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_SORT_U32_TI_dmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *inBufDesc, const IVISION_BufDesc *outBufDesc);

#endif

