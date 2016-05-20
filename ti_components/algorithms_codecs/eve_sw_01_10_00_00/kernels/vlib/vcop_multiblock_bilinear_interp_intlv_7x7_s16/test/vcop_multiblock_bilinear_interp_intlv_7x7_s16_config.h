/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_CONFIG_H_
#define _VCOP_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_CONFIG_H_

#include "configparser.h"
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

typedef struct
{
  char           inFileName1[MAX_FILE_NAME_SIZE];
  char           inFileName2[MAX_FILE_NAME_SIZE];
  char           outFileName1[MAX_FILE_NAME_SIZE];
  char           outFileName2[MAX_FILE_NAME_SIZE];
  unsigned short input1Stride;
  unsigned short input2Stride;
  unsigned short outputStride;
  unsigned short blkWidth;
  unsigned short blkHeight;
  unsigned short blkOffset;
  unsigned short numKeyPoints;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} smultiblock_bilinear_interp_intlv_7x7_s16_Config;

extern smultiblock_bilinear_interp_intlv_7x7_s16_Config gConfig_multiblock_bilinear_interp_intlv_7x7_s16;
extern sTokenMapping gsTokenMap_multiblock_bilinear_interp_intlv_7x7_s16[MAX_ITEMS_TO_PARSE];

#endif
