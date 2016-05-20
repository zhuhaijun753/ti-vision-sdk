/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file       eve_edma_bam_interface.h
*
*  @brief      This header defines all constants and functions
*              shared by implementations of the EDMA BAM interface.
*/

#ifndef EVE_EDMA_BAM_INTERFACE_H
#define EVE_EDMA_BAM_INTERFACE_H

#include "bam_kernel_interface.h"
#include "eve_edma_user_interface.h"

/**
*  @brief      Error codes returned by various BAM EDMA APIs.
*
*  @remarks
*/
typedef enum edma_err
{
    DMANODE_EDMA_ERR_SUCCESS,               /**< Error code showing Success */
    DMANODE_EDMA_ERR_FAILED,                /**< Error code returned for Failiures due to unknown reason */
    DMANODE_EDMA_ERR_NULL_CONTEXT,          /**< Error code returned if a NULL context structure pointer is found*/
    DMANODE_EDMA_ERR_NULL_ARGS,             /**< Error code returned if a NULL ARGS structure pointer is found*/
    DMANODE_EDMA_ERR_CROSSED_MAX_NODE_CHANNELS,/**< Error code returned if ARGS structure contains more than allowed number of channels */
    DMANODE_EDMA_ERR_CROSSED_MAX_CHANNELS,  /**< Error code returned if all avialable EDMA channels are occupied */
    DMANODE_EDMA_ERR_NULL_DDR_PTR,          /**< Error code returned if a NULL DDR buffer pointer is found */
    DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR,   /**< Error code returned if a NULL internal buffer pointer is found */
    DMANODE_EDMA_ERR_NULL_STRIDE,           /**< Error code returned if a NULL DDR stride is found */
    DMANODE_EDMA_ERR_INVALID_IMAGE_DIM,     /**< Error code returned if wrong image dimensions are found */
    DMANODE_EDMA_ERR_INVALID_BLOCK_DIM,     /**< Error code returned if wrong block dimensions are found */
    DMANODE_EDMA_ERR_UNKNOWN_TRANSFER_TYPE, /**< Error code returned if nature of transfer (1D_1D, 1D_2D, etc) could not be resolved */
    DMANODE_EDMA_ERR_LAST_BLOCK             /**< Error code returned if last output block is encountered */
} DMANODE_EdmaErr;

/**
*  @brief      DMA Read kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaAutoIncrementReadKernel;

/**
*  @brief      DMA Read kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaReadAutoIncrementKernelHelperFunc;

/**
*  @brief      DMA Read kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaReadAutoIncrementKernelExecFunc;

/**
*  @brief      DMA Write kernel info
*/
extern BAM_KernelInfo gBAM_TI_dmaAutoIncrementWriteKernel;

/**
*  @brief      DMA Write kernel helper function definition
*/
extern BAM_KernelHelperFuncDef gBAM_TI_dmaWriteAutoIncrementKernelHelperFunc;

/**
*  @brief      DMA Write kernel execute function definition
*/
extern BAM_KernelExecFuncDef gBAM_TI_dmaWriteAutoIncrementKernelExecFunc;


#endif

