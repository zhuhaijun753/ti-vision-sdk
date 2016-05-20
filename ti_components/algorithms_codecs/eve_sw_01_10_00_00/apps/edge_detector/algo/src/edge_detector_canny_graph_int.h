/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       edge_detector_canny_graph_int.h
 *
 *  @brief      This file defines the interface for graph for canny edge detector
 *  @version 0.0 (Dec 2014) : Base version.
 */

#ifndef EDGE_DETECTOR_CANNY_GRAPH_INT_H_
#define EDGE_DETECTOR_CANNY_GRAPH_INT_H_

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "edma_utils_autoincrement.h"
#include "bam_canny_non_maximum_suppression.h"
#include "bam_gradXYmag.h"
#include "bam_yuv420_fir2d_separable.h"


#define EDGE_DETECTOR_CANNY_MAX_BLOCK_WIDTH   (128U)
#define EDGE_DETECTOR_CANNY_MAX_BLOCK_HEIGHT  (60U)

#define EDGE_DETECTOR_CANNY_OUT_BLOCK_WIDTH   (44U)
#define EDGE_DETECTOR_CANNY_OUT_BLOCK_HEIGHT  (44U)

#define EDGE_DETECTOR_CANNY_FILTER_SIZE (3)
/* Total border for Canny edge detector comprises of following 3 kernels :
Filter                          : total border of 2
Gradient and magnitude : total border of 2
Canny NMS                 : total border of 2
Hence total border size would be 6 */
#define EDGE_DETECTOR_CANNY_FILTER_BORDER   (2U)
#define EDGE_DETECTOR_CANNY_GRADIENT_BORDER (2U)
#define EDGE_DETECTOR_CANNY_NMS_BORDER      (2U)

#define EDGE_DETECTOR_CANNY_BORDER (EDGE_DETECTOR_CANNY_FILTER_BORDER + EDGE_DETECTOR_CANNY_GRADIENT_BORDER + EDGE_DETECTOR_CANNY_GRADIENT_BORDER)

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define EDGE_DETECTOR_CANNY_GRAPH_OBJ_SIZE             (3992)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define EDGE_DETECTOR_CANNY_GRAPH_SCRATCH_SIZE         (1456)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define EDGE_DETECTOR_CANNY_GRAPH_CONTEXT_SIZE         (4)




/** ========================================================
 *  @name   EDGE_DETECTOR_CANNY_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          NMS graph
 *
 *  @field createParams
 *          pointer to the create params passed by user using iVision interface
 *
 *  ===============================================================
 */
typedef struct
{
  EDGE_DETECTOR_TI_CreateParams * iEdgeDetectorCreateParams;
}EDGE_DETECTOR_CANNY_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct EDGE_DETECTOR_CANNY_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  createParams                Pointer to grarh Create params
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam      dmaReadKernelArgs;
  BAM_Yuv420_fir2dseparable_Args          filter2dArgs;
  BAM_GradXYmag_Args                      gradientXyArgs;
  BAM_CannyNonMaximumSuppression_Args     cannyNmsArgs;
  EDMA_UTILS_autoIncrement_initParam      dmaWriteKernelArgs;
  EDGE_DETECTOR_CANNY_TI_graphCreateParams *createParams;
  uint8_t                                  filterCoeff[9];
} EDGE_DETECTOR_CANNY_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          EDGE_DETECTOR_CANNY_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t EDGE_DETECTOR_CANNY_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          EDGE_DETECTOR_CANNY_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           EDGE_DETECTOR_CANNY_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    createParams   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t EDGE_DETECTOR_CANNY_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                      EDGE_DETECTOR_CANNY_TI_graphCreateParams * createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          EDGE_DETECTOR_CANNY_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           EDGE_DETECTOR_CANNY_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t EDGE_DETECTOR_CANNY_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          EDGE_DETECTOR_CANNY_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before IMAGE_PYRAMID_U8_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           EDGE_DETECTOR_CANNY_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    winWidth  : Window Width for NMS
 *  @param [in]    winHeight  : Window Height for NMSt
 *  @param [in]    inElemSize  : Input Element size for NMS
 *  @param [in]    computeWidth  : Compute Width used by kernel
 *  @param [in]    computeHeight  : Compute Height used by kernel
 *  @param [in]    inBufDesc  : Pointer to buffer discriptor for input Buffer
 *  @param [in]    outBufDesc  :Pointer to buffer discriptor for output Buffer
 *  @param [in]    ptrToListSize  : Pointer to the area where size of list will be stored
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t EDGE_DETECTOR_CANNY_TI_dmaControl(
                                const BAM_GraphMem *graphMem,
                                uint16_t imageWidth,
                                uint16_t imageHeight,
                                uint16_t inputPitch,
                                uint16_t outputPitch,
                                uint8_t  *inputDataPtr,
                                uint8_t  *outputDataPtr,
                                uint8_t  outputFormat
                                );


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          EDGE_DETECTOR_CANNY_TI_kernelControl
 *  @brief         This function should be called after the graph is created. This function set the control
 *                    arguments of contrast stretching kernel
 *  @pre           EDGE_DETECTOR_CANNY_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to the input args or the applet
 *  @param [in]    imageWidth  : Image width
 *  @param [in]    inElemSize  : Input Element size for NMS
 *  @param [in]    computeWidth  : Compute Width used by kernel
 *  @param [in]    computeHeight  : Compute Height used by kernel
 *  @return         status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t EDGE_DETECTOR_CANNY_TI_kernelControl( const BAM_GraphMem * graphMem,
                                  uint8_t lowThreshold,
                                  uint8_t highThreshold
                                  );



#endif /* EDGE_DETECTOR_CANNY_GRAPH_INT_H_ */

