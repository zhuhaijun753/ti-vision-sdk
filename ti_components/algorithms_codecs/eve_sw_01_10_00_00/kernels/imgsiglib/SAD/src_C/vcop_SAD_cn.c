
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

//#define __PRINT__   1

void vcop_SAD_cn
(
    signed char   *in, 
    signed char   *ref,
    signed short  *sad,
    signed short  *min_sad,
    int           blk_w,      
    int           blk_h,      
    int           in_w,      
    int           in_h,       
    int           ref_w,      
    int           ref_h,      
    int           offset_horz,
    int           offset_vert,
    int           steps_horz, 
    int           steps_vert,
    int           no_input_blks_horz,
    int           no_input_blks_vert
)
{
    int m, n, i, j, k, l;
    int cnt, sad_index;
    int loc_i, loc_j;
    int total_ref_arrays;
    
    /*-------------------------------------------------------------------*/
    /* Grab a new reference block to be compared to input block.         */
    /*-------------------------------------------------------------------*/

    total_ref_arrays = steps_horz * steps_vert;

    sad_index = 0;
    for ( n = 0; n < no_input_blks_vert; n++) //in_h
    {
        for ( m = 0; m < no_input_blks_horz; m++) //in_w
        {
#ifdef __PRINT__
            printf("--- New input block ---\n\n");
#endif
            cnt = ((n * no_input_blks_horz) + m ) * total_ref_arrays;

            /*-----------------------------------------------------------*/
            /* Grab a new reference block to be compared to input block. */
            /*-----------------------------------------------------------*/

            for ( j = 0; j < steps_vert; j++)
            {               
                for ( i = 0; i < steps_horz; i++)
                {
                    sad_index = cnt + (j * steps_horz) + i;
                    sad[sad_index] = 0;

                    for ( l = 0; l < blk_h; l++)
                    {
                        for ( k = 0; k < blk_w; k++)
                        {
                            sad[sad_index]  += abs( in[((n + l) * in_w) + (m + k)] - ref[(((j * offset_vert) + l) * ref_w) + ((i * offset_horz) + k)] );
                        }
                    }
#ifdef __PRINT__
                    printf("0x%3.3x, ", sad[sad_index] );
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
#ifdef __PRINT__
        printf("\n");
#endif
    }
    
    /*-------------------------------------------------------------------*/
    /* Identify the minimum SAD value and its location                   */
    /*-------------------------------------------------------------------*/

    for ( n = 0; n < no_input_blks_vert; n++) //in_h
    {
        for ( m = 0; m < no_input_blks_horz; m++) //in_w
        {
            cnt = ((n * no_input_blks_horz) + m ) * total_ref_arrays;

            min_sad[(n * no_input_blks_horz) + m] = 0x7FFF;

            for ( j = 0; j < steps_vert; j++)
            {
                for ( i = 0; i < steps_horz; i++)
                {
                    sad_index = cnt + (j * steps_horz) + i;

                    if ( sad[sad_index] < min_sad[(n * no_input_blks_horz) + m])
                    {
                        min_sad[(n * no_input_blks_horz) + m] = sad[sad_index];
                        loc_i = i * offset_horz;
                        loc_j = j * offset_vert;
                    }
                }
            }
#ifndef __PRINT__
            printf(" \n Minimum SAD = is  0x%3.3x and located at (%d, %d)\n\n", min_sad[(n * no_input_blks_horz) + m], loc_i, loc_j );
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
