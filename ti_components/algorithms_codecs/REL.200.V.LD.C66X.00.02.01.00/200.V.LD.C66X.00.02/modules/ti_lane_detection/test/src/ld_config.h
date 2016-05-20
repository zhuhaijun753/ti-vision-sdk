/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2014 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef LD_CONFIG_H_
#define LD_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "ild_ti.h"

#define LD_FILE_NAME_SIZE  (256)
#define LD_NUM_MAX_TESTCASES (20)

typedef struct
{
    uint8_t  inFileName[LD_FILE_NAME_SIZE];
    uint8_t  outFileName[LD_FILE_NAME_SIZE];
    uint16_t maxImageWidth;
    uint16_t maxImageHeight;
    uint16_t actualImgWidth;
    uint16_t actualImgHeight;
    uint16_t maxFrames;
    uint16_t roiWidth;
    uint16_t roiHeight;
    uint16_t startX;
    uint16_t startY;
    uint8_t  cannyHiThresh;
    uint8_t  cannyLoThresh;
    uint8_t  houghNmsThresh;
    uint16_t  maxRho;
    uint16_t  startThetaLeft;
    uint16_t  endThetaLeft;
    uint16_t  startThetaRight;
    uint16_t  endThetaRight;
    uint8_t  thetaStepSize;
    uint8_t  trackMethod;
    uint8_t  enableWarning;
    uint8_t  numHoughMaximasDet;
    uint8_t  numHoughMaximasTrack;
    uint16_t departThetaLeftMin;
    uint16_t departThetaLeftMax;
    uint16_t departRhoLeftMin;
    uint16_t departRhoLeftMax;
    uint16_t departThetaRightMin;
    uint16_t departThetaRightMax;
    uint16_t departRhoRightMin;
    uint16_t departRhoRightMax;
} sLD_Config;

extern uint32_t ld_numTestCases;
extern sLD_Config gConfig_LD[LD_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_LD[MAX_ITEMS_TO_PARSE];

#endif /* LD_CONFIG_H_ */

