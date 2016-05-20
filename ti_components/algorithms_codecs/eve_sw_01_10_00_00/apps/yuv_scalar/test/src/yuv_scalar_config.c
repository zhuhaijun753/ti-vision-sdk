/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "yuv_scalar_config.h"
#pragma RESET_MISRA ("required")


yuv_scalar_config gParams;

sTokenMapping gsTokenMap_yuv_scalar[MAX_ITEMS_TO_PARSE] =
{
        {(char* )"numFrames",          &gParams.numFrames                      , INT_32, SINGLE},
        {(char* )"imWidth",            &gParams.imWidth                        , INT_32, SINGLE},
        {(char* )"imHeight",           &gParams.imHeight                       , INT_32, SINGLE},
        {(char* )"outWidth" ,          &gParams.outWidth                       , INT_32, SINGLE},
        {(char* )"outHeight",          &gParams.outHeight                      , INT_32, SINGLE},
        {(char* )"scaleRatioQ12",      &gParams.scaleRatioQ12                  , INT_32, SINGLE},
        {(char* )"scalingMethod",      &gParams.scalingMethod                  , INT_8,  SINGLE},
        {(char* )"fracQFmt",           &gParams.fracQFmt                       , INT_8,  SINGLE},
        {(char* )"startFrame",         &gParams.startFrame                     , INT_32, SINGLE},
        {(char *)"inImage",            &gParams.inImage                        , STRING, SINGLE},
        {(char *)"outImage",           &gParams.outImage                       , STRING, SINGLE},
        {(char *)"refImage",           &gParams.refImage                       , STRING, SINGLE},
        {(char *)"testCaseName",       &gParams.testCaseName                   , STRING, SINGLE},
        {(char *)"testCaseDesc",       &gParams.testCaseDesc                   , STRING, SINGLE},
        {(char* )"performanceTestcase",&gParams.performanceTestcase            , INT_8,  SINGLE},
} ;





