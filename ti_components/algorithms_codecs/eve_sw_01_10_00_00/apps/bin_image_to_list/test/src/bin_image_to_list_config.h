/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef BIN_IMAGE_TO_LIST_CONFIG_H_
#define BIN_IMAGE_TO_LIST_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "ibin_image_to_list_ti.h"

#define FILE_NAME_SIZE  (256)
#define BIN_IMAGE_TO_LIST_NUM_MAX_TESTCASES 20
#define DESCRIPTION_SIZE (256)

typedef struct
{
    uint8_t   inputImage[FILE_NAME_SIZE];
    uint8_t   inputMask[FILE_NAME_SIZE];
    uint8_t   outputListXY[FILE_NAME_SIZE];
    uint16_t  imgWidth;
    uint16_t  imgHeight;
    uint16_t  inputImagePitch;
    uint16_t  inputMaskPitch;
    uint8_t   inputDataFormat;
    uint8_t   inputMaskFormat;
    uint16_t  numFrames;
    uint8_t   enableMasking;
    uint8_t   outputListOrder;
    uint8_t   outputListQFormat;
    uint8_t   enableListSuppression;
    uint8_t   listSuppressionMethod;
    uint32_t  suppressionValue;
    uint32_t  randSeed;
    uint8_t   testCaseName[FILE_NAME_SIZE];
    uint8_t   performanceTestcase;
    uint8_t   desc[DESCRIPTION_SIZE];
} sBinImageToList_Config;

extern sBinImageToList_Config gConfig_binImageToList[BIN_IMAGE_TO_LIST_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_binImageToList[MAX_ITEMS_TO_PARSE];

#endif /*BIN_IMAGE_TO_LIST_CONFIG_H_*/

