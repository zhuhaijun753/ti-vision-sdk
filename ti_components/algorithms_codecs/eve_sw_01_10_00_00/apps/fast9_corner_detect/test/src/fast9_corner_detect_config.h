/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef FAST9_CORNER_DETECT_CONFIG_H_
#define FAST9_CORNER_DETECT_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "ifast9_corner_detect_ti.h"

#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)
#define FAST9_NUM_MAX_TESTCASES 20

typedef struct
{
    uint8_t inImage[FAST9_CORNER_DETECT_TI_MAXLEVELS][FILE_NAME_SIZE];
    uint8_t outImage[FAST9_CORNER_DETECT_TI_MAXLEVELS][FILE_NAME_SIZE];
    uint16_t srcImageWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS]  ;
    uint16_t srcImageHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS] ;
    uint16_t srcImagePitch[FAST9_CORNER_DETECT_TI_MAXLEVELS] ;
    uint8_t numLevels;
    uint8_t fileBased;
    uint8_t fast9Threshold[FAST9_CORNER_DETECT_TI_MAXLEVELS];
    uint16_t frameStartX[FAST9_CORNER_DETECT_TI_MAXLEVELS];
    uint16_t frameStartY[FAST9_CORNER_DETECT_TI_MAXLEVELS];
    uint8_t  testCaseName[FILE_NAME_SIZE];
    uint8_t  performanceTestcase;
    uint8_t  desc[DESCRIPTION_SIZE];
} sFast9CornerDetect_Config;

extern uint32_t fast9CornerDetect_numTestCases;
extern sFast9CornerDetect_Config gConfig_fast9CornerDetect[FAST9_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_fast9CornerDetect[MAX_ITEMS_TO_PARSE];

#endif /*FAST9_CORNER_DETECT_CONFIG_H_*/

