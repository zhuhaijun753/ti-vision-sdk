/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#pragma RESET_MISRA ("required")

#include "morphology_config.h"

sMorphology_Config gConfig_morphology;
sTokenMapping gsTokenMap_morphology[] =
{
  {(char* )"testCaseName",           &gConfig_morphology.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_morphology.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImage",                &gConfig_morphology.inImage                , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_morphology.outImage               , STRING, SINGLE},
  {(char* )"inImageType",            &gConfig_morphology.inImageType            ,  INT_8, SINGLE},
  {(char* )"morphologyMode",         &gConfig_morphology.morphologyMode         ,  INT_8, SINGLE},
  {(char* )"seShape",                &gConfig_morphology.seShape                ,  INT_8, SINGLE},
  {(char* )"seCoefficient",          &gConfig_morphology.seCoefficient          ,  INT_8, MULTI },
  {(char* )"srcWidth",               &gConfig_morphology.srcWidth               , INT_16, SINGLE},
  {(char* )"srcPitch",               &gConfig_morphology.srcPitch               , INT_16, SINGLE},
  {(char* )"srcHeight",              &gConfig_morphology.srcHeight              , INT_16, SINGLE},
  {(char* )"seWidth",                &gConfig_morphology.seWidth                , INT_16, SINGLE},
  {(char* )"seHeight",               &gConfig_morphology.seHeight               , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_morphology.desc                   , STRING, SINGLE},
} ;

