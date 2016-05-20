/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef HOUGH_FOR_CIRCLES_CONFIG_H_
#define HOUGH_FOR_CIRCLES_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "ihough_for_circles_ti.h"

#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE (256)

#define HOUGH_FOR_CIRCLES_NUM_MAX_TESTCASES 1

typedef struct
{
    uint8_t   inImg[FILE_NAME_SIZE];
    uint8_t   edgeImg[FILE_NAME_SIZE];
    uint8_t   outputImage[FILE_NAME_SIZE];
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint16_t  imagePitch;
    uint32_t  maxPercentageEdges;
    uint8_t   circleType;
    uint8_t   houghSpaceScaling;
    uint8_t   genEdgeMap;
    uint8_t   numRadius;
    uint8_t   radius[HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS];
    uint8_t   houghScoreThreshold[HOUGH_FOR_CIRCLES_TI_MAX_NUM_RADIUS];
    uint32_t  randSeed;
    uint8_t    testCaseName[FILE_NAME_SIZE];
    uint8_t    performanceTestcase;
    uint8_t    desc[DESCRIPTION_SIZE];
} sHoughForCircles_Config;

extern uint32_t houghForCircles_numTestCases;
extern sHoughForCircles_Config gConfig_houghForCircles[HOUGH_FOR_CIRCLES_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_houghForCircles[MAX_ITEMS_TO_PARSE];

#endif /*HOUGH_FOR_CIRCLES_CONFIG_H_*/

