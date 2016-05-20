/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "pyramid_lk_sof_config.h"
#pragma RESET_MISRA ("required")

#pragma DATA_SECTION (gsTokenMap_sof, ".fardata");
#pragma DATA_SECTION (gParams, ".fardata");

char * SOFKeyPointMethos[] =
{
  "SOF_EXTERNAL_KEY_POINTS",
  "SOF_HARRIS_KEY_POINTS  ",
  "SOF_FAST9_KEY_POINTS   ",
};

config_params gParams ;
sTokenMapping gsTokenMap_sof[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inVideoSeqFile",            &(gParams.inVideoSeqFile)        , STRING, SINGLE},
  {(char* )"outVideoSeqFile",           &(gParams.outVideoSeqFile)       , STRING, SINGLE},
  {(char* )"currFrameFile",             &(gParams.currFrameFile)         , STRING, SINGLE},
  {(char* )"prevFrameFile",             &(gParams.prevFrameFile)         , STRING, SINGLE},
  {(char* )"gtFileName",                &(gParams.gtFileName)            , STRING, SINGLE},
  {(char* )"outFileName",               &(gParams.outFileName)           , STRING, SINGLE},
  {(char* )"refFileName",               &(gParams.refFileName)           , STRING, SINGLE},
  {(char* )"statsFileName",             &(gParams.statsFileName)         , STRING, SINGLE},
  {(char* )"keyPointFile",              &(gParams.keyPointFile)          , STRING, SINGLE},
  {(char* )"maxNumKeyPoints",           &gParams.maxNumKeyPoints         , INT_32, SINGLE},
  {(char* )"maxPrevTrackPoints",        &gParams.maxPrevTrackPoints      , INT_32, SINGLE},
  {(char* )"numLevels",                 &gParams.numLevels               , INT_32, SINGLE},
  {(char* )"numLevelsPerCall",          &gParams.numLevelsPerCall        , INT_32, SINGLE},
  {(char* )"imWidth",                   &gParams.imWidth                 , INT_32, SINGLE},
  {(char* )"imHeight",                  &gParams.imHeight                , INT_32, SINGLE},
  {(char* )"roiWidth",                  &gParams.roiWidth                , INT_32, SINGLE},
  {(char* )"roiHeight",                 &gParams.roiHeight               , INT_32, SINGLE},
  {(char* )"startX",                    &gParams.startX                  , INT_32, SINGLE},
  {(char* )"startY",                    &gParams.startY                  , INT_32, SINGLE},
  {(char* )"harrisScaling",             &gParams.harrisScaling           , INT_32, SINGLE},
  {(char* )"nmsThreshold",              &gParams.nmsThreshold            , INT_32, SINGLE},
  {(char* )"harrisWindowSize",          &gParams.harrisWindowSize     , INT_8 , SINGLE},
  {(char* )"harrisScoreMethod",         &gParams.harrisScoreMethod    , INT_8 , SINGLE},
  {(char* )"suppressionMethod",         &gParams.suppressionMethod    , INT_8 , SINGLE},
  {(char* )"keyPointDetectMethod",      &gParams.keyPointDetectMethod    , INT_8,  SINGLE},
  {(char* )"fast9Threshold",            &gParams.fast9Threshold          , INT_32, SINGLE},
  {(char* )"trackErrThr",               &gParams.trackErrThr             , INT_32, SINGLE},
  {(char* )"trackMinFlowQ4",            &gParams.trackMinFlowQ4          , INT_32, SINGLE},
  {(char* )"trackNmsWinSize",           &gParams.trackNmsWinSize         , INT_32, SINGLE},
  {(char* )"keyPointDetectInterval",    &gParams.keyPointDetectInterval  , INT_32, SINGLE},
  {(char* )"inPutType",                 &gParams.inPutType               , INT_32, SINGLE},
  {(char* )"startFrame",                &gParams.startFrame              , INT_32, SINGLE},
  {(char* )"numFrames",                 &gParams.numFrames               , INT_32, SINGLE},
  {(char* )"maxItersLK",                &gParams.maxItersLK[0]           , INT_32, MULTI},
  {(char* )"minErrValue",               &gParams.minErrValue[0]          , INT_32, MULTI},
  {(char* )"searchRange",               &gParams.searchRange[0]          , INT_32, MULTI},
  {(char *)"testCaseName",              &gParams.testCaseName            , STRING, SINGLE},
  {(char *)"testCaseDesc",              &gParams.testCaseDesc            , STRING, SINGLE},
  {(char* )"performanceTestcase",       &gParams.performanceTestcase     , INT_8,  SINGLE},
} ;

void printConfigParams(config_params *params)
{
  int i;
  printf("currFrameFile          %s\n",params->currFrameFile );
  printf("prevFrameFile          %s\n",params->prevFrameFile );
  printf("gtFileName             %s\n",params->gtFileName    );
  printf("outFileName            %s\n",params->outFileName   );
  printf("statsFileName          %s\n",params->statsFileName );
  printf("keyPointFile           %s\n",params->keyPointFile );
  printf("maxNumKeyPoints        %d\n",params->maxNumKeyPoints );
  printf("maxPrevTrackPoints     %d\n",params->maxPrevTrackPoints);
  printf("numLevels              %d\n",params->numLevels    );
  printf("imWidth                %d\n",params->imWidth      );
  printf("imHeight               %d\n",params->imHeight     );
  printf("roiWidth               %d\n",params->roiWidth     );
  printf("roiHeight              %d\n",params->roiHeight    );
  printf("startX                 %d\n",params->startX       );
  printf("startY                 %d\n",params->startY       );
  printf("harrisScaling          %d\n",params->harrisScaling);
  printf("nmsThreshold           %d\n",params->nmsThreshold );
  printf("keyPointDetectMethod   %s\n",SOFKeyPointMethos[params->keyPointDetectMethod] );
  for(i = 0; i < params->numLevels; i++)
  {
    printf("minErrValue  %d  :         %d\n",i,params->minErrValue[i]  );
    printf("maxItersLK   %d  :         %d\n",i,params->maxItersLK[i]   );
    printf("searchRange  %d  :         %d\n",i,params->searchRange[i]   );
  }
}
