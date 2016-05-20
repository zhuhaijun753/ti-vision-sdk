/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_extract_bit_field_u32_config.h"

sextract_bit_field_u32_Config gConfig_extract_bit_field_u32;
sTokenMapping gsTokenMap_extract_bit_field_u32[] =
{
  {(char* )"inList",                 &gConfig_extract_bit_field_u32.inList                   , STRING, SINGLE},
  {(char* )"outList",                &gConfig_extract_bit_field_u32.outList                  , STRING, SINGLE},
  {(char* )"listLength",             &gConfig_extract_bit_field_u32.listLength               , INT_16, SINGLE},
  {(char* )"bitMask",                &gConfig_extract_bit_field_u32.bitMask                  , INT_32, SINGLE},
  {(char* )"shift",                  &gConfig_extract_bit_field_u32.shift                    , INT_8 , SINGLE},
  {(char* )"randSeed",               &gConfig_extract_bit_field_u32.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_extract_bit_field_u32.numIter                  , INT_8 , SINGLE}
} ;
