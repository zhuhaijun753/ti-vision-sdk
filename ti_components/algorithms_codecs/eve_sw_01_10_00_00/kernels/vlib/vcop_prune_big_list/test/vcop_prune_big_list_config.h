/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_PRUNE_BIG_LIST_CONFIG_H_
#define _VCOP_PRUNE_BIG_LIST_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
typedef struct
{
  uint8_t   inList[FILE_NAME_SIZE];
  uint8_t   inIdx[FILE_NAME_SIZE];
  uint8_t   outList[FILE_NAME_SIZE];
  uint16_t  listLength;
  uint16_t  threshold;
  uint16_t  bestN;
  uint8_t   pattern;
  uint32_t  randSeed;
  uint8_t   numIter;
} sprune_big_list_Config;

extern sprune_big_list_Config gConfig_prune_big_list;
extern sTokenMapping gsTokenMap_prune_big_list[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_PRUNE_BIG_LIST_CONFIG_H_ */
