/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_calc_determinant_tensor_matrix_cn.c                             */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference for the                                  */
/*   vcop_calc_determinant_tensor_matrix  kernel                            */
/*   This routine accepts an 32-bit teson matrix ans outputs determinant    */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>


#define BLK_WIDTH  (7)
#define BLK_HEIGHT (7)


void vcop_calc_determinant_tensor_matrix_cn
  (
  int             *Ix2,         
  int             *Iy2,        
  int             *Ixy,        
  unsigned short  *out_d_nrsb,        
  int             *out_d_norm,        
  unsigned short   n
  )
{
  int k;
  long long x;
  long long d;
  unsigned short d_nrsb;
  int d_norm;

    for(k = 0; k < n; k++) 
    {
      x = d = (long long)Ix2[k] * Iy2[k] - (long long)Ixy[k] * Ixy[k]; 

      d_nrsb = 0;
      if(d < 0)
      {
        while( d < 0)
        {
          d = d << 1;
          d_nrsb++;
        }
      }
      else
      {
        while( d >= 0 && d_nrsb < 64)
        {
          d = d << 1;
          d_nrsb++;
        }
      }
      d_nrsb =  d_nrsb-1;

      d_norm = (x << d_nrsb) >> 32; 

      out_d_nrsb[k] = d_nrsb;
      out_d_norm[k] = d_norm;

    }

    return;

}


