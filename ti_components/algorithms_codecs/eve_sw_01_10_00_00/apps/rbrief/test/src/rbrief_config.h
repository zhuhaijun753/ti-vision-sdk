/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef RBRIEF_CONFIG_H_
#define RBRIEF_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "irbrief_ti.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

#define RBEIEF_NUM_MAX_TESTCASES (20)

typedef struct
{
    uint8_t inImage[RBRIEF_TI_MAXLEVELS][FILE_NAME_SIZE];
    uint16_t srcImageWidth[RBRIEF_TI_MAXLEVELS]  ;
    uint16_t srcImageHeight[RBRIEF_TI_MAXLEVELS] ;
    uint16_t srcImagePitch[RBRIEF_TI_MAXLEVELS] ;
    uint8_t outImage[FILE_NAME_SIZE];
    uint16_t  maxNumFeatures;
    uint8_t xyLevelListFile[FILE_NAME_SIZE];
    uint8_t numLevels;
    uint8_t fileBased;
    uint8_t        testCaseName[FILE_NAME_SIZE];
    uint8_t        performanceTestcase;
    uint8_t        desc[DESCRIPTION_SIZE];
} sRbrief_Config;

extern uint32_t rbrief_numTestCases;
extern sRbrief_Config gConfig_rbrief[RBEIEF_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_rbrief[MAX_ITEMS_TO_PARSE];

#endif /*EVELIB_RBRIEF_CONFIG_H_*/

