/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "yuv_padding_config.h"
#pragma RESET_MISRA ("required")


yuv_padding_config gParams;

sTokenMapping gsTokenMap_yuv_padding[MAX_ITEMS_TO_PARSE] =
{
        {(char* )"numFrames",          &gParams.numFrames                      , INT_32, SINGLE},
        {(char* )"imWidth",            &gParams.imWidth                        , INT_32, SINGLE},
        {(char* )"imHeight",           &gParams.imHeight                       , INT_32, SINGLE},
        {(char* )"topPadding",         &gParams.topPadding                     , INT_32, SINGLE},
        {(char* )"leftPadding",        &gParams.leftPadding                    , INT_32, SINGLE},
        {(char* )"rightPadding",       &gParams.rightPadding                   , INT_32, SINGLE},
        {(char* )"BottomPadding",      &gParams.BottomPadding                  , INT_32, SINGLE},
        {(char *)"inImage",            &gParams.inImage                        , STRING, SINGLE},
        {(char *)"outImage",           &gParams.outImage                       , STRING, SINGLE},
        {(char *)"refImage",           &gParams.refImage                       , STRING, SINGLE},
        {(char *)"testCaseName",       &gParams.testCaseName                   , STRING, SINGLE},
        {(char *)"testCaseDesc",       &gParams.testCaseDesc                   , STRING, SINGLE},
        {(char* )"performanceTestcase",&gParams.performanceTestcase            , INT_8,  SINGLE},
} ;





