/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "evelib_harrisCornerDetection32_config.h"
#pragma RESET_MISRA ("required")

sharrisCornerDetection32_Config gConfig_harrisCornerDetection32[1];
sTokenMapping gsTokenMap_harrisCornerDetection32[] =
{
        {(char* )"inImage",               &gConfig_harrisCornerDetection32[0].inImage              , STRING, SINGLE},
        {(char* )"srcImageWidth",          &gConfig_harrisCornerDetection32[0].srcImageWidth       , INT_32, SINGLE},
        {(char* )"srcImageHeight",         &gConfig_harrisCornerDetection32[0].srcImageHeight      , INT_32, SINGLE},
        {(char* )"srcImagePitch",         &gConfig_harrisCornerDetection32[0].srcImagePitch       , INT_32, SINGLE},

        {(char* )"outImage",              &gConfig_harrisCornerDetection32[0].outImage           , STRING, SINGLE},
        {(char* )"dstImagePitch",         &gConfig_harrisCornerDetection32[0].dstImagePitch      , INT_32, SINGLE},
        {(char* )"scaling",                &gConfig_harrisCornerDetection32[0].harrisScaling           , INT_16, SINGLE},
        {(char* )"thresh",                 &gConfig_harrisCornerDetection32[0].nmsThresh           , INT_32, SINGLE},
        {(char* )"qshift",                 &gConfig_harrisCornerDetection32[0].qShift           , INT_8, SINGLE},
        {(char* )"outputFormat",           &gConfig_harrisCornerDetection32[0].outputFormat             , INT_8 , SINGLE},
        {(char* )"harrisWindowSize",       &gConfig_harrisCornerDetection32[0].harrisWindowSize             , INT_8 , SINGLE},
        {(char* )"harrisScoreMethod",      &gConfig_harrisCornerDetection32[0].harrisScoreMethod             , INT_8 , SINGLE},
        {(char* )"suppressionMethod",      &gConfig_harrisCornerDetection32[0].suppressionMethod             , INT_8 , SINGLE},
        {(char* )"pattern",                &gConfig_harrisCornerDetection32[0].pattern             , INT_8 , SINGLE},
        {(char* )"testCaseName",           &gConfig_harrisCornerDetection32[0].testCaseName           , STRING, SINGLE},
        {(char* )"testCaseDesc",           &gConfig_harrisCornerDetection32[0].testCaseDesc           , STRING, SINGLE},
        {(char* )"performanceTestcase",    &gConfig_harrisCornerDetection32[0].performanceTestcase             , INT_8 , SINGLE},
} ;
