/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_tensor_matrix_7x7_s16_grad_cn.c                                 */
/*                                                                          */
/*     DESCRIPTION                                `                          */
/*         This is the c-reference for the vcop_tensor_matrix_7x7_s16       */
/*     _grad_kernel. This routine accepts an 16-bit grad x & Y and outputs  */
/*    tensor mtarix (Ix2,Iy2 and Ixy) for 7x7 patch                         */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>

#define BLK_WIDTH  (7)
#define BLK_HEIGHT (7)


void vcop_tensor_matrix_7x7_s16_grad_cn
(
    short           *gradX,         
    short           *gradY,         
    unsigned short   stride,            
    unsigned short   n,              
    int           *Ix2,         
    int           *Iy2,         
    int           *Ixy
)
{
    int i,j,k;
    short x,y;
    int sumIx2,sumIy2,sumIxy;

    for(k = 0; k < n; k++) 
    {
      sumIx2 = 0;
      sumIy2 = 0;
      sumIxy = 0;
      for(i = 0; i < BLK_HEIGHT; i++) 
      {
          for(j = 0; j < BLK_WIDTH; j++) 
          {
            x = gradX[k*stride*BLK_HEIGHT + i*stride+j];
            y = gradY[k*stride*BLK_HEIGHT + i*stride+j];
            sumIx2 += x*x;
            sumIy2 += y*y;
            sumIxy += x*y;
          }
      }
      Ix2[k] = sumIx2;
      Iy2[k] = sumIy2;
      Ixy[k] = sumIxy;
    }

    return;

}


