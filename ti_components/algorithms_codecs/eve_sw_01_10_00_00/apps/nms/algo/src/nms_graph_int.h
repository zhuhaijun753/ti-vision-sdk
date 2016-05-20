/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       nms_graph_int.h
 *
 *  @brief      This file defines the interface for graph for nms
 *  @version 0.0 (Aug 2014) : Base version.
 */

#ifndef NMS_TI_GRAPH_INT_H
#define NMS_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "edma_utils_autoincrement.h"

#include "bam_nms_s16_to_list.h"
#include "bam_dma_custom_nms_node.h"
/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define NMS_GRAPH_OBJ_SIZE             (4260U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define NMS_GRAPH_SCRATCH_SIZE         (1404U)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define NMS_GRAPH_CONTEXT_SIZE         (4U)


#define NMS_TI_ROUND_BIT_POS (4U)


/** ========================================================
 *  @name   NMS_TI_graphConstructParams
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
  NMS_TI_CreateParams * inmsCreateParams;
}NMS_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct NMS_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  createParams                Pointer to grarh Create params
*/
typedef struct
{
  BAM_DMA_CUSTOM_NMS_READ_args       dmaReadKernelArgs;
  NMS_TI_graphCreateParams *createParams;
} NMS_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          NMS_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t NMS_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          NMS_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           NMS_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    createParams   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t NMS_TI_graphCreate(const BAM_GraphMem * graphMem,
                                       NMS_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          NMS_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           NMS_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structuree
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t NMS_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          NMS_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before IMAGE_PYRAMID_U8_TI_execute()
 *                 to control the source and sink node's parameters.
 *  @pre           NMS_TI_graphCreate should be called to create graph
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
int32_t NMS_TI_dmaControl(const BAM_GraphMem *graphMem,
                                uint8_t winWidth,
                                uint8_t winHeight,
                                uint8_t inElemSize,
                                uint16_t computeWidth,
                                uint16_t computeHeight,
                                const IVISION_BufDesc *inBufDesc,
                                const IVISION_BufDesc *outBufDesc,
                                uint8_t * ptrToListSize
                                );


/**
 *******************************************************************************
 *  @ingroup       BAM_nms
 *  @func          NMS_TI_kernelControl
 *  @brief         This function should be called after the graph is created. This function set the control
 *                    arguments of contrast stretching kernel
 *  @pre           NMS_TI_graphCreate should be called to create graph
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
int32_t NMS_TI_kernelControl(const  BAM_GraphMem * graphMem,
                                  const NMS_TI_InArgs * inArgs,
                                  uint16_t imageWidth,
                                  uint8_t  inElemSize,
                                  uint16_t computeWidth,
                                  uint16_t computeHeight
                                  );



#endif /* NMS_TI_GRAPH_INT_H */

