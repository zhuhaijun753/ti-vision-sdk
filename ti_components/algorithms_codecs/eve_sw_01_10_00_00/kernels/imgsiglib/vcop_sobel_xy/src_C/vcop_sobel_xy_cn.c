/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SAT_LO          (-128)
#define SAT_HI          (127)

void vcop_sobelXY_3x3_separable_uchar_cn
(
  uint8_t  *inData,
  int16_t  *interimDataX,
  int16_t  *interimDataY,
  int8_t   *outDataX,
  int8_t   *outDataY,
  uint16_t  computeWidth,
  uint16_t  computeHeight,
  uint16_t  inputPitch,
  uint16_t  outputPitch,
  uint8_t   roundShift
)
{
  uint32_t i, j;
  uint32_t k, l;
  uint8_t * inPtr;
  int16_t outX;
  int16_t outY;

  int8_t coeffPtrX[]={1, 0, -1,
                      2, 0, -2,
                      1, 0, -1};
  int8_t coeffPtrY[]= {+1, +2, +1,
                        0,  0, 0,
                       -1, -2, -1};


  for ( j = 0; j < computeHeight ; j++)
  {
    for ( i = 0; i < computeWidth; i++)
    {
      outX = 0;
      outY = 0;
      inPtr = &inData[ i + j * inputPitch];
      for ( l = 0; l < 3; l++)
      {
        for ( k = 0; k < 3; k++)
        {
            outX+= coeffPtrX[k + l * 3] * inPtr[ k + l * inputPitch];
            outY+= coeffPtrY[k + l * 3] * inPtr[ k + l * inputPitch];
        }
      }

      outX = (outX + (1<< (roundShift - 1)) )>> roundShift;
      outY = (outY + (1<< (roundShift - 1)) )>> roundShift;

      if ( outX > SAT_HI )
      {
        outX = SAT_HI;
      }
      if ( outX < SAT_LO )
      {
        outX = SAT_LO;
      }

      if ( outY > SAT_HI )
      {
        outY = SAT_HI;
      }
      if ( outY < SAT_LO )
      {
        outY = SAT_LO;
      }

      outDataX[i + j * outputPitch] = outX;
      outDataY[i + j * outputPitch] = outY;
    }
  }

}

void vcop_sobelXy_3x3_L1_thresholding_cn
(
   int8_t   *gradX,
   int8_t   *gradY,
   uint8_t  *outData,
   uint16_t  computeWidth,
   uint16_t  computeHeight,
   uint16_t  inputPitch,
   uint16_t  outputPitch,
   uint16_t  threshold
)
{
  uint32_t mag;
  uint32_t i,j;
  int8_t   gx,gy;

  for ( j = 0; j < computeHeight ; j++)
  {
    for ( i = 0; i < computeWidth; i++)
    {
      gx = gradX[i + j * inputPitch];
      gy = gradY[i + j * inputPitch];

      mag = abs(gx) + abs(gy);

      if ( mag > threshold )
      {
        outData[i + j * outputPitch] = 255;
      }
      else
      {
        outData[i + j * outputPitch] = 0;
      }
    }
  }

}


void vcop_sobelXy_3x3_L1_thresholding_binPack_cn
(
   int8_t   *gradX,
   int8_t   *gradY,
   uint8_t  *outData,
   uint16_t  computeWidth,
   uint16_t  computeHeight,
   uint16_t  inputPitch,
   uint16_t  outputPitch,
   uint16_t  threshold
)
{
  uint32_t mag;
  uint32_t i,j;
  int8_t   gx,gy;
  uint8_t  bitCount = 0;
  unsigned char bitMask = 0;

  for ( j = 0; j < computeHeight ; j++)
  {
    for ( i = 0; i < computeWidth; i++)
    {
      gx = gradX[i + j * inputPitch];
      gy = gradY[i + j * inputPitch];

      mag = abs(gx) + abs(gy);


      if ( mag >= threshold )
      {
        bitMask = (bitMask) | (0x1U << bitCount) ;
      }
      else
      {
         bitMask = (bitMask);
      }
      bitCount++;

      if ( i == computeWidth - 1)
      {
        bitCount = 0;
      }

      if ( bitCount % 8  == 0)
      {
        outData[(i/8) + j * outputPitch] = bitMask;
        bitCount = 0;
        bitMask = 0;
      }

    }
  }

}


