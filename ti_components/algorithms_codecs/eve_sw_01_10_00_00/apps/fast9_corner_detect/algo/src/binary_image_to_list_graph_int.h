/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       binary_image_to_list_graph_int.h
 *
 *  @brief      This file defines the interface for binary image to list graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef BIN_IMAGE_TO_LIST_TI_GRAPH_INT_H
#define BIN_IMAGE_TO_LIST_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_scatterGather.h"
#include "edma_utils_context_size.h"
#include "bin_img_to_list_bam_dma_node.h"
#include "bam_bin_image_to_list.h"
#include "bam_common.h"
#include "ifast9_corner_detect_ti.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_GRAPH_OBJ_SIZE             (2596)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_GRAPH_SCRATCH_SIZE         (416)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_GRAPH_CONTEXT_SIZE         (4)

/**
  @struct BIN_IMAGE_TO_LIST_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.
  @param  binToListKernelArgs     Parameters for binary image to list kernel
*/
typedef struct
{
  BAM_Bin_image_to_list_Args                     binToListKernelArgs;
} BIN_IMAGE_TO_LIST_TI_graphArgs;


/**
  @struct BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs
  @brief  This structure contains parameters which can be configured
              for DMA using control call
  @param  imgWidth     Image Width
  @param  imgHeight    Image Height
  @param  imgPitch     Image Pitch
  @param  blkWidth     Block width for dma
  @param  blkHeight    Block height for dma
  @param  dx     delta x from startx
  @param  dx     delta y from startx
  @param  *pListSize     Pointer to the list size
  @param  level     Current level for the process call
*/
typedef struct
{
    uint16_t    imgWidth;
    uint16_t    imgHeight;
    uint16_t    imgPitch;
    uint16_t    blkWidth;
    uint16_t    blkHeight;
    uint16_t    dx;
    uint16_t    dy;
    uint32_t    *pListSize;
    uint8_t     level;
}
BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           BIN_IMAGE_TO_LIST_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_graphCreate(const BAM_GraphMem * graphMem,
                                         BIN_IMAGE_TO_LIST_TI_graphArgs * createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_graphControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function controls the kernel parameters for the graph
 *  @pre           BIN_IMAGE_TO_LIST_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    binToImgListCtrlArgs   : Pointer to control parameter for the kernels
 *                       refer BAM_Bin_image_to_list_ctrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_graphControl(
        const BAM_GraphMem *graphMem,
        BAM_Bin_image_to_list_ctrlArgs * binToImgListCtrlArgs
        );

/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_graphDmaControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function is used to control the dma parameter before
 *                 calling process call
 *  @pre           BIN_IMAGE_TO_LIST_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    inBufDesc   : Pointer to input ivision buf
 *  @param [in]    outBufDesc   : Pointer to output ivision buf
 *  @param [in]    dmaCtrlParams   : : Pointer to control parameter for the dma nodes
 *                       refer BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */

int32_t BIN_IMAGE_TO_LIST_TI_graphDmaControl(
              const BAM_GraphMem *graphMem,
              const IVISION_BufDesc *inBufDesc,
              const IVISION_BufDesc *outBufDesc,
              const BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs * dmaCtrlParams);


/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BIN_IMAGE_TO_LIST_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

#endif

