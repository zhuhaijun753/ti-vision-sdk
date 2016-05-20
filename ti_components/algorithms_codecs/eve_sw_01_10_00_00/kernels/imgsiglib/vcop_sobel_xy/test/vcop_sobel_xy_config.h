/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_SOBEL_XY_CONFIG_H_
#define VCOP_SOBEL_XY_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

typedef struct
{
  char      inputData[FILE_NAME_SIZE];
  char      outputData[FILE_NAME_SIZE];
  uint16_t  blockWidth;
  uint16_t  blockHeight;
  uint16_t  inputPitch;
  uint16_t  outputPitch;
  uint8_t   kernelSize;
  uint16_t  threshold;
  uint32_t  randSeed;
  uint8_t   numIter;
  uint8_t    testCaseName[FILE_NAME_SIZE];
  uint8_t    performanceTestcase;
  uint8_t    desc[DESCRIPTION_SIZE];
} sSobel_Xy_Config;

extern sSobel_Xy_Config gConfig_sobel_xy;
extern sTokenMapping gsTokenMap_sobel_xy[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_SOBEL_XY_CONFIG_H_ */

