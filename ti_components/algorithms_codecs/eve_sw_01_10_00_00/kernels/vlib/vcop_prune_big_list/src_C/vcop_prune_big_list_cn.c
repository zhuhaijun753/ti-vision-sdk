/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "vcop_prune_big_list_cn.h"

void vcop_prune_big_list_cn
(
    uint32_t  *inList,
    uint16_t  *inSortedIndexList,
    uint32_t  *inSortedIndexList32,
    uint32_t  *outList,
    uint32_t  *nonBestNSize,
    uint16_t  threshold,
    uint16_t  bestN    
)
{
    int32_t i, idx;
    int32_t count = 0;
    int32_t payload;
    int32_t shift = 16;
    
    for(i = 0; i < bestN; i++) 
    {
      // Extract indices from inSortedIndexList entries
      idx = inSortedIndexList[2*i];
      // Pruned output list
      outList[i] = inList[idx];
    }
    /* Check if payload of index is non-zero */
    for(i = 0; i < bestN; i++)
    {
      payload = inSortedIndexList32[i] >> shift;
      if(threshold < payload)
      {
        break;
      }
      count++;
    }
    *nonBestNSize = count;
}
