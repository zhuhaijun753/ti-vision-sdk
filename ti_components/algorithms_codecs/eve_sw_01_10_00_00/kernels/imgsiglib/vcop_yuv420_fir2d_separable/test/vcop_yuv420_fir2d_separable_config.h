/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_YUV420_FIR2D_SEPARABLE_CONFIG_H_
#define VCOP_YUV420_FIR2D_SEPARABLE_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

#define MAX_NUM_COEFFICIENTS (15)

typedef struct
{
  char      inputData[FILE_NAME_SIZE];
  uint8_t   horzCoefficients[MAX_NUM_COEFFICIENTS];
  uint8_t   vertCoefficients[MAX_NUM_COEFFICIENTS];
  uint8_t   numCoefficients;
  uint16_t  width;
  uint16_t  height;
  uint16_t  pitch;
  uint8_t   roundBits;
  uint32_t  randSeed;
  uint8_t   numIter;
  uint8_t    testCaseName[FILE_NAME_SIZE];
  uint8_t    performanceTestcase;
  uint8_t    desc[DESCRIPTION_SIZE];
} sYUV420_fir2d_separable_Config;

extern sYUV420_fir2d_separable_Config gConfig_yuv420_fir2d_separable;
extern sTokenMapping gsTokenMap_yuv420_fir2d_separable[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_YUV420_FIR2D_SEPARABLE_CONFIG_H_ */

