/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdint.h>

int32_t vcop_intensity_scaling_cn
(
                  uint8_t  *pInput,
                  uint8_t  *scalingLUT,
                  uint8_t  *pScaledImg,
                  uint16_t imageWidth,
                  uint16_t imageHeight,
                  uint16_t imagePitch
)
{
  uint32_t i, j;
  int32_t status = 0;

  /* Perform intensity scaling */
  for(i = 0; i < imageHeight; i++) {
    for(j = 0; j < imageWidth; j++) {
      pScaledImg[i*imageWidth + j] = scalingLUT[pInput[i*imagePitch + j]];
    }
  }

  return status;
}
