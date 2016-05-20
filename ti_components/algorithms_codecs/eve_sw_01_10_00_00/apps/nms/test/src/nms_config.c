/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "nms_config.h"
#pragma RESET_MISRA ("required")

sNms_Config gConfig_nms[NMS_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_nms[] =
{
  {(char *)"inputImage"       ,&gConfig_nms[0].inputImage     , STRING, SINGLE},
  {(char *)"outputListXY"     ,&gConfig_nms[0].outputListXY   , STRING, SINGLE},
  {(char *)"inputByteDepth"   ,&gConfig_nms[0].inputByteDepth  , INT_16, SINGLE},
  {(char *)"imgWidth"         ,&gConfig_nms[0].imgWidth       , INT_16, SINGLE},
  {(char* )"imgHeight"        ,&gConfig_nms[0].imgHeight      , INT_16, SINGLE},
  {(char* )"imgStride"        ,&gConfig_nms[0].imgStride      , INT_16, SINGLE},
  {(char* )"nmsThreshold"     ,&gConfig_nms[0].nmsThreshold   , INT_32, SINGLE},
  {(char* )"windowWidth"      ,&gConfig_nms[0].windowWidth    , INT_8, SINGLE},
  {(char* )"windowHeight"     ,&gConfig_nms[0].windowHeight   , INT_8, SINGLE},
  {(char* )"randSeed"         ,&gConfig_nms[0].randSeed       , INT_32, SINGLE},
  {(char* )"numFrames"        ,&gConfig_nms[0].numFrames      , INT_16 , SINGLE},
  {(char* )"testCaseName",           &gConfig_nms[0].testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_nms[0].performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                   &gConfig_nms[0].desc                   , STRING, SINGLE}
} ;

