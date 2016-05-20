/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bin_image_to_list_select_list_elems_graph_int.h
 *
 *  @brief      This file defines the interface for graph for bin img to list
 *  @version 0.0 (April 2015) : Base version.
 */

#ifndef BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMS_GRAPH_INT_H_
#define BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMS_GRAPH_INT_H_

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "edma_utils_autoincrement.h"

#include "bam_select_list_elements.h"

#include "bam_dma_custom_select_list_elem_node.h"
/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_OBJ_SIZE             (2380U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_SCRATCH_SIZE         (344U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_GRAPH_CONTEXT_SIZE         (4U)


#define BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_MAX_LIST_SIZE (4064U)
#define BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_SELECTION_MASK_SIZE (128U)

/** ========================================================
 *  @name   BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphConstructParams
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
}BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  createParams                Pointer to grarh Create params
*/
typedef struct
{
  BAM_DMA_CUSTOM_SELECT_LIST_ELEM_READ_args            dmaReadKernelArgs;
  BAM_Select_list_elements_Args                        selectListElemsKernelArgs;
  BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreateParams *createParams;
} BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    createParams   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate(const BAM_GraphMem * graphMem,
                                       BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_execute(const BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before IMAGE_PYRAMID_U8_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate should be called to create graph
 *  @param [in]    inputListPtr   : Pointer to the input list
 *  @param [in]    outputListPtr  : Pointer to the output list
 *  @param [in]    ptrToListSize  : pointer to the area where list size will be stored
 *  @param [in]    listSize  : total list size
 *  @param [in]    listChunkSize  : Size of the list chunk to be used
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint8_t * inputListPtr,
                                uint8_t * outputListPtr,
                                uint8_t * ptrToListSize,
                                uint32_t  listSize,
                                uint16_t  listChunkSize
                                );


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_kernelControl
 *  @brief         This function should be called after the graph is created. This function set the control
 *                    arguments of contrast stretching kernel
 *  @pre           BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    listChunkSize  : Size of the list chunk to be used
 *  @param [in]    listSize  : total list size
 *  @param [in]    selectionMaskSize  : size of the selection mask to be used
 *  @param [in]    selectionMaskPtr  :   Pointer to the selection mask tp be used
 *  @return         status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMENTS_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  uint32_t listSize,
                                  uint16_t listChunkSize,
                                  uint8_t  selectionMaskSize,
                                  uint8_t  *selectionMaskPtr
                                  );



#endif /* BIN_IMAGE_TO_LIST_SELECT_LIST_ELEMS_GRAPH_INT_H_ */

