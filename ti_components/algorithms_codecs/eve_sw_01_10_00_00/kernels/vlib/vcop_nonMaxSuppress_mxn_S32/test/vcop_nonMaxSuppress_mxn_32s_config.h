/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_NONMAXSUPPRESS_MXN_32S_CONFIG_H_
#define VCOP_NONMAXSUPPRESS_MXN_32S_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

typedef struct
{
  char      inputImage[FILE_NAME_SIZE];
  char      outputImage[FILE_NAME_SIZE];
  uint16_t  width;
  uint16_t  height;
  uint16_t  inputStride;
  uint16_t  outputStride;
  uint16_t  windowWidth;/*m*/
  uint8_t   windowHeight;/*2*/
  int16_t   nmsThreshold;
  uint8_t   outputFormat;
  uint32_t  randSeed;
  uint8_t   numIter;
  uint8_t        testCaseName[FILE_NAME_SIZE];
  uint8_t        performanceTestcase;
  uint8_t        desc[DESCRIPTION_SIZE];
} sNms_mxn_32s_Config;

extern sNms_mxn_32s_Config gConfig_nms_mxn_32s;
extern sTokenMapping gsTokenMap_nms_mxn_32s[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_NONMAXSUPPRESS_MXN_32S_CONFIG_H_ */

