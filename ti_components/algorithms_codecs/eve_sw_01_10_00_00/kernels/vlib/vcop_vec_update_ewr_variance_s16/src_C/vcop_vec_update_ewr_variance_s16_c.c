/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_update_ewr_variance_s16_cn                                  */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_update_ewr_variance_s16_cn                             */
/*     (                                                                    */
/*         short         * currentVar,                                      */
/*         short         * currentMean,                                     */
/*         unsigned char * newestData,                                      */
/*         unsigned int  * foreground,                                      */
/*         unsigned short  weight,                                          */
/*         unsigned int    frameSize                                        */
/*     )                                                                    */
/*                                                                          */
/*     currentVar   :  EW running variance buffer to be updated (SQ12.3)    */
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
/*     variance statistics. The running variance is not updated for         */
/*     foreground pixels.                                                   */
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

//#include "vcop_vec_update_ewr_variance_s16_c.h"

void vcop_vec_update_ewr_variance_s16_cn
(
    short         * currentVar,     
    short         * currentMean, 
    unsigned char * newestData, 
    unsigned int  * foreground, 
    unsigned short  weight, 
    unsigned int    frameSize    
)
{

    unsigned int i4;
    unsigned char shiftRight, updateFlag;
    unsigned int mask32bit;
    unsigned int offset2   = 0;
    unsigned short weight2 = (weight & 0x3fff) << 1;
    
    short diff;
    int temp1,temp4;
    short temp2,temp3,temp5,temp6;
    
    for (i4 = 0; i4 < frameSize; i4++) 
    {
    
       shiftRight = i4 & 31;
       
       if (!shiftRight) 
       mask32bit = foreground[offset2++];
       
       updateFlag = (mask32bit >> (31-shiftRight)) & 1;
       
       if (updateFlag == 0) 
       {
           diff = (newestData[i4] << 7) - currentMean[i4];
           temp1 = (diff * diff) ;
           temp2 = temp1 >> 15;
           temp3 = temp2 - (currentVar[i4] >> 3);
           temp4 = (temp3 * weight2) ; 
           temp5 = temp4 >> 15; 
           temp6 = abs(currentVar[i4] + temp5); 
           
           currentVar[i4] = temp6;
       }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_variance_s16_c.c                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


