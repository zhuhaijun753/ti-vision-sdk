/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       filter_2d_graph_int.h
 *
 *  @brief      This file defines the interface for graph for 2d filter
 *  @version 0.0 (Jan 2014) : Base version.
 */

#ifndef FILTER_2D_TI_GRAPH_INT_H
#define FILTER_2D_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "edma_utils_autoincrement.h"

#include "bam_yuv420_fir2d_separable.h"
#include "bam_histogram.h"
#include "bam_contrast_stretching.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FILTER_2D_GRAPH_OBJ_SIZE             (4260U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FILTER_2D_GRAPH_SCRATCH_SIZE         (1404U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FILTER_2D_GRAPH_CONTEXT_SIZE         (4U)


#define FILTER_2D_TI_ROUND_BIT_POS (4U)



/** ========================================================
 *  @name   FILTER_2D_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          rBrief graph
 *
 *  @field createParams
 *          pointer to the create params passed by user using iVision interface
 *
 * @ field ptrToRemapCtrlArgs
 *         it is pointer to the memory for ctrl arguments for remap kernel
 *  ===============================================================
 */
typedef struct
{
  FILTER_2D_CreateParams * ifilterCreateParams;
}FILTER_2D_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct FILTER_2D_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  filter2dYArgs  Parameters for filter 2d
  @param  filter2dUvArgs      Parameters for filter 2d
  @param  dmaWriteKernelArgs       Parameters for DMA SINK node
  @param  createParams            Creation time parameters
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam      dmaReadKernelArgs;
  BAM_Yuv420_fir2dseparable_Args          filter2dYArgs;
  BAM_Yuv420_fir2dseparable_Args          filter2dUvArgs;
  BAM_Histogram_Args                      histogramArgs;
  BAM_ContrastStretching_Args             contrastStretchingArgs;
  EDMA_UTILS_autoIncrement_initParam      dmaWriteKernelArgs;
  FILTER_2D_TI_graphCreateParams *createParams;
} FILTER_2D_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FILTER_2D_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FILTER_2D_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FILTER_2D_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           FILTER_2D_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FILTER_2D_TI_graphCreate(const BAM_GraphMem * graphMem,
                                       FILTER_2D_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FILTER_2D_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           FILTER_2D_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FILTER_2D_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);


/**
 *******************************************************************************
 *  @ingroup       filter 2D
 *  @func          FILTER_2D_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before IMAGE_PYRAMID_U8_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           FILTER_2D_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    filterCoefWidth  : Filter Coefiicient width
 *  @param [in]    filterCoefHeight  : Filter Coefiicient height
 *  @param [in]    sinkNodeId  : Id of the Sink Node
 *  @param [in]    inBufs  : Pointer to input buffer's descriptions
 *  @param [in]    outBufs : Pointer to output buffer's descriptions
 *  @param [out]    effectiveImageWidth: Effective output width for the filter
 *  @param [out]    effectiveImageHeight:Effective output height for the filter
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FILTER_2D_TI_dmaControl(const BAM_GraphMem *graphMem,
                                          uint8_t filterCoefWidth,
                                          uint8_t filterCoefHeight,
                                          uint8_t sinkNodeId,
                                          const IVISION_BufDesc *inBufDesc,
                                          const IVISION_BufDesc *outBufDesc,
                                          uint16_t * effectiveImageWidth,
                                          uint16_t * effectiveImageHeight
                                          );


/**
 *******************************************************************************
 *  @ingroup       filter 2D
 *  @func          FILTER_2D_TI_getHist8CopyBuf
 *  @brief         This function should be called after the graph is created. This function gives the
                        internnal memory address of histogram 8 copy buffer
 *  @pre           FILTER_2D_TI_graphCreate should be called to create graph
 *  @param [in]    imageWidth  : Input Image Width
 *  @param [in]    imageWidth  : Input Image Height
 *  @param [out]    effDims  : Pointer to effective dimension structure
 *  @return         status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FILTER_2D_TI_getEffectiveDimensionsUsed(
                                        uint16_t imageWidth,
                                        uint16_t imageHeight,
                                        FILTER_2D_EffectiveDims * effDims);


/**
 *******************************************************************************
 *  @ingroup       filter 2D
 *  @func          FILTER_2D_TI_setContrastStretchingArgs
 *  @brief         This function should be called after the graph is created. This function set the control
 *                    arguments of contrast stretching kernel
 *  @pre           FILTER_2D_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    minVal  : minVal for histogram
 *  @param [in]    scaleFactorQ16  : Scaling factor in Q16 format. Scale factor is
 *                                             calculated using following formula.
 *                               1 / ( maxVal - minVal) in Q16 format;
 *  @return         status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
 int32_t FILTER_2D_TI_setContrastStretchingArgs(const  BAM_GraphMem * graphMem,
                                                    uint32_t minVal,
                                                    uint32_t scaleFactorQ16);


/**
 *******************************************************************************
 *  @ingroup       filter 2D
 *  @func          FILTER_2D_TI_getHist8CopyBuf
 *  @brief         This function should be called after the graph is created. This function gives the
                        internnal memory address of histogram 8 copy buffer
 *  @pre           FILTER_2D_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @return        Returns the pointer to the histogram 8 copy buffer. Returns NULL if error occurs
 *  @remarks
 *              -# None
 *******************************************************************************
 */
uint32_t * FILTER_2D_TI_getHist8CopyBuf(const  BAM_GraphMem * graphMem);

/**
 *******************************************************************************
 *  @ingroup       filter 2D
 *  @func          FILTER_2D_TI_setHistogramImageDim
 *  @brief         This function should be called after the graph is created. This function
 *                    sets the valid region in which histogram kernel should work
 *  @pre           FILTER_2D_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    imageWidth  : Image Width
 *  @param [in]    imageHeight  : Image Height
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FILTER_2D_TI_setHistogramImageDim(const  BAM_GraphMem * graphMem,
                                                  uint16_t imageWidth,
                                                  uint16_t imageHeight);


#endif /* FILTER_2D_TI_GRAPH_INT_H */

