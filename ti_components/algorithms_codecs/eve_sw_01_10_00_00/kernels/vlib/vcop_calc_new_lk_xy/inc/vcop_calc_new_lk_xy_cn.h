/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_calc_new_lk_xy_cn.h                                             */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference header for the vcop_calc_new_lk_xy_cn    */
/*   This routine accepts tesnsor matrix and the IxIt/IyIT matrix to        */
/*   calculate the new x and y co-oridinates                                */
/*                                                                          */
/*     @version 0.1 (Nov 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_CALC_NEW_LK_XY_CN
#define _VCOP_CALC_NEW_LK_XY_CN  1

void vcop_calc_new_lk_xy_cn
  (
  int             *IxIt,         
  int             *IyIt,        
  short           *Ix2,        
  short           *Iy2,        
  short           *Ixy,        
  unsigned short  *X,        
  unsigned short  *Y,        
  unsigned short  *frameXY,
  unsigned short  *numValidPoints,        
  unsigned char   *currValidPoints,        
  unsigned short  qFormatePel,
  unsigned short  minErrValue,
  unsigned char   searchRange,
  unsigned short  n
  );
#endif /* _VCOP_CALC_NEW_LK_XY_CN */
