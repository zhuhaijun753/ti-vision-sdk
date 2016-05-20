/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_IMAGE_PYRAMID_U8_CONFIG_H_
#define _EVELIB_IMAGE_PYRAMID_U8_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iImagePyramid_u8_ti.h"

#define FILE_NAME_SIZE  (256)
typedef struct
{
    unsigned char pattern;

    unsigned char numLevels;
    unsigned char filterType;
    unsigned char inImage[FILE_NAME_SIZE];
    unsigned char testCaseName[FILE_NAME_SIZE];
    unsigned char testCaseDesc[FILE_NAME_SIZE];
    unsigned char performanceTestcase;

    unsigned int srcImageWidth  ;
    unsigned int srcImageHeight ;
    unsigned int srcImagePitch ;

    unsigned char outImage[IMGPYRAMID_MAX_NUM_LEVELS][FILE_NAME_SIZE];
    unsigned int dstImagePitch[IMGPYRAMID_MAX_NUM_LEVELS];
} simagePyramid_u8_Config;

extern uint32_t imagePyramid_u8_numTestCases;
extern simagePyramid_u8_Config gConfig_imagePyramid_u8[1];
extern sTokenMapping gsTokenMap_imagePyramid_u8[MAX_ITEMS_TO_PARSE];

#endif
