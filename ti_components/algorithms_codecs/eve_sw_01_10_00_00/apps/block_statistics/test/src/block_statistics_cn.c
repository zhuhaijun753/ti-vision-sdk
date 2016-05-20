/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : block_statistics_cn.c                                            */
/*                                                                            */
/*   @brief  : This file contains all functions calls for block statistics    */
/*             reference                                                      */
/*                                                                            */
/*   @version 0.2 (Aug 2014) : Base version.                                  */
/*                                                                            */
/*============================================================================*/
#include "block_statistics_cn.h"

void blockStat_cn(
    BLOCK_STATISTICS_TI_CreateParams *createParams,
    uint16_t imageStride,
    uint8_t  *inbuff,
    uint8_t  *refMinOutbuff,
    uint8_t  *refMaxOutbuff,
    uint16_t *refMeanOutbuff,
    uint32_t *refVarOutbuff)
{
  unsigned short sum;
  unsigned int sqSum;
  unsigned char min, max;
  unsigned int uiRow, uiCol, uiNumPix, i, j;
  const unsigned char *pPixel;

  unsigned char *pMinimumVal = refMinOutbuff;
  unsigned char *pMaximumVal = refMaxOutbuff;
  unsigned short *pMeanVal   = refMeanOutbuff;
  unsigned int *pVarianceVal = refVarOutbuff;

  if((inbuff == NULL) || (refMinOutbuff == NULL) ||
     (refMaxOutbuff == NULL) || (refMeanOutbuff == NULL) ||
     (refVarOutbuff == NULL))
  {
    printf("ERROR!! : MEMORY ALLOCATION FAILED ");
  }
  else
  {
    for (uiRow =0; uiRow < createParams->imageHeight; uiRow = uiRow+createParams->statBlockHeight) {
      for (uiCol = 0; uiCol< createParams->imageWidth; uiCol = uiCol+createParams->statBlockWidth) {
        sum = 0;
        sqSum = 0;
        min = 255;
        max = 0;

        for (i = 0; i < createParams->statBlockWidth; i++) {
          for (j = 0; j < createParams->statBlockHeight; j++) {
            pPixel = (unsigned char*) &inbuff[(uiRow+j)*imageStride + (uiCol+i)];

            sum += *pPixel;

            sqSum += ((*pPixel) * (*pPixel));

            if(min > *pPixel) {
              min = *pPixel;
            }

            if(max < *pPixel) {
              max = *pPixel;
            }
          }
        }
        uiNumPix = (createParams->statBlockWidth * createParams->statBlockHeight);

        if (pMeanVal != NULL) {
          *(pMeanVal++) = sum;
        }

        if (pVarianceVal != NULL) {
          *(pVarianceVal++) = (unsigned int)(uiNumPix*sqSum - (int)(sum*sum));
        }

        if (pMinimumVal != NULL) {
          *(pMinimumVal++) = min;
        }

        if (pMaximumVal != NULL) {
          *(pMaximumVal++) = max;
        }
      }
    }
  }
}
