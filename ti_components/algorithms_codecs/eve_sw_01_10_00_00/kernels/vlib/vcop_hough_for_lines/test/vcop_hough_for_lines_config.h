/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_HOUGH_FOR_LINES_CONFIG_H_
#define VCOP_HOUGH_FOR_LINES_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char     edgeMapList[FILE_NAME_SIZE];
  char     outputVotedRhoTheta[FILE_NAME_SIZE];
  uint16_t width;
  uint16_t height;
  uint16_t listSize;
  uint16_t  thetaStart;
  uint16_t  thetaEnd;
  uint8_t   thetaStepSize;
  uint16_t  rhoMaxLength;
  uint32_t randSeed;
  uint8_t  numIter;
} sHough_for_lines_Config;

extern sHough_for_lines_Config gConfig_hough_for_lines;
extern sTokenMapping gsTokenMap_hough_for_lines[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_HOUGH_FOR_LINES_CONFIG_H_ */

