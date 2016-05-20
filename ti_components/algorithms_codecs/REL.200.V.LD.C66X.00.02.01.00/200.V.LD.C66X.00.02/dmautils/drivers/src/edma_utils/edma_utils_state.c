/** ===========================================================================
* @file   dma_utils_state.c
*
* @path   $(STARTERWAREPATH)/drivers/src/edma_utils
*
* @desc   This  File contains functions that implement dma_resource manager
*
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*/


#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <string.h>
#pragma RESET_MISRA ("required")

#include "edma_utils_state.h"

/*Global Variable to store the State of all EDMA utilities */
#ifdef HOST_EMULATION
DMA_utilsStateStruct gDmaUtilsStateStruct;
#else
near DMA_utilsStateStruct gDmaUtilsStateStruct;
#endif

/* Deceration is needed for MISRA-C */
static int32_t utils_searchValidIndex(uint32_t numChannels , uint32_t * validIndex );

/* ==================================================
 *  @func   utils_searchValidIndex
 *
 *  @desc   Searches a valid Index available to store the resources
 *          in global Utility State Structure. A valid index is the
 *          one which contains continous free index to store all the
 *          resource allocated by resource Allocator for a particular
 *          usecase.
 *
 *  @modif    NONE
 *
 *  @inputs   This function takes following Inputs
 *              numChannels :
 *                  Total Number channels that needs to be stored in
 *                  gDmaUtilsStateStruct
 *  @outputs
 *              validIndex :
 *                  Valid Index found based on critera
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
static int32_t utils_searchValidIndex(uint32_t numChannels , uint32_t * validIndex )
{
    uint32_t indexCnt = 0;
    uint32_t resourceCnt = 0;
    int32_t validIndexFound = 0;
    int32_t status = 0;
    int32_t exitFlag = 0;

    while( indexCnt < NUM_MAX_CHANNELS )
    {
        if ( gDmaUtilsStateStruct.logicalChanNo[indexCnt] == -1 )
        {
            exitFlag = 0;
            for ( resourceCnt = 0; resourceCnt < numChannels ; resourceCnt++ )
            {
                if ( (indexCnt + resourceCnt) < NUM_MAX_CHANNELS )
                {
                    if ( gDmaUtilsStateStruct.logicalChanNo[indexCnt + resourceCnt] != -1 )
                    {
                        exitFlag = 1;
                    }
                }
                else
                {
                    status = -1;
                    exitFlag = 1;
                }
                if ( exitFlag == 1 )
                {
                    break;
                }
            }

            if ( resourceCnt == numChannels )
            {
                validIndexFound = 1;
                *validIndex      = indexCnt;
                break;
            }
            indexCnt = indexCnt + resourceCnt;
        }
        else
        {
            indexCnt++;
        }
    }

    if ( validIndexFound == 0 )
    {
        status = -1;
    }

    return status;

}

/* ==================================================
 *  @func   DMA_utils_resetStateStruct
 *
 *  @desc   This function reset the state structure for all the
 *          EDMA utility usecases
 *
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_utils_resetStateStruct(void)
{
    uint32_t indexCnt;
    for ( indexCnt = 0 ; indexCnt < NUM_MAX_CHANNELS ; indexCnt++ )
    {
        gDmaUtilsStateStruct.logicalChanNo[indexCnt] = -1;
    }
}

/* ==================================================
 *  @func   DMA_utils_updateStateStruct
 *
 *  @desc   This functions updates the state structure for Utilities
 *          based on the resources allocated by using resource Allocator
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaResources :
 *                  Pointer to the resource structure defined in dma_resource.h.
 *                  User is expected to populate following fields of this
 *                  structure as an input and resourceAllocator will  populate
 *                  the remaining fields.
 *  @outputs
 *              startIndex :
 *                  The index at which edmaResources are stored in utilsStateStruct
 *                  Usecase should be using this index to fetch the data
 *                  corresponding to it.
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_utils_updateStateStruct(const DMA_resourceStruct * edmaResources , uint8_t * startIndex)
{
    int32_t     status = 0;
    uint32_t     indexCnt;
    uint32_t    validIndex = 0;

    if ( edmaResources == NULL )
    {
        status = -1;
    }

    if ( status == 0 )
    {
        status = utils_searchValidIndex(edmaResources->numChannels , &validIndex);

        if ( status == 0 )
        {
            for (indexCnt = 0 ; indexCnt < edmaResources->numChannels ; indexCnt++ )
            {
                gDmaUtilsStateStruct.logicalChanNo[indexCnt + validIndex] =
                    (int8_t)edmaResources->logicalChannelNo[indexCnt];
                gDmaUtilsStateStruct.tccVal[indexCnt + validIndex] =
                    (int8_t)edmaResources->tccVal[indexCnt];
                gDmaUtilsStateStruct.baseParam[indexCnt + validIndex] =
                    edmaResources->baseParam[indexCnt];

                *startIndex = validIndex;
            }
        }
        else
        {
#ifdef DEBUG
            printf("DMA_utils_updateStateStruct : gDmaUtilsStateStruct is FULL \n");
#endif
        }
    }

    return status;
}


/* ==================================================
 *  @func   DMA_utils_freeStateStruct
 *
 *  @desc   This functions frees the state structure for Utilities
 *          based on the startIndex and numEnteries
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   This function takes following Inputs
 *              startIndex :
 *                  The index at which edmaResources are stored in utilsStateStruct
 *
 *              numEnteries :
 *                  Number of enteries that needs to be freed from utilsStateStruct
 *                  starting from startIndex
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void DMA_utils_freeStateStruct(uint8_t startIndex , uint8_t numEnteries)
{
    uint32_t indexCnt;

    for ( indexCnt = 0; indexCnt < numEnteries ; indexCnt++ )
    {
        gDmaUtilsStateStruct.logicalChanNo[indexCnt + startIndex] = -1;
    }
}

