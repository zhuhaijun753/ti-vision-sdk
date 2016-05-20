/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_gradient5x5PyramidKernel_8_kernel_cn                            */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_gradientH5x5PyramidKernel_8                                */
/*     (                                                                    */
/*         unsigned char   pIn[],                                           */
/*         short           pB[],                                            */
/*         unsigned short  width,                                           */
/*         unsigned short  pitch,                                           */
/*         unsigned short  height,                                          */
/*         unsigned char   pOut[]                                           */
/*     )                                                                    */
/*                                                                          */
/*     vcop_gradientV5x5PyramidKernel_8                                     */
/*     (                                                                    */
/*         unsigned char  pIn[],                                            */
/*         short          pB[],                                             */
/*         unsigned short width,                                            */
/*         unsigned short pitch,                                            */
/*         unsigned short height,                                           */
/*         unsigned char  pOut[]                                            */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  8-bit input image                                        */
/*     pB       :  Intermediate buffer                                      */
/*     width    :  Width of the input image                                 */
/*     pitch    :  Pitch of the input image                                 */
/*     height   :  Height of the input image                                */
/*     pOut     :  8-bit output image                                       */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of gradient pyramid in the pOut array.                        */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 8.  */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_image_pyramid_u16_CN
#define _vcop_image_pyramid_u16_CN  1

void vcop_gradientH5x5PyramidKernel_8
(
    unsigned char   pIn[],  
    short           pB[],     
    unsigned short  width, 
    unsigned short  pitch, 
    unsigned short  height,
    unsigned char   pOut[]
);

void vcop_gradientV5x5PyramidKernel_8
(
    unsigned char  pIn[],      
    short          pB[],             
    unsigned short width,  
    unsigned short pitch,  
    unsigned short height,
    unsigned char  pOut[]
);

#endif

/* ======================================================================== */
/*  End of file:  vcop_gradient5x5PyramidKernel_8_cn.h                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
