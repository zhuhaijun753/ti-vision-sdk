/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_CONFIG_H_
#define _VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_CONFIG_H_

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
  char           inFileName3[MAX_FILE_NAME_SIZE];
  char           outFileName1[MAX_FILE_NAME_SIZE];
  char           outFileName2[MAX_FILE_NAME_SIZE];
  unsigned short numKeyPoints;
  unsigned short qFormatMaxFactor;
  unsigned short qShift;
  unsigned short blkStride;
  unsigned short outputStride;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} sweight_address_bilinear_interpolation_Config;

extern sweight_address_bilinear_interpolation_Config gConfig_weight_address_bilinear_interpolation;
extern sTokenMapping gsTokenMap_weight_address_bilinear_interpolation[MAX_ITEMS_TO_PARSE];

#endif
