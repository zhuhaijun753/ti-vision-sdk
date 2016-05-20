/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       feature_matching_graph_int.h
 *
 *  @brief      This file defines the interface for feature matching graph
 *
 *  @version    0.1 (Aug 2014) : Base version.
 */

#ifndef FEATURE_MATCHING_TI_GRAPH_INT_H
#define FEATURE_MATCHING_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"
#include "feature_matching_bam_dma_node.h"
#include "bam_feature_matching.h"

#include "edma_utils_autoincrement.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


#define FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT1     (464U)
#define FEATURE_MATCHING_TI_DESC_LE_32_MAX_NUM_FEAT2     (160U)
#define FEATURE_MATCHING_TI_DESC_LE_32_MIN_NUM_FEAT      (128U)

#define FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT1     (144U)
#define FEATURE_MATCHING_TI_DESC_GT_32_MAX_NUM_FEAT2     (106U)
#define FEATURE_MATCHING_TI_DESC_GT_32_MIN_NUM_FEAT      (32U)

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FEATURE_MATCHING_GRAPH_OBJ_SIZE             (2800U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FEATURE_MATCHING_GRAPH_SCRATCH_SIZE         (520U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FEATURE_MATCHING_GRAPH_CONTEXT_SIZE         (4U)


/** ========================================================
 *  @name   FEATURE_MATCHING_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for
 *          constructing feature matching graph
 *
 *  @field descriptorLength
 *          Length of each feature descriptor in bytes.
 *
 *  ===============================================================
 */
typedef struct
{
  uint16_t       descriptorLength;
}FEATURE_MATCHING_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct FEATURE_MATCHING_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs            Parameters for DMA node
  @param  featMatchKernelArgs          Parameters for feature matching
                                       compute kernel
  @param  createParams                 Creation time parameters
*/
typedef struct
{
  BAM_DMA_NODE_FEAT_MATCH_args            dmaReadKernelArgs;
  BAM_featureMatching_Args                featMatchKernelArgs;
  FEATURE_MATCHING_TI_graphCreateParams  *createParams;
} FEATURE_MATCHING_TI_graphArgs;


/*--------------------------------------------------------------------*/
/**
  @struct FEATURE_MATCHING_TI_graphCtrlArgs
  @brief  This structure is for passing control parameters for BAM graph.

  @param  numDescriptors1 : Number of feature descriptors in list 1
  @param  numDescriptors2 : Number of feature descriptors in list 2
  @param  numDesc1PerIter : Number of descriptors from list 1 to be
                            processed in one iteration
  @param  numDesc2PerIter : Number of descriptors from list 2 to be
                            processed in one iteration
*/
typedef struct
{
  uint16_t  numDescriptors1;
  uint16_t  numDescriptors2;
  uint16_t  minDistanceThres;
  uint16_t  matchConfidence;
  uint16_t  numDesc1PerIter;
  uint16_t  numDesc2PerIter;
} FEATURE_MATCHING_TI_graphCtrlArgs;


/**
 *******************************************************************************
 *  @ingroup       BAM_featureMatching
 *  @func          FEATURE_MATCHING_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FEATURE_MATCHING_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_featureMatching
 *  @func          FEATURE_MATCHING_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           FEATURE_MATCHING_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FEATURE_MATCHING_TI_graphCreate(const BAM_GraphMem * graphMem,
            FEATURE_MATCHING_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_featureMatching
 *  @func          FEATURE_MATCHING_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           FEATURE_MATCHING_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FEATURE_MATCHING_TI_execute(BAM_GraphMem *graphMem,
            const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       BAM_featureMatching
 *  @func          FEATURE_MATCHING_TI_graphControl
 *  @brief         This function can be called after the graph is created and
 *                 before FEATURE_MATCHING_TI_execute() to control the Feature
 *                 matching node's parameters. It allows to set the parameter
 *                 values.
 *  @pre           FEATURE_MATCHING_TI_graphCreate should be called to
 *                 create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inParams  : Pointer to input control parameters
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FEATURE_MATCHING_TI_graphControl(const BAM_GraphMem *graphMem,
        const FEATURE_MATCHING_TI_graphCtrlArgs *inParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_featureMatching
 *  @func          FEATURE_MATCHING_TI_dmaControl
 *  @brief         This function can be called after the graph is created and
 *                 before FEATURE_MATCHING_TI_execute() to control the source
 *                 and sink node's parameters.
 *  @pre           FEATURE_MATCHING_TI_graphCreate should be called to create
 *                 the graph
 *  @param [in]    graphMem   : Pointer to graph memory structure
 *  @param [in]    in1BufDesc : Pointer to input 1 buffer's descriptions
 *  @param [in]    in2BufDesc : Pointer to input 2 buffer's descriptions
 *  @param [in]    outBufDesc : Pointer to output buffer's descriptions
 *  @param [in]    numDesc1PerIter : Number of descriptors from list 1 to be
 *                                   processed in one iteration
 *  @param [in]    numDesc2PerIter : Number of descriptors from list 2 to be
 *                                   processed in one iteration
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FEATURE_MATCHING_TI_dmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *in1BufDesc, const IVISION_BufDesc *in2BufDesc,
        const IVISION_BufDesc *outBufDesc, uint16_t numDesc1PerIter,
        uint16_t numDesc2PerIter);

#endif

