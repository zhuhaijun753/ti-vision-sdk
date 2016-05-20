/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef MEDIAN_FILTER_CONFIG_H_
#define MEDIAN_FILTER_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define FILE_NAME_SIZE   (256)
#define DESCRIPTION_SIZE (256)

typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       outImg[FILE_NAME_SIZE];
  uint16_t   imageWidth;
  uint16_t   imageHeight;
  uint16_t   imagePitch;
  uint8_t    blockWidth;
  uint8_t    blockHeight;
  uint16_t   stepSizeHorz;
  uint16_t   stepSizeVert;
  uint32_t   randSeed;
  uint8_t    numIter;
  uint8_t    testCaseName[FILE_NAME_SIZE];
  uint8_t    performanceTestcase;
  uint8_t    desc[DESCRIPTION_SIZE];

} sMedianFilter_Config;

extern sMedianFilter_Config gConfig_median_filter;
extern sTokenMapping gsTokenMap_median_filter[MAX_ITEMS_TO_PARSE];

#endif /* MEDIAN_FILTER_CONFIG_H_ */

