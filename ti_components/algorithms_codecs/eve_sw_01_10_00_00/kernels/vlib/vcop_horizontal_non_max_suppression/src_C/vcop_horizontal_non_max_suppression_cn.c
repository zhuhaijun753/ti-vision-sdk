/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : vcop_horizontal_non_max_suppression: natural C                */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2103 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include "stdlib.h"
#include "math.h"
#define LSHIFT6  6
#define LSHIFT12  12

#include "../inc/vcop_horizontal_non_max_suppression_cn.h"

void horizontal_nms(unsigned int* corners, unsigned int num_corners, unsigned short* scores, unsigned int* nms_x_corners, unsigned short* nms_x_score)
{
    int i;
    int left_xy, right_xy, center_xy;
    int right_scr, center_scr, left_scr;
    int Vsf1, Vsf2;
    int Vnf1, Vnf2;
    int Vf1, Vf2;
    int Vconst = 65536;
    int Vmask1 = 0xFFFF0000;
    int Vmask2 = 0x0000FFFF;
    int x, y;

    for(i=0; i<1;i++)
    {
        x = corners[0] & Vmask1;
        y = corners[0] & Vmask2;

        /* Read 2nd element */
        left_xy = corners[0] + Vconst;

        Vnf1 = (left_xy == corners[1]);
        Vsf1 = (scores[0] <= scores[1]);

        Vf1 = Vnf1 & Vsf1;

        nms_x_corners[0] = (x << LSHIFT6) | (y << LSHIFT12) | 0;
        if(Vf1)
          nms_x_score[0] = 0;
        else
          nms_x_score[0] = scores[0];

        x = corners[num_corners-1] & Vmask1;
        y = corners[num_corners-1] & Vmask2;

        /* Read last but 1 element and add constant */
        left_xy = corners[num_corners-2] + Vconst;

        Vnf1 = (left_xy == corners[num_corners-1]);
        Vsf1 = (scores[num_corners-1] <= scores[num_corners-2]);

        Vf1 = Vnf1 & Vsf1;

        nms_x_corners[num_corners-1] = ( x << LSHIFT6) | ( y << LSHIFT12) | (num_corners-1);
        if(Vf1)
          nms_x_score[num_corners-1] = 0;
        else
          nms_x_score[num_corners-1] = scores[num_corners-1];
    }
    // first do the NMS is X direction
    for(i=1; i<(num_corners-1); i++) // i = 1 to num_corners-1 since we need 1 pixel border in each side
    {
        left_xy = corners[i-1];
        center_xy = corners[i];
        right_xy = corners[i+1];

        left_scr = scores[i-1];
        center_scr = scores[i];
        right_scr = scores[i+1];

        left_xy += Vconst;
        right_xy -= Vconst;

        Vnf1 = (left_xy == center_xy);
        Vnf2 = (right_xy == center_xy);

        Vsf1 = (center_scr <= left_scr);
        Vsf2 = (center_scr <= right_scr);

        Vf1 = Vnf1 & Vsf1;
        Vf2 = Vnf2 & Vsf2;

        Vf1 |= Vf2;

        x = center_xy & Vmask1;
        y = center_xy & Vmask2;

        // pack X, Y and ID: 10 bit X, 10 bit Y and 12 bit ID
        nms_x_corners[i] = (x << LSHIFT6) | (y << LSHIFT12) | (i);
        if(Vf1)
            nms_x_score[i] = 0;
        else
            nms_x_score[i] = scores[i];

    }

}


/*----------------------------------------------------------------------------*/
/* End of file: vcop_horizontal_non_max_suppression_cn.c                      */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/

