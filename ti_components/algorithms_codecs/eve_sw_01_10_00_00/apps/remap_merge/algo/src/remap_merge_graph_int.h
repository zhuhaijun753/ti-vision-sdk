/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       remap_merge_graph_int.h
 *
 *  @brief      This file defines the interface for Remap Merge Graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef REMAP_MERGE_TI_GRAPH_INT_H
#define REMAP_MERGE_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"

#include "remap.h"
#include "remap_common.h"

/* Helper Fxn Headers */
#include "bam_dma_custom_remap_merge_node.h"  /* SOURCE NODE */
#include "bam_remap.h"                        /* KERNEL NODE  */
#include "bam_memcpy.h"                       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv420nv12.h"       /* KERNEL NODE  */
#include "bam_yuv_420nv12_to_422uyvy.h"       /* KERNEL NODE  */
#include "edma_utils_autoincrement.h"         /* SINK NODE      */
#include "iremap_merge_ti.h"


/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define REMAP_MERGE_GRAPH_OBJ_SIZE             (6720U)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define REMAP_MERGE_GRAPH_SCRATCH_SIZE         (896U )

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define REMAP_MERGE_GRAPH_CONTEXT_SIZE         (0   )


/** ========================================================
 *  @name   REMAP_MERGE_TI_graphCreateParams
 *
 *  @desc   This structure specifies the properties needed for configuring the Remap and Merge Graph
 *
 *  @field remapParams
 *          parameters to configure Remap kernel
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  @field dstFormat
 *          Format of output
 *
 *  ===============================================================
 */
typedef BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args REMAP_MERGE_TI_graphCreateParams;


/** ========================================================
 *  @name   BAM_Remap_Merge_Args
 *
 *  @desc   This structure specifies the properties needed for configuring DMA
 *
 *  @field remapKernelArgs
 *          parameters to configure Remap kernel
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  @field dstFormat
 *          Format of output
 *
 *  @field memcpyKernelArgs
 *          parameters to configure Memcpy kernel
 *
 *  @field formatConvertKernelArgs
 *          parameters to configure Format Convert kernel
 *
 *  @field alphaBlendKernelArgs
 *          parameters to configure Alpha Blend kernel
 *  ===============================================================
 */

/** ========================================================
 *  @name   REMAP_MERGE_TI_graphArgs
 *
 *  @desc   This structure is the infomration holder for BAM graph
 *
 *  @field dmaReadWriteKernelArgs
 *          parameters to configure DMA Source and Sink Node
 *
 *  @field remapKernelArgs
 *          parameters to configure Remap Kernel Node
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  @field dstFormat
 *          Format of output
 *
 *  @field memcpyKernelArgs
 *          parameters to configure Memcpy kernel
 *
 *  @field formatConvertKernelArgs
 *          parameters to configure Format Convert Kernel Node
 *
 *  @field alphaBlendKernelArgs
 *          parameters to configure Alpha Blend Kernel Node
 *
 *  @field createParams
 *          Applet configuration parameters
 *
 *  ===============================================================
 */

typedef struct
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args      dmaReadWriteKernelArgs;
    BAM_Remap_Args                            remapKernelArgs;
    uint8_t                                   enableMerge;
    Format                                    dstFormat;
    BAM_Memcpy_Args                           memcpyKernelArgs;
    BAM_Yuv_420nv12_to_422uyvy_Args           formatConvertKernelArgs;
    BAM_Alpha_Blend_YUV420nv12_Args           alphaBlendKernelArgs;
    REMAP_MERGE_TI_graphCreateParams         *createParams;
} REMAP_MERGE_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_remapMerge
 *  @func            REMAP_MERGE_TI_getGraphMemReq
 *  @brief            This is first function to be called to request graph memory
 *  @param [in]  memReq : Pointer to graph memory structure
 *  @return         status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t REMAP_MERGE_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_remapMerge
 *  @func            REMAP_MERGE_TI_graphCreate
 *  @brief            This is function to be called after having memory allocated for
 *                       graph
 *  @pre             REMAP_MERGE_TI_getGraphMemReq should be called to know the
 *                       graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t REMAP_MERGE_TI_graphCreate(const BAM_GraphMem               *graphMem,
                                                 REMAP_MERGE_TI_graphCreateParams *createParams);


/**
 *******************************************************************************
 *  @ingroup        BAM_remapMerge
 *  @func             REMAP_MERGE_TI_graphDmaControl
 *  @brief            This is first function to be called to control the dma parameters for DMA node
 *  @pre              REMAP_MERGE_TI_graphCreate should be called to create graph
 *  @param [in]   graphMem  : Pointer to graph memory structure
 *  @param [in]   inBufs  : Pointer to graph memory structure
 *  @param [in]   outBufs : Pointer to graph memory structure
 *   @param[in]   sinkNodeId : Id of the SINK node in graph
 *  @return          status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t REMAP_MERGE_TI_graphDmaControl(const BAM_GraphMem *graphMem,
      const IVISION_InBufs *inBuf, const IVISION_OutBufs *outBuf, uint8_t sinkNodeId);

/**
 *******************************************************************************
 *  @ingroup        BAM_remapMerge
 *  @func             REMAP_MERGE_TI_execute
 *  @brief            This is first function to be called once the graph is created
 *  @pre              REMAP_MERGE_TI_graphCreate should be called to create graph
 *  @param [in]   graphMem  : Pointer to graph memory structure
 *  @param [in]   inArgs  : Pointer to graph memory structure
 *  @param [in]   outArgs : Pointer to graph memory structure
 *  @return          status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t REMAP_MERGE_TI_execute(BAM_GraphMem *graphMem,
                                 const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);



#endif /* REMAP_MERGE_TI_GRAPH_INT_H */

