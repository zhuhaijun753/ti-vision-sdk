/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_update_ewr_mean_s16_kernel                                  */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_update_ewr_mean_s16                                    */
/*     (                                                                    */
/*         __vptr_int16   currentMean,                                      */
/*         __vptr_uint8   newestData,                                       */
/*         __vptr_uint8   foreground,                                       */
/*         unsigned short weight,                                           */
/*         unsigned short weight_neg,                                       */
/*         unsigned int   frameSize                                         */
/*      )                                                                   */
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

#define ELEMSZ          sizeof(*newestData)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define weight_neg1      (2^16- 1 - weight)

void vcop_vec_update_ewr_mean_s16
(
    __vptr_int16  currentMean,
    __vptr_uint8  newestData, 
    __vptr_uint8  foreground, 
    unsigned short weight, 
    unsigned short weight_neg, 
    unsigned int frameSize    
)
{
    __vector R0,R2,R3,R1,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15; 
       
    R12 = -9; 
    R13 = -16; 
    R4 = weight;
    R5 = weight_neg; 
    R14 =1;
    R15 = 0xFF;
    
    for(int I1 = 0; I1 < frameSize/VCOP_SIMD_WIDTH; I1 ++ )
    {
         __agen Addr1,Addr2,Addr3;
         
        Addr1 = I1*VECTORSZ;
        Addr2 = I1*VECTORSZ*2;
        Addr3 = I1;

        R1 = foreground[Addr3];    
        R2 = newestData[Addr1];  
        R3 = currentMean[Addr2]; 
                
        R6 = R4 * R2  ;         
        R7 = R5 * R3  ;         
        
        R8 = R6 << R12;       
        R9 = R7 << R13;       

        R10 = R8 + R9 ;         
        R6  = R1 ^ R15;

        R2 = unpack(R6,R14);
        
        currentMean[Addr2] = R10.predicate(R2);
    }        
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_mean_s16_kernel.k                     */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


