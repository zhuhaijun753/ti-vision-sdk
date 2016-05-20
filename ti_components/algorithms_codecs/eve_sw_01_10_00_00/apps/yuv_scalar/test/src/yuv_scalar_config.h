/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_YUV_SCALAR_CONFIG_H_
#define _EVELIB_YUV_SCALAR_CONFIG_H_

#include "configparser.h"

#define FILE_NAME_SIZE  (256)

typedef struct
{
    uint32_t numFrames  ;
    uint32_t imWidth  ;
    uint32_t imHeight ;
    uint32_t startFrame  ;
    uint32_t outWidth  ;
    uint32_t outHeight ;
    uint32_t scaleRatioQ12 ;
    uint8_t scalingMethod ;
    uint8_t fracQFmt      ;
    uint8_t performanceTestcase ;
    uint8_t inImage[FILE_NAME_SIZE];
    uint8_t outImage[FILE_NAME_SIZE];
    uint8_t refImage[FILE_NAME_SIZE];
    uint8_t testCaseName[FILE_NAME_SIZE];
    uint8_t testCaseDesc[FILE_NAME_SIZE];
    uint8_t configLine[FILE_NAME_SIZE];
    uint8_t configParam[FILE_NAME_SIZE];
} yuv_scalar_config;

extern yuv_scalar_config gParams;
extern sTokenMapping gsTokenMap_yuv_scalar[MAX_ITEMS_TO_PARSE];

#endif /* _EVELIB_YUV_SCALAR_CONFIG_H_*/
