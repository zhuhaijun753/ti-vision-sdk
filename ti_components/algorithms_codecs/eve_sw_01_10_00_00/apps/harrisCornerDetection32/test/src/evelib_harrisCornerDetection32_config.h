/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_HARRISCORNER_CONFIG_H_
#define _EVELIB_HARRISCORNER_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iHarrisCornerDetection32_ti.h"

#define FILE_NAME_SIZE  (256)

typedef struct
{
    unsigned char pattern;

    unsigned char inImage[FILE_NAME_SIZE];
    unsigned int srcImageWidth  ;
    unsigned int srcImageHeight ;
    unsigned int srcImagePitch ;
    unsigned int dstImagePitch ;
    unsigned short harrisScaling; /**< scaling factor used by harris score kernel*/
    int      nmsThresh;                /**< threshold parameter for non maximum suppression kernel */
    unsigned char qShift;
    unsigned char harrisWindowSize;
    unsigned char harrisScoreMethod;
    unsigned char suppressionMethod;
    unsigned char outputFormat;
    unsigned char outImage[FILE_NAME_SIZE];
    unsigned char testCaseName[FILE_NAME_SIZE];
    unsigned char testCaseDesc[FILE_NAME_SIZE];
    unsigned char performanceTestcase;

} sharrisCornerDetection32_Config;

extern uint32_t harrisCornerDetection32_numTestCases;
extern sharrisCornerDetection32_Config gConfig_harrisCornerDetection32[1];
extern sTokenMapping gsTokenMap_harrisCornerDetection32[MAX_ITEMS_TO_PARSE];

#endif
