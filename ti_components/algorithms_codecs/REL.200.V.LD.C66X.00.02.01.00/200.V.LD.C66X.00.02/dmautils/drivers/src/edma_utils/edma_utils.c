/*
*******************************************************************************
*
* EDMA utility functions
*
*  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
*******************************************************************************
*/

/**
*****************************************************************************
* @file
*  edma_utils.c
*
* @brief    This function implements functions which can be used accross all usecases
*
* @author: Anshu Jain (anshu_jain@ti.com)
*
* @version 0.1 (Aug 2013) : First version of edma utils
*
*****************************************************************************
*/

#include "edma_utils.h"

#pragma CHECK_MISRA ("none")
#include "csl_edma.h"
#include "cslr_edmacc.h"
#pragma RESET_MISRA ("required")

#include "GlobalTypes.h"
#include "dma_funcs.h"
#include "dma_resource_allocator.h"
#include "edma_utils_state.h"

#ifdef HOST_EMULATION

CSL_EdmaccRegs dummyEDMAreg;
CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)(&dummyEDMAreg);                   /**< Pointer to the start of EDMA CC0 */

#else

CSL_EdmaccRegsOvly            gEdmaCc = (CSL_EdmaccRegsOvly)CSL_EDMACC_0_REGS;                   /**< Pointer to the start of EDMA CC0 */

#endif

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
void  EDMA_UTILS_setEdma3RmHandle(EDMA3_RM_Handle edma3RmHandle)
{
    DMA_resourceAllocator_setEdma3RmHandle(edma3RmHandle);
}


/* ==================================================
*  @func     EDMA_UTILS_globalReset
*
*  @desc   This function resets the global utils state structure which contains
*          all resources allocatred for different utility usecases also it
*          releases all the resources allocated by resources mangaer so far.
*          This function should be called once before using EDMA utilities
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
void  EDMA_UTILS_globalReset(void)
{
  /* If we are not using EDMA3LLD then just set the EDMA3 RM handle to NULL */
#ifndef USE_EDMA3LLD
    DMA_resourceAllocator_setEdma3RmHandle(NULL);
#endif

    /* Reset global Utility State Structure */
    DMA_utils_resetStateStruct();

    /* Initalize all the resources in resource allocator */
    DMA_resourceAllocator_initResources();

    /* Clear All pending interrupts so as to start with clear state */
    if ( gEdmaCc->IPR != 0 )
    {
#ifdef DEBUG
        printf ("Warning : EDMA_UTILS_globalReset - Previous IPR registers are not cleared \n");
#endif
        gEdmaCc->ICR= gEdmaCc->IPR;
        gEdmaCc->ICRH= gEdmaCc->IPRH;
    }
    gEdmaCc->QEECR = 0xFFU;

}

