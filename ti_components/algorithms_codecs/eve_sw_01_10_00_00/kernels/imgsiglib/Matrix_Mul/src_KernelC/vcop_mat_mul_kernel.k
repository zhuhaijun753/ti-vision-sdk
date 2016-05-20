/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_mat_mul, Matrix Multiplication code for the VICP library.   */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_mat_mul                                                    */
/*     (                                                                    */
/*         __vptr_uint8   in1_ary,                                          */
/*         __vptr_uint8   in2_ary,                                          */
/*         __vptr_int16   res,                                              */
/*         int            w_in1,                                            */
/*         int            h_in1,                                            */
/*         int            w_in2,                                            */
/*         int            rnd_shift                                         */
/*     );                                                                   */
/*                                                                          */
/*     in1_ary,    :  Pointer to first input array.                         */
/*     in2_ary,    :  Pointer to second input array.                        */
/*     res,        :  Pointer to output array.                              */
/*     w_in1,      :  Width of the first input array in pixels.             */
/*     h_in1,      :  Height of the first input array in pixels.            */
/*     w_in2,      :  Width of the second input array in pixels.            */
/*     rnd_shift   :  Rounding and shifting amount.                         */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine multiplies two matrices.                        */
/*                                                                          */
/*     ASSUMPTION                                                           */
/*     --This code assumes that 'w_in1' == 'h_in2'.                         */
/*     --The result is a matrix of dimensions 'w_in2 x h_in1'.              */
/*                                                                          */
/*     CYCLES/PERFORMANCE                                                   */
/*                                                                          */
/*     w_in1/VCOP_SIMD_WIDTH   cyc/pix                                      */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define ELEMSZ_IN1        sizeof(*in1_ary)
#define VECTORSZ_IN1      (VCOP_SIMD_WIDTH * ELEMSZ_IN1)

#define ELEMSZ_IN2        sizeof(*in2_ary)
#define VECTORSZ_IN2     (VCOP_SIMD_WIDTH * ELEMSZ_IN2)

#define ELEMSZ_OUT       sizeof(*res)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define SAT_LO_CHAR           (-128)
#define SAT_HI_CHAR           (127)
#define SAT_LO_SHORT          (-32768)
#define SAT_HI_SHORT          (32767)

void vcop_mat_mul_uchar_uchar_short
(
    __vptr_uint8   in1_ary,      // Pointer to first input array.      
    __vptr_uint8   in2_ary,      // Pointer to second input array.
    __vptr_int16   res,          // Pointer to output array. 
    int            w_in1,        // Width of the first input array in pixels.             
    int            h_in1,        // Height of the first input array in pixels.            
    int            w_in2,        // Width of the second input array in pixels.           
    int            rnd_shift     // Rounding and shifting amount.                                                             
)
{
    __vector v_in1, v_in2, v_sum;

    /*-------------------------------------------------------------------*/
    /* Actual matrix multiplication step.                                */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_in1; I1++)
    {
        v_sum = 0;
        
        for ( int I2 = 0; I2 < w_in2/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr = I1 * ELEMSZ_OUT * w_in1 + I2 * ELEMSZ_OUT * VCOP_SIMD_WIDTH;
            
            for ( int I3 = 0; I3 < w_in1; I3++)
            {
                    __agen in1_Addr, in2_Addr;

                    in1_Addr = I1 * ELEMSZ_IN1 * w_in1 + I3 * ELEMSZ_IN1;
                    in2_Addr = I2 * ELEMSZ_IN2 * VCOP_SIMD_WIDTH + I3 * ELEMSZ_IN2 * w_in2;

                    v_in1  =  in1_ary[in1_Addr].onept();
                    v_in2  =  in2_ary[in2_Addr].npt();
                    
                    v_sum += (v_in1 * v_in2);
             }
             
             res[outAddr].npt() = v_sum.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }         

     }
}

/*-----------------------------------------------------------------*/
/* End of file : vcop_mat_mul_kernel.k                             */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                       */
/*=================================================================*/
