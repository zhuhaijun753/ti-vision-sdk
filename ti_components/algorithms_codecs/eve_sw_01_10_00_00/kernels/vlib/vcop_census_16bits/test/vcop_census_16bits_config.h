/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_CENSUS_16BITS_CONFIG_H_
#define _VCOP_CENSUS_16BITS_CONFIG_H_

#include "configparser.h"
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

typedef struct
{
  char           inFileName[MAX_FILE_NAME_SIZE];
  char           outFileName[MAX_FILE_NAME_SIZE];
  unsigned char  winWidth;
  unsigned char  winHeight;
  unsigned short computeWidth;
  unsigned short computeHeight;
  unsigned short inStride;
  unsigned short outStride;
  unsigned char  winHorzStep;
  unsigned char  winVertStep;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} scensus_16bits_Config;

extern scensus_16bits_Config gConfig_census_16bits;
extern sTokenMapping gsTokenMap_census_16bits[MAX_ITEMS_TO_PARSE];

#endif
