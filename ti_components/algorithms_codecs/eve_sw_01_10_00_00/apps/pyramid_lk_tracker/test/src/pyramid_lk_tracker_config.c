/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "pyramid_lk_tracker_config.h"
#pragma RESET_MISRA ("required")

config_params gParams ;
sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] = 
{
  {(char* )"currFrameFile",             &(gParams.currFrameFile)         , STRING, SINGLE},                    
  {(char* )"prevFrameFile",             &(gParams.prevFrameFile)         , STRING, SINGLE},                    
  {(char* )"inKeyPointsFile",           &(gParams.inKeyPointsFile)       , STRING, SINGLE},                    
  {(char* )"outKeyPointsFile",          &(gParams.outKeyPointsFile)      , STRING, SINGLE},                    
  {(char* )"refKeyPointsFile",          &(gParams.refKeyPointsFile)      , STRING, SINGLE},                    
  {(char* )"numKeyPoints",              &gParams.numKeyPoints            , INT_32, SINGLE},                    
  {(char* )"numLevels",                 &gParams.numLevels               , INT_32, SINGLE},                    
  {(char* )"imWidth",                   &gParams.imWidth                 , INT_32, SINGLE},                    
  {(char* )"imHeight",                  &gParams.imHeight                , INT_32, SINGLE},                    
  {(char* )"maxItersLK",                &gParams.maxItersLK[0]           , INT_32, MULTI},
  {(char* )"minErrValue",               &gParams.minErrValue[0]          , INT_32, MULTI},
  {(char* )"searchRange",               &gParams.searchRange[0]          , INT_32, MULTI},
  {(char *)"testCaseName",              &gParams.testCaseName            , STRING, SINGLE},
  {(char *)"testCaseDesc",              &gParams.testCaseDesc            , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gParams.performanceTestcase     , INT_8,  SINGLE},
} ;


