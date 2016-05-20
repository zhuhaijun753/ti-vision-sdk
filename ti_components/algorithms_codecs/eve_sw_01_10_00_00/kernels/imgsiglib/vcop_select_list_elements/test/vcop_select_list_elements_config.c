/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_select_list_elements_config.h"

sSelect_list_elements_Config gConfig_select_list_elements;
sTokenMapping gsTokenMap_select_list_elements[] =
{
  {(char* )"inputList",              &gConfig_select_list_elements.inputList                , STRING, SINGLE},
  {(char* )"outputList",             &gConfig_select_list_elements.outputList               , STRING, SINGLE},
  {(char* )"listSize",               &gConfig_select_list_elements.listSize                 , INT_16, SINGLE},
  {(char* )"selectionMaskSize",      &gConfig_select_list_elements.selectionMaskSize        , INT_16, SINGLE},
  {(char* )"randSeed",               &gConfig_select_list_elements.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_select_list_elements.numIter                  , INT_8 , SINGLE},
  {(char *)"testCaseName",           &gConfig_select_list_elements.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_select_list_elements.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc",                   &gConfig_select_list_elements.desc                 , STRING, SINGLE}
} ;

