/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_multiblock_gradient_xy_cn.h                             */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing gradients of multiple blocks corresponding to */
/*     different feature/key point                                          */
/*                                                                          */
/*     vcop_multiblock_gradient_xy_cn                                       */
/*         This is the c-reference for the vcop_multiblock_gradient_xy      */
/*         kernel. This routine accepts an 8-bit input image and outputs    */
/*         16-bit gradients along X and Y directions in interleaved format  */
/*         for 'numblocks' wherein each output block is of dimension,       */
/*         4 * (blkWidth) x (blkHeight) wherein a factor of '4' bytes is    */
/*         to denote 2 bytes each for gradient along X and Y directions     */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_gradient_xy_cn                                  */
/*     (                                                                    */
/*         uint8_t     *pIn,                                          */
/*         int16_t             *pIntlvGradXY,                               */
/*         uint16_t     inputStride,                                        */
/*         uint16_t     blkWidth,                                           */
/*         uint16_t     blkHeight,                                          */
/*         uint16_t     blkOffset,                                          */
/*         uint16_t     numBlocks                                           */
/*     )                                                                    */
/*                                                                          */
/*     pInput         : Pointer to input image data                         */
/*     pIntlvGradXY   : Pointer to interleaved gradient output per block    */
/*     inputStride    : Stride in the input buffer                          */
/*     blkWidth       : Width of the block for which gradients is computed  */
/*     blkHeight      : Height of the block for which gradients is computed */
/*     blkOffset      : Offset to the start of next block from current block*/
/*     numBlocks      : Number of blocks for which gradients is computed    */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_MULTIBLOCK_GRADIENT_XY_CN
#define VCOP_MULTIBLOCK_GRADIENT_XY_CN  1
/*!

  @fn     vcop_multiblock_gradient_xy_cn

  @brief  This function is a C reference that is used to compute gradients along
          X and Y directions in interleaved format for multiple blocks
          corresponding to each feature or key point
  @param  *pIn             pointer to input image data
  @param  *pIntlvGradXY    pointer to interleaved gradient output per block
  @param  inputStride      stride in the input buffer
  @param  blkWidth         width of the block for which gradients is computed
  @param  blkHeight        height of the block for which gradients is computed
  @param  blkOffset        offset to the start of next block from current block
  @param  numBlocks        number of blocks for which gradients is computed

*/
void vcop_multiblock_gradient_xy_cn
(
    uint8_t     *pIn,                /* pointer to input image data                         */
    int16_t           *pIntlvGradXY,       /* pointer to interleaved gradient output per block    */
    uint16_t     inputStride,        /* stride in the input buffer                          */
    uint16_t     blkWidth,           /* width of the block for which gradients is computed  */
    uint16_t     blkHeight,          /* height of the block for which gradients is computed */
    uint16_t     blkOffset,          /* offset to the start of next block from current block*/
    uint16_t     numBlocks           /* number of blocks for which gradients is computed    */
);

#endif /* VCOP_MULTIBLOCK_GRADIENT_XY_CN */
