/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _EVELIB_REMAPEXECUTE_CONFIG_H_
#define _EVELIB_REMAPEXECUTE_CONFIG_H_

#include <stdint.h>
#include "configparser.h"
#include "xdais_types.h"


#define FILE_NAME_SIZE  (256)
#define MODE_NAME_SIZE (10)
#define EVELIB_REMAPEXECUTE_NUM_TESTCASES 10

typedef struct
{
    unsigned char pattern;
    unsigned char inputFile[FILE_NAME_SIZE];
    unsigned char convertedBinMapFile[FILE_NAME_SIZE];
    unsigned char originalMapFile[FILE_NAME_SIZE];
    unsigned char outputFile[FILE_NAME_SIZE];
    unsigned int remapWidth; /* in number of pixels */
    unsigned int remapHeight; /* in number of pixels */
    unsigned int inputWidth;
    unsigned int inputHeight;
    unsigned char colorFormat;
} sremapExecute_Config;

extern uint32_t remapExecute_numTestCases;
extern sremapExecute_Config gConfig_remapExecute[EVELIB_REMAPEXECUTE_NUM_TESTCASES];
extern sTokenMapping gsTokenMap_remapExecute[MAX_ITEMS_TO_PARSE];

#endif
