/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*==========================================================================*/
/**
 *  @file:      block_statistics_graph_int.h
 *
 *  @brief:     This file defines the functions for block statistics graph
 *
 *  @version:   0.2 (Aug 2014) : Base version.
 */
/*==========================================================================*/

#ifndef BLOCK_STATS_GRAPH_INT_H
#define BLOCK_STATS_GRAPH_INT_H

#include <xdais_types.h>
#include <ivision.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "iblock_statistics_ti.h"
#include "bam_block_statistics.h"
#include "edma_utils_autoincrement.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BLOCK_STATS_GRAPH_OBJ_SIZE             (3068U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BLOCK_STATS_GRAPH_SCRATCH_SIZE         (1040U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BLOCK_STATS_GRAPH_CONTEXT_SIZE         (4U)

/**
 * Additional BAM error codes specific to Block Statistics.
 */
#define BLOCK_STATS_BAM_E_CUSTOMFAILEND             (-1024)    /**< BLOCK STATISTICS BAM custom error code end */


/*--------------------------------------------------------------------*/
/**
  @struct BLOCK_STATS_TI_graphConstructParams
  @brief  This structure specifies the properties needed for constructing
          block statistics graph

  @param  imageWidth       Width in pixels of the input image
  @param  imageHeight      Height of the input image
  @param  statBlockWidth   Width of the block over which statistics is
                           computed
  @param  statBlockHeight  Height of the block over which statistics
                           is computed
 */
typedef struct
{
  uint16_t    imageWidth;
  uint16_t    imageHeight;
  uint16_t    statBlockWidth;
  uint16_t    statBlockHeight;
} BLOCK_STATS_TI_graphCreateParams;

/*--------------------------------------------------------------------*/
/**
  @struct BLOCK_STATS_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs      Parameters for DMA node
  @param  blockStatKernelArgs    Parameters for block statistics kernel
  @param  dmaWriteKernelArgs     Parameters for DMA SINK node
  @param  createParams           Creation time parameters
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
  BAM_Block_Statistics_Args          blockStatKernelArgs;
  EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
  BLOCK_STATS_TI_graphCreateParams *createParams;
} BLOCK_STATS_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 for graph
 *  @pre           BLOCK_STATS_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_graphCreate(const BAM_GraphMem * graphMem,
            BLOCK_STATS_TI_graphCreateParams* createParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BLOCK_STATS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs    : Pointer to graph memory structure
 *  @param [in]    outArgs   : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_execute(BAM_GraphMem *graphMem,
           const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       BAM_blockStatistics
 *  @func          BLOCK_STATS_TI_dmaControl
 *  @brief         This function can be called after the graph is created and
 *                 before BLOCK_STATS_TI_execute() to control the source and
 *                 sink node's parameters.
 *  @pre           BLOCK_STATS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem   : Pointer to graph memory structure
 *  @param [in]    inBufDesc  : Pointer to input buffer's descriptions
 *  @param [in]    outMinBufDesc  : Pointer to minimum buffer's descriptions
 *  @param [in]    outMaxBufDesc  : Pointer to maximum buffer's descriptions
 *  @param [in]    outMeanBufDesc : Pointer to mean buffer's descriptions
 *  @param [in]    outVarBufDesc  : Pointer to variance buffer's descriptions
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BLOCK_STATS_TI_dmaControl(const BAM_GraphMem *graphMem,
           const IVISION_BufDesc *inBufDesc,
           const IVISION_BufDesc *outMinBufDesc,
           const IVISION_BufDesc *outMaxBufDesc,
           const IVISION_BufDesc *outMeanBufDesc,
           const IVISION_BufDesc *outVarBufDesc);
#endif
