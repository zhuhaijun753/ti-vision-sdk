/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_calc_determinant_tensor_matrix_cn.h                             */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference header for the                           */
/*   vcop_calc_determinant_tensor_matrix  kernel                            */
/*   This routine accepts an 32-bit teson matrix ans outputs determinant    */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_DETERMINANT_TESONR_CN
#define VCOP_DETERMINANT_TESONR_CN  1

void vcop_calc_determinant_tensor_matrix_cn
  (
  int32_t             *Ix2,
  int32_t             *Iy2,
  int32_t             *Ixy,
  uint16_t  *out_d_nrsb,        
  int32_t         *out_d_norm,
  uint16_t   n
  );

#endif /* VCOP_DETERMINANT_TESONR_CN */
