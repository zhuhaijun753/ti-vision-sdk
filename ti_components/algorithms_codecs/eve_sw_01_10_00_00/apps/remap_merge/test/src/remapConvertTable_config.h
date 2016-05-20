/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_REMAPCONVERTTABLE_CONFIG_H_
#define _EVELIB_REMAPCONVERTTABLE_CONFIG_H_

#include <stdint.h>
#include "configparser.h"
#include "xdais_types.h"


#define FILE_NAME_SIZE  (256)
#define MODE_NAME_SIZE (10)
#define EVELIB_REMAPCONVERTTABLE_NUM_TESTCASES 10

typedef struct
{
    unsigned char pattern;
    unsigned char functionName[FILE_NAME_SIZE];
    unsigned char inputMapFileFormat; /* 0: binary 1: text */
    unsigned char inputMapFile[FILE_NAME_SIZE];
    unsigned char outputMapFileFormat; /* 0: binary 1: text */
    unsigned char outputMapFile[FILE_NAME_SIZE];
    unsigned int blockWidth;
    unsigned int blockHeight;
    unsigned int remapWidth; /* in number of pixels */
    unsigned int remapHeight; /* in number of pixels */
    unsigned char colorFormat;
    unsigned char qShift;

} sremapConvertTable_Config;

extern uint32_t remapConvertTable_numTestCases;
extern sremapConvertTable_Config gConfig_remapConvertTable[EVELIB_REMAPCONVERTTABLE_NUM_TESTCASES];
extern sTokenMapping gsTokenMap_remapConvertTable[MAX_ITEMS_TO_PARSE];

#endif
