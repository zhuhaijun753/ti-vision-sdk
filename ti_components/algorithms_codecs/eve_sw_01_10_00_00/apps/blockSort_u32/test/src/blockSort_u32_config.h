/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_BLOCK_SORT_U32_CONFIG_H_
#define _EVELIB_BLOCK_SORT_U32_CONFIG_H_

#include "configparser.h"
#include "xdais_types.h"
#include "iBlockSort_u32_ti.h"

#define FILE_NAME_SIZE  (256)
#define EVELIB_BLOCKSORT_NUM_TESTCASES 10
#define DESCRIPTION_SIZE  (256)

typedef struct
{
    unsigned int  pattern;

    unsigned char  inImage[FILE_NAME_SIZE];
    unsigned int   srcImageWidth  ;
    unsigned int   srcImageHeight ;
    unsigned int   srcImagePitch ;
    unsigned short blockWidth;
    unsigned short blockHeight;
    unsigned char  outImage[FILE_NAME_SIZE];
    unsigned int   dstImagePitch;
    unsigned char  testCaseName[FILE_NAME_SIZE];
    unsigned int   performanceTestcase;
    unsigned char  desc[DESCRIPTION_SIZE];
} sblockSort_u32_Config;

extern uint32_t blockSort_u32_numTestCases;
extern sblockSort_u32_Config gConfig_blockSort_u32[EVELIB_BLOCKSORT_NUM_TESTCASES];
extern sTokenMapping gsTokenMap_blockSort_u32[MAX_ITEMS_TO_PARSE];

#endif
