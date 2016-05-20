/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       glcm_graph_int.h
 *
 *  @brief      This file defines the interface for Gray-level co-occurrence
 *              matrix graph
 *
 *  @version    0.1 (Jan 2014) : Base version.
 */

#ifndef GLCM_TI_GRAPH_INT_H
#define GLCM_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"
#include "glcm_bam_dma_node.h"
#include "bam_intensity_scaling.h"
#include "bam_glcm.h"

#include "edma_utils_autoincrement.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define GLCM_GRAPH_OBJ_SIZE             (2808U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define GLCM_GRAPH_SCRATCH_SIZE         (468U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define GLCM_GRAPH_CONTEXT_SIZE         (4U)


/** ========================================================
 *  @name   GLCM_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          Gray-level co-occurrence matrix graph
 *
 *  @field numPoints
 *          Number of points to be processed by kernel per compute call
 *
 *  @field sensitivityParam
 *          Sensitivity parameter for Harris score computation. This is in
 *          Q1.15 format.
 *
 *  ===============================================================
 */
typedef struct
{
    uint16_t    imageWidth;
    uint16_t    imageHeight;
    uint8_t     numLevels;
    uint8_t     loPixelVal;
    uint8_t     hiPixelVal;
    uint8_t     numDirections;
    int8_t      (*rowOffset)[];
    int8_t      (*colOffset)[];
}GLCM_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct GLCM_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs            Parameters for DMA node
  @param  intensityScalingKernelArgs   Parameters for intensity scaling
                                       kernel
  @param  glcmKernelArgs               Parameters for glcm compute
                                       kernel
  @param  createParams                 Creation time parameters
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
  BAM_Intensity_scaling_Args         intensityScalingKernelArgs;
  BAM_Glcm_Args                      glcmKernelArgs;
  GLCM_TI_graphCreateParams         *createParams;
} GLCM_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_sparseHarrisScore
 *  @func          GLCM_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t GLCM_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_sparseHarrisScore
 *  @func          GLCM_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           GLCM_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t GLCM_TI_graphCreate(const BAM_GraphMem * graphMem,
            GLCM_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_sparseHarrisScore
 *  @func          GLCM_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           GLCM_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t GLCM_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       BAM_glcm
 *  @func          GLCM_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before GLCM_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           GLCM_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inBufs  : Pointer to input buffer's descriptions
 *  @param [in]    outBufs : Pointer to output buffer's descriptions
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t GLCM_TI_dmaControl(const BAM_GraphMem *graphMem, const IVISION_BufDesc *inBufDesc, uint32_t *intGlcmBufAddr);

#endif

