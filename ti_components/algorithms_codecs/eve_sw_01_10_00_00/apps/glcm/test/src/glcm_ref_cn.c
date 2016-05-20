/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vcop_intensity_scaling_cn.h"
#include "vcop_intensity_scaling.h"
#include "vcop_glcm_cn.h"

int32_t glcm_ref_cn(uint8_t  *pInput,
                    uint16_t *pCoMatrix,
                    uint16_t  imageWidth,
                    uint16_t  imageHeight,
                    uint16_t  imagePitch,
                    uint8_t   loPixelVal,
                    uint8_t   hiPixelVal,
                    uint8_t   numLevels,
                    uint8_t   numDirections,
                    int8_t   *rowOffset,
                    int8_t   *colOffset)
{
  int32_t status = 0;
  uint8_t  *pScaledImg;
  uint8_t scalingLUT[256];


  /* Prepare LUT for intensity scaling */
  prepare_lut(loPixelVal, hiPixelVal, numLevels, 1, scalingLUT);
  
  pScaledImg = (uint8_t *)malloc(imageWidth*imageHeight);

  status = vcop_intensity_scaling_cn(pInput, scalingLUT, pScaledImg,
                                     imageWidth, imageHeight, imagePitch);
  if(status != 0) {
    printf("GLCM C reference: Intensity Scaling failed.\n");
    goto EXIT;
  }

  status = vcop_glcm_cn(pScaledImg, pCoMatrix, imageWidth, imageHeight, imagePitch,
                        numLevels, numDirections, (char *)rowOffset, (char *)colOffset);

  if(status != 0) {
    printf("GLCM C reference: Co-occurrence Matrix computation failed.\n");
    goto EXIT;
  }

EXIT:
  free(pScaledImg);

  return (status);
}

