/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       hough_for_lines_graph_int.h
 *
 *  @brief      This file defines the interface for Hough For Lines graph
 *  @version 0.0 (July 2014) : Base version.
 */

#ifndef HOUGH_FOR_LINES_TI_GRAPH_INT_H
#define HOUGH_FOR_LINES_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"
#include "bam_hough_for_lines.h"
#include "bam_dma_custom_hough_for_lines_node.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define HOUGH_FOR_LINES_GRAPH_OBJ_SIZE             (2096U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define HOUGH_FOR_LINES_GRAPH_SCRATCH_SIZE         (416U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define HOUGH_FOR_LINES_GRAPH_CONTEXT_SIZE         (1440U)

/** ========================================================
 *  @name   HOUGH_FOR_LINES_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          hough_for_lines graph
 *
 *  @field createParams
 *          pointer to the create params passed by user using iVision interface
 *
 *  ===============================================================
 */
typedef struct
{
    HOUGH_FOR_LINES_TI_CreateParams  * iHoughForLinesCreateParams;
}HOUGH_FOR_LINES_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct HOUGH_FOR_LINES_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  hough_for_linesKernelArgs        Parameters for hough_for_lines kernel
  @param  createParams            Creation time parameters
*/
typedef struct
{
  HOUGH_FOR_LINES_TI_graphCreateParams            *createParams;
} HOUGH_FOR_LINES_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_hough_for_lines
 *  @func          HOUGH_FOR_LINES_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HOUGH_FOR_LINES_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_hough_for_lines
 *  @func          HOUGH_FOR_LINES_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           HOUGH_FOR_LINES_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HOUGH_FOR_LINES_TI_graphCreate(const BAM_GraphMem * graphMem,
                                       HOUGH_FOR_LINES_TI_graphCreateParams* createParams);

/**
 *******************************************************************************
 *  @ingroup        BAM_hough_for_lines
 *  @func             HOUGH_FOR_LINES_TI_graphDmaControl
 *  @brief            This is first function to be called to control the dma parameters for DMA node
 *  @pre              HOUGH_FOR_LINES_TI_graphCreate should be called to create graph
 *  @param [in]   graphMem  : Pointer to graph memory structure
 *  @param [in]   inBufDesc  : Pointer to inBuf descriptor
 *  @param [in]   xyListBufDesc  : Pointer to xy list buf descriptor
 *  @param [in]   levelListBufDesc  : Pointer to level list buf descriptor
 *  @param [in]   outBufs : Pointer to graph memory structure
 *  @return          status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
  int32_t HOUGH_FOR_LINES_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const HOUGH_FOR_LINES_InArgs * inArgs,
        uint8_t * ptrToList,
        uint8_t * ptrToRhoThetaSpace,
        uint16_t  currListSize);


int32_t HOUGH_FOR_LINES_TI_graphKernelControl(const BAM_GraphMem *graphMem,
        const HOUGH_FOR_LINES_InArgs * inArgs,
        uint16_t  currListSize);

/**
 *******************************************************************************
 *  @ingroup       BAM_hough_for_lines
 *  @func          HOUGH_FOR_LINES_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           HOUGH_FOR_LINES_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HOUGH_FOR_LINES_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);



#endif /* HOUGH_FOR_LINES_TI_GRAPH_INT_H */

