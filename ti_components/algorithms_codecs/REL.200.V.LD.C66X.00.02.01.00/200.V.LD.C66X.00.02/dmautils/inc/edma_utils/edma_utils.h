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
 *  edma_utils.h
 *
 * @brief    This function declares functions which can be used accross all usecases
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 *
 * @version 0.1 (Aug 2013) : First version of eve edma utils
 *
 *****************************************************************************
 */

#ifndef EDMA_UTILS_H_
#define EDMA_UTILS_H_

#include "edma3lld_support.h"
#include "dma_resource_allocator.h"
/** ======================= ============================
 *  @name   EDMA_UTILS_TRANSFER_TYPE
 *
 *  @desc   Describes the type of transfer you want to configure while configuring
 *                 auto increments
 *
 *  @field  EDMA_UTILS_TRANSFER_IN
 *             Indicates IN transfer, external memory to Internal memory
 *
 *  @field  EDMA_UTILS_TRANSFER_OUT
 *             Indicates OUT transfer, internal memory to external memory
 *
 *  @field  EDMA_UTILS_TRANSFER_INOUT
 *             Indicates that user wants to configure both IN and OUT transfer together
 *  ====================================================
 */
typedef enum
{
    EDMA_UTILS_TRANSFER_IN,
    EDMA_UTILS_TRANSFER_OUT,
    EDMA_UTILS_TRANSFER_INOUT
}EDMA_UTILS_TRANSFER_TYPE;

/* ==================================================
*  @func     EDMA_UTILS_setEdma3RmHandle
*
*  @desc   This is first function which should be called before calling any
*               utility function ane even before EDMA_UTILS_globalReset function is called.
*               This function sets the EDMA3 LLD handle which will be used for resource
*               allocation. User can pass the handle as NULL also for the cases he/she doesnt
*               want to use EDMA3 LLD.
*
*  @modif    NONE
*
*  @inputs   edma3RmHandle : Handle to the EDMA3 LLD resoruce manager instance
*                 This can take value as NULL for the cases where user doesnt want to use
*                 EDMA3 LLD
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
void  EDMA_UTILS_setEdma3RmHandle(EDMA3_RM_Handle edma3RmHandle);

/* ==================================================
*  @func     EDMA_UTILS_globalReset
*
*  @desc   This function resets the global utils state structure which contains
*          all resources allocatred for different utility usecases also it
*          releases all the resources allocated by resources mangaer so far.
*          This function should be called once before using EDMA utilities. It is
*          IMPORTANT to note that EDMA_UTILS_setEdma3RmHandle function
*          should have been called before calling this function
*
*  @modif    NONE
*
*  @inputs   NONE
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
void  EDMA_UTILS_globalReset(void);

#endif

