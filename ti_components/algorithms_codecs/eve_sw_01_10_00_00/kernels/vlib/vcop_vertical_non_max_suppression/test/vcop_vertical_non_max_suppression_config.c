/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_vertical_non_max_suppression_config.h"

svertical_nms_Config gConfig_vertical_nms;
sTokenMapping gsTokenMap_vertical_nms[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_vertical_nms.inputSrc                 , STRING, SINGLE},
  {(char* )"inFile1Name",             &gConfig_vertical_nms.inFile1Name              , STRING, SINGLE},
  {(char* )"inFile2Name",             &gConfig_vertical_nms.inFile2Name              , STRING, SINGLE},
  {(char* )"outFile1Name",            &gConfig_vertical_nms.outFile1Name             , STRING, SINGLE},
  {(char* )"outFile2Name",            &gConfig_vertical_nms.outFile2Name             , STRING, SINGLE},
  {(char* )"num_corners",             &gConfig_vertical_nms.num_corners              , INT_16, SINGLE},
  {(char* )"max_corners",             &gConfig_vertical_nms.max_corners              , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_vertical_nms.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_vertical_nms.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_vertical_nms.seedForRND               , INT_32, SINGLE},
} ;
