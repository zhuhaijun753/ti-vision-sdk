/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef MORPHOLOGY_CONFIG_H_
#define MORPHOLOGY_CONFIG_H_

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#pragma RESET_MISRA ("required")

#include "configparser.h"


#define FILE_NAME_SIZE    (256)
#define DESCRIPTION_SIZE  (256)

#define MAX_COEFFICIENT_WIDTH  (10)
#define MAX_COEFFICIENT_HEIGHT (10)
#define MAX_COEFFICIENT_SIZE   (MAX_COEFFICIENT_WIDTH*MAX_COEFFICIENT_HEIGHT)


typedef struct
{
  uint8_t        testCaseName[FILE_NAME_SIZE];
  uint8_t        performanceTestcase;
  uint8_t        inImage[FILE_NAME_SIZE];
  uint8_t        outImage[FILE_NAME_SIZE];
  uint8_t        inImageType;
  uint8_t        morphologyMode;
  uint8_t        seShape;
  uint8_t        seCoefficient[MAX_COEFFICIENT_SIZE];
  uint16_t       srcWidth;
  uint16_t       srcPitch;
  uint16_t       srcHeight;
  uint16_t       seWidth;
  uint16_t       seHeight;
  uint8_t        desc[DESCRIPTION_SIZE];
} sMorphology_Config;

extern sMorphology_Config gConfig_morphology;
extern sTokenMapping gsTokenMap_morphology[MAX_ITEMS_TO_PARSE];


#endif /*MORPHOLOGY_CONFIG_H_*/

