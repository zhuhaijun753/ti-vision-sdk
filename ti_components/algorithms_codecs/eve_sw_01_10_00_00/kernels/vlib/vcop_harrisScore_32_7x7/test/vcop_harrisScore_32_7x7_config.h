/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_HARRIS_SCORE_32_7x7_CONFIG_H_
#define VCOP_HARRIS_SCORE_32_7x7_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char     inputBlock[FILE_NAME_SIZE];
  char     outputScore[FILE_NAME_SIZE];
  uint16_t width;
  uint16_t height;
  uint16_t srcPitch;
  uint16_t destPitch;
  uint16_t sensitivityParam;
  uint8_t  windowSize;
  uint8_t  scoreMethod;
  uint32_t randSeed;
  uint8_t  numIter;
  unsigned char testCaseName[FILE_NAME_SIZE];
  unsigned char testCaseDesc[FILE_NAME_SIZE];
  unsigned char performanceTestcase;
} sHarris_score_32_7x7_Config;

extern sHarris_score_32_7x7_Config gConfig_harris_score_32_7x7;
extern sTokenMapping gsTokenMap_harris_score_32_7x7[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_HARRIS_SCORE_32_7x7_CONFIG_H_ */

