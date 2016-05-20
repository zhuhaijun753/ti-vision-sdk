/*==========================================================================*/ 
/*     TEXAS INSTRUMENTS, INC.                                              */ 
/*                                                                          */ 
/*     NAME                                                                 */ 
/*     vcop_vec_bin_image_erode_single_pixel_cn                             */ 
/*                                                                          */ 
/*     USAGE                                                                */ 
/*     This routine is C-callable and can be called as:                     */ 
/*                                                                          */ 
/*     void vcop_vec_bin_image_erode_single_pixel_cn                        */ 
/*     (                                                                    */ 
/*         unsigned int in[],                                               */ 
/*         unsigned int out[],                                              */ 
/*         int           cols,                                              */ 
/*         int           pitch,                                             */ 
/*         int           height                                             */ 
/*     )                                                                    */ 
/*                                                                          */ 
/*                                                                          */ 
/*     in        :  32-bit packed input binary image                        */ 
/*     out       :  32-bit packed output binary image                       */ 
/*     cols      :  Number of columns in the binary image                   */ 
/*     pitch     :  Pitch of the binary image                               */ 
/*     height    :  Number of rows in the binary image                      */ 
/*                                                                          */ 
/*     Returns :  None or void.                                             */ 
/*                                                                          */ 
/*                                                                          */ 
/*     DESCRIPTION                                                          */ 
/*             This routine accepts 32-bit packed input binary image and    */ 
/*     performs erosion of isolated pixels (ON pixels that do not have any  */ 
/*     ON neighbors) and outputs a 32-bit packed output binary image.       */ 
/*                                                                          */ 
/*     ASSUMPTIONS                                                          */ 
/*     The number of columns in the input binary image should be a          */ 
/*     multiple of 32.                                                      */ 
/*                                                                          */ 
/*==========================================================================*/ 
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */ 
/*                      All Rights Reserved                                 */ 
/*==========================================================================*/ 

#include <stdio.h>
#include <stdlib.h>

#include "vcop_vec_bin_image_erode_single_pixel_c.h"

void vcop_vec_bin_image_erode_single_pixel_cn                        
(                                                                    
    unsigned int in[],                                               
    unsigned int out[],                                              
    int cols,                                                        
    int pitch,                                                       
    int height                                                       
)
{
    int i4,i3;
    unsigned int r,in00, in01, in10, in11, in20, in21; 


    for(i3 = 0; i3 < height; i3 ++ )
    {
        for (i4 = 0; i4 < cols/32; i4 ++)
        {
            in00 = in[i4+i3*pitch/32];                  
            in01 = in[i4+i3*pitch/32+1];                
            in10 = in[i4+i3*pitch/32+ pitch/32];        
            in11 = in[i4+i3*pitch/32+ pitch/32 +1];     
            in20 = in[i4+i3*pitch/32+ pitch/16];        
            in21 = in[i4+i3*pitch/32+ pitch/16+1];      

            r = 0;
            r |= in00;
            r |= (in00<<1  | in01 >>31);
            r |= (in00<<2  | in01 >>30);
            r |= in10;
            r |= (in10<<2  | in11 >>30);
            r |= in20;
            r |= (in20<<1  | in21 >>31);
            r |= (in20<<2  | in21 >>30);

           out[i4+i3*pitch/32] =  (in10<<1  | in11 >>31) & r ; 
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_single_pixel_c.c                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


