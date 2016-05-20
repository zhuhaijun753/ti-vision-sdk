/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_sobel_xy_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Sobel xy computation for circles.                   */
/*                                                                          */
/*  @version 0.1 (Dec 2014) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_SOBEL_XY_CN_H_
#define VCOP_SOBEL_XY_CN_H_


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @func     vcop_sobelXY_3x3_separable_uchar_cn
 *
 *  @desc     Implementation of sobel X and Y operator together
 *                 which is [1 2 1] x [1 0 -1]'
 *
 *  @inputs   This func takes following Inputs
 *                  inData :
 *                          Input data pointer
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  roundShift :
 *                          Rounding that needs to be applied to the output
 *
 *  @scratch   This function needs  following scratch buffers
 *                  interimDataX :
 *                          This is dummy pointer just to keep interface of ref and kernel same. Its not really required
 *                          by reference C
 *                  interimDataY :
 *                          This is dummy pointer just to keep interface of ref and kernel same. Its not really required
 *                          by reference C
 *
 *  @outputs   This function produce following outputs
 *                  outDataX
 *                          Pointer to the output for X component
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *                  outDataY
 *                          Pointer to the output for Y component
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXY_3x3_separable_uchar_cn
(
  uint8_t  *inData,
  int16_t  *interimDataX,
  int16_t  *interimDataY,
  int8_t   *outDataX,
  int8_t   *outDataY,
  uint16_t  computeWidth,
  uint16_t  computeHeight,
  uint16_t  inputPitch,
  uint16_t  outputPitch,
  uint8_t   roundShift
);


/* ==================================================
 *  @func     vcop_sobelXy_3x3_L1_thresholding_cn
 *
 *  @desc     This function uses L1 norm and thesholding
 *
 *
 *  @inputs   This function takes following Inputs
 *                  gradX :
 *                          Gradient X
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  gradY :
 *                          Gradient Y
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  threshold :
 *                          Threshold to be used for thresholding magnitude
 *
 *  @scratch   This function needs  following scratch buffers
 *                          None
 *
 *  @outputs   This function produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl containing 255 at places where edges are present and 0 otherwise
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t)
 *
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_sobelXy_3x3_L1_thresholding_cn
(
   int8_t   *gradX,
   int8_t   *gradY,
   uint8_t  *outData,
   uint16_t  computeWidth,
   uint16_t  computeHeight,
   uint16_t  inputPitch,
   uint16_t  outputPitch,
   uint16_t  threshold
);

/* ==================================================
 *  @func  vcop_sobelXy_3x3_L1_thresholding_binPack_cn
 *
 *  @desc     This function uses L1 norm and thesholding and gives a binary image output
 *                whose bits indicate edge if it is 1 and non-edge if it is zero. While loading
 *                a data in byte lower most bit will correspond to the first pixel.
 *
 *
 *  @inputs   This function takes following Inputs
 *                  gradX :
 *                          Gradient X
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  gradY :
 *                          Gradient Y
 *                          Size of this buffer should be computeWidth * computeHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel. This is basicaly blockWidth - border
 *                  computeHeight :
 *                          Width of the output of this kernel. This is basicaly blockHeight - border
 *                  inputPitch :
 *                          Pitch of the input data
 *                  outputPitch :
 *                          Pitch of the output data
 *                  threshold :
 *                          Threshold to be used for thresholding magnitude
 *
 *  @outputs   This function produce following outputs
 *                  outData :
 *                          Pointer to the output of this kenerl containing 1 and places where edges are present and 0 otherwise
 *                          Size of this buffer should be ( ALIGN_2SIMD(computeWidth) * computeHeight * size(int8_t) /8
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_sobelXy_3x3_L1_thresholding_binPack_cn
(
   int8_t   *gradX,
   int8_t   *gradY,
   uint8_t  *outData,
   uint16_t  computeWidth,
   uint16_t  computeHeight,
   uint16_t  inputPitch,
   uint16_t  outputPitch,
   uint16_t  threshold
);


#endif /* VCOP_SOBEL_XY_CN_H_ */

