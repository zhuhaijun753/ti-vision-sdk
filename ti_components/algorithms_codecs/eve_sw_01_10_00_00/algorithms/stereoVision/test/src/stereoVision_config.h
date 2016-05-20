/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_STEREOVISION_CONFIG_H_
#define _EVELIB_STEREOVISION_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iDisparity_ti.h"
#include "iCensus_ti.h"

#define FILE_NAME_SIZE  (256)
#define MODE_NAME_SIZE (10)
#define EVELIB_STEREOVISION_NUM_TESTCASES 10

typedef struct
{
    unsigned char pattern;
    unsigned char inImageLeft[FILE_NAME_SIZE];
    unsigned char inImageRight[FILE_NAME_SIZE];
    unsigned char gtImage[FILE_NAME_SIZE];
    unsigned char stereoMode[MODE_NAME_SIZE];
    unsigned char remapLeft[FILE_NAME_SIZE];
    unsigned char remapRight[FILE_NAME_SIZE];
    unsigned char gtScale;
    unsigned int imageWidth  ; /* in number of pixels */
    unsigned int imageHeight ; /* in number of lines */
    unsigned int srcImagePitch ; /* in number of pixels */
    unsigned int remapWidth; /* in number of pixels */
    unsigned int remapHeight; /* in number of pixels */
    int offset_x;
    int offset_y;

    unsigned char inputBitDepth;
    unsigned char censusWinWidth;
    unsigned char censusWinHeight;
    unsigned char censusWinHorzStep;
    unsigned char censusWinVertStep;

    unsigned char disparityWinWidth;
    unsigned char disparityWinHeight;
    unsigned short numDisparities;
    unsigned char disparityStep;
    unsigned char searchDir;
    unsigned char lrCheck;
    
    unsigned char isRectifyMapInEveFormat;
    unsigned char saveRectifyMapInEveFormat;
    unsigned char enableRectify;
    char          disparityOffset;
    
    float maxMinCostRatio;
    
    unsigned char outImage[FILE_NAME_SIZE];
    unsigned int dstImagePitch; /* in number of bytes */
} sstereoVision_Config;

extern uint32_t stereoVision_numTestCases;
extern sstereoVision_Config gConfig_stereoVision[EVELIB_STEREOVISION_NUM_TESTCASES];
extern sTokenMapping gsTokenMap_stereoVision[MAX_ITEMS_TO_PARSE];

#endif
