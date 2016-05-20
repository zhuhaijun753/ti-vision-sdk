/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef FEATURE_MATCHING_CONFIG_H_
#define FEATURE_MATCHING_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define  FILE_NAME_SIZE       (256)
#define  CONFIG_LINE_SIZE     (300)
#define  PARAM_STRING_SIZE    (30)


#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

typedef struct
{
    char      inFeatureList1[FILE_NAME_SIZE];
    char      inFeatureList2[FILE_NAME_SIZE];
    char      outCorrespondence[FILE_NAME_SIZE];

    uint16_t  numDescriptors1;
    uint16_t  numDescriptors2;
    uint16_t  descriptorLength;
    uint16_t  minDistanceThres;
    uint16_t  matchConfidence;

    uint32_t  randSeed1;
    uint32_t  randSeed2;

    uint8_t   testCaseName[FILE_NAME_SIZE];
    uint8_t   testCaseDesc[FILE_NAME_SIZE];
    uint8_t   performanceTestcase;
    char      configLine[CONFIG_LINE_SIZE] ;
    char      configParam[PARAM_STRING_SIZE];

} sFeatureMatching_Config;

extern sFeatureMatching_Config gConfig_feature_matching;
extern sTokenMapping gsTokenMap_feature_matching[MAX_ITEMS_TO_PARSE];

#endif /* FEATURE_MATCHING_CONFIG_H_ */

