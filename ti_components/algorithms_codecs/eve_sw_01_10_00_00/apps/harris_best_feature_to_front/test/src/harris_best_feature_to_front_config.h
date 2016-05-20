/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef HARRIS_BEST_FEATURE_TO_FRONT_CONFIG_H_
#define HARRIS_BEST_FEATURE_TO_FRONT_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define FILE_NAME_SIZE (256)
#define DESCRIPTION_SIZE (256)
#define MAX_NUM_LEVELS 3
#define HARRIS_BFTF_NUM_MAX_TESTCASES 20

typedef struct
{
    char     inImage[MAX_NUM_LEVELS][FILE_NAME_SIZE];
    uint16_t srcImageWidth[MAX_NUM_LEVELS];
    uint16_t srcImageHeight[MAX_NUM_LEVELS];
    uint16_t srcImagePitch[MAX_NUM_LEVELS];

    uint8_t  xyListInDmem;
    char     inXyList[MAX_NUM_LEVELS][FILE_NAME_SIZE];
    uint16_t numPoints[MAX_NUM_LEVELS];

    char     outXyList[FILE_NAME_SIZE];
    char     outLevelIds[FILE_NAME_SIZE];

    uint8_t  numLevels;
    uint16_t maxNumFeaturesIn;
    uint16_t bestNFeaturesOut;
    uint16_t sensitivityParam;

    uint8_t  fileBased;
    uint32_t randSeed;
    uint8_t  testCaseName[FILE_NAME_SIZE];
    uint8_t  performanceTestcase;
    uint8_t  desc[DESCRIPTION_SIZE];
} sHarrisBestFeatureToFront_Config;

extern uint32_t numTestCases;
extern sHarrisBestFeatureToFront_Config gConfig_harrisBestFeatureToFront[HARRIS_BFTF_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_harrisBestFeatureToFront[MAX_ITEMS_TO_PARSE];

#endif /* HARRIS_BEST_FEATURE_TO_FRONT_CONFIG_H_ */

