/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bin_image_to_list_with_masking_graph_int.h
 *
 *  @brief      This file defines the interface for graph for bin img to list
 *  @version 0.0 (April 2015) : Base version.
 */

#ifndef BIN_IMAGE_TO_LIST_WITH_MASKING_TI_GRAPH_INT_H
#define BIN_IMAGE_TO_LIST_WITH_MASKING_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "edma_utils_autoincrement.h"

#include "bam_bin_image_to_list.h"
#include "bam_binary_masking.h"

#include "bam_dma_custom_bin_to_list_node.h"
/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_OBJ_SIZE             (4260U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_SCRATCH_SIZE         (1404U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_WITH_MASKING_GRAPH_CONTEXT_SIZE         (4U)

#define BIN_IMAGE_TO_LIST_WITH_MASKING_TI_MAX_BLOCK_SIZE (16300U)


/** ========================================================
 *  @name   BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          BIN_IMAGE_TO_LIST graph
 *
 *  @field createParams
 *          pointer to the create params passed by user using iVision interface
 *
 *  ===============================================================
 */
typedef struct
{
  BIN_IMAGE_TO_LIST_TI_CreateParams            * icreateParams;
}BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  createParams                Pointer to grarh Create params
*/
typedef struct
{
  BAM_DMA_CUSTOM_BIN_TO_LIST_READ_args                 dmaReadKernelArgs;
  BAM_BinaryMasking_Args                               binaryMaskingKernelArgs;
  BAM_Bin_image_to_list_Args                           binImgToListKernelArgs;
  BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreateParams *createParams;
} BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_WITH_MASKING_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           BIN_IMAGE_TO_LIST_WITH_MASKING_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    createParams   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate(const BAM_GraphMem * graphMem,
                                       BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_WITH_MASKING_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_execute(const BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_WITH_MASKING_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before IMAGE_PYRAMID_U8_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    winWidth  : Window Width for BIN_IMAGE_TO_LIST
 *  @param [in]    winHeight  : Window Height for BIN_IMAGE_TO_LISTt
 *  @param [in]    inElemSize  : Input Element size for BIN_IMAGE_TO_LIST
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
int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint8_t * inputDataPtr,
                                uint8_t * inputMaskPtr,
                                uint8_t * outputListPtr,
                                uint8_t * ptrToListSize,
                                uint16_t  imageWidth,
                                uint16_t  imageHeight,
                                uint16_t  inputDataPitch,
                                uint16_t  inputMaskPitch,
                                uint16_t computeWidth,
                                uint16_t computeHeight,
                                uint8_t  enableMasking
                                );


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_WITH_MASKING_TI_kernelControl
 *  @brief         This function should be called after the graph is created. This function set the control
 *                    arguments of contrast stretching kernel
 *  @pre           BIN_IMAGE_TO_LIST_WITH_MASKING_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to the input args or the applet
 *  @param [in]    imageWidth  : Image width
 *  @param [in]    inElemSize  : Input Element size for BIN_IMAGE_TO_LIST
 *  @param [in]    computeWidth  : Compute Width used by kernel
 *  @param [in]    computeHeight  : Compute Height used by kernel
 *  @return         status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_WITH_MASKING_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  uint16_t computeWidth,
                                  uint16_t computeHeight,
                                  uint8_t  startX,
                                  uint8_t  startY,
                                  uint8_t  outputListQFormat,
                                  uint8_t  outputListOrder,
                                  uint8_t  enableMasking
                                  );



#endif /* BIN_IMAGE_TO_LIST_WITH_MASKING_TI_GRAPH_INT_H */

