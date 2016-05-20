/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file       eve_edma_scatter_gather.h
*
*  @brief      This header defines all types, constants, and functions
*              shared by all implementations of the EDMA interface.
*/

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")

#include "dma_funcs.h"

#define OPT_CHAINED_EARLY_ABSYNC        0x00400804ul

/**
*  @brief      Triggers all the transfers assigned to the channel.
*
*  @param[in] edmaHWChnlId              Channeld number to be triggered
*  @param[in] dmaStateStruct            DMA state structure initialized with dma_state_struct_populate().
*  @param[in] edmaCc                    Pointer to the EDMA Base.
*
*
*  @return      EVELIB_EDMAScatterGatherErr
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*/
static inline void  EVELIB_EDMAScatterGatherTrigger(uint32_t index,/* Index in EDMA resource Structure */
                                             DMA_resourceStruct *edmaResources,         /**< EDMA state structure */
                                             CSL_EdmaccRegsOvly    edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                            )
{
    uint32_t  evtNo = edmaResources->logicalChannelNo[index];
    uint32_t submitWord  = (uint32_t)CSL_EDMACC_ESR_E0_SET << evtNo;
    DMA_SUBMIT (edmaCc, submitWord);
}

/**
*  @brief      Waits for all the transfers assigned to the channel to finish.
*
*  @param[in] edmaHWChnlId              Channeld number to be Waited
*  @param[in] dmaStateStruct            DMA state structure initialized with dma_state_struct_populate().
*  @param[in] edmaCc                    Pointer to the EDMA Base.
*
*
*  @return      EVELIB_EDMAScatterGatherErr
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*/
static inline void  EVELIB_EDMAScatterGatherWait(uint32_t index,/* Index in EDMA resource Structure */
                                             DMA_resourceStruct      *edmaResources,         /**< EDMA state structure */
                                             CSL_EdmaccRegsOvly    edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                            )
{
    uint32_t    tccNo = edmaResources->tccVal[index];
    uint32_t waitWord  = (uint32_t)0x1U << tccNo;
    DMA_WAIT (edmaCc, waitWord);
}

/**
*  @brief      Configures the channels with list of pointers of the blocks to be transferred.
*
*  @param[in]  srcList                  List of source pointers of the blocks to be transfered.
*  @param[in]  dstList                  List of destination pointers of the blocks to be transfered.
*  @param[in]  numTransfers             Number of transfers to be assigned on the channel.
*  @param[in] edmaHWChnlId              Channel number to be used for the transfer.
*  @param[in] dmaStateStruct            DMA state structure initialized with dma_state_struct_populate().
*  @param[in] edmaCc                    Pointer to the EDMA Base.
*
*
*  @return      EVELIB_EDMAScatterGatherErr
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*               EVELIB_EDMAScatterGatherInit() must be called in prior to this call.
*/
static inline void  EVELIB_EDMAScatterGatherConfigure(uint8_t **srcList,
                                                                uint8_t **dstList,
                                                                int32_t numTransfers,
                                                                uint32_t index,
                                                                DMA_resourceStruct * edmaResources,
                                                                CSL_EdmaccRegsOvly    edmaCc
                                                                )
{
    volatile uint32_t   *trigParam = 0;
    uint32_t            j = 0;
    trigParam       =    edmaResources->baseParam[index];

    if(numTransfers > 1)
    {
        trigParam[0]    = OPT_CHAINED_EARLY_ABSYNC | (edmaResources->logicalChannelNo[index] << 12);
    }
    for (j = 0; j <numTransfers; j++)
    {
        trigParam[1]  = (uint32_t)srcList[j];
        trigParam[3]  = (uint32_t)dstList[j];
        trigParam += 8;
    }

    return;
}

#ifndef EVE_EDMA_SCATTER_GATHER_H
#define EVE_EDMA_SCATTER_GATHER_H


#define MAX_SCATTERGATHER_TRANSFERS     16U

/**
*  @brief      Error codes returned by EDMA scatter gather APIs.
*
*  @remarks
*/
typedef enum eve_lib_edma_scattergather_Err
{
    EVELIB_EDMASCATTERGATHER_ERR_SUCCESS,               /**< Error code showing Success */
    EVELIB_EDMASCATTERGATHER_ERR_FAILED,                /**< Error code returned for Failiures due to unknown reason */
    EVELIB_EDMASCATTERGATHER_ERR_CROSSED_MAX_TRANSFERS,  /**< Error code returned if number of transfers requested exceeds MAX_SCATTERGATHER_TRANSFERS */
    EVELIB_EDMASCATTERGATHER_ERR_NULL_PTR,                   /**< Error code returned if a NULL pointer is found */
    EVELIB_EDMASCATTERGATHER_ERR_NULL_STRIDE,           /**< Error code returned if a NULL stride is found */
    EVELIB_EDMASCATTERGATHER_ERR_INVALID_BLOCK_DIM     /**< Error code returned if wrong block dimensions are found */
} EVELIB_EDMAScatterGatherErr;

/**
*  @brief      Initializes All ParamSets required for the Transfer.
*
*  @param[in]  numTransfers             Number of transfers to be assigned on the channel.
*  @param[in]  index                    Index of EDMA resource Structure
*  @param[in]  blkWidth                 Width of the block in bytes to be transferred.
*  @param[in] blkHeight                 Height of the block.
*  @param[in] srcStride                 Stride of the source buffer.
*  @param[in] dstStride                 Stride of the destination buffer.
*  @param[in] edmaResources             Pointer to the resources allocated using dma resource allocator API
*  @param[in] edmaCc                    Pointer to the EDMA Base.
*
*
*  @return      EVELIB_EDMAScatterGatherErr
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*/
EVELIB_EDMAScatterGatherErr  EVELIB_EDMAScatterGatherInit( int32_t               numTransfers,   /**< Number of Transfers required */
                                                            uint32_t              index,  /**< Index of EDMA resource Structure*/
                                                            uint32_t              blkWidth,      /**< Width of the Block in int. memory (in bytes)*/
                                                            uint32_t              blkHeight,     /**< Height of the Block in int. memory */
                                                            int16_t               srcStride,     /**< Stride of Source buffer (in bytes)*/
                                                            int16_t               dstStride,     /**< Stride of Destination buffer (in bytes)*/
                                                            DMA_resourceStruct   *edmaResources,    /**< EDMA state structure */
                                                            CSL_EdmaccRegsOvly    edmaCc              /**< Pointer to the start of EDMA CC0 */
                                                            );

/**
*  @brief      De-init EDMA Scatter Gather.
*
*  @param[in] edmaResources             Pointer to the resources allocated using dma resource allocator API.
*  @param[in] edmaCc                    Pointer to the EDMA Base.
*
*
*  @return      EVELIB_EDMAScatterGatherErr
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*/
EVELIB_EDMAScatterGatherErr  EVELIB_EDMAScatterGatherDeInit(DMA_resourceStruct *edmaResources,         /**< EDMA state structure */
                                                             CSL_EdmaccRegsOvly    edmaCc                   /**< Pointer to the start of EDMA CC0 */
                                                             );



#endif
