/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef EDGE_DETECTOR_CONFIG_H_
#define EDGE_DETECTOR_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "iedge_detector_ti.h"

#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE (256)

#define EDGE_DETECTOR_NUM_MAX_TESTCASES 1

typedef struct
{
    uint8_t   inImage[FILE_NAME_SIZE];
    uint8_t   outImage[FILE_NAME_SIZE];
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint16_t  imagePitch;
    uint16_t  outputPitch;
    uint8_t   kernelSize;
    uint16_t  threshold1;
    uint16_t  threshold2;
    uint8_t   outputFormat;
    uint8_t   method;
    uint32_t  randSeed;
    uint8_t   numIter;
    uint8_t   testCaseName[FILE_NAME_SIZE];
    uint8_t   performanceTestcase;
    uint8_t   desc[DESCRIPTION_SIZE];
} sEdgeDetector_Config;

extern uint32_t edgeDetector_numTestCases;
extern sEdgeDetector_Config gConfig_edgeDetector[EDGE_DETECTOR_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_edgeDetector[MAX_ITEMS_TO_PARSE];

#endif /*EDGE_DETECTOR_CONFIG_H_*/

