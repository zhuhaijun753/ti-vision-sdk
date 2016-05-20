/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_MEDIAN_3x3_CONFIG_H_
#define _VCOP_MEDIAN_3x3_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       outImg[FILE_NAME_SIZE];
  uint16_t   blockWidth;
  uint16_t   blockHeight;
  uint8_t    dataType;
  uint32_t   randSeed;
  uint8_t    numIter;
} sMedian3x3_Config;

extern sMedian3x3_Config gConfig_median3x3;
extern sTokenMapping gsTokenMap_median3x3[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_MEDIAN_3x3_CONFIG_H_ */
