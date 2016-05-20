/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "imagePyramid_u8_config.h"
#pragma RESET_MISRA ("required")


simagePyramid_u8_Config gConfig_imagePyramid_u8[1];

sTokenMapping gsTokenMap_imagePyramid_u8[] =
{
        {(char* )"inImage",               &gConfig_imagePyramid_u8[0].inImage              , STRING, SINGLE},
        {(char* )"srcImageWidth",         &gConfig_imagePyramid_u8[0].srcImageWidth       , INT_32, SINGLE},
        {(char* )"srcImageHeight",        &gConfig_imagePyramid_u8[0].srcImageHeight      , INT_32, SINGLE},
        {(char* )"srcImagePitch",         &gConfig_imagePyramid_u8[0].srcImagePitch       , INT_32, SINGLE},

        {(char* )"outImage0",              &gConfig_imagePyramid_u8[0].outImage[0]           , STRING, SINGLE},
        {(char* )"dstImagePitch0",         &gConfig_imagePyramid_u8[0].dstImagePitch[0]      , INT_32, SINGLE},
        {(char* )"outImage1",              &gConfig_imagePyramid_u8[0].outImage[1]           , STRING, SINGLE},
        {(char* )"dstImagePitch1",         &gConfig_imagePyramid_u8[0].dstImagePitch[1]      , INT_32, SINGLE},
        {(char* )"outImage2",              &gConfig_imagePyramid_u8[0].outImage[2]           , STRING, SINGLE},
        {(char* )"dstImagePitch2",         &gConfig_imagePyramid_u8[0].dstImagePitch[2]      , INT_32, SINGLE},
        {(char* )"outImage3",              &gConfig_imagePyramid_u8[0].outImage[3]           , STRING, SINGLE},
        {(char* )"dstImagePitch3",         &gConfig_imagePyramid_u8[0].dstImagePitch[3]      , INT_32, SINGLE},
        {(char* )"outImage4",              &gConfig_imagePyramid_u8[0].outImage[4]           , STRING, SINGLE},
        {(char* )"dstImagePitch4",         &gConfig_imagePyramid_u8[0].dstImagePitch[4]      , INT_32, SINGLE},
        {(char* )"pattern",                &gConfig_imagePyramid_u8[0].pattern             , INT_8 , SINGLE},
        {(char* )"numLevels",              &gConfig_imagePyramid_u8[0].numLevels           , INT_8 , SINGLE},
        {(char* )"filterType",             &gConfig_imagePyramid_u8[0].filterType          , INT_8 , SINGLE},
        {(char* )"testCaseName",           &gConfig_imagePyramid_u8[0].testCaseName           , STRING, SINGLE},
        {(char* )"testCaseDesc",           &gConfig_imagePyramid_u8[0].testCaseDesc           , STRING, SINGLE},
        {(char* )"performanceTestcase",    &gConfig_imagePyramid_u8[0].performanceTestcase             , INT_8 , SINGLE},
} ;
