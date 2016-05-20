/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_CONTRAST_STRETCHING_CONFIG_H_
#define VCOP_CONTRAST_STRETCHING_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char       inputImage[FILE_NAME_SIZE];
  char       outputImage[FILE_NAME_SIZE];
  uint16_t   imageWidth;
  uint16_t   imageHeight;
  uint16_t   inputPitch;
  uint16_t   outputPitch;
  uint32_t   randSeed;
  uint8_t    numIter;
} sContrastStretching_Config;

extern sContrastStretching_Config  gConfig_contrast_stretching;
extern sTokenMapping gsTokenMap_contrast_stretching[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_CONTRAST_STRETCHING_CONFIG_H_ */

