/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_ALPHA_BLEND_YUV420NV12_CONFIG_H_
#define _VCOP_ALPHA_BLEND_YUV420NV12_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
typedef struct
{
  unsigned char inImage1[FILE_NAME_SIZE];
  unsigned char inImage2[FILE_NAME_SIZE];
  unsigned char outImage[FILE_NAME_SIZE];
  unsigned short blockWidth  ;
  unsigned short blockHeight ;
  unsigned short blockStride ;
  unsigned char  pattern     ; 
  unsigned char  numIter     ; 
} salpha_blend_yuv420nv12_Config;

extern salpha_blend_yuv420nv12_Config gConfig_alpha_blend;
extern sTokenMapping gsTokenMap_alpha_blend[MAX_ITEMS_TO_PARSE];

#endif
