/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_GLCM_CONFIG_H_
#define _VCOP_GLCM_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define MAX_NUM_DIRECTIONS (4)

typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       outGLCM[FILE_NAME_SIZE];
  uint16_t   imageWidth;
  uint16_t   imageHeight;
  uint16_t   imagePitch;
  uint8_t    numLevels;
  uint8_t    numOffsets;
  char       rowOffsets[MAX_NUM_DIRECTIONS];
  char       colOffsets[MAX_NUM_DIRECTIONS];
  uint32_t   randSeed;
  uint8_t    numIter;
} sGlcm_Config;

extern sGlcm_Config gConfig_glcm;
extern sTokenMapping gsTokenMap_glcm[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_GLCM_CONFIG_H_ */
