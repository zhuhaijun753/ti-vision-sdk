/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "glcm_config.h"
#pragma RESET_MISRA ("required")

sGlcm_Config gConfig_glcm;

sTokenMapping gsTokenMap_glcm[] =
{
        {(char  * )"inImage",                &gConfig_glcm.inImage               , STRING, SINGLE},
        {(char  * )"srcImageWidth",          &gConfig_glcm.srcImageWidth         , INT_16, SINGLE},
        {(char  * )"srcImageHeight",         &gConfig_glcm.srcImageHeight        , INT_16, SINGLE},
        {(char  * )"srcImagePitch",          &gConfig_glcm.srcImagePitch         , INT_16, SINGLE},

        {(char  * )"outGlcm",                &gConfig_glcm.outGlcm               , STRING, SINGLE},

        {(char  * )"loPixelVal",             &gConfig_glcm.loPixelVal            , INT_8 , SINGLE},
        {(char  * )"hiPixelVal",             &gConfig_glcm.hiPixelVal            , INT_8 , SINGLE},
        {(char  * )"numLevels",              &gConfig_glcm.numLevels             , INT_8 , SINGLE},

        {(char  * )"numDirections",          &gConfig_glcm.numDirections         , INT_8 , SINGLE},
        {(char  * )"rowOffset0",             &gConfig_glcm.rowOffset[0]         , INT_8 , SINGLE},
        {(char  * )"colOffset0",             &gConfig_glcm.colOffset[0]         , INT_8 , SINGLE},
        {(char  * )"rowOffset1",             &gConfig_glcm.rowOffset[1]         , INT_8 , SINGLE},
        {(char  * )"colOffset1",             &gConfig_glcm.colOffset[1]         , INT_8 , SINGLE},
        {(char  * )"rowOffset2",             &gConfig_glcm.rowOffset[2]         , INT_8 , SINGLE},
        {(char  * )"colOffset2",             &gConfig_glcm.colOffset[2]         , INT_8 , SINGLE},
        {(char  * )"rowOffset3",             &gConfig_glcm.rowOffset[3]         , INT_8 , SINGLE},
        {(char  * )"colOffset3",             &gConfig_glcm.colOffset[3]         , INT_8 , SINGLE},
        {(char  * )"rowOffset4",             &gConfig_glcm.rowOffset[4]         , INT_8 , SINGLE},
        {(char  * )"colOffset4",             &gConfig_glcm.colOffset[4]         , INT_8 , SINGLE},
        {(char  * )"rowOffset5",             &gConfig_glcm.rowOffset[5]         , INT_8 , SINGLE},
        {(char  * )"colOffset5",             &gConfig_glcm.colOffset[5]         , INT_8 , SINGLE},
        {(char  * )"rowOffset6",             &gConfig_glcm.rowOffset[6]         , INT_8 , SINGLE},
        {(char  * )"colOffset6",             &gConfig_glcm.colOffset[6]         , INT_8 , SINGLE},
        {(char  * )"rowOffset7",             &gConfig_glcm.rowOffset[7]         , INT_8 , SINGLE},
        {(char  * )"colOffset7",             &gConfig_glcm.colOffset[7]         , INT_8 , SINGLE},

        {(char  * )"randSeed",               &gConfig_glcm.randSeed             , INT_32, SINGLE},
        {(char  * )"testCaseName",           &gConfig_glcm.testCaseName         , STRING, SINGLE},
        {(char  * )"performanceTestcase",    &gConfig_glcm.performanceTestcase  ,  INT_8, SINGLE},
        {(char  * )"desc",                   &gConfig_glcm.testCaseDesc         , STRING, SINGLE},
} ;

