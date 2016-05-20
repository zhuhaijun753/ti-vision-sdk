/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_grayscale_morphology_config.h"

sGrayscale_Morphology_Config gConfig_grayscale_morphology;
sTokenMapping gsTokenMap_grayscale_morphology[] =
{
  {(char* )"testCaseName",           &gConfig_grayscale_morphology.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_grayscale_morphology.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImage",                &gConfig_grayscale_morphology.inImage                , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_grayscale_morphology.outImage               , STRING, SINGLE},
  {(char* )"morphologyMode",         &gConfig_grayscale_morphology.morphologyMode         ,  INT_8, SINGLE},
  {(char* )"structuringElementType", &gConfig_grayscale_morphology.structuringElementType ,  INT_8, SINGLE},
  {(char* )"seCoefficient",          &gConfig_grayscale_morphology.seCoefficient          ,  INT_8, MULTI },
  {(char* )"blkWidth",               &gConfig_grayscale_morphology.blkWidth               , INT_16, SINGLE},
  {(char* )"blkStride",              &gConfig_grayscale_morphology.blkStride              , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_grayscale_morphology.blkHeight              , INT_16, SINGLE},
  {(char* )"seWidth",                &gConfig_grayscale_morphology.seWidth                , INT_16, SINGLE},
  {(char* )"seHeight",               &gConfig_grayscale_morphology.seHeight               , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_grayscale_morphology.desc                   , STRING, SINGLE},
} ;

