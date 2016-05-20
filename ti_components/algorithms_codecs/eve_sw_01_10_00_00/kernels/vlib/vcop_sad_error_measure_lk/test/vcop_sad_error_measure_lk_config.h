/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_SAD_ERROR_MEASURE_LK_CONFIG_H_
#define _VCOP_SAD_ERROR_MEASURE_LK_CONFIG_H_

#include "configparser.h"
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE     (20)

typedef struct
{
  char           inFileName1[MAX_FILE_NAME_SIZE]   ;
  char           inFileName2[MAX_FILE_NAME_SIZE]   ;
  char           inFileName3[MAX_FILE_NAME_SIZE]   ;
  char           outFileName[MAX_FILE_NAME_SIZE]   ;
  unsigned short inputStride                       ;
  unsigned short frmWidth                          ;
  unsigned short frmHeight                         ;
  unsigned short blkWidth                          ;
  unsigned short blkHeight                         ;
  unsigned short numKeyPoints                      ;
  unsigned short shiftValue                        ;
  unsigned char  numIter                           ;
  int            writeOutput                       ;
  int            seedForRND                        ;
  char           inputSrc[MAX_PARAM_STRING_SIZE]   ;
  char           configLine[MAX_CONFIG_LINE_SIZE]  ;
  char           configParam[MAX_PARAM_STRING_SIZE];
} ssad_error_measure_lk_Config;

extern ssad_error_measure_lk_Config gConfig_sad_error_measure_lk;
extern sTokenMapping gsTokenMap_sad_error_measure_lk[MAX_ITEMS_TO_PARSE];

#endif
