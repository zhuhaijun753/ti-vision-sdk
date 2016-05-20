/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
*  @file       eve_qdma_interface.h
*
*  @brief      This header defines all types and constants
*              shared by implementations of the QDMA user interface.
*/

#ifndef EVE_QDMA_INTERFACE_H
#define EVE_QDMA_INTERFACE_H

#pragma CHECK_MISRA ("none")
#include "stdint.h"
#pragma RESET_MISRA ("required")

#define EVE_QDMA_SYSTEM_PARAMSET_ID     63U     /**< ID of the DMA Paramset assigned for system QDMA */
#define EVE_QDMA_SYSTEM_CHANNEL_ID      0U      /**< ID of the DMA channel assigned for system QDMA */
#define EVE_QDMA_SYSTEM_TCC             15U     /**< TCC assigned for system QDMA channel*/

#define EVE_QDMA_ALGORITHM_PARAMSET_ID     62U      /**< ID of the DMA Paramset assigned for algorithm QDMA */
#define EVE_QDMA_ALGORITHM_CHANNEL_ID      1U       /**< ID of the DMA channel assigned for algorithm QDMA */
#define EVE_QDMA_ALGORITHM_TCC             14U      /**< TCC assigned for algorithm QDMA channel*/

/**
*  @brief      Error codes returned by various QDMA APIs.
*
*  @remarks
*/
typedef enum _dmanode_qdmaerr
{
    DMANODE_QDMA_ERR_SUCCESS,               /**< Error code showing Success */
    DMANODE_QDMA_ERR_FAILED,                /**< Error code returned for Failiures due to unknown reason */
    DMANODE_QDMA_ERR_NULL_PTR,              /**< Error code returned if a NULL DDR buffer pointer is found */
    DMANODE_QDMA_ERR_NULL_INT_MEMORY_PTR,   /**< Error code returned if a NULL internal buffer pointer is found */
    DMANODE_QDMA_ERR_NULL_STRIDE,           /**< Error code returned if a NULL DDR stride is found */
    DMANODE_QDMA_ERR_INVALID_DIM,           /**< Error code returned if wrong image dimensions are found */
    DMANODE_QDMA_ERR_UNKNOWN_TRANSFER_TYPE /**< Error code returned if nature of transfer (1D_1D, 1D_2D, etc) could not be resolved */
} DMANODE_QdmaErr;


/**
*  @brief      1. Assigns event numbers, transfer complete codes, queue and register
*                 numbers to each channel.
*              2. Will perform the setup of the global registers. In this process we
*                 should disable interrupts and re-enable interrupts.
*                 For QDMA we will be setting up QCHMAP, QDMAQNUM, QRAEX, QEESR.
*                 Similarly for EDMA we will be setting up, DCHMAP, DMAQNUM, DRAEX,
*                 ESR, ESRH. Independent of QDMA and EDMA we need to set QUEPRI and
*                 QUETCMAP.
*              3. Populates the DMA state structure. All subseqent DMA transfers
*                 will refer to this for performing their transfer.
*
*  @remarks    This functions must be called once before any QDMA interface functions are used.
*              This function takes no arguments. It initializes [EVE_QDMA_SYSTEM_CHANNEL_ID] QDMA channel of the module
*              with [EVE_QDMA_SYSTEM_PARAMSET_ID] paRAM set and [EVE_QDMA_SYSTEM_TCC] as TCC. Since TCC is
*              shared between EDMA and QDMA channels, possible chances of conflict should be considered.
*/
DMANODE_QdmaErr DMANODE_qdmaGlobalInit(void);


/**
*  @brief      This function performs de-Init of EDMA resources
*
*  @remarks    No QDMA interface functions should be used after this function is called.
*              This function takes no arguments. It de-init first QDMA channel of the module.
*/
DMANODE_QdmaErr DMANODE_qdmaGlobalDeint(void);


/**
*  @brief      This function performs memcpy() operation using QDMA. It is supposed to used by System.
*
*
*  @param[in]   dstPtr     Pointer to the destination buffer.
*  @param[in]   srcPtr     Pointer to the source buffer.
*  @param[in]   bytes       Number of bytes to be copied.
*
*  @remarks    This function is a blocking call.
*
*
*  @return      DMANODE_QdmaErr
*/
DMANODE_QdmaErr DMANODE_qdmaSysMemcpy(void *dstPtr,
                                      void *srcPtr,
                                      uint32_t bytes);


/**
*  @brief      This function performs memcpy() operation using QDMA. It is supposed to be used by Algorithm.
*
*
*  @param[in]   dstPtr     Pointer to the destination buffer.
*  @param[in]   srcPtr     Pointer to the source buffer.
*  @param[in]   bytes       Number of bytes to be copied.
*
*  @remarks    This function is a blocking call.
*
*
*  @return      DMANODE_QdmaErr
*/
DMANODE_QdmaErr DMANODE_qdmaAlgMemcpy(void *dstPtr,
                                      void *srcPtr,
                                      uint32_t bytes);

/**
*  @brief      This function performs a 2D memcpy() using QDMA. It is supposed to used by System.
*
*
*  @param[in]   dstPtr     Pointer to the destination buffer.
*  @param[in]   srcPtr     Pointer to the source buffer.
*  @param[in]   dstStride  Stride of the destination buffer (signed short).
*  @param[in]   srcStride  Srtide of the source buffer (signed short).
*  @param[in]   width       Width in bytes to be copied.
*  @param[in]   height      Height of the buffer to be copied.
*
*  @remarks    This function is a blocking call.
*
*
*  @return      DMANODE_QdmaErr
*/
DMANODE_QdmaErr DMANODE_qdmaSysMemcpy_2d(void *dstPtr,
        void *srcPtr,
        int16_t dstStride,
        int16_t srcStride,
        uint16_t width,
        uint16_t height);


/**
*  @brief      This function performs a 2D memcpy() using QDMA. It is supposed to be used by Algorithm.
*
*
*  @param[in]   dstPtr     Pointer to the destination buffer.
*  @param[in]   srcPtr     Pointer to the source buffer.
*  @param[in]   dstStride  Stride of the destination buffer (signed short).
*  @param[in]   srcStride  Srtide of the source buffer (signed short).
*  @param[in]   width       Width in bytes to be copied.
*  @param[in]   height      Height of the buffer to be copied.
*
*  @remarks    This function is a blocking call.
*
*
*  @return      DMANODE_QdmaErr
*/
DMANODE_QdmaErr DMANODE_qdmaAlgMemcpy_2d(void *dstPtr,
        void *srcPtr,
        int16_t dstStride,
        int16_t srcStride,
        uint16_t width,
        uint16_t height);

#endif
