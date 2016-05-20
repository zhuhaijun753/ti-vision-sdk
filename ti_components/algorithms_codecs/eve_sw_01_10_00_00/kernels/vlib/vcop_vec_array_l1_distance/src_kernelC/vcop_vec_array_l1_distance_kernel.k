/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_array_l1_distance_kernel.k                                  */
/*                                                                          */
/*     USAGE                                                                */
/*     The VCOP-C function prototype is:                                    */
/*                                                                          */
/*     void vcop_vec_array_l1_distance                                      */
/*     (                                                                    */
/*         __vptr_int16   a,                                                */
/*         __vptr_int16   b,                                                */
/*         __vptr_uint32  c,                                                */
/*            int         array_len                                         */
/*     )                                                                    */ 
/*                                                                          */
/*     a         :  Pointer to an input array of shorts.                    */
/*     b         :  Pointer to second input array of shorts.                */
/*     c         :  Pointer to 16 values which has to be summed to get L1D. */
/*     array_len :  length of the arrays A and B                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to two input arrays of         */
/*     length array_len and returns a single integer value representing     */
/*     the L1 distance between the two arrays.                              */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     While the C code does not have any assumptions on the length of      */
/*     the arrays, the kernel-C code assumes that array_len the length      */
/*     of the arrays is a multiple of 16.                                   */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define ELEMSZ          sizeof(*a)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_vec_array_l1_distance
(
    __vptr_int16    a,
    __vptr_int16    b,
    __vptr_uint32   c,
      int           array_len
)
{
    __vector Va_1,Va_2;                
    __vector Vb_1,Vb_2;                
    __vector Vacc1,Vacc2;                  
   
    Vacc1  = 0;
    Vacc2  = 0;

    for (int I2 = 0; I2 < 1; I2++)  
    {
         __agen Addr2;
        Addr2 = 0;
         
        for (int I1 = 0; I1 < array_len/(2*VCOP_SIMD_WIDTH); I1++)  
        {
            __agen Addr1;
            
            Addr1 = I1*VECTORSZ*2;
            
            (Va_1,Va_2) = a[Addr1].deinterleave();   
            (Vb_1,Vb_2) = b[Addr1].deinterleave();
            
            Vacc1 += abs(Vb_1 - Va_1);
            Vacc2 += abs(Vb_2 - Va_2);
        }
        
         c     [Addr2] = Vacc1;
        (c+8*4)[Addr2] = Vacc2; 
    }    
        
}

/* ======================================================================== */
/*  End of file:  vcop_vec_array_l1_distance_kernel.k                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


