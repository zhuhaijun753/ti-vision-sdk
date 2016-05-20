
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_transparentBlt, transparentBlt for the VICP lib.            */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_transparentBlt_ushort_ushort                               */
/*     (                                                                    */
/*         unsigned short  *inrgb555_ptr,                                   */
/*         unsigned short  *back_rgb555_ptr,                                */
/*         unsigned short   transparentClr,                                 */
/*         unsigned short   in_rgb555_w,                                    */
/*         unsigned short   in_rgb555_h,                                    */
/*         unsigned short   back_rgb555_w,                                  */ 
/*         unsigned short   back_rgb555_h.                                  */
/*         unsigned short   out_w,                                          */
/*         unsigned short   out_h,                                          */
/*         unsigned short  *outptr                                          */
/*     );                                                                   */
/*                                                                          */
/*                                                                          */
/*      *inrgb555_ptr   :  Pointer to an rgb555 source array.               */
/*      *back_rgb555_ptr:  Pointer to an rgb555 background array.           */
/*      transparentBlt  :  Pointer to alpha array.                          */
/*      in_rgb555_w     :  Width of the input1 image in pixels.             */
/*      in_rgb555_h     :  Height of input1 array in pixels.                */
/*      back_rgb555_w   :  Width of the input1 image in pixels.             */
/*      back_rgb555_h   :  Height of input1 array in pixels.                */
/*      out_w           :  Width of the input1 image in pixels.             */
/*      out_h           :  Height of input1 array in pixels.                */
/*      *outptr         :  Pointer to output array.                         */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*      This routine accepts pointers to a input region and background      */
/*     and does a transparentBlt function to produce output pointed to by   */
/*     outptr, using "transparentClr" as the color that is made transparent.*/
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include "../inc/vcop_transparentBlt_c.h"


/* * * * * * * * * * * * * * * * * * * * */

void vcop_transparentBlt_ushort_ushort
( 
    unsigned short   *in_rgb555_ptr, 
    unsigned short   *back_rgb555_ptr, 
    unsigned int     transparentClr, 
    unsigned short   in_rgb555_w, 
    unsigned short   in_rgb555_h,                
    unsigned short   back_rgb555_w, 
    unsigned short   back_rgb555_h,
    unsigned short   comp_w,
    unsigned short   comp_h,
    unsigned short   out_w,
    unsigned short   out_h,
    unsigned short   *outptr             
)
{
    int I1, I2; 
    int alpha;

    int fg_pix;
    int bg_pix;

    for (I1 = 0; I1 < comp_h; I1++) 
    {
        for (I2 = 0; I2 < comp_w; I2++) 
        {
            fg_pix = in_rgb555_ptr[ (I1 * in_rgb555_w) + I2];
            bg_pix = back_rgb555_ptr[ (I1 * back_rgb555_w) + I2];

            (in_rgb555_ptr[(I1 * in_rgb555_w) + I2] == transparentClr ) ? (outptr[ (I1 * out_w) + I2] = bg_pix) : (outptr[ (I1 * out_w) + I2] = fg_pix);
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * */


