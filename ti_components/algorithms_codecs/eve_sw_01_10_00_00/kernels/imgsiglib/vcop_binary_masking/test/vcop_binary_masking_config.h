/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_BINARY_MASKING_CONFIG_H_
#define VCOP_BINARY_MASKING_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

typedef struct
{
  char      inByteData[FILE_NAME_SIZE];
  char      inBitPackedData[FILE_NAME_SIZE];
  char      outBitPackedData[FILE_NAME_SIZE];
  uint16_t  blockWidth;
  uint16_t  blockHeight;
  uint16_t  inputByteDataPitch;
  uint16_t  inputBitDataPitch;
  uint16_t  outputPitch;
  uint32_t  randSeed;
  uint8_t   numIter;
  uint8_t    testCaseName[FILE_NAME_SIZE];
  uint8_t    performanceTestcase;
  uint8_t    desc[DESCRIPTION_SIZE];
} sBinary_masking_Config;

extern sBinary_masking_Config gConfig_binary_masking;
extern sTokenMapping gsTokenMap_binary_masking[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_BINARY_MASKING_CONFIG_H_ */

