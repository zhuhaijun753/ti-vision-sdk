/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef NMS_CONFIG_H_
#define NMS_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "inms_ti.h"

#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

#define NMS_NUM_MAX_TESTCASES 20

typedef struct
{
    uint8_t   inputImage[FILE_NAME_SIZE];
    uint8_t   outputListXY[FILE_NAME_SIZE];
    uint8_t   inputByteDepth;
    uint16_t  imgWidth;
    uint16_t  imgHeight;
    uint16_t  imgStride;
    int32_t   nmsThreshold;
    uint8_t   windowWidth;
    uint8_t   windowHeight;
    uint32_t  randSeed;
    uint16_t  numFrames;
    uint8_t        testCaseName[FILE_NAME_SIZE];
    uint8_t        performanceTestcase;
    uint8_t        desc[DESCRIPTION_SIZE];
} sNms_Config;

extern sNms_Config gConfig_nms[NMS_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_nms[MAX_ITEMS_TO_PARSE];

#endif /*NMS_CONFIG_H_*/

