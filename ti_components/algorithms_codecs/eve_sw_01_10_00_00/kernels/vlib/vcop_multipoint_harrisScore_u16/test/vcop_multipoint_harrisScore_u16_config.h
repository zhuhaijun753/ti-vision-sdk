/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_MULTIPOINT_HARRISSCORE_U16_CONFIG_H_
#define _VCOP_MULTIPOINT_HARRISSCORE_U16_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)
typedef struct
{
  char     inImageBlocks[FILE_NAME_SIZE];
  char     outHarrisScore[FILE_NAME_SIZE];
  uint16_t numPoints;
  uint16_t interBlockOffset;
  uint16_t inputStride;
  uint16_t sensitivityParam;
  uint16_t start_id;
  uint32_t randSeed;
  uint8_t  numIter;
} sMultipoint_harris_score_Config;

extern sMultipoint_harris_score_Config gConfig_multipoint_harris_score;
extern sTokenMapping gsTokenMap_multipoint_harris_score[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_MULTIPOINT_HARRISSCORE_U16_CONFIG_H_ */
