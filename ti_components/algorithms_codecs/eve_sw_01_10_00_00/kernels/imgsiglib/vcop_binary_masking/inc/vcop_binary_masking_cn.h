/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_binary_masking_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for binary masking kernel.                   */
/*                                                                          */
/*  @version 0.1 (Mar 2015) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_BINARY_MASKING_CN_H_
#define VCOP_BINARY_MASKING_CN_H_


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_binary_masking_cm
 *
 *  @desc     This function does the "AND" operation on a byte mask containing 0 and 1 with
 *                a bit packed mask binary image
 *
 *  @inputs   This kernel takes following Inputs
 *                  inByteData :
 *                          Input byte data containing only 0 and 1
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  inBitPackedData :
 *                          Input bit data containing bit packed data
 *                          Size of this buffer should be blockWidth /8 * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel.
 *                  computeHeight :
 *                          Width of the output of this kernel.
 *                  inputByteDataPitch :
 *                          Pitch in bytes for the byte data
 *                  inputBitDataPitch :
 *                          Pitch in bytes for the bit packed data
 *                  outputPitch :
 *                          Pitch of the output data
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                  outBitPackedData
 *                          Pointer to the output buffer containing the output of this kernel in bit packed data
 *                          Size of this buffer should be ( (computeWidth) / 8 * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_binary_masking_cn
(
  uint8_t  *inByteData,
  uint8_t  *inBitPackedData,
  uint8_t  *outBitPackedData,
  unsigned short computeWidth,
  unsigned short computeHeight,
  unsigned short inputByteDataPitch,
  unsigned short inputBitDataPitch,
  unsigned short outputPitch
);

#endif /* VCOP_BINARY_MASKING_CN_H_ */

