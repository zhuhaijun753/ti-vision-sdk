/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*==========================================================================*/
/**
 *  @file:      median_filter_graph_int.h
 *
 *  @brief:     This file defines the functions for median filtering
 *
 *  @version:   0.2 (July 2014) : Base version.
 */
/*==========================================================================*/

#ifndef MEDIAN_FILTER_GRAPH_INT_H
#define MEDIAN_FILTER_GRAPH_INT_H

#include <xdais_types.h>
#include <ivision.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "imedian_filter_ti.h"
#include "bam_median_filter.h"
#include "bam_median3x3.h"
#include "edma_utils_autoincrement.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))

#define ALIGNED_DIM(IMG_DIM, BLK_DIM, OVERLAP) ((((IMG_DIM) - (OVERLAP)) + ((BLK_DIM) - (OVERLAP) - 1U))/((BLK_DIM) - (OVERLAP))*((BLK_DIM) - (OVERLAP)) + (OVERLAP))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define MEDIAN_FILTER_GRAPH_OBJ_SIZE             (2200U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define MEDIAN_FILTER_GRAPH_SCRATCH_SIZE         (988U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define MEDIAN_FILTER_GRAPH_CONTEXT_SIZE         (4U)

/**
  These are macros which are algorithm specfic and indicative of
  maximum block dimensions that can be used
*/
#define MEDIAN_FILTER_MAX_BLK_WIDTH              (64U)
#define MEDIAN_FILTER_MAX_BLK_HEIGHT             (62U)

/**
 * Additional BAM error codes specific to Median Filter.
 */
#define MEDIAN_FILTER_BAM_E_CUSTOMFAILEND             (-1024)    /**< MEDIAN FILTER BAM custom error code end */


/*--------------------------------------------------------------------*/
/**
  @struct MEDIAN_FILTER_TI_graphConstructParams
  @brief  This structure specifies the properties needed for constructing
          median filter graph

  @param  imageWidth    Width in pixels of the input image
  @param  imageHeight   Height of the input image
  @param  blockWidth    Width of the block over which median has to be
                        computed
  @param  blockHeight   Height of the block over which median has to be
                        computed
  @param  stepSizeHorz  Number of pixels by which the block has to be
                        advanced horizontally
  @param  stepSizeVert  Number of lines by which the block has to be
                        advanced vertically
 */
typedef struct
{
  uint16_t    imageWidth;
  uint16_t    imageHeight;
  uint8_t     blockWidth;
  uint8_t     blockHeight;
  uint16_t    stepSizeHorz;
  uint16_t    stepSizeVert;
} MEDIAN_FILTER_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct MEDIAN_FILTER_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs      Parameters for DMA node
  @param  medianFilterKernelArgs Parameters for large block median filter kernel
  @param  median3x3KernelArgs    Parameters for 3x3 median filtering kernel
  @param  dmaWriteKernelArgs     Parameters for DMA SINK node
  @param  createParams           Creation time parameters
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
  BAM_Median_Filter_Args             medianFilterKernelArgs;
  BAM_Median3x3_Args                 median3x3KernelArgs;
  EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
  MEDIAN_FILTER_TI_graphCreateParams *createParams;
} MEDIAN_FILTER_TI_graphArgs;


/**
 *******************************************************************************
 *  @ingroup       BAM_medianFilter
 *  @func          MEDIAN_FILTER_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t MEDIAN_FILTER_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_medianFilter
 *  @func          MEDIAN_FILTER_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           MEDIAN_FILTER_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t MEDIAN_FILTER_TI_graphCreate(const BAM_GraphMem * graphMem,
            MEDIAN_FILTER_TI_graphCreateParams* createParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_medianFilter
 *  @func          MEDIAN_FILTER_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           MEDIAN_FILTER_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs    : Pointer to graph memory structure
 *  @param [in]    outArgs   : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t MEDIAN_FILTER_TI_execute(BAM_GraphMem *graphMem,
            const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       BAM_medianFilter
 *  @func          MEDIAN_FILTER_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before
 *                 MEDIAN_FILTER_TI_execute() to control the source and sink node's parameters.
 *  @pre           MEDIAN_FILTER_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem   : Pointer to graph memory structure
 *  @param [in]    inBufDesc  : Pointer to input buffer's descriptions
 *  @param [in]    outBufDesc : Pointer to output buffer's descriptions
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t MEDIAN_FILTER_TI_dmaControl(const BAM_GraphMem *graphMem,
            const IVISION_BufDesc *inBufDesc,
            const IVISION_BufDesc *outBufDesc);

#endif
