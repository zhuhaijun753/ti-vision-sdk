/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
#include "../inc/vcop_yuv420_fir2d_separable_cn.h"

void vcop_yuv420_fir2d_separable_y_cn
(
    uint8_t *        inputPtr,     // input data pointer
    int8_t *        horzCoeffPtr,    // horizontal coef data pointer
    int8_t *        vertCoeffPtr,    // vertical  coef data pointer
    uint16_t   blkw,         // width of input block, in elements
    uint16_t  lofst,        // offset between input lines, in elems
    uint16_t  blkh,         // height of input block
    uint16_t  numCoef,     // width of coef block, in elements
    uint8_t * outputPtr,   // output data pointer
    uint16_t rndBits      // bit position for rounding
)
{
  uint32_t i,j,k,l;
  uint8_t * ptr;
  uint32_t inData;
  uint32_t coefVal;
  uint32_t outData;
  uint8_t  * coeffPtr = NULL;

  coeffPtr = (uint8_t*)malloc(numCoef * numCoef);

  for ( j = 0; j < numCoef; j++)
  {
    for ( i = 0; i < numCoef; i++)
    {
      coeffPtr[i+j*numCoef] = horzCoeffPtr[j] * vertCoeffPtr[i];
    }
  }

  for ( i = 0; i < blkh; i++)
  {
    for ( j = 0 ; j < blkw; j++)
    {

      ptr = &inputPtr[j + ( i * lofst)];
      outData = 0;
      for ( k = 0 ; k < numCoef ; k++)
      {
        for ( l = 0 ; l < numCoef ; l++)
        {
          inData = ptr[l + k * lofst];
          coefVal = coeffPtr[l + k * numCoef];
          outData += inData * coefVal;

        }
      }
      outputPtr[j + ( i * (blkw))] = ( outData + (1<< (rndBits - 1))) >> rndBits ;
    }
  }

  if ( coeffPtr )
  {
    free(coeffPtr);
  }
}




/* ======================================================================== */
/*  End of file:  vcop_yuv420_fir2d_separable_cn.c                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


