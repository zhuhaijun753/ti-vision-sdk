/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file      yuv_scalar_graph_int.h
 *
 *  @brief      This file defines the interface for YUV scalar graph
 *  @date   05 Mar 2014
 */

#ifndef YUV_SCALAR_TI_GRAPH_INT_H
#define YUV_SCALAR_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "evealgframework.h"
#include "bam_common.h"
#include "bam_yuv_scalar.h"
#include "edma_utils_autoincrement.h"
#include "bam_dma_custom_yuv_scalar_node.h"
#include "iyuv_scalar_ti.h"

#define MAX_KERNEL_ID (255)

typedef enum
{
    BAM_TI_KERNELID_SCALAR_DMAREAD                = 0,
    BAM_TI_KERNELID_YUV_SCALAR                    = 1,
    BAM_TI_KERNELID_SCALAR_DMAWRITE_AUTOINCREMENT = 2,
    BAM_TI_KERNELID_SCALAR_MAX                    = MAX_KERNEL_ID
} BAM_TI_SCALAR_KernelID;

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define YUV_SCALAR_GRAPH_OBJ_SIZE             (4188)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define YUV_SCALAR_GRAPH_SCRATCH_SIZE         (1456)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define YUV_SCALAR_GRAPH_CONTEXT_SIZE         (160)

/*--------------------------------------------------------------------*/
/* These are macros which are algorithm specfic and indicative to BAM */
/* to help decide the optimal block dimensions                        */
/*--------------------------------------------------------------------*/
#define YUV_SCALAR_BLOCK_WIDTH  (64)
#define YUV_SCALAR_BLOCK_HEIGHT (32)
#define Q_FORMATE_SCALE_RATIO                   (12U)
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7     */
/* These are simple non-harmful macros.          */	
#define ALIGN_SIZE(x,y) ((((x) + ((y)-1U)) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

/** ========================================================
 *  @name   YUV_SCALAR_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          harris corner detect graph
 *
 * @param  YUV_SCALAR_TI_CreateParams
 *         create time parameters of YUC scalar applet
 *
 *  ===============================================================
 */
typedef struct
{
    uint8_t  inputDataType;    /*0 --> Luma 1--> UV interleaved         */
    YUV_SCALAR_TI_CreateParams *appCreateParams;
}YUV_SCALAR_TI_graphCreateParams;


/*--------------------------------------------------------------------*/
/**
  @struct YUV_SCALAR_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  YUV_SCALAR_TI_CreateParams    Parameters for yuv_padding kernel
  @param  createParams            Creation time parameters
 */
typedef struct
{
    BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_Args dmaReadKernelArgs;
    EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
    BAM_yuv_scalar_Args           verScaleKernelArgs;
    BAM_yuv_scalar_Args           horScaleKernelArgs;
    YUV_SCALAR_TI_graphCreateParams *createParams;
    uint16_t  blockWidth ;        
    uint16_t  blockHeight;        
} YUV_SCALAR_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_yuv_padding
 *  @func          YUV_SCALAR_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t YUV_SCALAR_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_yuv_padding
 *  @func          YUV_SCALAR_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           YUV_SCALAR_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t YUV_SCALAR_TI_graphCreate(const BAM_GraphMem * graphMem,
        YUV_SCALAR_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_yuv_padding
 *  @func          YUV_SCALAR_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           YUV_SCALAR_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t YUV_SCALAR_TI_execute(BAM_GraphMem *graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);


int32_t YUV_SCALAR_TI_kernelControl(const BAM_GraphMem *graphMem, uint8_t  inputDataType, uint16_t scaleRatioQ12);

int32_t YUV_SCALAR_TI_dmaControl(const BAM_GraphMem *graphMem, BAM_DMA_CUSTOM_YUV_SCALAR_SOURCE_NODE_ctrl_args  *srcDMACtrlArgs, const IVISION_BufPlanes  ivisionBufPlane[]);

#endif

