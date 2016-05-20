/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_glcm_cn.h                                                  */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Gray-level Co-occerence Matrix.                            */
/*                                                                          */
/*  vcop_glcm_cn                                                            */
/*      This is the c-reference for the vcop_glcm kernel. This              */
/*      routine accepts an 8-bit input image and outputs gray-level         */
/*      co-occurrence matrices or gray tone spatial dependency matrices     */
/*      for each of the directions of analysis specified by the user.       */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  void vcop_glcm_cn(uint8_t  *pInput,                                     */
/*                    uint16_t *pCoMatrix,                                  */
/*                    uint16_t imageWidth,                                  */
/*                    uint16_t imageHeight,                                 */
/*                    uint16_t imagePitch,                                  */
/*                    uint8_t  numLevels,                                   */
/*                    uint8_t  numOffsets,                                  */
/*                    int8_t*  rowOffsets,                                  */
/*                    int8_t*  colOffsets)                                  */
/*                                                                          */
/*  pInput        :  [in] Pointer to grayscale input image, 8 bit           */
/*                   unsigned. This image will be scaled and quantized      */
/*                   to the range [0, numLevels-1].                         */
/*  pCoMatrix     :  [out] Pointer to output Co-Occurrence Matrices, each   */
/*                   of size numLevels x numLevels. The function outputs    */
/*                   one GLCM matrix per direction of analysis.             */
/*  imageWidth    :  Image width                                            */
/*  imageHeight   :  Image height                                           */
/*  imagePitch    :  Image pitch/stride                                     */
/*  numLevels     :  Number of gray-levels to be used for GLCM computation  */
/*  numOffsets    :  Number of directions over which analysis need to be    */
/*                   performed                                              */
/*  rowOffsets    :  Array of number of rows between the pixel of interest  */
/*                   and its neighbor. The array contains as many elements  */
/*                   as numOffsets.                                         */
/*  colOffsets    :  Array of number of columns between the pixel of        */
/*                   interest and its neighbor. The array contains as many  */
/*                   elements as numOffsets.                                */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*  @version 0.1 (Jan 2014) : Base version.                                 */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_GLCM_CN
#define _VCOP_GLCM_CN

int32_t vcop_glcm_cn(uint8_t  *pInput,
                  uint16_t *pCoMatrix,
                  uint16_t imageWidth,
                  uint16_t imageHeight,
                  uint16_t imagePitch,
                  uint8_t  numLevels,
                  uint8_t  numOffsets,
                  char    *rowOffsets,
                  char    *colOffsets);

#endif /* _VCOP_GLCM_CN */
