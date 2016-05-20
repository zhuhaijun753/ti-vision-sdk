/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_BIN_MORPHOLOGY_DILATE_MASK_H_
#define VCOP_BIN_MORPHOLOGY_DILATE_MASK_H_

#include "configparser.h"
#define FILE_NAME_SIZE    (256)
#define DESCRIPTION_SIZE  (256)

#define COEFFICIENT_WIDTH  (3)
#define COEFFICIENT_HEIGHT (3)
#define COEFFICIENT_SIZE   (COEFFICIENT_WIDTH*COEFFICIENT_HEIGHT)


typedef struct
{
  uint8_t        testCaseName[FILE_NAME_SIZE];
  uint8_t        performanceTestcase;
  uint8_t        inImage[FILE_NAME_SIZE];
  uint8_t        outImage[FILE_NAME_SIZE];
  uint8_t        seCoefficient[COEFFICIENT_SIZE];
  uint16_t       blkWidth;
  uint16_t       blkStride;
  uint16_t       blkHeight;
  uint8_t        desc[DESCRIPTION_SIZE];
} sBin_Morphology_Dilate_Mask_Config;

extern sBin_Morphology_Dilate_Mask_Config gConfig_bin_morphology_dilate_mask;
extern sTokenMapping gsTokenMap_bin_morphology_dilate_mask[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_BIN_MORPHOLOGY_DILATE_MASK_H_ */

