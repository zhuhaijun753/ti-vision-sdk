/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       harrisCornerDetection_graph_int.h
 *
 *  @brief      This file defines the interface for fast9 corner detect graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef HARRIS_CORNER_DETECTION_32_TI_GRAPH_INT_H
#define HARRIS_CORNER_DETECTION_32_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "bam_gradXYmag.h"
#include "bam_harrisScore_32_7x7.h"
#include "bam_nonMaxSuppress_mxn_S32.h"
#include "bam_generateList.h"

#include "bam_natcGradXYmag.h"
#include "bam_natcHarrisScore_32_7x7.h"
#include "bam_natcNonMaxSuppress_mxn_S32.h"
#include "bam_natcGenerateList.h"

#include "bam_dma_one_shot_node.h"

#include "edma_utils_autoincrement.h"

#include "iHarrisCornerDetection32_ti.h"

#define MAX_KERNEL_ID (255)

typedef enum
{
  BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT = 0,
  BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT = 1,
  BAM_TI_KERNELID_DMAWRITE_ONESHOT = 2,
  BAM_TI_KERNELID_GRAD_XYMAG = 3,
  BAM_TI_KERNELID_HARRISSCORE_32_7x7= 4,
  BAM_TI_KERNELID_HARRISSCORE_32_METHOD_B=5,
  BAM_TI_KERNELID_NONMAXSUPPRESS_MxN= 6,
  BAM_TI_KERNELID_NONMAXSUPPRESS_MxN_BINPACK= 7,
  BAM_TI_KERNELID_GENERATELIST= 8,
  BAM_TI_KERNELID_NATCGRAD_XYMAG= 9,
  BAM_TI_KERNELID_NATCHARRISSCORE_32_7x7= 10,
  BAM_TI_KERNELID_NATCNONMAXSUPPRESS_MxN= 11,
  BAM_TI_KERNELID_NATCGENERATELIST= 12,
  BAM_TI_KERNELID_MAX = MAX_KERNEL_ID
} BAM_TI_KernelID;

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define HARRIS_CORNER_DETECTION_GRAPH_OBJ_SIZE             (5320)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define HARRIS_CORNER_DETECTION_GRAPH_SCRATCH_SIZE         (1872)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
  For this algorithm actually 0 bytes is necessary but since we already allocate a memTab
  for this purpose, we just set the size to a non-zero value such as 1 bytes
  so malloc() doesn't fail. Later if actual external memory is required, it is easy
  just to update the below number
 */
#define HARRIS_CORNER_DETECTION_GRAPH_CONTEXT_SIZE         (1)

/*--------------------------------------------------------------------*/
/* These are macros which are algorithm specfic and indicative to BAM */
/* to help decide the optimal block dimensions                        */
/*--------------------------------------------------------------------*/
#define HARRIS_CORNER_DETECTION_BLK_WIDTH      32 /* Minimum width of the processing block that will be picked by the function */
#define HARRIS_CORNER_DETECTION_BLK_HEIGHT     24/* Minimum height of the processing block that will be picked by the function */

#define HARRIS_CORNER_DETECTION_BLK_WIDTH_STEP 8 /* Step size used during the search for the best processing block's width */
#define HARRIS_CORNER_DETECTION_BLK_HEIGHT_STEP 2 /* Step size used during the search for the best processing block's height */

/** ========================================================
 *  @name   HARRIS_CORNER_DETECTION_32_TI_graphConstructParams
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
 * @param  maxNumCorners
 *         Maximum number of corners that the function can return
 *
 * @param  harrisScoreScalingFactor
 *         Scaling factor used by harris score kernel
 *
 * @param  nmsThresh
 *         Threshold parameter for non maximum suppression kernel
 *
 * @param  activeImgWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
 *                          For this function, it should always be equal to (createParams->imgFrameWidth + TOTAL_FILTER_SZ)
 *
 * @param  activeImgHeight   Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
 *                           For this function, it should always be equal to (createParams->imgFrameHeight + TOTAL_FILTER_SZ)
 *
 * @param  outputBlockWidth
 *         Output block width returned by BAM_createGraph(). That's useful information to understand performance.
 *
 * @param  outputBlockheight
 *         Output block height returned by BAM_createGraph(). That's useful information to understand performance.
 *
 * @param outputFormat
 *                The format in which output is required. Kindly refer to HARRIS_CORNER_DETECTION_32_TI_OutputFormat
 *                           for supported formats
 *
 *  ===============================================================
 */
typedef struct
{
    uint16_t      imgFrameWidth;
    uint16_t      imgFrameHeight;

    uint16_t      maxNumCorners;
    uint16_t      harrisScoreScalingFactor;
    int32_t       nmsThresh;

    uint16_t     activeImgWidth;
    uint16_t     activeImgHeight;

    uint16_t      outputBlockWidth;
    uint16_t      outputBlockHeight;
    uint8_t       qShift;
    uint8_t       outputFormat;
    uint8_t       harrisWindowSize;
    uint8_t       nmsWindowSize;
    uint8_t       harrisScoreMethod;
    uint8_t       totalBorderRequired;

}HARRIS_CORNER_DETECTION_32_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct HARRIS_CORNER_DETECTION_32_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  BAM_GradXYmag_Args      Parameters for gradient computation kernel
  @param  BAM_HarrisScore_32_7x7_Args Parameters for harris score kernel
  @param  BAM_NonMaxSuppress_mxn_S32_Args Parameters for non max suppression kernel
  @param  BAM_GenerateList_Args   Parameters for generate list from image kernel
  @param  createParams            Creation time parameters
 */
typedef struct
{
    EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
    EDMA_UTILS_autoIncrement_initParam dmaWriteBitPackedKernelArgs;
#if defined(_ONLY_GRAD_OUTPUT) || defined (_ONLY_HARRIS_OUTPUT) || defined (_ONLY_NMS_OUTPUT)
    EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
#else
    BAM_DMA_OneShot_Args dmaWriteKernelArgs;
#endif
    BAM_GradXYmag_Args                 gradArgs;
    BAM_HarrisScore_32_7x7_Args        harrisScoreArgs;
    BAM_NonMaxSuppress_mxn_S32_Args    nmsArgs;
    BAM_GenerateList_Args              genListArgs;
    HARRIS_CORNER_DETECTION_32_TI_graphCreateParams *createParams;
} HARRIS_CORNER_DETECTION_32_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_harrisCornerDetection32
 *  @func          HARRIS_CORNER_DETECTION_32_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HARRIS_CORNER_DETECTION_32_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_harrisCornerDetection32
 *  @func          HARRIS_CORNER_DETECTION_32_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           HARRIS_CORNER_DETECTION_32_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HARRIS_CORNER_DETECTION_32_TI_graphCreate(const BAM_GraphMem * graphMem,
        HARRIS_CORNER_DETECTION_32_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_harrisCornerDetection32
 *  @func          HARRIS_CORNER_DETECTION_32_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           HARRIS_CORNER_DETECTION_32_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HARRIS_CORNER_DETECTION_32_TI_execute(BAM_GraphMem *graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       BAM_harrisCornerDetection32
 *  @func          HARRIS_CORNER_DETECTION_32_TI_graphControl
 *  @brief         This function can be called after the graph is created and before HARRIS_CORNER_DETECTION_32_TI_execute()
 *                 to control the NMS node's threshold parameter. It is possible to get or set the threshold value.
 *  @pre           HARRIS_CORNER_DETECTION_32_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    cmd  : command can be HARRIS_CORNER_DETECTION_GET_THRESHOLD or HARRIS_CORNER_DETECTION_SET_THRESHOLD
 *  @param [in]    inParams : Pointer to input control parameters
 *  @param [in]    outParams  : Pointer to output control parameters
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HARRIS_CORNER_DETECTION_32_TI_graphControl(
        const BAM_GraphMem *graphMem,
        IALG_Cmd cmd,
        const HARRIS_CORNER_DETECTION_32_TI_ControlInParams *inParams,
        HARRIS_CORNER_DETECTION_32_TI_ControlOutParams *outParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_harrisCornerDetection32
 *  @func          HARRIS_CORNER_DETECTION_32_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before HARRIS_CORNER_DETECTION_32_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           HARRIS_CORNER_DETECTION_32_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inBufs  : Pointer to input buffer's descriptions
 *  @param [in]    outBufs : Pointer to output buffer's descriptions
 *  @param [in]    pNumKeyPoints : Pointer to location where number of keypoints detected will be written to
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t HARRIS_CORNER_DETECTION_32_TI_dmaControl(const BAM_GraphMem *graphMem,
                                                                  const IVISION_BufDesc *inBufDesc,
                                                                  const IVISION_BufDesc *outBufDesc,
                                                                  const uint16_t *pNumKeyPoints,
                                                                  uint8_t outputFormat,
                                                                  uint8_t totalBorder);
#endif

