/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef GLCM_CONFIG_H_
#define GLCM_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define FILE_NAME_SIZE     (256)
#define CONFIG_LINE_SIZE   (300)
#define PARAM_STRING_SIZE  (30)
#define MAX_NUM_OFFSETS    (8)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

typedef struct
{
    char     inImage[FILE_NAME_SIZE];
    uint16_t srcImageWidth;
    uint16_t srcImageHeight;
    uint16_t srcImagePitch;

    char     outGlcm[FILE_NAME_SIZE];

    uint8_t  loPixelVal;
    uint8_t  hiPixelVal;
    uint8_t  numLevels;
    uint8_t  numDirections;
    char     rowOffset[MAX_NUM_OFFSETS];
    char     colOffset[MAX_NUM_OFFSETS];

    uint32_t randSeed;

    uint8_t   testCaseName[FILE_NAME_SIZE];
    uint8_t   testCaseDesc[FILE_NAME_SIZE];
    uint8_t   performanceTestcase;
    char      configLine[CONFIG_LINE_SIZE] ;
    char      configParam[PARAM_STRING_SIZE];

} sGlcm_Config;

extern sGlcm_Config gConfig_glcm;
extern sTokenMapping gsTokenMap_glcm[MAX_ITEMS_TO_PARSE];

#endif /* GLCM_CONFIG_H_ */

