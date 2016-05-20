/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_DISPARITY_NXM_16_CONFIG_H_
#define _VCOP_DISPARITY_NXM_16_CONFIG_H_

#include "configparser.h"
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

typedef struct
{
  char           inLeftFileName[MAX_FILE_NAME_SIZE];
  char           inRightFileName[MAX_FILE_NAME_SIZE];
  char           outFileName[MAX_FILE_NAME_SIZE];
  unsigned char  winWidth;
  unsigned char  winHeight;
  unsigned short width;
  unsigned short numRows;
  unsigned short numDisparities;
  unsigned char  disparityStep;
  unsigned short leftStride;
  unsigned short rightStride;
  unsigned char  numRowSegments;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} sdisparity_sad16_row_Config;

extern sdisparity_sad16_row_Config gConfig_disparity_sad16_row;
extern sTokenMapping gsTokenMap_disparity_sad16_row[MAX_ITEMS_TO_PARSE];

#endif
