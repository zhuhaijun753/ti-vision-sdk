/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_sum_grad_cross_inter_frame_diff_7x7_cn.h                        */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference header for the                           */
/*   vcop_sum_grad_cross_inter_frame_diff_7x7  kernel                       */
/*   This routine accepts an 16-bit grad x & Y , prev pixels, current pixels*/
/*   and outputs (Ix*It,Iy*It) sum for 7x7 patch                            */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_SUM_GRAD_IFDIFF_CN
#define _VCOP_SUM_GRAD_IFDIFF_CN  1

void vcop_sum_grad_cross_inter_frame_diff_7x7_cn
(
    short           *gradX,         
    short           *gradY,         
    unsigned char   *im1,            
    unsigned char   *im2,              
    unsigned short   gradStride,            
    unsigned short   imStride,            
    unsigned short   n,              
    int             *IxIt,         
    int             *IyIt        
);

#endif /* _VCOP_SUM_GRAD_IFDIFF_CN */
