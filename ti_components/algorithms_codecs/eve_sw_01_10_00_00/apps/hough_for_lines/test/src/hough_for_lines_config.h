/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef HOUGH_FOR_LINES_CONFIG_H_
#define HOUGH_FOR_LINES_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "ihough_for_lines_ti.h"

#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)
#define HOUGH_FOR_LINES_NUM_MAX_TESTCASES 20

typedef struct
{
    uint8_t   edgeMapList[FILE_NAME_SIZE];
    uint8_t   votedRhoThetaSpace[FILE_NAME_SIZE];
    uint8_t   refImage[FILE_NAME_SIZE];
    uint16_t  srcImageWidth;
    uint16_t  srcImageHeight;
    uint16_t  listSize;
    uint16_t  thetaStart;
    uint16_t  thetaEnd;
    uint8_t   thetaStepSize;
    uint16_t  rhoMaxLength;
    uint32_t  randSeed;
    uint8_t        testCaseName[FILE_NAME_SIZE];
    uint8_t        performanceTestcase;
    uint8_t        desc[DESCRIPTION_SIZE];
} sHoughForLines_Config;

extern uint32_t houghForLines_numTestCases;
extern sHoughForLines_Config gConfig_houghForLines[HOUGH_FOR_LINES_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_houghForLines[MAX_ITEMS_TO_PARSE];

#endif /*HOUGH_FOR_LINES_CONFIG_H_*/

