/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_disparity_hammingDistance_row_config.h"

sdisparity_hammingDistance_row_Config gConfig_disparity_hammingDistance_row;
sTokenMapping gsTokenMap_disparity_hammingDistance_row[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_disparity_hammingDistance_row.inputSrc                 , STRING, SINGLE},
  {(char* )"inLeftFileName",          &gConfig_disparity_hammingDistance_row.inLeftFileName           , STRING, SINGLE},
  {(char* )"inRightFileName",         &gConfig_disparity_hammingDistance_row.inRightFileName          , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_disparity_hammingDistance_row.outFileName              , STRING, SINGLE},
  {(char* )"winWidth",                &gConfig_disparity_hammingDistance_row.winWidth                 , INT_8, SINGLE},
  {(char* )"winHeight",               &gConfig_disparity_hammingDistance_row.winHeight                , INT_8, SINGLE},
  {(char* )"width",                   &gConfig_disparity_hammingDistance_row.width                    , INT_16, SINGLE},
  {(char* )"numRows",                 &gConfig_disparity_hammingDistance_row.numRows                  , INT_16, SINGLE},
  {(char* )"numDisparities",          &gConfig_disparity_hammingDistance_row.numDisparities           , INT_16, SINGLE},
  {(char* )"disparityStep",           &gConfig_disparity_hammingDistance_row.disparityStep            , INT_8, SINGLE},
  {(char* )"leftStride",              &gConfig_disparity_hammingDistance_row.leftStride               , INT_16, SINGLE},
  {(char* )"rightStride",             &gConfig_disparity_hammingDistance_row.rightStride              , INT_16, SINGLE},
  {(char* )"offset",                  &gConfig_disparity_hammingDistance_row.offset                   , INT_16, SINGLE},
  {(char* )"rightLeftDisp",           &gConfig_disparity_hammingDistance_row.rightLeftDisp            , INT_8, SINGLE},
  {(char* )"interpOutput",            &gConfig_disparity_hammingDistance_row.interpOutput             , INT_8, SINGLE},
  {(char* )"codeWordLen",             &gConfig_disparity_hammingDistance_row.codeWordLen              , INT_8, SINGLE},
  {(char* )"numRowSegments",          &gConfig_disparity_hammingDistance_row.numRowSegments           , INT_8, SINGLE},
  {(char* )"numIter",                 &gConfig_disparity_hammingDistance_row.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_disparity_hammingDistance_row.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_disparity_hammingDistance_row.seedForRND               , INT_32, SINGLE},
} ;
