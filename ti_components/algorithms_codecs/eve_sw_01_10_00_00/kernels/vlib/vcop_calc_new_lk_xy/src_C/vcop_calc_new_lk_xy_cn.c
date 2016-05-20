/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_calc_new_lk_xy_cn.c                                             */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference for the vcop_calc_new_lk_xy_cn  kernel   */
/*   This routine accepts tesnsor matrix and the IxIt/IyIT matrix to        */
/*   calculate the new x and y co-oridinates                                */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VCOP_LK_PATCH_WIDTH          (7) // 7x7
#define Q_FORMAT_FOR_ERR_VALUE       (10)

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
  )
{
  int k;
  short vx;
  short vy;

  int valid_left_pels    = ((VCOP_LK_PATCH_WIDTH/2+1) << qFormatePel);
  int valid_right_pels   = (((searchRange*2) + VCOP_LK_PATCH_WIDTH- VCOP_LK_PATCH_WIDTH/2 -2) << qFormatePel);
  int valid_top_pels     = valid_left_pels;
  int valid_bot_pels     = valid_right_pels;
  short errTh = minErrValue >> (Q_FORMAT_FOR_ERR_VALUE - qFormatePel);
  *numValidPoints = 0;

    for(k = 0; k < n; k++)
    {
      if(currValidPoints[k])
      {
        if(X[k]< valid_left_pels  ||   X[k]>= valid_right_pels || Y[k]< valid_top_pels || Y[k] >= valid_bot_pels)
        {
          continue;
        }
        vx = (((long long)IxIt[k] * Iy2[2*k]) >> (Iy2[2*k+1]*-1)) - (((long long)IyIt[k] * Ixy[2*k]) >> (Ixy[2*k+1]*-1));
        vy = (((long long)IyIt[k] * Ix2[2*k]) >> (Ix2[2*k+1]*-1)) - (((long long)IxIt[k] * Ixy[2*k]) >> (Ixy[2*k+1]*-1));

        if(vx <= -valid_left_pels)
            vx = -valid_left_pels;

        if(vx >= valid_left_pels)
            vx = valid_left_pels;

        if(vy <= -valid_left_pels)
            vy = -valid_left_pels;

        if(vy >= valid_left_pels)
            vy = valid_left_pels;
        
        X[k]        += vx;
        Y[k]        += vy;
        frameXY[2*k]   += vx;
        frameXY[2*k+1] += vy;
        if((abs(vy) > errTh) || (abs(vx) > errTh))
        {
          (*numValidPoints)++;
        }
        else
        {
          currValidPoints[k] = 0;
        }
#if 0
    int max_pels           = (((searchRange*2) + VCOP_LK_PATCH_WIDTH) << qFormatePel);
    if(X[k] < 0  ||   X[k] >= max_pels || Y[k] < 0 || Y[k] >= max_pels)
    {
      X[k]           -= vx;
      Y[k]           -= vy;
      frameXY[2*k]   -= vx;
      frameXY[2*k+1] -= vy;
    }
#endif
      }
    }

    return;

}
