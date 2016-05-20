/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_horizontal_non_max_suppression_config.h"

shorizontal_nms_Config gConfig_horizontal_nms;
sTokenMapping gsTokenMap_horizontal_nms[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_horizontal_nms.inputSrc                 , STRING, SINGLE},
  {(char* )"inFile1Name",             &gConfig_horizontal_nms.inFile1Name              , STRING, SINGLE},
  {(char* )"inFile2Name",             &gConfig_horizontal_nms.inFile2Name              , STRING, SINGLE},
  {(char* )"outFile1Name",            &gConfig_horizontal_nms.outFile1Name             , STRING, SINGLE},
  {(char* )"outFile2Name",            &gConfig_horizontal_nms.outFile2Name             , STRING, SINGLE},
  {(char* )"num_corners",             &gConfig_horizontal_nms.num_corners              , INT_16, SINGLE},
  {(char* )"max_corners",             &gConfig_horizontal_nms.max_corners              , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_horizontal_nms.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_horizontal_nms.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_horizontal_nms.seedForRND               , INT_32, SINGLE},
} ;
