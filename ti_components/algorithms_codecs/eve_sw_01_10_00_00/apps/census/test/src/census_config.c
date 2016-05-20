/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "census_config.h"
#pragma RESET_MISRA ("required")

uint32_t census_numTestCases;

scensus_Config gConfig_census[EVELIB_CENSUS_NUM_TESTCASES];

sTokenMapping gsTokenMap_census[] =
{
        {(char* )"numTestCases",           &census_numTestCases                   , INT_32, SINGLE},

        {(char* )"inImage",               &gConfig_census[0].inImage             , STRING, SINGLE},
        {(char* )"srcImageWidth",         &gConfig_census[0].srcImageWidth       , INT_32, SINGLE},
        {(char* )"srcImageHeight",        &gConfig_census[0].srcImageHeight      , INT_32, SINGLE},
        {(char* )"srcImagePitch",         &gConfig_census[0].srcImagePitch       , INT_32, SINGLE},

        {(char* )"outImage",              &gConfig_census[0].outImage            , STRING, SINGLE},
        {(char* )"dstImagePitch",         &gConfig_census[0].dstImagePitch       , INT_32, SINGLE},
        {(char* )"pattern",               &gConfig_census[0].pattern             , INT_8 , SINGLE},
        {(char* )"inputBitDepth",         &gConfig_census[0].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"winWidth",              &gConfig_census[0].winWidth            , INT_8 , SINGLE},
        {(char* )"winHeight",             &gConfig_census[0].winHeight           , INT_8 , SINGLE},
        {(char* )"winHorzStep",           &gConfig_census[0].winHorzStep         , INT_8 , SINGLE},
        {(char* )"winVertStep",           &gConfig_census[0].winVertStep         , INT_8 , SINGLE},

        {(char* )"0inImage",               &gConfig_census[0].inImage             , STRING, SINGLE},
        {(char* )"0srcImageWidth",         &gConfig_census[0].srcImageWidth       , INT_32, SINGLE},
        {(char* )"0srcImageHeight",        &gConfig_census[0].srcImageHeight      , INT_32, SINGLE},
        {(char* )"0srcImagePitch",         &gConfig_census[0].srcImagePitch       , INT_32, SINGLE},

        {(char* )"0outImage",              &gConfig_census[0].outImage         	  , STRING, SINGLE},
        {(char* )"0dstImagePitch",         &gConfig_census[0].dstImagePitch       , INT_32, SINGLE},
        {(char* )"0pattern",               &gConfig_census[0].pattern             , INT_8 , SINGLE},
        {(char* )"0inputBitDepth",         &gConfig_census[0].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"0winWidth",              &gConfig_census[0].winWidth            , INT_8 , SINGLE},
        {(char* )"0winHeight",             &gConfig_census[0].winHeight           , INT_8 , SINGLE},
        {(char* )"0winHorzStep",           &gConfig_census[0].winHorzStep         , INT_8 , SINGLE},
        {(char* )"0winVertStep",           &gConfig_census[0].winVertStep         , INT_8 , SINGLE},

        {(char* )"1inImage",               &gConfig_census[1].inImage             , STRING, SINGLE},
        {(char* )"1srcImageWidth",         &gConfig_census[1].srcImageWidth       , INT_32, SINGLE},
        {(char* )"1srcImageHeight",        &gConfig_census[1].srcImageHeight      , INT_32, SINGLE},
        {(char* )"1srcImagePitch",         &gConfig_census[1].srcImagePitch       , INT_32, SINGLE},

        {(char* )"1outImage",              &gConfig_census[1].outImage            , STRING, SINGLE},
        {(char* )"1dstImagePitch",         &gConfig_census[1].dstImagePitch       , INT_32, SINGLE},
        {(char* )"1pattern",               &gConfig_census[1].pattern             , INT_8 , SINGLE},
        {(char* )"1inputBitDepth",         &gConfig_census[1].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"1winWidth",              &gConfig_census[1].winWidth            , INT_8 , SINGLE},
        {(char* )"1winHeight",             &gConfig_census[1].winHeight           , INT_8 , SINGLE},
        {(char* )"1winHorzStep",           &gConfig_census[1].winHorzStep         , INT_8 , SINGLE},
        {(char* )"1winVertStep",           &gConfig_census[1].winVertStep         , INT_8 , SINGLE},

        {(char* )"2inImage",               &gConfig_census[2].inImage             , STRING, SINGLE},
        {(char* )"2srcImageWidth",         &gConfig_census[2].srcImageWidth       , INT_32, SINGLE},
        {(char* )"2srcImageHeight",        &gConfig_census[2].srcImageHeight      , INT_32, SINGLE},
        {(char* )"2srcImagePitch",         &gConfig_census[2].srcImagePitch       , INT_32, SINGLE},

        {(char* )"2outImage",              &gConfig_census[2].outImage            , STRING, SINGLE},
        {(char* )"2dstImagePitch",         &gConfig_census[2].dstImagePitch       , INT_32, SINGLE},
        {(char* )"2pattern",               &gConfig_census[2].pattern             , INT_8 , SINGLE},
        {(char* )"2inputBitDepth",         &gConfig_census[2].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"2winWidth",              &gConfig_census[2].winWidth            , INT_8 , SINGLE},
        {(char* )"2winHeight",             &gConfig_census[2].winHeight           , INT_8 , SINGLE},
        {(char* )"2winHorzStep",           &gConfig_census[2].winHorzStep         , INT_8 , SINGLE},
        {(char* )"2winVertStep",           &gConfig_census[2].winVertStep         , INT_8 , SINGLE},

        {(char* )"3inImage",               &gConfig_census[3].inImage             , STRING, SINGLE},
        {(char* )"3srcImageWidth",         &gConfig_census[3].srcImageWidth       , INT_32, SINGLE},
        {(char* )"3srcImageHeight",        &gConfig_census[3].srcImageHeight      , INT_32, SINGLE},
        {(char* )"3srcImagePitch",         &gConfig_census[3].srcImagePitch       , INT_32, SINGLE},

        {(char* )"3outImage",              &gConfig_census[3].outImage            , STRING, SINGLE},
        {(char* )"3dstImagePitch",         &gConfig_census[3].dstImagePitch       , INT_32, SINGLE},
        {(char* )"3pattern",               &gConfig_census[3].pattern             , INT_8 , SINGLE},
        {(char* )"3inputBitDepth",         &gConfig_census[3].inputBitDepth       , INT_8 , SINGLE},
        {(char* )"3winWidth",              &gConfig_census[3].winWidth            , INT_8 , SINGLE},
        {(char* )"3winHeight",             &gConfig_census[3].winHeight           , INT_8 , SINGLE},
        {(char* )"3winHorzStep",           &gConfig_census[3].winHorzStep         , INT_8 , SINGLE},
        {(char* )"3winVertStep",           &gConfig_census[3].winVertStep         , INT_8 , SINGLE},

} ;
