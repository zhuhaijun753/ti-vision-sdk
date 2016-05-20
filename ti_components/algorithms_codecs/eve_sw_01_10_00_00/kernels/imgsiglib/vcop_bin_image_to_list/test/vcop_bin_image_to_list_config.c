/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_bin_image_to_list_config.h"

sbin_image_to_list_Config gConfig_bin_image_to_list;
sTokenMapping gsTokenMap_bin_image_to_list[] =
{
  {(char* )"inImage",                &gConfig_bin_image_to_list.inImage                  , STRING, SINGLE},
  {(char* )"outListXY",              &gConfig_bin_image_to_list.outListXY                , STRING, SINGLE},
  {(char* )"blockWidth",             &gConfig_bin_image_to_list.blockWidth               , INT_16, SINGLE},
  {(char* )"blockHeight",            &gConfig_bin_image_to_list.blockHeight              , INT_16, SINGLE},
  {(char* )"blockStride",            &gConfig_bin_image_to_list.blockStride              , INT_16, SINGLE},
  {(char* )"upperLeftXY",            &gConfig_bin_image_to_list.upperLeftXY              , INT_32, SINGLE},
  {(char* )"outputQformat",          &gConfig_bin_image_to_list.outputQformat            , INT_8 , SINGLE},
  {(char* )"xyOrder",                &gConfig_bin_image_to_list.xyOrder                  , INT_8 , SINGLE},
  {(char* )"pattern",                &gConfig_bin_image_to_list.pattern                  , INT_8 , SINGLE},
  {(char* )"randSeed",               &gConfig_bin_image_to_list.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_bin_image_to_list.numIter                  , INT_8 , SINGLE}
} ;
