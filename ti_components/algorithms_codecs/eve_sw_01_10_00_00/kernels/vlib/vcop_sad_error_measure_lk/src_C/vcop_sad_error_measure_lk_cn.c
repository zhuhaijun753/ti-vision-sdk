/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_sad_error_measure_lk_cn.c                               */
/*                                                                          */
/*     @brief : This file contains definitions for the C reference          */
/*     function namely vcop_sad_error_measure_lk_cn                         */
/*                                                                          */
/*     @version 1.0 (January 2014) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

#include <vcop_sad_error_measure_lk_cn.h>
#include <stdlib.h>

#define VCOP_LK_PATCH_WIDTH          (7) // 7x7

void vcop_sad_error_measure_lk_cn
(
   uint8_t     *pPrevBiLinImg_A,
   uint8_t     *pCurrBiLinImg_B,
   uint16_t    *pNewXYList_X,
   uint16_t    *pOutErrorMeasure_C,
   uint16_t     inputStride,
   uint16_t     frmWidth,
   uint16_t     frmHeight,
   uint16_t     blkWidth,
   uint16_t     blkHeight,
   uint16_t     numKeyPoints,
   uint16_t     shiftValue
)
{
    uint16_t i, j, k;
    uint16_t absPixDiff;
    uint8_t  currFrmPix, prevFrmPix;
    uint32_t sumAbsPixDiff;
    uint8_t  boundaryFlag;
    uint16_t xInt, yInt;

    //Compute the SAD Error Measure for each key point
    for(k = 0; k < numKeyPoints; k++)
    {
      sumAbsPixDiff = 0;
      for(i = 0; i < blkHeight; i++)
      {
          for(j = 0; j < blkWidth; j++)
          {
            prevFrmPix = pPrevBiLinImg_A[k*inputStride*blkHeight + i*inputStride + j];
            currFrmPix = pCurrBiLinImg_B[k*inputStride*blkHeight + i*inputStride + j];
            absPixDiff = abs(currFrmPix-prevFrmPix);
            sumAbsPixDiff += absPixDiff;
          }
      }
      pOutErrorMeasure_C[k] = sumAbsPixDiff;
    }

    //Check the boundary conditions and set the error measure to 0xFFFF if it is out of bound
    for(k = 0; k < numKeyPoints; k++)
    {
        xInt = (pNewXYList_X[2*k] >> shiftValue);
        yInt = (pNewXYList_X[2*k+1] >> shiftValue);
        boundaryFlag = 0;

        //Out of bound check condition implies that the given point location (xInt, yInt)
        //does not have a valid 7x7 window and therefore reset the error measure to 0xFFFF
        boundaryFlag |= xInt <  (VCOP_LK_PATCH_WIDTH/2+1);
        boundaryFlag |= xInt >= (frmWidth - VCOP_LK_PATCH_WIDTH/2-2);
        boundaryFlag |= yInt <  (VCOP_LK_PATCH_WIDTH/2+1);
        boundaryFlag |= yInt >= (frmHeight - VCOP_LK_PATCH_WIDTH/2-2);

        if(boundaryFlag)
        {
            pOutErrorMeasure_C[k] = 0xFFFF;
        }
    }
}
