/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_alpha_blend_yuv420nv12_config.h"

salpha_blend_yuv420nv12_Config gConfig_alpha_blend ;
sTokenMapping gsTokenMap_alpha_blend[] = 
{
  {(char* )"inImage1",               &gConfig_alpha_blend.inImage1                 , STRING, SINGLE},                    
  {(char* )"inImage2",               &gConfig_alpha_blend.inImage2                 , STRING, SINGLE},                    
  {(char* )"outImage",               &gConfig_alpha_blend.outImage                 , STRING, SINGLE},                    
  {(char* )"blockWidth",             &gConfig_alpha_blend.blockWidth               , INT_16, SINGLE},                    
  {(char* )"blockHeight",            &gConfig_alpha_blend.blockHeight              , INT_16, SINGLE},                    
  {(char* )"blockStride",            &gConfig_alpha_blend.blockStride              , INT_16, SINGLE},                    
  {(char* )"pattern",                &gConfig_alpha_blend.pattern                  , INT_8 , SINGLE},                    
  {(char* )"numIter",                &gConfig_alpha_blend.numIter                  , INT_8 , SINGLE}                   
} ;
