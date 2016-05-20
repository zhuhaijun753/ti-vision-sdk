/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_intensity_scaling_cn.h                                     */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Gray-scale image intensity scaling.                        */
/*                                                                          */
/*  vcop_intensity_scaling_cn                                               */
/*  The function accepts a gray-scale input image (pInput) and              */
/*  bins the input gray-scale pixels into bins as specified by              */
/*  'scalingLUT'. The output at 'pScaledImg' is of size imageHeight by      */
/*  imageWidth.                                                             */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  int32_t vcop_intensity_scaling_cn(                                      */
/*                    uint8_t  *pInput,                                     */
/*                    uint8_t  *scalingLUT,                                 */
/*                    uint8_t  *pScaledImg,                                 */
/*                    uint16_t imageWidth,                                  */
/*                    uint16_t imageHeight,                                 */
/*                    uint16_t imagePitch)                                  */
/*                                                                          */
/*  pInput        :  [in] Pointer to grayscale input image, 8 bit           */
/*                   unsigned. This image will be scaled and quantized      */
/*                   to the range [0, numLevels-1].                         */
/*  scalingLUT    :  [in] Pointer to look-up table for performing intensity */
/*                   scaling.                                               */
/*  pScaledImg    :  [out] Pointer to intensity scaled output image.        */
/*  imageWidth    :  Image width.                                           */
/*  imageHeight   :  Image height.                                          */
/*  imagePitch    :  Image pitch/stride.                                    */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*  @version 0.1 (Jan 2014) : Base version.                                 */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_INTENSITY_SCALING_CN
#define _VCOP_INTENSITY_SCALING_CN

int32_t vcop_intensity_scaling_cn(
                  uint8_t  *pInput,
                  uint8_t  *scalingLUT,
                  uint8_t  *pScaledImg,
                  uint16_t imageWidth,
                  uint16_t imageHeight,
                  uint16_t imagePitch);

#endif /* _VCOP_INTENSITY_SCALING_CN */
