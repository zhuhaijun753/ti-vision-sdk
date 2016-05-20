/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_HOUGH_FOR_CIRCLES_CONFIG_H_
#define VCOP_HOUGH_FOR_CIRCLES_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char      gradDir[FILE_NAME_SIZE];
  char      xyList[FILE_NAME_SIZE];
  char      houghIdx[FILE_NAME_SIZE];

  uint8_t   testCase;
  uint16_t  listSize;
  uint16_t  imgWidth;
  uint16_t  imgHeight;
  uint8_t   radius;
  uint8_t   houghSpaceDownScale;
  uint8_t   houghScoreThreshold;

  uint16_t  startX;
  uint16_t  startY;

  uint32_t  randSeedGrad;
  uint32_t  randSeedXY;
  uint32_t  randSeedHoughIdx;
  uint8_t   numIter;
} sHough_for_circles_Config;

extern sHough_for_circles_Config gConfig_hough_for_circles;
extern sTokenMapping gsTokenMap_hough_for_circles[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_HOUGH_FOR_CIRCLES_CONFIG_H_ */

