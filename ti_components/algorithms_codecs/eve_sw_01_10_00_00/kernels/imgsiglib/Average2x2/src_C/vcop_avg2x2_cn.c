/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_average2x2, average2x2 filter for the VICP library.         */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_average2x2_cn                                              */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *scratch1,                                        */
/*          signed char   *out,                                             */
/*          int           w_input,                                          */
/*          int           w_comp,                                           */
/*          int           blk_w,                                            */
/*          int           blk_h,                                            */
/*          int           shift,                                            */
/*          int           type_input,                                       */
/*          int           type_output                                       */
/*     )                                                                    */
/*                                                                          */
/*                                                                          */
/*     *in        :  Pointer to an input array of "type_input".             */
/*     *scratch1  :  Pointer to intermediate array.                         */
/*     *out       :  Pointer to output array of "type_output".              */
/*     w_input    :  Width of the input image in pixels.                    */
/*     w_comp     :  Width of the compute block in pixels.                  */
/*     blk_w      :  The block width for computing the average.             */
/*     blk_h      :  The compute height for computing average.              */
/*     shift      :  The no. of elements in the block, to compute average.  */
/*     type_input :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT             */
/*     type_output:  0 - BYTE,  1 - SHORT                                   */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the average2x2 over a block of the image.                   */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include "../inc/vcop_avg2x2_cn.h"

void vcop_average2x2_cn
(
    unsigned char  *in, 
    unsigned char  *out,
    int            in_w, 
    int            blk_w,
    int            blk_h,
    int            shift,
    int            type_input,
    int            type_output
)
{
    
    int i, j, k, prev;

        for ( j = 0; j < blk_w; j++ )
        {
            prev = 0;
            for ( i  = 0; i < blk_h; i++)
            {
                out[(i * blk_w) + j] = (prev + in[(i * in_w) + j] + in[(i * in_w) + j + 1]) >> 2;
                prev = in[(i * in_w) + j] + in[(i * in_w) + j + 1];
            }
        }                
                

   return;
}
