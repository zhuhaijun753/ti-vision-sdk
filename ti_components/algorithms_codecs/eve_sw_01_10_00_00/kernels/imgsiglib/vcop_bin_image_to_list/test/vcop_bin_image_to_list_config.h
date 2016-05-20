/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_BIN_IMAGE_TO_LIST_CONFIG_H_
#define _VCOP_BIN_IMAGE_TO_LIST_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
typedef struct
{
  uint8_t  inImage[FILE_NAME_SIZE];
  uint8_t  outListXY[FILE_NAME_SIZE];
  uint16_t blockWidth;
  uint16_t blockHeight;
  uint16_t blockStride;
  uint32_t upperLeftXY;
  uint8_t  outputQformat;
  uint8_t  xyOrder;
  uint8_t  pattern;
  uint32_t randSeed;
  uint8_t  numIter;
} sbin_image_to_list_Config;

extern sbin_image_to_list_Config gConfig_bin_image_to_list;
extern sTokenMapping gsTokenMap_bin_image_to_list[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_BIN_IMAGE_TO_LIST_CONFIG_H_ */
