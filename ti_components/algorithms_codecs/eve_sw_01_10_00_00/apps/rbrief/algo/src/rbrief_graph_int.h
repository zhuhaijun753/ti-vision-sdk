/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       rbrief_graph_int.h
 *
 *  @brief      This file defines the interface for rBrief graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef RBRIEF_TI_GRAPH_INT_H
#define RBRIEF_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"
#include "bam_rBrief.h"
#include "bam_dma_custom_rbrief_node.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define RBRIEF_GRAPH_OBJ_SIZE             (2080U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define RBRIEF_GRAPH_SCRATCH_SIZE         (676U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define RBRIEF_GRAPH_CONTEXT_SIZE         (2668U)

/*--------------------------------------------------------------------*/
/* These are macros which are algorithm specfic and indicative to BAM */
/* to help decide the optimal block dimensions                        */
/*--------------------------------------------------------------------*/
#define RBRIEF_TI_BLOCK_WIDTH  (48U)
#define RBRIEF_TI_BLOCK_HEIGHT (48U)

/* Number of features to be processed at a time */
#define RBRIEF_TI_NUM_FEATURE (1U)


/** ========================================================
 *  @name   RBRIEF_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          rBrief graph
 *
 *  @field createParams
 *          pointer to the create params passed by user using iVision interface
 *
 *  ===============================================================
 */
typedef struct
{
    RBRIEF_TI_CreateParams  * iRbriefCreateParams;
}RBRIEF_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct RBRIEF_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  rBriefKernelArgs        Parameters for rBrief kernel
  @param  createParams            Creation time parameters
*/
typedef struct
{
  BAM_DMA_CUSTOM_RBRIEF_NODE_args        dmaReadKernelArgs;
  BAM_rBrief_Args                        rBriefKernelArgs;
  RBRIEF_TI_graphCreateParams            *createParams;
} RBRIEF_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_rbrief
 *  @func          RBRIEF_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t RBRIEF_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_rbrief
 *  @func          RBRIEF_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           RBRIEF_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t RBRIEF_TI_graphCreate(const BAM_GraphMem * graphMem,
                                       RBRIEF_TI_graphCreateParams* createParams);

/**
 *******************************************************************************
 *  @ingroup        BAM_rbrief
 *  @func             RBRIEF_TI_graphDmaControl
 *  @brief            This is first function to be called to control the dma parameters for DMA node
 *  @pre              RBRIEF_TI_graphCreate should be called to create graph
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
  int32_t RBRIEF_TI_graphDmaControl(const BAM_GraphMem *graphMem,
          const IVISION_BufDesc *inBufDesc,
          const IVISION_BufDesc *xyListBufDesc,
          const IVISION_BufDesc *levelListBufDesc,
          const IVISION_OutBufs *outBuf);


/**
 *******************************************************************************
 *  @ingroup       BAM_rbrief
 *  @func          RBRIEF_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           RBRIEF_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t RBRIEF_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);



#endif /* RBRIEF_TI_GRAPH_INT_H */

