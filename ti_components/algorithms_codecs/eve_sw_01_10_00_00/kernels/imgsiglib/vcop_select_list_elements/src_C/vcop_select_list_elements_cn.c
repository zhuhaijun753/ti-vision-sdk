/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vcop_select_list_elements_cn.h"


/* ==================================================
 *  @func     vcop_select_list_elements_cn
 *
 *  @desc     This function uses the selectionMask and selects only those elements from the
 *                  inputList where selectionMask at that byte location has a value of 1
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputList :
 *                          Input list data
 *                          Size of this buffer should be listSize *  sizeof(uint32_t)
 *                  selectionMask :
 *                          Mask which will be used to select elements from the list, Mask will have a value of 1
 *                          at the location where we want to pick the value from the list and 0 at other places.
 *                          The size of this mask should be multiple of 8.
 *                          Size of this buffer should be selectionMaskSize * sizeof(uint8_t)
 *                  listSize :
 *                          Total number of elements present in the list
 *                  selectionMaskSize :
 *                          Size of the mask to be used in terms of bytes. This should be multiple of 8.
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                  outputList
 *                          Pointer to the output buffer which will contain the elements which are selected from the
 *                          input list based on the mask provided
 *                          User should give a worst case buffer size which is same as inputList size
 *
 *  @constraints Following constraints
 *                          selectionMaskSize should be multiple of 8
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_select_list_elements_cn
(
  uint32_t  *inputList,
  uint32_t  *outputList,
  uint8_t   *selectionMask,
  uint32_t   *ouputListSize,
  uint32_t  listSize,
  uint16_t  selectionMaskSize
)

{
  uint32_t i,j, k;
  uint32_t listCount = 0;

  uint32_t numElemsDelta;

  numElemsDelta = listSize - (listSize / selectionMaskSize) * selectionMaskSize;

  for ( i= 0; i < listSize / selectionMaskSize; i++)
  {
    for ( j = 0; j < selectionMaskSize; j++)
    {
      if ( selectionMask[j] == 1 )
      {
        outputList[listCount] = inputList[i* selectionMaskSize + j];
        listCount++;
      }
    }
  }

  /* To take care of non multiple of selectionMaskSize case */
  for ( k = 0; k < numElemsDelta; k++)
  {
    if ( selectionMask[k] == 1 )
    {
      outputList[listCount] = inputList[i * selectionMaskSize + k];
      listCount++;
    }
  }
  *ouputListSize = listCount;
}
