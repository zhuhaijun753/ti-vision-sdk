/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_nonMaxSuppress_mxn_32s_c.h                              */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for non-maximum suppression using mxn window on 32 bit      */
/*     images.                                                              */
/*                                                                          */
/*     vcop_nonMaxSuppress_mxn_32s_cn                                       */
/*         This is the c-reference for the vcop_nonMaxSuppress_mxn_32s      */
/*         kernel. This routine accepts an 32-bit input image and outputs   */
/*         non-maxima suppressed image using a mxn window.                  */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nonMaxSuppress_mxn_32s_cn                                  */
/*     (                                                                    */
/*         unsigned int   im [],                                            */
/*         unsigned char  out[],                                            */
/*         int            height,                                           */
/*         int            width,                                            */
/*         int            m,                                                */
/*         int            n,                                                */
/*         int            thresh                                            */
/*     )                                                                    */
/*                                                                          */
/*     im         :  32-bit input image                                     */
/*     out        :  8-bit binary output image                              */
/*     height     :  Height of the input image                              */
/*     width      :  Width of the input image                               */
/*     m          :  Height of the NMS window                               */
/*     n          :  Width of the NMS window                                */
/*     thresh     :  Threshold for pruning peaks                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/*     @version 1.0 (March 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_NONMAXSUPPRESS_MxN_32S_CN
#define _VCOP_NONMAXSUPPRESS_MxN_32S_CN  1

void vcop_nonMaxSuppress_mxn_32s_cn
(
    int   im[],
    unsigned char  out[],
    int            width,
    int            height,
    int            input_stride,
    int            output_stride,
    int            m,
    int            n,
    int            thresh
);

void vcop_nonMaxSuppress_mxn_32s_bitPack_cn
(
    int im[],
    unsigned char  out[],
    unsigned short width,
    unsigned short height,
    unsigned short inputStride,
    unsigned short outputSrtide,
    int            windowWidth,
    int            windowHeight,
    int            thresh
);


#endif /* _VCOP_NONMAXSUPPRESS_MxN_32S_CN */
