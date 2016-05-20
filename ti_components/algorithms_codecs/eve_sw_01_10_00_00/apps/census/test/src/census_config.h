/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_CENSUS_CONFIG_H_
#define _EVELIB_CENSUS_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iCensus_ti.h"

#define FILE_NAME_SIZE  (256)
#define EVELIB_CENSUS_NUM_TESTCASES 7

typedef struct
{
    unsigned char pattern;
    unsigned char inImage[FILE_NAME_SIZE];
    unsigned int srcImageWidth  ; /* in number of pixels */
    unsigned int srcImageHeight ; /* in number of lines */
    unsigned int srcImagePitch ; /* in number of bytes */

    unsigned char inputBitDepth;
    unsigned char winWidth;
    unsigned char winHeight;
    unsigned char winHorzStep;
    unsigned char winVertStep;

    unsigned char outImage[FILE_NAME_SIZE];
    unsigned int dstImagePitch; /* in number of bytes */
} scensus_Config;

extern uint32_t census_numTestCases;
extern scensus_Config gConfig_census[EVELIB_CENSUS_NUM_TESTCASES];
extern sTokenMapping gsTokenMap_census[MAX_ITEMS_TO_PARSE];

#endif
