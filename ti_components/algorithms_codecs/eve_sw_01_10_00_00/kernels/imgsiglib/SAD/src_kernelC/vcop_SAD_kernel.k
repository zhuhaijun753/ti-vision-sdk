/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_SAD, SAD compute for the VICP library.                      */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This rsadine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_SAD_char_int                                               */
/*     (                                                                    */
/*          signed char  *in_data,                                          */
/*          signed char  *ref_data,                                         */
/*          signed char  *vert_sad,                                         */
/*          signed char  *vert_sad_t,                                       */
/*          signed char  *sad_array,                                        */
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
/*     *vert_sad   :  Pointer to SAD in vertical direction.                 */
/*     *vert_sad_t :  Pointer to intermediate SADs transposed.              */
/*     *sad_array  :  Pointer to SADs between one input block and ref blks. */
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
/*      steps_horz :  Total block matches in horizontal direction.          */
/*      steps_vert :  Total block matches in vertical direction.            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This kernel accepts pointers to a input region "in", and     */
/*     computes the SAD over (blk_w X blk_h) block of the image.            */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#define ELEMSZ_IN      sizeof(*in)
#define VECTORSZ_IN    (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_REF     sizeof(*ref)
#define VECTORSZ_REF   (VCOP_SIMD_WIDTH * ELEMSZ_REF)

#define ELEMSZ_OUT     sizeof(*vert_sad)
#define VECTORSZ_OUT   (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define   TRANSPOSE_WIDTH    8
#define   TRANSPOSE_WIDTH_IN_BYTES  (8 * 4)
#define   TRANSPOSE_WIDTH_IN_HW     (8 * 2)

#define   BYTES_IN_HALF_WD   2
#define   BYTES_IN_WORD      4

#define   TWOSIXTY           260 

void vcop_SAD_char_int
(
    __vptr_int8   in,            // Pointer to input array.                              
    __vptr_int8   ref,           // Pointer to reference data array.                     
    __vptr_int16  vert_sad,      // Pointer to SAD in vertical direction.                
    __vptr_int16  vert_sad_t,    // Pointer to intermediate SADs transposed.             
    __vptr_int16  sad_array,     // Pointer to SADs between one input block and ref blks.
    int           blk_w,         // Block width over which matching is done.             
    int           blk_h,         // Block height over which matching is done.            
    int           in_w,          // Width of the input region being matched.             
    int           in_h,          // Height of the input region being matched.            
    int           ref_w,         // Width of the reference region being matched.         
    int           ref_h,         // Height of the reference region being matched.        
    int           offset_horz,   // Horizontal offset for pixels to be skipped before next match.   
    int           offset_vert,   // Horizontal offset for pixels to be skipped before next match.                                         
    int           steps_horz,    // Total block matches in horizontal direction.    
    int           steps_vert     // Total block matches in vertical direction.                                         
)                                            
{                                              
 
    __vector Vsad1, Vsad2;
    __vector Vin;
    __vector Vin1, Vin2;
    __vector Vref;
    __vector Vzero;
    __vector Vout;
    
    /*---------------------------------------------------------------*/
    /* Grab a new reference block to be compared to input block.     */
    /* We will have (steps_vert * step_horz) number of columns       */
    /* in the intermediate buffer "vert_sad" at the end of          */
    /* these loops.                                                  */
    /*---------------------------------------------------------------*/
    
    for (int I1 = 0; I1 < steps_vert; I1++)
    {
        for ( int I2 = 0; I2 < steps_horz; I2++)
        {
            for ( int I3 = 0; I3 <  blk_w/VCOP_SIMD_WIDTH; I3++)
            {
                __agen interAddr;

                interAddr  =    (I1 * blk_w * steps_horz * ELEMSZ_OUT) 
                              + (I2 * blk_w * ELEMSZ_OUT) 
                              + (I3 * VCOP_SIMD_WIDTH * ELEMSZ_OUT);                    

                Vsad1 = 0;
                
                for ( int I4 = 0; I4 < blk_h ; I4++)
                {
                    __agen inAddr;
                    __agen refAddr;

                    inAddr    = (I3 * VCOP_SIMD_WIDTH * ELEMSZ_IN) + (I4 * in_w * ELEMSZ_IN);

                    refAddr   = (I1 * offset_vert * ref_w * ELEMSZ_REF) 
                              + (I2 * offset_horz * ELEMSZ_REF) 
                              + (I3 * VCOP_SIMD_WIDTH * ELEMSZ_REF) 
                              + (I4 * ref_w * ELEMSZ_REF);  
                        
                    Vin    =   in[inAddr].npt();
                    Vref   =   ref[refAddr].npt();
                    
                    Vsad1 +=   abs(Vin - Vref);
                } 
                
                /*-------------------------------------------------------*/
                /* At this point we have 8 intermediate sum of abso-     */
                /* lute differences that need to be added up again       */
                /* to compute the final SAD result in the next VLOOP.    */
                /*-------------------------------------------------------*/
                
                vert_sad[interAddr].npt() = Vsad1;
            }
        }
    }

    /*-------------------------------------------------------------------*/
    /* Now, we compute the sum of differences for the intermediate array */
    /* computed in the above loop.                                       */
    /*-------------------------------------------------------------------*/

    Vzero = 0;
    for (int I1 = 0; I1 < steps_vert; I1++)
    {
        for ( int I2 = 0; I2 < (steps_horz/TRANSPOSE_WIDTH_IN_HW); I2++)
        { 
            for (int I3 = 0; I3 < TRANSPOSE_WIDTH_IN_HW; I3++)
            {
                for ( int I4 = 0; I4 <  blk_w/VCOP_SIMD_WIDTH; I4++)
                {
                    __agen inAddr;
                    __agen outAddr;
                    
                    inAddr = (I4 * VCOP_SIMD_WIDTH * ELEMSZ_OUT) + 
                             (I3 * blk_w * ELEMSZ_OUT) + 
                             (I2 * blk_w * TRANSPOSE_WIDTH_IN_HW * ELEMSZ_OUT ) + 
                             (I1 * steps_horz * blk_w * ELEMSZ_OUT);

                   outAddr =(I3 * ELEMSZ_OUT) + // This gives the width of transposed array -- 16 bytes in this case
                            (I4 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH_IN_HW + 2)  * ELEMSZ_OUT) + // BLK_W becomes height after transpose
                            (I2 * blk_w * (TRANSPOSE_WIDTH_IN_HW + 2) * ELEMSZ_OUT) + 
                            (I1 * steps_horz * (blk_w + (blk_w/TRANSPOSE_WIDTH)) * ELEMSZ_OUT);

                    Vin = vert_sad[inAddr].npt();
                    Vout = Vin;

                    vert_sad_t[outAddr].offset_np1() = Vout;

                }
            }
        }
    }

    /*-------------------------------------------------------------------*/
    /* Add the columns of the transposed array to get final SAD values.  */
    /*-------------------------------------------------------------------*/
    
    for (int I1 = 0; I1 < steps_vert; I1++)
    {
        for ( int I2 = 0; I2 < (steps_horz/TRANSPOSE_WIDTH_IN_HW); I2++)
        { 
            __agen outAddr;

            Vsad1 = 0;
            Vsad2 = 0;

            outAddr = (I2 * TRANSPOSE_WIDTH_IN_HW * ELEMSZ_OUT) + (I1 * steps_horz * ELEMSZ_OUT);

            for (int I3 = 0; I3 < blk_w; I3++)
            {
                 __agen inAddr;


                inAddr = (I3 * (TRANSPOSE_WIDTH_IN_HW + 2) * ELEMSZ_OUT) + 
                         (I2 * blk_w * (TRANSPOSE_WIDTH_IN_HW + 2) * ELEMSZ_OUT) + 
                         (I1 * steps_horz * (blk_w + (blk_w/TRANSPOSE_WIDTH)) * ELEMSZ_OUT);


                (Vin1, Vin2) = vert_sad_t[inAddr].deinterleave();
            
                Vsad1 += Vin1;
                Vsad2 += Vin2;

           }

           sad_array[outAddr].interleave() = (Vsad1, Vsad2);
          
       }
   }
}
