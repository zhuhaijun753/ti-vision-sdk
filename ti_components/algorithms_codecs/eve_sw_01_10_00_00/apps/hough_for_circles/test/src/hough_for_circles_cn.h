/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>
#include "ihough_for_circles_ti.h"


void dumpEdgeMap_cn(
  uint8_t  *edgeMap,
  uint16_t imgWidth,
  uint16_t imgHeight,
  uint16_t imgPitch
);

void genEdgeMap_cn(
  uint8_t  *inputData,
  uint8_t  *edgeMap,
  uint16_t imgWidth,
  uint16_t imgHeight,
  uint16_t imgPitch,
  uint16_t edgeMapPitch,
  uint16_t gradThr

  );

void houghForCircle_cn(
  uint8_t  *inputData,
  uint8_t  *edgeMap,
  HOUGH_FOR_CIRCLES_TI_CreateParams *createparams,
  HOUGH_FOR_CIRCLES_TI_InArgs *inArgs,
  HOUGH_FOR_CIRCLES_TI_OutArgs *outArgs,
  uint16_t imgWidth,
  uint16_t imgHeight,
  uint16_t imgPitch,
  uint16_t edgeMapPitch,
  uint16_t maxNumCirc
  );

void houghForCircle_TileBased_cn(
  uint8_t  *inputData,
  uint8_t  *edgeMap,
  HOUGH_FOR_CIRCLES_TI_CreateParams *createparams,
  HOUGH_FOR_CIRCLES_TI_InArgs *inArgs,
  HOUGH_FOR_CIRCLES_TI_OutArgs *outArgs,
  uint16_t imgWidth,
  uint16_t imgHeight,
  uint16_t imgPitch,
  uint16_t edgeMapPitch,
  uint16_t  edgePer,
  uint16_t maxNumCirc
  );

