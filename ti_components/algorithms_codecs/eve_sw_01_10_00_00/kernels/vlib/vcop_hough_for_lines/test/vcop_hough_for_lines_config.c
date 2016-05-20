/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_hough_for_lines_config.h"

sHough_for_lines_Config gConfig_hough_for_lines;
sTokenMapping gsTokenMap_hough_for_lines[] =
{
  {(char* )"edgeMapList",        &gConfig_hough_for_lines.edgeMapList    , STRING, SINGLE},
  {(char* )"outputVotedRhoTheta",  &gConfig_hough_for_lines.outputVotedRhoTheta, STRING, SINGLE},
  {(char* )"width",             &gConfig_hough_for_lines.width           , INT_16, SINGLE},
  {(char* )"height",            &gConfig_hough_for_lines.height          , INT_16, SINGLE},
  {(char* )"listSize",          &gConfig_hough_for_lines.listSize        , INT_16, SINGLE},
  {(char* )"thetaStart",        &gConfig_hough_for_lines.thetaStart      , INT_16, SINGLE},
  {(char* )"thetaEnd",          &gConfig_hough_for_lines.thetaEnd        , INT_16, SINGLE},
  {(char* )"thetaStepSize",     &gConfig_hough_for_lines.thetaStepSize   , INT_8, SINGLE},
  {(char* )"rhoMaxLength",      &gConfig_hough_for_lines.rhoMaxLength    , INT_16, SINGLE},
  {(char* )"randSeed",          &gConfig_hough_for_lines.randSeed        , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_hough_for_lines.numIter         , INT_8 , SINGLE},
} ;

