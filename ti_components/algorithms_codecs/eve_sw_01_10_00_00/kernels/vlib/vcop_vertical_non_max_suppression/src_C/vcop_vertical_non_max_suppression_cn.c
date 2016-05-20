/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : vcop_vertical_non_max_suppression: natural C                  */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include "stdlib.h"
#include "math.h"

#include "vcop_vertical_non_max_suppression_cn.h"
#define MAX_CORNERS 2048

void vertical_nms(unsigned int* corners, 
                  unsigned int num_corners, 
                  unsigned short* nms_x_score,
                  unsigned short* nms_id,
                  unsigned short* nms_y_score,
                  unsigned short* nms_y_corners,
                  unsigned int* nms_corners, 
                  unsigned int* nms_score)
{
  int i;
  unsigned int top_xy, center_xy, bottom_xy;
  unsigned int xy0, xy1;
  unsigned short top_scr, center_scr, bottom_scr;
  unsigned short score0, score1;
  unsigned short *nms_x, *nms_y;
  int Vsf1, Vsf2;
  int Vnf1, Vnf2;
  int Vf1, Vf2, Vf;
  int id = 0;

  nms_x = nms_y_corners;
  nms_y = nms_y_corners + MAX_CORNERS;
  //unpack X, Y and ID
  for(i=0; i<num_corners; i++)
  {
    nms_x[i] = (corners[i] & 0xFFC00000) >> 22; // x
    nms_y[i] = (corners[i] & 0x003FF000) >> 12; // y
    nms_id[i] = (corners[i] & 0x00000FFF); // id
  }
  
  // re-arrange score based on sorted X
  for(i=0; i<num_corners; i++)
  {
    nms_y_score[i] = nms_x_score[nms_id[i]];
  }

  xy0 = (nms_x[0] << 16) | (nms_y[0]);
  xy1 = (nms_x[1] << 16) | (nms_y[1]);
  score0 = nms_y_score[0];
  score1 = nms_y_score[1];

  Vnf1 = ((xy0+1) == xy1);
  Vsf1 = (score0 <= score1);
  Vf1 = Vnf1 & Vsf1;
  Vf = 1 - Vf1;
  nms_corners[0] = (nms_x[0] << 16) | (nms_y[0]);

  if(Vf1)
    nms_score[0] = 0;
  if(Vf)
    nms_score[0] = (nms_y_score[0] << 16) | (id);

  id++ ;

  // Apply NMS in Y direction
  for(i=1; i<num_corners-1; i++)
  {
    top_xy = (nms_x[i-1] << 16) | ( nms_y[i-1]);
    center_xy = (nms_x[i] << 16) | (nms_y[i]);
    bottom_xy = (nms_x[i+1] << 16) | (nms_y[i+1]);

    top_scr = nms_y_score[i-1];
    center_scr = nms_y_score[i];
    bottom_scr = nms_y_score[i+1];

    top_xy += 1;
    bottom_xy -= 1;

    Vnf1 = (top_xy == center_xy);
    Vnf2 = (bottom_xy == center_xy);

    Vsf1 = (center_scr <= top_scr);
    Vsf2 = (center_scr <= bottom_scr);

    Vf1 = Vnf1 && Vsf1;
    Vf2 = Vnf2 && Vsf2;

    Vf1 |= Vf2;

    Vf = 1 - Vf1;

    nms_corners[i] = (nms_x[i] << 16) | (nms_y[i]);

    if(Vf1)
    {
      nms_score[i] = 0;
    }

    if(Vf)
    {
      nms_score[i] = (center_scr << 16) | id;
    }
    id++;
  }

  xy0 = (nms_x[i-1] << 16) | (nms_y[i-1]);
  xy1 = (nms_x[i] << 16) | (nms_y[i]);
  score0 = nms_y_score[i-1];
  score1 = nms_y_score[i];

  Vnf1 = ((xy0+1) == xy1);
  Vsf1 = (score0 <= score1);
  Vf1 = Vnf1 & Vsf1;
  Vf = 1 - Vf1;
  nms_corners[i] = (nms_x[i] << 16) | (nms_y[i]);

  if(Vf1)
    nms_score[i] = 0;
  if(Vf)
    nms_score[i] = (nms_y_score[i] << 16) | (id);

}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_vertical  _non_max_suppression_cn.c                      */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/

