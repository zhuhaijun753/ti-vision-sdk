/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_EXTRACT_BIT_FIELD_U32_CONFIG_H_
#define _VCOP_EXTRACT_BIT_FIELD_U32_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
typedef struct
{
  char       inList[FILE_NAME_SIZE];
  char       outList[FILE_NAME_SIZE];
  uint16_t   listLength;
  uint32_t   bitMask;
  uint8_t    shift;
  uint32_t   randSeed;
  uint8_t    numIter;
} sextract_bit_field_u32_Config;

extern sextract_bit_field_u32_Config gConfig_extract_bit_field_u32;
extern sTokenMapping gsTokenMap_extract_bit_field_u32[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_EXTRACT_BIT_FIELD_U32_CONFIG_H_ */
