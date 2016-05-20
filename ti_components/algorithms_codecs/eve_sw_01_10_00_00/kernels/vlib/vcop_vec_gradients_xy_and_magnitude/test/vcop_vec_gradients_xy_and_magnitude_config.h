/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_VEC_GRADIENTS_XY_AND_MAGNITUDE_CONFIG_H_
#define VCOP_VEC_GRADIENTS_XY_AND_MAGNITUDE_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

typedef struct
{
  char      inputData[FILE_NAME_SIZE];
  uint16_t  width;
  uint16_t  height;
  uint16_t  inDataPitch;
  uint16_t  edgeMapPitch;
  uint32_t  randSeed;
  uint8_t   numIter;
} sGradient_xy_magnitude_Config;

extern sGradient_xy_magnitude_Config gConfig_gradient_xy_magnitude;
extern sTokenMapping gsTokenMap_gradient_xy_magnitude[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_VEC_GRADIENTS_XY_AND_MAGNITUDE_CONFIG_H_ */

