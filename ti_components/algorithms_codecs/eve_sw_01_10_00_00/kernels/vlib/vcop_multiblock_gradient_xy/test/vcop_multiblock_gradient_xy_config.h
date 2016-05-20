/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_MULTIBLOCK_GRADIENT_XY_CONFIG_H_
#define _VCOP_MULTIBLOCK_GRADIENT_XY_CONFIG_H_

#include "configparser.h"
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE     (20)

typedef struct
{
  char           inFileName[MAX_FILE_NAME_SIZE];
  char           outFileName[MAX_FILE_NAME_SIZE];
  unsigned short inputStride;
  unsigned short blkWidth;
  unsigned short blkHeight;
  unsigned short blkOffset;
  unsigned short numBlocks;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} smultiblock_gradient_xy_Config;

extern smultiblock_gradient_xy_Config gConfig_multiblock_gradient;
extern sTokenMapping gsTokenMap_multiblock_gradient[MAX_ITEMS_TO_PARSE];

#endif
