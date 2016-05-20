/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void vcop_binary_masking_cn
(
  uint8_t  *inByteData,
  uint8_t  *inBitPackedData,
  uint8_t  *outBitPackedData,
  unsigned short computeWidth,
  unsigned short computeHeight,
  unsigned short inputByteDataPitch,
  unsigned short inputBitDataPitch,
  unsigned short outputPitch

)
{
  uint32_t i, j;
  uint32_t bitCount;
  uint8_t byteData;
  uint8_t bitData;
  uint8_t finalOutput;
  uint8_t currentValue;
  bitCount = 0;

  for ( j = 0; j < computeHeight ; j++)
  {
    for ( i = 0; i < computeWidth / 8 ; i++)
    {
      finalOutput= 0;
      for(bitCount = 0; bitCount < 8; bitCount++)
      {
        byteData = inByteData[ (8 * i + bitCount) + j * inputByteDataPitch];
        bitData  = (inBitPackedData[i + ( j * inputBitDataPitch)] >> bitCount ) & 0x1U;

        currentValue  = byteData & bitData;
        finalOutput   |= currentValue << bitCount;
        outBitPackedData[i  + j * outputPitch] = finalOutput;
      }

    }
  }

}


