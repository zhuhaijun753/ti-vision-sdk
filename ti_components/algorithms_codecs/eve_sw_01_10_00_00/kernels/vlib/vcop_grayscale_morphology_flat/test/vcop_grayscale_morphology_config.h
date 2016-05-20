/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef VCOP_GRAYSCALE_MORPHOLOGY_H_
#define VCOP_GRAYSCALE_MORPHOLOGY_H_

#include "configparser.h"
#define FILE_NAME_SIZE    (256)
#define DESCRIPTION_SIZE  (256)

#define MAX_COEFFICIENT_WIDTH  (10)
#define MAX_COEFFICIENT_HEIGHT (10)
#define MAX_COEFFICIENT_SIZE   (MAX_COEFFICIENT_WIDTH*MAX_COEFFICIENT_HEIGHT)


typedef enum
{
  grayscaleMorphologyDilation  = 0,
  grayscaleMorphologyErosion   = 1,
  grayscaleMorphologyOpening   = 2,
  grayscaleMorphologyClosing   = 3,
  grayscaleMorphologyTopHat    = 4,
  grayscaleMorphologyBottomHat = 5,
  grayscaleMorphologyMorphologicalGradient = 6,
  grayscaleMorphologyMaxMode  = 7
} eGrayscaleMorphologyMode;

typedef uint8_t grayscaleMorphologyMode;

typedef enum
{
  grayscaleMorphologyMask  = 0,
  grayscaleMorphologyRect  = 1,
  grayscaleMorphologyCross = 2,
  grayscaleMorphologyMaxSE = 3
} eGrayscaleMorphologyStructuringElement;

typedef uint8_t grayscaleMorphologyStructuringElement;


typedef struct
{
  uint8_t        testCaseName[FILE_NAME_SIZE];
  uint8_t        performanceTestcase;
  uint8_t        inImage[FILE_NAME_SIZE];
  uint8_t        outImage[FILE_NAME_SIZE];
  grayscaleMorphologyMode                 morphologyMode;
  grayscaleMorphologyStructuringElement   structuringElementType;
  uint8_t        seCoefficient[MAX_COEFFICIENT_SIZE];
  uint16_t       blkWidth;
  uint16_t       blkStride;
  uint16_t       blkHeight;
  uint16_t       seWidth;
  uint16_t       seHeight;
  uint8_t        desc[DESCRIPTION_SIZE];
} sGrayscale_Morphology_Config;

extern sGrayscale_Morphology_Config gConfig_grayscale_morphology;
extern sTokenMapping gsTokenMap_grayscale_morphology[MAX_ITEMS_TO_PARSE];

#endif  /* VCOP_GRAYSCALE_MORPHOLOGY_H_ */

