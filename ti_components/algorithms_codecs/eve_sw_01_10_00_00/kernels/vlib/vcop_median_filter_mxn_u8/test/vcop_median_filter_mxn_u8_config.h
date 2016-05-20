/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_MEDIAN_MxN_CONFIG_H_
#define _VCOP_MEDIAN_MxN_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       outImg[FILE_NAME_SIZE];
  uint16_t   blkWidth;
  uint16_t   blkHeight;
  uint16_t   blkPitch;
  uint8_t    kernelWidth;
  uint8_t    kernelHeight;
  uint16_t   stepSizeHorz;
  uint16_t   stepSizeVert;
  uint32_t   randSeed;
  uint8_t    numIter;
} sMedianFilter_mxn_u8_Config;

extern sMedianFilter_mxn_u8_Config gConfig_median_filter_mxn_u8;
extern sTokenMapping gsTokenMap_median_filter_mxn_u8[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_MEDIAN_MxN_CONFIG_H_ */

