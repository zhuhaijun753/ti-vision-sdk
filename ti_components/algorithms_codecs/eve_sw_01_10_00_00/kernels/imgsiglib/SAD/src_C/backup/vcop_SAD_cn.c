/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_SAD, SAD compute for the VICP library.                      */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_SAD_cn                                                     */
/*     (                                                                    */
/*          signed char  *in_data,                                          */
/*          signed char  *ref_data,                                         */
/*          signed char  *sad,                                              */
/*          int           blk_width,                                        */
/*          int           blk_height,                                       */
/*          int           in_width,                                         */
/*          int           in_height,                                        */
/*          int           ref_width,                                        */
/*          int           ref_height,                                       */
/*          int           offset_horz,                                      */
/*          int           offset_vert,                                      */
/*          int           step_horz,                                        */
/*          int           step_vert,                                        */
/*      );                                                                  */
/*                                                                          */
/*     *in         :  Pointer to input array.                               */
/*     *ref        :  Pointer to reference data array.                      */
/*     *sad        :  Pointer to sad output array.                          */
/*      blk_w      :  Block width over which matching is done.              */
/*      blk_h      :  Block height over which matching is done.             */
/*      in_w       :  Width of the input region being matched.              */
/*      in_h       :  Height of the input region being matched.             */
/*      ref_w      :  Width of the reference region being matched.          */
/*      ref_h      :  Height of the reference region being matched.         */
/*      offset_horz:  Horizontal offset for pixels to be skipped before     */
/*                    next match.                                           */
/*      offset_vert:  Horizontal offset for pixels to be skipped before     */
/*                    next match.                                           */
/*      steps_horz :  Total matches in horizontal direction.                */
/*      steps_vert :  Total matches in vertical direction.                  */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This function accepts pointers to a input region "in", and   */
/*     computes the SAD over (blk_w X blk_h) block of the image.            */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <stdlib.h>

#include "../inc/EVE_SAD_cn.h"

#define __PRINT__   1

void vcop_SAD_cn
(
    signed char *in, 
    signed char *ref,
    signed int  *sad,
    signed int  *min_sad,
    int         blk_w,      
    int         blk_h,      
    int         in_w,      
    int         in_h,       
    int         ref_w,      
    int         ref_h,      
    int         offset_horz,
    int         offset_vert,
    int         steps_horz, 
    int         steps_vert
)
{
    int m, n, i, j, k, l;
    int cnt, sad_index;
    int loc_i, loc_j;
    int total_ref_arrays;
    
    /*-------------------------------------------------------------------*/
    /* Grab a new reference block to be compared to input block.         */
    /*-------------------------------------------------------------------*/

    total_ref_arrays = (ref_w * ref_h)/(offset_vert * offset_horz);

    sad_index = 0;
    for ( n = 0; n < in_h - 2; n++) //in_h
    {
        for ( m = 0; m < in_w - 2; m++) //in_w
        {
#ifdef __PRINT__
            printf("--- New input block ---\n\n");
#endif
            cnt = ((n * in_w) + m ) * total_ref_arrays;

            /*-----------------------------------------------------------*/
            /* Grab a new reference block to be compared to input block. */
            /*-----------------------------------------------------------*/

            for ( j = 0; j < (int)(ref_h/offset_vert); j += offset_vert)
            {
                for ( i = 0; i < (int)(ref_w/offset_horz); i += offset_horz)
                {
                    sad_index = cnt + (j * (ref_w/offset_horz) ) + i;
                    sad[sad_index] = 0;

                    for ( l = 0; l < blk_h; l++)
                    {
                        for ( k = 0; k < blk_w; k++)
                        {
                            sad[sad_index]  += abs( in[((n + l ) * in_w) + (m + k)] - ref[(j + l) * ref_w + (i + k)] );

                        }
                    }
#ifdef __PRINT__
                    printf("0x%3.3x, ", sad[sad_index] );
#endif
                }
#ifdef __PRINT__
                printf("\n");
#endif
            }
#ifdef __PRINT__
            printf("\n");
#endif
        }
#ifdef __PRINT__
        printf("\n");
#endif
    }
    
    /*-------------------------------------------------------------------*/
    /* Identify the minimum SAD value and its location                   */
    /*-------------------------------------------------------------------*/

    for ( n = 0; n < in_h - (blk_h - 1); n++) //in_h
    {
        for ( m = 0; m < in_w - (blk_w - 1); m++) //in_w
        {
            cnt = ((n * in_w) + m ) * total_ref_arrays;
            min_sad[(n * (in_w - blk_w + 1)) + m] = 0xAAAA;

            for ( j = 0; j < (int)(ref_h/offset_vert); j += offset_vert)
            {
                for ( i = 0; i < (int)(ref_w/offset_horz); i += offset_horz)
                {
                    sad_index = cnt + (j * (ref_w/offset_horz) ) + i;

                    if ( sad[sad_index] < min_sad[(n * (in_w - blk_w + 1)) + m])
                    {
                        min_sad[(n * (in_w - blk_w + 1)) + m] = sad[sad_index];
                        loc_i = i;
                        loc_j = j;
                    }
                }
            }
#ifdef __PRINT__

            printf(" \n Minimum SAD = is  0x%3.3x and located at (%d, %d)\n\n", min_sad[(n * (in_w - blk_w + 1)) + m], loc_i, loc_j );
#endif
        }
#ifdef __PRINT__
        printf("\n");
#endif
    }
#ifdef __PRINT__
    printf("\n");
#endif
}
