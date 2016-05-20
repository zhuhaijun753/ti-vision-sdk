/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------*/
/* NAME : vcop_BayerCFA_interpolate                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The "vcop_BayerCFA_interpolate" code accepts 8 or 16-bit data   */
/* in the form of 8 or 16-bit Bayer Pattern, and writes out        */
/* the result as separate R, G and B planes. The output is         */
/* interpolated data to match the input width and height.          */
/* Interpolation is carried out by averaging the left and right    */
/* pixels, or the top and bottom pixels as the case may be.        */
/* In some cases, all four of the top-bottom-left-right pixels are */
/* used to compute the center pixel value.                         */
/*                                                                 */
/*                                                                 */
/* The Bayer pattern is as follows:                                */
/* -------------------------------                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/*                                                                 */
/* After demosiacing or deinterleaving step we get:                */
/* ------------------------------------------------                */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/*                                                                 */
/* rz ry rz ry rz  ry ry                                           */
/* rx R  rx R  rx  R  R                                            */
/* rz ry rz ry rz  ry ry                                           */
/* rx R  rx R  rx  R  R                                            */
/*                                                                 */
/* gy G gy  G  gy G  gy                                            */
/* G  gx G  gx G  gx  G                                            */
/* gy G gy  G  gy G  gy                                            */
/* G  gx G  gx G  gx  G                                            */
/*                                                                 */
/* At this stage, bx, by, bz, rx, ry, rz, gx, gy are zeros.        */
/*                                                                 */
/* After interpolating we get:                                     */
/* ---------------------------                                     */
/* Where bx = (Bleft + Bright)/2                                   */
/* Where by = (Btop  + Bbottom)/2                                  */
/* Where bz = (Bleft + Bright + Btop + Bbottom)/4                  */
/*                                                                 */
/* Where rx = (Rleft + Rright)/2                                   */
/* Where ry = (Rtop  + Rbottom)/2                                  */
/* Where rz = (Rleft + Rright + Rtop + Rbottom)/4                  */
/*                                                                 */
/* Where gx = (Gleft + Gright)/2                                   */
/* Where gy = (Gtop  + Gbottom)/2                                  */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_BayerCFA_Interpolate_char                             */
/* (                                                               */
/*     __vptr_uint8   CFA_char,                                    */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint8   R_char,                                      */
/*     __vptr_uint8   G_char,                                      */
/*     __vptr_uint8   B_char                                       */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop__BayerCFA_Interpolate_short                           */
/* (                                                               */
/*     __vptr_uint16  CFA_short,                                   */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint16  R_short,                                     */
/*     __vptr_uint16  G_short,                                     */
/*     __vptr_uint16  B_short                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* BayerCFA_interpolate_char:                                      */
/* BayerCFA_interpolate_short:                                     */
/*                                                                 */
/*=================================================================*/


#ifndef __VCOP_BAYER_CFA_INTERPOLATE_C_H__
#define __VCOP_BAYER_CFA_INTERPOLATE_C_H__    1

void vcop_BayerCFA_interpolate_char
(
    unsigned char  *CFA_char,  
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    unsigned char  *R_char,
    unsigned char  *G_char,
    unsigned char  *B_char
);


void vcop_BayerCFA_interpolate_short
(
    unsigned short  *CFA_short,  
    unsigned int    in_w,
    unsigned int    blk_w,
    unsigned int    blk_h,
    unsigned short  *R_short,
    unsigned short  *G_short,
    unsigned short  *B_short
);

#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_BayerCFA_interpolate_kernel.h                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

