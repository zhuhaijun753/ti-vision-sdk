/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "bin_image_to_list_config.h"
#pragma RESET_MISRA ("required")

sBinImageToList_Config gConfig_binImageToList[BIN_IMAGE_TO_LIST_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_binImageToList[] =
{
  {(char *)"inputImage"               ,&gConfig_binImageToList[0].inputImage             , STRING, SINGLE},
  {(char *)"inputMask"                ,&gConfig_binImageToList[0].inputMask              , STRING, SINGLE},
  {(char *)"outputListXY"             ,&gConfig_binImageToList[0].outputListXY           , STRING, SINGLE},
  {(char *)"imgWidth"                 ,&gConfig_binImageToList[0].imgWidth               , INT_16, SINGLE},
  {(char* )"imgHeight"                ,&gConfig_binImageToList[0].imgHeight              , INT_16, SINGLE},
  {(char* )"inputImagePitch"          ,&gConfig_binImageToList[0].inputImagePitch        , INT_16, SINGLE},
  {(char* )"inputMaskPitch"           ,&gConfig_binImageToList[0].inputMaskPitch         , INT_16, SINGLE},
  {(char* )"inputDataFormat"          ,&gConfig_binImageToList[0].inputDataFormat        , INT_8, SINGLE},
  {(char* )"inputMaskFormat"          ,&gConfig_binImageToList[0].inputMaskFormat        , INT_8, SINGLE},
  {(char* )"numFrames"                ,&gConfig_binImageToList[0].numFrames              , INT_16, SINGLE},
  {(char* )"enableMasking"            ,&gConfig_binImageToList[0].enableMasking          , INT_8, SINGLE},
  {(char* )"outputListQFormat"        ,&gConfig_binImageToList[0].outputListQFormat      , INT_8, SINGLE},
  {(char* )"outputListOrder"          ,&gConfig_binImageToList[0].outputListOrder        , INT_8, SINGLE},
  {(char* )"enableListSuppression"    ,&gConfig_binImageToList[0].enableListSuppression  , INT_8, SINGLE},
  {(char* )"listSuppressionMethod"    ,&gConfig_binImageToList[0].listSuppressionMethod  , INT_8, SINGLE},
  {(char* )"suppressionValue"         ,&gConfig_binImageToList[0].suppressionValue       , INT_32, SINGLE},
  {(char* )"randSeed"                 ,&gConfig_binImageToList[0].randSeed               , INT_32, SINGLE},
  {(char *)"testCaseName"             ,&gConfig_binImageToList[0].testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase"      ,&gConfig_binImageToList[0].performanceTestcase    , INT_8,  SINGLE},
  {(char *)"desc"                     ,&gConfig_binImageToList[0].desc                   , STRING, SINGLE},
} ;

