/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_VERTICAL_NMS_CONFIG_H_
#define _VCOP_VERTICAL_NMS_CONFIG_H_

#include "configparser.h"
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

typedef struct
{
  char           inFile1Name[MAX_FILE_NAME_SIZE];
  char           inFile2Name[MAX_FILE_NAME_SIZE];
  char           outFile1Name[MAX_FILE_NAME_SIZE];
  char           outFile2Name[MAX_FILE_NAME_SIZE];
  unsigned short num_corners;
  unsigned short max_corners;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} svertical_nms_Config;

extern svertical_nms_Config gConfig_vertical_nms;
extern sTokenMapping gsTokenMap_vertical_nms[MAX_ITEMS_TO_PARSE];

#endif
