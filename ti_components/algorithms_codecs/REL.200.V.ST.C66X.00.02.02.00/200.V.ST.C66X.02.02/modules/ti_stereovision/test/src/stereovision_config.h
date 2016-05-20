/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2014 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef STEREOVISION_CONFIG_H_
#define STEREOVISION_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "istereovision_ti.h"

#define STEREOVISION_FILE_NAME_SIZE  (256)
#define STEREOVISION_NUM_MAX_TESTCASES (20)

typedef struct
{
    uint8_t  inImageFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  inDisparityFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  inAuxDisparityFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  inCostFileName[STEREOVISION_FILE_NAME_SIZE];
    uint8_t  outFileName[STEREOVISION_FILE_NAME_SIZE];
    uint16_t maxImageWidth;
    uint16_t maxImageHeight;
    uint16_t maxFrames;
    uint16_t roiWidth;
    uint16_t roiHeight;
    uint16_t startX;
    uint16_t startY;
    unsigned char inputBitDepth;
    unsigned char censusWinWidth;
    unsigned char censusWinHeight;
    unsigned char censusWinHorzStep;
    unsigned char censusWinVertStep;

    unsigned char costSupportWinWidth;
    unsigned char costSupportWinHeight;
    unsigned short numDisparities;
    unsigned char disparityStep;
    unsigned char searchDir;
    unsigned char smoothingStrength;
    unsigned char disparityNumFracBits;
    unsigned char disparityMinThreshold; /* 0 - 128 */
    unsigned char disparityMaxThreshold; /* 0 - 128 */
    unsigned char costMaxThreshold; /* in % 0 - 100 */
    unsigned char minConfidenceThreshold; /* in % 0 - 100 */
    unsigned char holeFillingStrength; /* in % 0 - 100 */
    unsigned char textureLumaLoThresh; /* 0 - 100 */
    unsigned char textureLumaHiThresh; /* 0 - 100 */
    unsigned char textureThreshold;    /* 0 - 100 */
    unsigned char maxDispDissimilarity; /* In number of disparities */
    unsigned char lrMaxDiffThreshold; /* In number of disparities */
    unsigned char minConfidentNSegment; /* In number of pixels */
} sSTEREOVISION_Config;

extern uint32_t stereovision_numTestCases;
extern sSTEREOVISION_Config gConfig_STEREOVISION[STEREOVISION_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_STEREOVISION[MAX_ITEMS_TO_PARSE];

#endif /* STEREOVISION_CONFIG_H_ */

