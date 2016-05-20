/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_FAST9_CONFIG_H_
#define _VCOP_FAST9_CONFIG_H_

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
  unsigned short pitch;
  unsigned short blkHeight;
  unsigned short comp_width;
  unsigned short comp_height;
  unsigned char  Thr;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} sfast9_Config;

extern sfast9_Config gConfig_fast9;
extern sTokenMapping gsTokenMap_fast9[MAX_ITEMS_TO_PARSE];

#endif
