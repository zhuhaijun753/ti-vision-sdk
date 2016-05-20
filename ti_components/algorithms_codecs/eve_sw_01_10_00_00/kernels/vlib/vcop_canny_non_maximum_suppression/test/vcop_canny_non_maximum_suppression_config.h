/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CONFIG_H_
#define VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

typedef struct
{
  char      inputData[FILE_NAME_SIZE];
  uint16_t  width;
  uint16_t  height;
  uint16_t  inDataPitch;
  uint16_t  outputPitch;
  uint8_t   lowThreshold;
  uint8_t   highThreshold;
  uint32_t  randSeed;
  uint8_t   numIter;
  uint8_t    testCaseName[FILE_NAME_SIZE];
  uint8_t    performanceTestcase;
  uint8_t    desc[DESCRIPTION_SIZE];
} sCanny_non_maximum_suppression_Config;

extern sCanny_non_maximum_suppression_Config gConfig_canny_non_maximum_suppression;
extern sTokenMapping gsTokenMap_canny_non_maximum_suppression[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CONFIG_H_ */

