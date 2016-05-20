/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_sum_grad_cross_inter_frame_diff_7x7_cn.c                        */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference for the                                  */
/*   vcop_sum_grad_cross_inter_frame_diff_7x7  kernel                       */
/*   This routine accepts an 16-bit grad x & Y , prev pixels, current pixels*/
/*   and outputs (Ix*It,Iy*It) sum for 7x7 patch                            */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>

#define BLK_WIDTH  (7)
#define BLK_HEIGHT (7)


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
)
{
    int i,j,k;
    short x,y,diff;
    unsigned char c,p;
    int sumIxIt,sumIyIt;
    for(k = 0; k < n; k++) 
    {
      sumIxIt = 0;
      sumIyIt = 0;
      for(i = 0; i < BLK_HEIGHT; i++) 
      {
          for(j = 0; j < BLK_WIDTH; j++) 
          {
            x = gradX[k*gradStride*BLK_HEIGHT + i*gradStride+j];
            y = gradY[k*gradStride*BLK_HEIGHT + i*gradStride+j];
            c = im1[k*imStride*BLK_HEIGHT + i*imStride+j];
            p = im2[k*imStride*BLK_HEIGHT + i*imStride+j];
            diff = c-p;
            sumIxIt += x*diff;
            sumIyIt += y*diff;
          }
      }
      IxIt[k] = sumIxIt;
      IyIt[k] = sumIyIt;
    }

    return;

}


