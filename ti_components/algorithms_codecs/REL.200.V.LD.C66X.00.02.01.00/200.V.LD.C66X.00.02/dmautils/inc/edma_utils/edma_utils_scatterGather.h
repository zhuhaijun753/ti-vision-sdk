/*
 *******************************************************************************
 *
 * EVE EDMA utility functions
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils_scatterGather.h
 *
 * @brief       This file contains the data types and util function prototype for
 *              configuring EVE EDMA scatter gather usecase.
 *
 * @remarks
 *
 * @remarks
 *              User can have multiple contexts for this usecase. Each context describing
 *              different transfer. This usecase uses QDMA channels with Linking and hence
 *              number of different context for this usecase is limited by number of
 *              QDMA channels
 *
 * @remarks Following is a standard sequence of operation user is expected to do
 *      EDMA_UTILS_scattherGather_getContextSize : To get the size of internal memory needed
 *                          by auto increment util function. User is expected to allocate this memory and
 *                          give it as an input to all util API's
 *
 *      EDMA_UTILS_scattherGather_init(edmaContext, initParams);
 *
 *      EDMA_UTILS_scattherGather_updateNtrigger(scatterGatherContext ,&updateParam);
 *
 *      EDMA_UTILS_scattherGather_wait(scatterGatherContext);
 *
 *      and so on.
 *
 * @remarks If user is only updating source or destination addrress after init then this utility
 *          provides dedicated trigger and update functions for those. Kindly use following
 *          function for this scenario
 *
 *          EDMA_UTILS_scattherGather_updateSrcNtrigger
 *          EDMA_UTILS_scattherGather_updatedstNtrigger
 *
 *          wait function is same across all
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Nov 2013) : First version of eve edma utils autoincrement 1D function
 *
 *****************************************************************************
 */


#ifndef EDMA_UTILS_SCATTERGATHER_H_
#define EDMA_UTILS_SCATTERGATHER_H_

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")


/** ======================= ============================
 *  @name   EDMA_UTILS_SCATTERGATHER_UPDATE_TYPE
 *
 *  @desc   Describes the parameters that needs to be updated while using
 *          generic trigger API (EDMA_UTILS_scattherGather_updateNtrigger)
 *          User can create a mask with more than one fields of this enum
 *          by ORing these fields to update more than one parameters
 *
 *  @field  EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W
 *             Update blockWidth with generic trigger
 *
 *  @field  EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_H
 *             Update blockHeight with generic trigger
 *
 *  @field  EDMA_UTILS_SCATTERGATHER_UPDATE_SRCPTR_STRIDE
 *             Update source and source pointer stride pointer with generic trigger
 *
 *  @field  EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE
 *             Update destination pointer and destination pointer stride with generic trigger
 *  ====================================================
 */
typedef enum
{
    EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W           = (uint32_t)1U << 0U,
    EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_H           = (uint32_t)1U << 1U,
    EDMA_UTILS_SCATTERGATHER_UPDATE_SRCPTR_STRIDE     = (uint32_t)1U << 2U,
    EDMA_UTILS_SCATTERGATHER_UPDATE_DSTPTR_STRIDE     = (uint32_t)1U << 3U,
    EDMA_UTILS_SCATTERGATHER_UPDATE_ALL               = 0xFFFFFFU
}EDMA_UTILS_SCATTERGATHER_UPDATE_TYPE;


/** ========================================================
 *  @name   EDMA_UTILS_scattherGather_transferProperties
 *
 *  @desc   This structure specifies the properties of the transfer for
 *          scatter gather usecase.
 *
 *  @field updateMask
 *              Mask of fields telling which fields needs to be updated.
 *              Refer to EDMA_UTILS_SCATTERGATHER_UPDATE_TYPE for valid
 *              values. User can provided more than one field to be updated
 *              by ORing the above enum. This field is a don't care(ignored) during
 *              EDMA_UTILS_scattherGather_init
 *
 *  @field dmaQueNo
 *              DMA Que number to which particular transfer is expected to go.
 *              This is dont care (ignored) during EDMA_UTILS_scattherGather_updateNtrigger
 *
 *  @field srcPtr
 *             Pointer to the list of source pointer
 *
 *  @field t dstPtr
 *             Pointer to the list of destination pointer
 *
 *  @field srcPtrStride
 *              Pointer to the list of stride for the source pointer
 *
 *  @field dstPtrStride
 *              Pointer to the list of stride for the destination pointer
 *
 *  @field blkWidth
 *              Pointer to the list of Block width for the transfer
 *
 *  @field blkHeight
 *              Pointer to the list of  Block Height for the transrer
 *
 *  ===============================================================
 */
typedef struct
{
    uint8_t     updateMask;
    uint8_t     dmaQueNo;
    uint8_t     **srcPtr;
    uint8_t     **dstPtr;
    uint16_t    *srcPtrStride;
    uint16_t    *dstPtrStride;
    uint16_t    *blkWidth;
    uint16_t    *blkHeight;
}EDMA_UTILS_scattherGather_transferProperties;

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_getContextSize
 *
 *  @desc     This function returns the size of the EDMA UTILS scatter gather handle.
 *            User is then expected to allocate this memory and provide it to EDMA UTILS
 *            scatter gather function. It is always advisable to allocate this handle
 *            in EVE's internal memory for better performance.
 *
 *  @modif    NONE
 *
 *  @inputs   NONE
 *
 *  @outputs NONE
 *
 *  @return    Size of the EDMA UTILS scatter gather context in bytes
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_getContextSize(void);


/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_init
 *
 *  @desc     This function configures EDMA hardware based initParams
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          EDMA utils handle for the scatter gather usecase. This memory is
 *                          expected to be allocated by user by first getting the size using
 *                          EDMA_UTILS_scattherGather_getContextSize.It is always advisable
 *                          to allocate this memory in internal memory for better performance
 *                  initParams :
 *                          Pointer to structure describing init configuration for the EDMA transfer.
 *                          updateMask field of EDMA_UTILS_scattherGather_transferProperties is
 *                          ignored in this call
 *                  numTransfers :
 *                          Number of transfers that needs to be triggered
 *
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_init(void * scatterGatherContext ,
        const EDMA_UTILS_scattherGather_transferProperties * initParams ,
        uint8_t numTransfers);



/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_configure
 *
 *  @desc     TBD
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          EDMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_configure(void * scatterGatherContext );


/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_updateNtrigger
 *
 *  @desc   This function can selectively update four properties of the transfers and actually
 *          trigger the transfer. These prioperties are are sourceAddress, Destination Address,
 *          block widht and block Height. Which property needs to be updated can be given in
 *          EDMA_UTILS_scattherGather_updateParams. Refer this structure for futher details on
 *          each individual fields.
 *          This function can only be called after EDMA_UTILS_scattherGather_init
 *          has been called. Size of array update param should be same as what has
 *          already been initialized in EDMA_UTILS_scattherGather_init.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  updateParams :
 *                          Pointer to the EDMA_UTILS_scattherGather_transferProperties
 *                          describing property to be updated for all the transfers
 *                          which were initialized during init time. dmaQueNo field
 *                          is a don't care during this call. It is to be noted that
 *                          while updating source/destination pointer user is expected to
 *                          provide the source and destination stride also
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_updateNtrigger(void * scatterGatherContext ,
            const EDMA_UTILS_scattherGather_transferProperties * updateParams);


/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_updateSrcNtrigger
 *
 *  @desc   This function updates the source pointer for all the transfers and trigger the transfer.
 *          This function should be used when only source pointer is getting updated after initializing
 *          other parameters
 *          This function can only be called after EDMA_UTILS_scattherGather_init
 *          has been called. Size of array update param should be same as what has
 *          already been initialized in EDMA_UTILS_scattherGather_init.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  srcPtr :
 *                          Pointer to the list of source pointers that needs to be updated
 *                          It is to be noted that only sourcePtr is updated with this call
 *                          stride remains same as the one configured during the init call
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_updateSrcNtrigger(void * scatterGatherContext ,
        uint8_t * const * srcPtr);


/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_updateDstNtrigger
 *
 *  @desc   This function updates the destination pointer for all the transfers and trigger the transfer.
 *          This function should be used when only destination pointer is getting updated after initializing
 *          other parameters
 *          This function can only be called after EDMA_UTILS_scattherGather_init
 *          has been called. Size of array update param should be same as what has
 *          already been initialized in EDMA_UTILS_scattherGather_init.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *                  dstPtr :
 *                          Pointer to the list of source pointers that needs to be updated
 *                          It is to be noted that only destination pointers is updated with
 *                          this call stride remains same as the one configured during the init
 *                          call.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_updateDstNtrigger(void * scatterGatherContext ,
        uint8_t * const * dstPtr);

/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_wait
 *
 *  @desc   This function waits for the DMA transfer to be completed and can be used
 *          for any of the above trigger.
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_wait(void * scatterGatherContext);


/* ==================================================
 *  @func     EDMA_UTILS_scattherGather_deinit
 *
 *  @desc   This function releases all the DMA resource allocated in
 *              EDMA_UTILS_scattherGather_deinit
 *
 *  @modif    This function modifies scatterGatherContext
 *
 *  @inputs   This function takes following Inputs
 *                  scatterGatherContext :
 *                          DMA utils handle for the scatter gather usecase.
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
int32_t EDMA_UTILS_scattherGather_deinit(void * scatterGatherContext);


#endif /*#define EDMA_UTILS_SCATTERGATHER_H_*/



