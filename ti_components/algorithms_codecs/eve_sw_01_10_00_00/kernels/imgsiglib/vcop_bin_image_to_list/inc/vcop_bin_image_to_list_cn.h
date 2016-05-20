/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_bin_image_to_list_cn.h                                  */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for generating (X, Y) co-ordinate list of non-zero      */
/*         pixels from an input binary image.                               */
/*                                                                          */
/*     vcop_bin_image_to_list_cn                                            */
/*         This is the C-reference for the vcop_bin_image_to_list kernel.   */
/*         This routine accepts an 8-bit binary input image and outputs a   */
/*         list of (X, Y) co-ordinates of non-zero pixel locations in the   */
/*         image. The X and Y co-ordinates are both 16-bit and are packed   */
/*         into a 32-bit number. The lower 16-bits contain Y co-ordinate    */
/*         and upper 16-bits contain the X co-oridinate. The locations are  */
/*         reported in raster scan order in the input block.                */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bin_image_to_list_cn                                       */
/*     (                                                                    */
/*         uint8_t  *img,                                                   */
/*         uint32_t *upperLeftXY,                                           */
/*         uint32_t *outXY_list,                                            */
/*         uint32_t *list_size,                                             */
/*         uint16_t  width,                                                 */
/*         uint16_t  height,                                                */
/*         uint16_t  stride                                                 */
/*     )                                                                    */
/*                                                                          */
/*     img           : 8-bit binary input image. The exact format of the    */
/*                     binary bit mask in image is as shown below:          */
/*                     Pix7  Pix6  Pix5  ... Pix0  Pix15 Pix14 ... Pix8     */
/*                     Pix23 Pix22 Pix21 ... Pix16 ...                      */
/*     upperLeftXY   : (X, Y) location of the upper left pixel in the block */
/*                     X co-ordinate is expected in the upper 16-bits and   */
/*                     the Y co-ordinate is expected in the lower 16-bits.  */
/*     outXY_list    : (X, Y) co-ordinates of locations of non-zero pixels. */
/*                     Here lower 16-bits contain Y co-ordinate and upper   */
/*                     16-bits contain the X co-oridinate.                  */
/*     list_size     : Number of (X, Y) pairs in the output list            */
/*     width         : Width of the input image                             */
/*     height        : Height of the input image                            */
/*     stride        : Stride for the input image. This should be a         */
/*                     multiple of 8.                                       */
/*     outputQformat : Output Q format, ie amount of shift to be given to the coordniates */
/*                         before storing it */
/*     xyOrder : if xyOrder ==1 , then output witll have x in msb and y in lsb */
/*                       xyOrder == 0 , then output witll have y in msb and x in lsb */
/*                                                                          */
/*     Returns       :  None or void.                                       */
/*                                                                          */
/*     @version 1.0 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_BIN_IMAGE_TO_LIST_CN
#define _VCOP_BIN_IMAGE_TO_LIST_CN

void vcop_bin_image_to_list_cn
(
    uint8_t  *img,
    uint32_t *upperLeftXY,
    uint32_t *outXY_list,
    uint32_t *list_size,
    uint16_t  width,
    uint16_t  height,
    uint16_t  stride,
    uint16_t  outputQformat,
    uint8_t   xyOrder

);

#endif /* _VCOP_BIN_IMAGE_TO_LIST_CN */
