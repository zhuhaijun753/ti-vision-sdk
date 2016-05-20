/*
 *******************************************************************************
 *
 * BAM Source DMA node for Remap Merge Applet.
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  bam_dma_custom_remap_merge_node.h
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of custom DMA node for Remap Merge Applet
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef BAM_DMA_CUSTOM_REMAP_MERGE_NODE_H_
#define BAM_DMA_CUSTOM_REMAP_MERGE_NODE_H_

#include "bam_types.h"
#include "eve_edma_bam_interface.h"

#include "bam_remap.h"                        /* KERNEL NODE  */

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */

/*!

  @macro      REMAP_ASSERT
  @brief        To check and condition and exit is false

*/
#define REMAP_ASSERT(_COND_, _ERRORCODE_) do { \
        if( !(_COND_)) { status = (_ERRORCODE_); \
                         goto EXIT; } \
} while( 0 )

/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


/** ========================================================
 *  @name   bam_dma_custom_remap_merge_node_args
 *
 *  @desc   This structure specifies the properties needed for configuring DMA
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
typedef struct bam_dma_custom_remap_merge_node_args
{
    BAM_Remap_Args   remapParams;
    uint8_t          enableMerge;
    Format           dstFormat;
} BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args;


/* Source Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernel;
extern BAM_KernelInfo           gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomRemapMergeNodeReadKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernelExecFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernelExecFunc;

/* Sink Node kernel Info, helper, and exec functions */
extern BAM_KernelInfo           gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernel;
extern BAM_KernelInfo           gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernel;
extern BAM_KernelHelperFuncDef  gBAM_TI_dmaCustomRemapMergeNodeWriteKernelHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernelExecFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernelExecFunc;


#endif /* BAM_DMA_CUSTOM_REMAP_MERGE_NODE_H_ */

