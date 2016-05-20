/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_YUV_PADDING_CONFIG_H_
#define _EVELIB_YUV_PADDING_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iyuv_padding_ti.h"

#define FILE_NAME_SIZE  (256)

typedef struct
{
    uint32_t numFrames  ;
    uint32_t imWidth  ;
    uint32_t imHeight ;
    uint32_t topPadding    ;
    uint32_t leftPadding   ;
    uint32_t rightPadding  ;
    uint32_t BottomPadding ;
    uint8_t performanceTestcase ;
    uint8_t inImage[FILE_NAME_SIZE];
    uint8_t outImage[FILE_NAME_SIZE];
    uint8_t refImage[FILE_NAME_SIZE];
    uint8_t testCaseName[FILE_NAME_SIZE];
    uint8_t testCaseDesc[FILE_NAME_SIZE];
} yuv_padding_config;

extern yuv_padding_config gParams;
extern sTokenMapping gsTokenMap_yuv_padding[MAX_ITEMS_TO_PARSE];

#endif /* _EVELIB_YUV_PADDING_CONFIG_H_*/
