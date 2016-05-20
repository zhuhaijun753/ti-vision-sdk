/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef ORB_CONFIG_H_
#define ORB_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define FILE_NAME_SIZE  (256)
#define ORB_NUM_MAX_TESTCASES (20)

typedef struct
{
    uint8_t inImage[FILE_NAME_SIZE];
    uint16_t imgFrameWidth  ;
    uint16_t imgFrameHeight ;
    uint16_t imgFramePitch ;
    uint8_t  numLevels ;
    uint8_t fast9Threshold;
    uint16_t startX;
    uint16_t startY;
    uint16_t harrisSensitivityParam;
    uint16_t  totalFeatures; 
    uint8_t  fast9CornerSelectMethod;

    uint8_t outImage[FILE_NAME_SIZE];
    uint8_t fileBased;
} sORB_Config;

extern uint32_t orb_numTestCases;
extern sORB_Config gConfig_ORB[ORB_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_ORB[MAX_ITEMS_TO_PARSE];

#endif /*ORB_CONFIG_H_*/

