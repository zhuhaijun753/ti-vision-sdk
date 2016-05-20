/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     gauss5x5PyramidKernel_8_cn                                           */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_image_pyramid_u16_cn                                       */
/*     (                                                                    */
/*         unsigned short pIn[],                                            */
/*         unsigned short inCols,                                           */
/*         unsigned short inRows,                                           */
/*         unsigned short pOut[]                                            */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  16-bit input image                                       */
/*     inCols   :  Number of coluns in the image                            */
/*     inRows   :  Number of rows in the image                              */
/*     pOut     :  16-bit output image                                      */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of image pryamid in the pOut array.                           */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 16. */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _VCOP_GAUSS_5x5_PYRAMID_KERNEL_8_CN
#define _VCOP_GAUSS_5x5_PYRAMID_KERNEL_8_CN  1

void vcop_gauss5x5PyramidKernel_8_horiz_c
(
    unsigned char   pIn[],
    unsigned char   pOut[],
    unsigned short  width,
    unsigned short  height,
    unsigned short  inPitch,
    unsigned short  outPitch
);

void vcop_gauss5x5PyramidKernel_8_vert_c
(
    unsigned char   pIn[],
    unsigned char   pOut[],
    unsigned short  width,
    unsigned short  height,
    unsigned short  inPitch,
    unsigned short  outPitch
);

#endif

/* ======================================================================== */
/*  End of file:  vcop_gauss5x5PyramidKernel_8_c.h                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
