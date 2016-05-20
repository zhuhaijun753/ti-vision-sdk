/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_disparity_sad8_row_config.h"

sdisparity_sad8_row_Config gConfig_disparity_sad8_row;
sTokenMapping gsTokenMap_disparity_sad8_row[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_disparity_sad8_row.inputSrc                 , STRING, SINGLE},
  {(char* )"inLeftFileName",          &gConfig_disparity_sad8_row.inLeftFileName           , STRING, SINGLE},
  {(char* )"inRightFileName",         &gConfig_disparity_sad8_row.inRightFileName          , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_disparity_sad8_row.outFileName              , STRING, SINGLE},
  {(char* )"winWidth",                &gConfig_disparity_sad8_row.winWidth                 , INT_8, SINGLE},
  {(char* )"winHeight",               &gConfig_disparity_sad8_row.winHeight                , INT_8, SINGLE},
  {(char* )"width",                   &gConfig_disparity_sad8_row.width                    , INT_16, SINGLE},
  {(char* )"numRows",                 &gConfig_disparity_sad8_row.numRows                  , INT_16, SINGLE},
  {(char* )"numDisparities",          &gConfig_disparity_sad8_row.numDisparities           , INT_16, SINGLE},
  {(char* )"disparityStep",           &gConfig_disparity_sad8_row.disparityStep            , INT_8, SINGLE},
  {(char* )"leftStride",              &gConfig_disparity_sad8_row.leftStride               , INT_16, SINGLE},
  {(char* )"rightStride",             &gConfig_disparity_sad8_row.rightStride              , INT_16, SINGLE},
  {(char* )"numRowSegments",          &gConfig_disparity_sad8_row.numRowSegments           , INT_8, SINGLE},
  {(char* )"numIter",                 &gConfig_disparity_sad8_row.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_disparity_sad8_row.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_disparity_sad8_row.seedForRND               , INT_32, SINGLE},
} ;
