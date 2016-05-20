/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_sad_error_measure_lk_cn.h                               */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing SAD (Sum of Absolute Differences) based error */
/*     measure for each key point. It will also incorporate boundary check  */
/*     compute and initializes error to 0xFFFF for out of bound key points  */
/*     The following figure illustrates the input data arrangement of the   */
/*     bilinear interpolated patch windows for both previous and current    */
/*     frames across each key point.                                        */
/*                                                                          */
/*                           (inputStride) bytes                            */
/*                            (blkWidth) bytes                              */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (blkHeight)     |        Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |        Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |  Blk(numKeyPoints-1)  |                           */
/*                      |_______________________|                           */
/*                                                                          */
/*     @version 1.0 (January 2014) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

#include <stdint.h>

#ifndef _VCOP_SAD_ERROR_MEASURE_LK_CN
#define _VCOP_SAD_ERROR_MEASURE_LK_CN  1
/*!

  @fn     vcop_sad_error_measure_lk_cn

  @brief  This is the c-reference for the vcop_sad_error_measure_lk_cn
          kernel. This routine accepts tracked (X, Y) coordinates lists
          of length 'numKeyPoints', bilinear interpolated patch windows
          around the initial and tracked key point locations for both
          previous and current frame respectively. blkOffset denotes the
          inter block offset which implies distance between first pixel
          of Blk(n) and Blk(n-1) as illustrated in figure above. 7x7
          neighboorhood window is being used here, due to SIMD alignment
          8x7 is recommended as blkWidth x blkHeight. It computes the SAD
          based error measure of LK at every key point. For out of bound
          points, it will initialize the error to 0xFFFF

  @param  pPrevBiLinImg_A    : Pointer to previous frame bilinear interpolated patch windows
  @param  pCurrBiLinImg_B    : Pointer to current frame bilinear interpolated patch windows
  @param  pNewLocalXYList_X  : Pointer to local XY coordinates locations corresponding to the tracked locations
  @param  pOutErrorMeasure_C : Pointer to SAD based error measure for each key point being tracked
  @param  inputStride       : Stride of the previous or current frame bilinear interpolated patch windows, pPrevBiLinImg_A or pCurrBiLinImg_B
  @param  frmWidth           : Width of the previous or current frame in bytes
  @param  frmHeight          : Height of the previous or current frame in bytes
  @param  blkWidth           : Width of the input block around each key point
  @param  blkHeight          : Height of the input block around each key point
  @param  numKeyPoints       : Number of key points
  @param  shiftValue         : Number of fractional bits

*/
void vcop_sad_error_measure_lk_cn
(
   uint8_t     *pPrevBiLinImg_A,
   uint8_t     *pCurrBiLinImg_B,
   uint16_t    *pNewLocalXYList_X,
   uint16_t    *pOutErrorMeasure_C,
   uint16_t     inputStride,
   uint16_t     frmWidth,
   uint16_t     frmHeight,
   uint16_t     blkWidth,
   uint16_t     blkHeight,
   uint16_t     numKeyPoints,
   uint16_t     shiftValue
);
#endif /* _VCOP_SAD_ERROR_MEASURE_LK_CN */
