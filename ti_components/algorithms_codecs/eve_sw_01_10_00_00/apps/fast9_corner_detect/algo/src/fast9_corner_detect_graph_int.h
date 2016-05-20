/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       fast9_corner_detect_graph_int.h
 *
 *  @brief      This file defines the interface for fast9 corner detect graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef FAST9_CORNER_DETECT_TI_GRAPH_INT_H
#define FAST9_CORNER_DETECT_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"
#include "bam_fast9.h"
#include "ifast9_corner_detect_ti.h"
#include "edma_utils_autoincrement.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FAST9_CORNER_DETECT_GRAPH_OBJ_SIZE             (2200)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FAST9_CORNER_DETECT_GRAPH_SCRATCH_SIZE         (884 )

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FAST9_CORNER_DETECT_GRAPH_CONTEXT_SIZE         (368 )

/**
  @struct FAST9_CORNER_DETECT_TI_dmaCtrlArgs
  @brief  This structure contains parameters which can be configured
              for DMA using control call
  @param  activeImageWidth     Image Width
  @param  activeImageHeight    Image Height
  @param  blkWidth     Block width for dma
  @param  blkHeight    Block height for dma
  @param  dx     delta x from startx
  @param  dx     delta y from startx
  @param  level     Current level for the process call
*/
typedef struct
{
    uint16_t    activeImageWidth;
    uint16_t    activeImageHeight;
    uint16_t    blkWidth;
    uint16_t    blkHeight;
    uint16_t    dx;
    uint16_t    dy;
    uint8_t     level;
}FAST9_CORNER_DETECT_TI_dmaCtrlArgs;

/*--------------------------------------------------------------------*/
/**
  @struct FAST9_CORNER_DETECT_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  fast9KernelArgs        Parameters for FAST9 corner detect kernel
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam    dmaReadKernelArgs;
  BAM_Fast9_Args                        fast9KernelArgs;
  EDMA_UTILS_autoIncrement_initParam    dmaWriteKernelArgs;
} FAST9_CORNER_DETECT_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           FAST9_CORNER_DETECT_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                            FAST9_CORNER_DETECT_TI_graphArgs* createParams);


/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_graphControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function controls the kernel parameters for the graph
 *  @pre           FAST9_CORNER_DETECT_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    BAM_Fast9_ctrlArgs   : Pointer to control parameter for the kernels
 *                       refer FAST9_CORNER_DETECT_TI_dmaCtrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_graphControl(
        const BAM_GraphMem *graphMem,
        BAM_Fast9_ctrlArgs * fast9KernelCtrlArgs
        );


/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_graphDmaControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function is used to control the dma parameter before
 *                 calling process call
 *  @pre           FAST9_CORNER_DETECT_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    inBufDesc   : Pointer to input ivision buf
 *  @param [in]    outBufDesc   : Pointer to output ivision buf
 *  @param [in]    dmaCtrlParams   : : Pointer to control parameter for the dma nodes
 *                       refer FAST9_CORNER_DETECT_TI_dmaCtrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */

int32_t FAST9_CORNER_DETECT_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *inBufDesc, const IVISION_BufDesc *outBufDesc,
        const FAST9_CORNER_DETECT_TI_dmaCtrlArgs * dmaCtrlParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           FAST9_CORNER_DETECT_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);



#endif

