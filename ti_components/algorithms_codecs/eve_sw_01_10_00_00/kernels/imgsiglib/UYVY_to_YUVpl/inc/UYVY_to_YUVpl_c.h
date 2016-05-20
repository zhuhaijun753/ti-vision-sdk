/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     UYVY_to_YUVpl_c                                                      */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void UYVY_to_YUVpl_c                                                 */
/*     (                                                                    */
/*         unsigned char *YUV_422image,                                     */
/*         int width,                                                       */
/*         int pitch,                                                       */
/*         int height,                                                      */
/*         unsigned char *y,                                                */
/*         unsigned char *cr,                                               */
/*         unsigned char *cb                                                */
/*     )                                                                    */ 
/*                                                                          */
/*                                                                          */
/*     YUV_422image :  Pointer to an input array of interleaved chroma and  */
/*                     luma pixels. Each value is unsigned 8-bit.           */
/*                                                                          */                    
/*                     U0 Y0 V0 Y1 U1 Y2 V1 Y3                              */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*            (Source VLIB) This routine accepts a pointer to an            */
/*     interleaved YUV 422 data array and de-interleaves the color channels */
/*     into three separate memory locations.                                */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef _UYVY_to_YUVpl_C
#define _UYVY_to_YUVpl_C  1
void UYVY_to_YUVpl_c
(
    unsigned char  UYVY[],
    int  blk_w,
    int  pitch,
    int  blk_h,
    unsigned char Y[],
    unsigned char V[],
    unsigned char U[]
);
#endif

/* ======================================================================== */
/*  End of file:  UYVY_to_YUVpl_c.h                                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

