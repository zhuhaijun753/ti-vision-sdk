/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_CONFIG_H_
#define _VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_CONFIG_H_

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
  char           outFileName[MAX_FILE_NAME_SIZE];
  unsigned short inputStride;
  unsigned short outputStride;
  unsigned short numKeyPoints;
  unsigned char  numIter;
  int            writeOutput;
  int            seedForRND;
  char           inputSrc[MAX_PARAM_STRING_SIZE];
  char           configLine[MAX_CONFIG_LINE_SIZE];
  char           configParam[MAX_PARAM_STRING_SIZE];

} scalc_inverse_structure_tensor_2x2_Config;

extern scalc_inverse_structure_tensor_2x2_Config gConfig_calc_inverse_structure_tensor_2x2;
extern sTokenMapping gsTokenMap_calc_inverse_structure_tensor_2x2[MAX_ITEMS_TO_PARSE];

#endif
