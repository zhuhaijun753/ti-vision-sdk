/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_tensor_matrix_7x7_s16_grad_cn.h                                 */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference for the vcop_tensor_matrix_7x7_s16       */
/*     _grad_kernel. This routine accepts an 16-bit grad x & Y and outputs  */
/*    tensor mtarix (Ix2,Iy2 and Ixy) for 7x7 patch                         */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_TENSOR_MATRIX_CN
#define _VCOP_TENSOR_MATRIX_CN  1

void vcop_tensor_matrix_7x7_s16_grad_cn
(
	int16_t           *gradX,
    int16_t           *gradY,
    unsigned short   stride,            
    unsigned short   n,              
    int32_t           *Ix2,
    int32_t           *Iy2,
    int32_t           *Ixy
);

#endif /* _VCOP_TENSOR_MATRIX_CN */
