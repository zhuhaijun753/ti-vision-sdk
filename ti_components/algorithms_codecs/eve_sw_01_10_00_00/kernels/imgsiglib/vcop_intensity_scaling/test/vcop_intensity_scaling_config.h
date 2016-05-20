/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_INTENSITY_SCALING_CONFIG_H_
#define _VCOP_INTENSITY_SCALING_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       outImg[FILE_NAME_SIZE];
  uint16_t   imageWidth;
  uint16_t   imageHeight;
  uint16_t   imagePitch;
  uint8_t    loPixelVal;
  uint8_t    hiPixelVal;
  uint8_t    numLevels;
  uint32_t   randSeed;
  uint8_t    numIter;
} sIntensityScaling_Config;

extern sIntensityScaling_Config gConfig_intensity_scaling;
extern sTokenMapping gsTokenMap_intensity_scaling[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_INTENSITY_SCALING_CONFIG_H_ */
