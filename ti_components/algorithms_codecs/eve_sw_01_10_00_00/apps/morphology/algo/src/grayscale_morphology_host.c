/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file grayscale_morphology.c
 *
 *  @brief  This file implements an applet for grayscale morphology
 *
 *  @author Anoop K P <a-kp@ti.com>
 *
 *  @date   22 March 2013
 *
 *  Description
 *    This file contains code to perform grayscale morphological processing
 *    at the frame level.
 */


#include <stdint.h>
#include <vcop.h>
#include "xdais_types.h"
#include <stdio.h>

#include "imorphology_ti.h"
#include "grayscale_morphology_host.h"

#include "vcop_grayscale_morphology_kernel.h"
#include "vcop_grayscale_morphology.h"



void Grayscale_Morphology_exec(void *args)
{
  Grayscale_Morphology_ExecParams *execParams  = (Grayscale_Morphology_ExecParams *)args;
  MORPHOLOGY_TI_StructuringElementShape  seShape        = execParams->seShape;
  MORPHOLOGY_TI_Operation                morphologyMode = execParams->morphologyMode;
  uint16_t  blkWidth     = execParams->blkWidth;
  uint16_t  blkStride    = execParams->blkStride;
  uint16_t  blkHeight    = execParams->blkHeight;
  uint8_t  *dataPtr_A    = execParams->dataPtr_A;
  uint16_t  seWidth      = execParams->seWidth;
  uint16_t  seHeight     = execParams->seHeight;
  uint8_t  *sePtr_C      = execParams->sePtr_C;
  uint8_t  *seReflPtr_C  = execParams->seReflPtr_C;
  uint8_t  *scratchPtr_C = execParams->scratchPtr_C;
  uint8_t  *scratchPtr_A = execParams->scratchPtr_A;
  uint8_t  *outputPtr_B  = execParams->outputPtr_B;

  switch ( morphologyMode )
  {
    case MORPHOLOGY_TI_DILATE:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_dilate_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, seReflPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_dilate_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_dilate_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, (seHeight-1)/2, (seWidth-1)/2, scratchPtr_C, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_ERODE:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_erode_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_erode_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_erode_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, (seHeight-1)/2, (seWidth-1)/2, scratchPtr_C, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_OPEN:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_open_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_open_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_open_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_CLOSE:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_close_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_close_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_close_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_TOPHAT:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_tophat_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_tophat_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_tophat_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_BOTTOMHAT:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_bottomhat_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_bottomhat_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_bottomhat_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_GRADIENT:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_morph_grad_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_morph_grad_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_morph_grad_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
  }
}

