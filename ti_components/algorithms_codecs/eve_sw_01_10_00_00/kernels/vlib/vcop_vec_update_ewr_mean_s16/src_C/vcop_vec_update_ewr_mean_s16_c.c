/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_update_ewr_mean_s16_cn                                      */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_update_ewr_mean_s16_cn                                 */
/*     (                                                                    */
/*         short         * currentMean,                                     */
/*         unsigned char * newestData,                                      */
/*         unsigned int  * foreground,                                      */
/*         short           weight,                                          */
/*         unsigned int    frameSize                                        */
/*     )                                                                    */
/*                                                                          */
/*     currentMean  :  EW running mean buffer to be updated (SQ8.7)         */
/*     newestData   :  Most recent luma buffer                              */
/*     foreground   :  Foreground mask buffer                               */
/*     weight       :  Weight of the newest luma                            */
/*     frameSize    :  Number of pixels to process                          */
/*                                                                          */
/*     Returns      :  None or void.                                        */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine updates the exponentially weighted running      */
/*     mean statistics. The running mean is not updated for foreground      */
/*     pixels.                                                              */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     While The C code does not have any assumptions on the length of      */
/*     the arrays, the assembly code assumes that frameSize the length      */
/*     of the arrays is a multiple of 8.                                    */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "vcop_vec_update_ewr_mean_s16_c.h"

void vcop_vec_update_ewr_mean_s16_cn
(
    short         * currentMean, //SQ8.7
    unsigned char * newestData, 
    unsigned int  * foreground, 
    unsigned short  weight,      //SQ0.15
    unsigned int    frameSize    
)
{
    unsigned int i4 ;
    unsigned int offset2=0;
    unsigned short temp1;
    short temp2, temp3;
    unsigned short weight2;
    unsigned char shiftRight, updateFlag;
    unsigned int mask32bit;
        
    weight2 = 2^16-1 - weight;
    
    for (i4 = 0; i4 < frameSize; i4++) 
    {
        shiftRight = i4 & 31;
        
        if (!shiftRight) 
        mask32bit = foreground[offset2++];
        
        updateFlag = (mask32bit >> (31-shiftRight)) & 1;
        
        if (updateFlag == 0) 
        {
            temp1 = (weight  * newestData[i4] )  >> 9 ; 
                                              //0.16 x 8.0 = 8.16 >> 9 = 8.7
            temp2 = (weight2 * currentMean[i4])  >> 16; 
                                              //0.16 x 8.7 = 8.23 >> 16 = 8.7
            temp3 = (short)temp1 + temp2;
            currentMean[i4] = temp3;
        }
    }        
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_mean_s16_c.c                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


