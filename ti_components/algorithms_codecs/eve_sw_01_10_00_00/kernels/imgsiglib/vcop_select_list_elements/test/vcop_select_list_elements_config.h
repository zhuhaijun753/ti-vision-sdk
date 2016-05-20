/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_SELECT_LIST_ELEMENTS_CONFIG_H_
#define VCOP_SELECT_LIST_ELEMENTS_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
#define DESCRIPTION_SIZE  (256)

typedef struct
{
  char  inputList[FILE_NAME_SIZE];
  char  outputList[FILE_NAME_SIZE];
  uint16_t listSize;
  uint16_t selectionMaskSize;
  uint32_t randSeed;
  uint8_t  numIter;
  uint8_t    testCaseName[FILE_NAME_SIZE];
  uint8_t    performanceTestcase;
  uint8_t    desc[DESCRIPTION_SIZE];
} sSelect_list_elements_Config;

extern sSelect_list_elements_Config gConfig_select_list_elements;
extern sTokenMapping gsTokenMap_select_list_elements[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_SELECT_LIST_ELEMENTS_CONFIG_H_ */

