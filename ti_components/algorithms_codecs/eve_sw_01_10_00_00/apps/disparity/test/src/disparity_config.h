/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_DISPARITY_CONFIG_H_
#define _EVELIB_DISPARITY_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iDisparity_ti.h"

#define FILE_NAME_SIZE  (256)
#define EVELIB_DISPARITY_NUM_TESTCASES 10

typedef struct
{
    unsigned char pattern;
    unsigned char inImageLeft[FILE_NAME_SIZE];
    unsigned char inImageRight[FILE_NAME_SIZE];
    unsigned int srcImageWidth  ; /* in number of pixels */
    unsigned int srcImageHeight ; /* in number of lines */
    unsigned int srcImagePitchL ; /* in number of pixels */
    unsigned int srcImagePitchR ; /* in number of pixels */

    unsigned char inputBitDepth;
    unsigned char winWidth;
    unsigned char winHeight;
    unsigned short numDisparities;
    unsigned char disparityStep;
    unsigned char searchDir;
    unsigned char outputCostType;

    unsigned char outImage[FILE_NAME_SIZE];
    unsigned int dstImagePitch; /* in number of bytes */
} sdisparity_Config;

extern uint32_t disparity_numTestCases;
extern int8_t disparity_skipValidation;
extern sdisparity_Config gConfig_disparity[EVELIB_DISPARITY_NUM_TESTCASES];
extern sTokenMapping gsTokenMap_disparity[MAX_ITEMS_TO_PARSE];

#endif
