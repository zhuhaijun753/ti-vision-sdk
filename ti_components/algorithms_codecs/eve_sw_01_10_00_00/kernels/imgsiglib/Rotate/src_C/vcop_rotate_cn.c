/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_rotate, rotate function for the VICP library.               */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_rotate_cn                                                  */
/*     (                                                                    */
/*          uint8 *in,                                                      */
/*          uint8 *inter,                                                   */
/*          uint8 *out,                                                     */
/*          int   IMG_W,                                                    */
/*          int   IMG_H,                                                    */
/*          int   OUT_W,                                                    */
/*          int   OUT_H,                                                    */
/*          int   COMP_W,                                                   */
/*          int   COMP_H,                                                   */
/*          int   in_type,                                                  */
/*          int   inter_type                                                */
/*          int   out_type,                                                 */
/*          int   angle,                                                    */
/*          int   rnd_shift                                                 */
/*      );                                                                  */
/*                                                                          */
/*     *in        :  Pointer to an input array of "in_type".                */
/*     *inter     :  Pointer to intermediate array of "inter_type".         */
/*     *out       :  Pointer to output array of "out_type".                 */
/*     IMG_W      :  Width of input image in pixels.                        */
/*     IMG_H      :  Height of the input image in pixels.                   */
/*     OUT_W      :  Width of the output image in pixels.                   */
/*     OUT_H      :  Height of the input image in pixels.                   */
/*     COMP_W     :  The compute width over which rotate values are found.  */
/*     COMP_H     :  The compute height for rotate function.                */
/*     in_type    :  0 - BYTE,  1 - SHORT                                   */
/*     inter_type :  0 - BYTE,  1 - SHORT                                   */
/*     out_type   :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT             */
/*     angle      :  Angle of rotation, can be 90, 180 or 270.              */
/*     rnd_shift  :  Amount of rounding and shifting on output data.        */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the rotate over M X N pixels of the image. The image is     */
/*     split into blocks of size M X N and rotated.                         */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     M and N are assumed to be multiples of 8.                            */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;

#define TRANSPOSE_SIZE  (8)

void rotate
(
     uint8 *in, 
     uint8 *inter,
     uint8 *out,
     int IMG_W,
     int IMG_H,
     int OUT_W,
     int OUT_H,
     int COMP_W, 
     int COMP_H,
     int in_type,
     int inter_type,
     int out_type,
     int angle, 
     int rnd_shift
)
{
    int i, j, m;
    int dataAddr_inter;
    
    /*-----------------------------------------------------------*/
    /* For 90 degree rotation, we have two load/stores.          */
    /* This translates to 2 VLOOPs on VCOP.                      */
    /*-----------------------------------------------------------*/

    if (angle == 90)
    {
        /*-------------------------------------------------------*/
        /* First we do a transpose.                              */
        /*-------------------------------------------------------*/

        for ( i = 0; i <  COMP_W; i++)
        {
            for( j = 0; j < COMP_H; j++)
            {
                    inter[ (i * COMP_H) + j] = in[ (j * IMG_W) + i];
            }
        }

        /*-------------------------------------------------------*/
        /* Next, we switch the rows, topmost with the lowermost  */
        /* and so on and so forth.                               */
        /*-------------------------------------------------------*/

        out = out + (COMP_W - 1) * COMP_H;

        for ( i = 0; i <  COMP_W; i++)
        {
            for( j = 0; j < COMP_H; j++)
            {
                out[ ( -i * COMP_H) + j] = inter[ (i * COMP_H) + j];
            }
        }

    }
    
    /*-----------------------------------------------------------*/
    /* For 180 degree rotation, do the following.                */
    /*-----------------------------------------------------------*/
    
    else if (angle == 180)
    {

        out = out + (COMP_W * COMP_H - 1);

        for ( j = 0; j <  COMP_H; j++)
        {
            for( i = 0; i < COMP_W; i++)
            {
                out[  (-j * COMP_W) - i] = in[ ((j * IMG_W) + i)];
         
            }
        }
    }
    
    /*-----------------------------------------------------------*/
    /* For 270 degree rotation, do the following.                */
    /*-----------------------------------------------------------*/


    else if (angle == 270)
    {
        out = out + COMP_H - 1;

        for ( i = 0; i <  COMP_W; i++)
        {
            for( j = 0; j < COMP_H; j++)
            {
                out[ (j * COMP_H) - i] = in[(i * IMG_W) + j];
            }
        }
    }

    return;
}
