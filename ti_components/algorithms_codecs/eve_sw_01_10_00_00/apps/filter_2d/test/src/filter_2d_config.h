/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef FILTER_2D_CONFIG_H_
#define FILTER_2D_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "ifilter_2d_ti.h"

#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

#define FILTER_2D_NUM_MAX_TESTCASES 20
#define MAX_FILTER_COEF_WIDTH   15
#define MAX_FILTER_COEF_HEIGHT  15

typedef struct
{
    uint8_t inImage[FILE_NAME_SIZE];
    uint8_t outImage[FILE_NAME_SIZE];
    uint8_t refImage[FILE_NAME_SIZE];
    uint8_t  imageFormat;
    uint16_t srcImageWidth;
    uint16_t srcImageHeight;
    uint16_t srcImagePitch;
    uint8_t fileBased;
    uint8_t enableContrastStretching;
    uint8_t minPercentileThreshold;
    uint8_t maxPercentileThreshold;
    uint8_t enableFilter;
    uint8_t filterCoeffWidth;
    uint8_t filterCoeffHeight;
    uint8_t filterCoeffs[MAX_FILTER_COEF_WIDTH * MAX_FILTER_COEF_HEIGHT];
    uint8_t    testCaseName[FILE_NAME_SIZE];
    uint8_t    performanceTestcase;
    uint8_t    desc[DESCRIPTION_SIZE];
} sFilter2d_Config;

extern uint32_t filter2d_numTestCases;
extern sFilter2d_Config gConfig_filter2d[FILTER_2D_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_filter2d[MAX_ITEMS_TO_PARSE];

#endif /*FILTER_2D_CONFIG_H_*/

