/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file   grayscale_morphology.h
 *
 *  @brief  Grayscale Morphological Filtering Applet
 *
 *  @date   22 March 2013
 *
 *  This applet supports grayscale morphological filtering using a generic
 *  flat structuring element. The structuring element need to be specified
 *  as a mask of ones and zeros in an array of length se_width x se_height
 *  in 'struct_elem'. The user is also expected to provide the reflected
 *  structuring element array required for dilation in 'struct_elem_refl'.
 *  The input grayscale images are assumed to be 8-bit. The output is also
 *  an 8-bit grayscale image.
 *
 *  The supported grayscale morphological operations include: dilation,
 *  erosion, opening, closing, top hat, bottom hat and morphological gradient.
 *  Internally the applet processes the input image in blocks of 32x32. Hence
 *  the srcImageWidth and srcImageHeight needs to be multiples of 32 inorder to
 *  process the entire image.
 *
 */

#ifndef GRAYSCALE_MORPHOLOGY_H_
#define GRAYSCALE_MORPHOLOGY_H_

#include "vcop_grayscale_morphology.h"
#include "edma_utils_context_size.h"


typedef struct
{
    uint8_t                 *srcPtr_A;
    uint8_t                 *sePtr_C;
    uint8_t                 *seReflPtr_C;
    uint8_t                 *scratchPtr_C;
    uint8_t                 *scratchPtr_A;
    uint8_t                 *outputPtr_B;
    uint8_t                  autoIncrementContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
#if (!VCOP_HOST_EMULATION)
    stblock_morph_t          stParamBlock;
    stblock_open_close_t     stParamBlock_open_close;
#endif
} Grayscale_Morphology_Obj;


void Grayscale_Morphology_Init(Grayscale_Morphology_Obj *handle);


/**
*  @brief     Frame-level Grayscale Morphological Filtering API

*  EVELIB_grayscaleMorphology performs the specified grayscale morphological
*  operation on the input 8-bit grayscale image provided in src buffer with
*  the structuring element provided in struct_elem and writes the output into
*  dst buffer.
*
*  @code
*      void Grayscale_Morphology_Process(unsigned char  *src,
*                                      unsigned int    srcImageWidth,
*                                      unsigned int    srcImageHeight,
*                                      int             srcImagePitch,
*                                      unsigned char  *dst,
*                                      unsigned int    dstImageWidth,
*                                      unsigned int    dstImageHeight,
*                                      int             dstImagePitch,
*                                      unsigned char   struct_elem[],
*                                      unsigned char   struct_elem_refl[],
*                                      unsigned int    se_height,
*                                      unsigned int    se_width,
*                                      GrayscaleMorphologyOperation  operation)
*  @endcode
*
*  @param[in]   src               Pointer to the source buffer in SDRAM.
*  @param[in]   srcImageWidth     Input image width. Need to be a multiple of 32.
*  @param[in]   srcImageHeight    Input image height. Need to be a multiple of 32.
*  @param[in]   srcImagePitch     Stride of the input buffer.
*  @param[out]  dst               Pointer to the destination buffer in SDRAM.
*  @param[in]   dstImageWidth     Output image width.
*  @param[in]   dstImageHeight    Output image height.
*  @param[in]   dstImagePitch     Stride of the output buffer.
*  @param[in]   struct_elem       Pointer to structuring element array.
*  @param[in]   struct_elem_refl  Pointer to reflected structuring element array.
*  @param[in]   se_width          Structuring element width.
*  @param[in]   se_height         Structuring element height.
*  @param[in]   operation         Grayscale morphological operation to be performed.
*
*/
void Grayscale_Morphology_Process(
                         Grayscale_Morphology_Obj *handle,
                         uint8_t      *src,
                         uint16_t      srcImageWidth,
                         uint16_t      srcImageHeight,
                         uint16_t      srcImagePitch,
                         uint8_t      *dst,
                         uint16_t      dstImageWidth,
                         uint16_t      dstImageHeight,
                         uint16_t      dstImagePitch,
                         uint8_t       struct_elem[],
                         uint16_t      se_width,
                         uint16_t      se_height,
                         uint8_t       seShape,
                         uint8_t       operation);


void Grayscale_Morphology_Deinit(Grayscale_Morphology_Obj *handle);


#endif /*  GRAYSCALE_MORPHOLOGY_H_ */

