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

#ifndef GRAYSCALE_MORPHOLOGY_HOST_H_
#define GRAYSCALE_MORPHOLOGY_HOST_H_

#include "imorphology_ti.h"


typedef struct
{
    MORPHOLOGY_TI_StructuringElementShape  seShape;
    MORPHOLOGY_TI_Operation                morphologyMode;
    uint16_t  blkWidth;
    uint16_t  blkStride;
    uint16_t  blkHeight;
    uint8_t  *dataPtr_A;
    uint16_t  seWidth;
    uint16_t  seHeight;
    uint8_t  *sePtr_C;
    uint8_t  *seReflPtr_C;
    uint8_t  *scratchPtr_C;
    uint8_t  *scratchPtr_A;
    uint8_t  *outputPtr_B;
} Grayscale_Morphology_ExecParams;

/**
*  @brief     Frame-level Grayscale Morphological Filtering API for Host Emulation

*  Grayscale_Morphology_exec performs the specified grayscale morphological
*  operation on the input 8-bit grayscale image provided in src buffer with
*  the structuring element provided in struct_elem and writes the output into
*  dst buffer in Host Emulation.
*
*  @code
*      void Grayscale_Morphology_exec(void *args)
*  @endcode
*
*  @param[in]   args               Pointer to the Grayscale_Morphology_ExecParams.
*
*/
void Grayscale_Morphology_exec(void *args);


#endif /*  GRAYSCALE_MORPHOLOGY_HOST_H_ */

