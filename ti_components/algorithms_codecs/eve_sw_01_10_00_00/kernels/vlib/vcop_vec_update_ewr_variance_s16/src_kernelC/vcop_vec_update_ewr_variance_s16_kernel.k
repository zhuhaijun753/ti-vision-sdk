/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_update_ewr_variance_s16_kernel                              */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_update_ewr_variance_s16                                */
/*     (                                                                    */
/*         __vptr_int16   currentVar,                                       */
/*         __vptr_int16   currentVar_out,                                   */
/*         __vptr_int16   currentMean,                                      */
/*         __vptr_uint8   newestData,                                       */
/*         __vptr_uint8   foreground,                                       */
/*         unsigned short weight,                                           */
/*         unsigned short weight2,                                          */
/*         unsigned int   frameSize                                         */
/*      )                                                                   */
/*                                                                          */
/*     currentVar     :  EW running variance - input buffer (SQ12.3)        */
/*     currentVar_out :  EW running variance - updated buffer(SQ12.3)       */
/*     currentMean    :  EW running mean buffer to be updated (SQ8.7)       */
/*     newestData     :  Most recent luma buffer                            */
/*     foreground     :  Foreground mask buffer                             */
/*     weight         :  Weight of the newest luma                          */
/*     frameSize      :  Number of pixels to process                        */
/*                                                                          */
/*     Returns        :  None or void.                                      */
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

#define ELEMSZ          sizeof(*newestData)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_vec_update_ewr_variance_s16
(
    __vptr_int16 currentVar,
    __vptr_int16 currentVar_out,     
    __vptr_int16 currentMean, 
    __vptr_uint8  newestData, 
    __vptr_uint8  foreground, 
    unsigned short weight, 
    unsigned short weight2, 
    unsigned int frameSize    
)
{
     __vector R0,R2,R3,R1,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15,fg,R16; 
     
    R13 = 7;
    R14 = -3; 
    R15 = -15;
    R12 = weight2;
    R11 = 1;
    R16 = 0xFF;

    for(int I1 = 0; I1 < frameSize/VCOP_SIMD_WIDTH; I1++ )
    {

        __agen Addr1,Addr2,Addr3;
         
        Addr1 = I1*VECTORSZ;
        Addr2 = I1*VECTORSZ*2;
        Addr3 = I1;

        fg  = foreground  [Addr3];     
        R8  = newestData  [Addr1];                       
        R9  = currentMean [Addr2];                      
        R10 = currentVar  [Addr2];                      
        
        R7 = R8  << R13;                                            
        R3 = R10 << R14;
                                                                           
        R7 = R7 - R9;                                                      
        R5 = R16 ^ fg;
                                                                           
        R1 = R7 * R7;                                                      
        R4 = unpack(R5,R11);                                                                           
        
        R2 = R1 << R15;   
                                                                                                           
        R3 = R2 - R3;                                               
        
        R2 = R3 * R12;
        
        R1 = R2 << R15; 
        
        R6 = R10 + R1; 
        
        R6 = abs(R6);

        currentVar[Addr2] = R6.predicate(R4);
     }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_variance_s16_kernel.k                 */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


