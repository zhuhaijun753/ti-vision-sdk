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
/*         short * currentVar,                                              */
/*         short * currentMean,                                             */
/*         unsigned char * newestData,                                      */
/*         unsigned int * foreground,                                       */
/*         short weight,                                                    */
/*         unsigned int frameSize                                           */
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

#ifndef _vcop_vec_update_ewr_variance_s16_CN
#define _vcop_vec_update_ewr_variance_s16_CN  1

void vcop_vec_update_ewr_variance_s16_cn
(
    short * currentVar,     
    short * currentMean, 
    unsigned char * newestData, 
    unsigned int * foreground, 
    unsigned short weight, 
    unsigned int frameSize    
);

#endif

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_variance_s16_c.h                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



