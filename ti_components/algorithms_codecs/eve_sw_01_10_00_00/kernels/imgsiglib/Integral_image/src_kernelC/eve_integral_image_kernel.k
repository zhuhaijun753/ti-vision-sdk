
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     eve_integral_image_kernel.k                                          */
/*                                                                          */
/*S    REVISION HISTORY                                                    S*/
/*S    01/04/11..............Initial Version.........Kamath S.             S*/
/*S    03/03/11......Variable block size version.....Kamath S.             S*/
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void eve_integral_image_u8_int_int                                 */ 
/*           (                                                              */
/*              unsigned int    blk_w,                                      */
/*              unsigned int    blk_h,                                      */
/*              unsigned int    in_width,                                   */
/*              __vptr_uint32   acc_h_ptr,                                  */
/*              __vptr_uint32   acc_v_ptr,                                  */
/*              __vptr_uint8    in_ptr,                                     */
/*              __vptr_uint32   B0_ptr,                                     */
/*              __vptr_uint32   B1_ptr,                                     */
/*              __vptr_uint32   C0_ptr,                                     */
/*              __vptr_uint32   C1_ptr,                                     */
/*              __vptr_uint32   out_ptr                                     */
/*          );                                                              */
/*                                                                          */
/*     blk_h       :  II core kernel height is 'blk_h' in pixels.           */
/*     blk_w       :  II core kernel width is 'blk_w' in pixels.            */
/*     in_width    :  Width (or pitch) of the input image.                  */
/*     acc_h_ptr   :  Pointer to an horz accumulator 1-D array of type int. */
/*     acc_v_ptr   :  Pointer to an vert accumulator 1-D array of type int. */
/*     in_ptr      :  Pointer to an input array of type char.               */
/*     B0_ptr,     :  Pointer to an even intermediate array of type int.    */ 
/*     B1_ptr,     :  Pointer to an odd intermediate array of type int.     */
/*     C0_ptr,     :  Pointer to an even output array of type int.          */
/*     C1_ptr,     :  Pointer to an odd output array of type int.           */
/*     out_ptr     :  Pointer to interleaved output array of type int.      */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine computes the integral image of a blk_w x blk_h  */
/*     which is part of a larger image. It writes out the horizontal and    */
/*     vertical accumulated values to 'acc_h_ptr' and 'acc_v_ptr'           */
/*     respectively, to be used as starting accumulated values for the      */
/*     other remaining (blk_w x blk_h) blocks of the image.                 */
/*     B0_ptr and B1_ptr are intermediate arrays, used to store results of  */
/*     first VLOOP. C0_ptr and C1_ptr hold the final integral results,      */
/*     but need to be interleaved before being written out as the 'final'   */
/*     II result.                                                           */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     - This code works on block sizes that are multiples of 16 for 'width'*/
/*     and multiples of 8 for 'height'.                                     */
/*     - Intermediate and final results are always written out as 32-bit    */
/*     values, for optimal implementation sake. However, input can be of    */
/*     either 'char' or 'short' type.                                       */
/*                                                                          */
/*     PERFORMANCE                                                          */
/*     5/16 cyc/pix                                                         */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if (VCOP_HOST_EMULATION)
#include "vcop.h"
#endif

#define   VCOP_SIMD_WIDTH    8

#define   ELEMSZ_IN          sizeof(*in_ptr)
#define   VECTORSZ_IN        (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define   ELEMSZ_INTER       sizeof(*B0_ptr)
#define   VECTORSZ_INTER     (VCOP_SIMD_WIDTH * ELEMSZ_INTER)

#define   ELEMSZ_OUT         sizeof(*out_ptr)
#define   VECTORSZ_OUT       (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define   TRANSPOSE_WIDTH    8

#define   BYTES_IN_HALF_WD   2
#define   BYTES_IN_WORD      4

#define   TWOSIXTY           260 

// #define __PRINT__            1

void eve_integral_image_reset_accv(
        __vptr_uint32   acc_v_ptr,
        unsigned int blk_h){

    for(int i = 0; i < blk_h; i++)
    {
        __vector vZero;
        __agen Addr0=  i*sizeof(*acc_v_ptr);
        vZero= 0;

        acc_v_ptr[Addr0].onept() = vZero;
    }

}

void eve_integral_image_reset_acch(
        __vptr_uint32   acc_h_ptr,
        unsigned int blk_w){

    for(int i = 0; i < blk_w/VCOP_SIMD_WIDTH; i++)
    {
        __vector vZero;
        __agen Addr0=  i*VCOP_SIMD_WIDTH*sizeof(*acc_h_ptr);
        vZero= 0;

        acc_h_ptr[Addr0].npt() = vZero;
    }

}

/*-------------------------------------------------------------*/
/* For input type of 'char' or 'uchar', we call the function   */
/* eve_integral_image_u8_int_int().                          */
/*-------------------------------------------------------------*/

void eve_integral_image_u8_int_int
(
    unsigned int    blk_w,      // II core kernel height            
    unsigned int    blk_h,      // II core kernel width             
    unsigned int    in_width,   // Width (or pitch) of the input image.                 
    __vptr_uint32   acc_h_ptr,  // Pointer to an horz accumulator 1-D array of type int.
    __vptr_uint32   acc_v_ptr,  // Pointer to an vert accumulator 1-D array of type int.
    __vptr_uint8    in_ptr,     // Pointer to an input array of type char.              
    __vptr_uint32   B0_ptr,     // Pointer to an even intermediate array of type int.   
    __vptr_uint32   B1_ptr,     // Pointer to an odd intermediate array of type int.    
    __vptr_uint32   C0_ptr,     // Pointer to an even output array of type int.         
    __vptr_uint32   C1_ptr,     // Pointer to an odd output array of type int.          
    __vptr_uint32   out_ptr,     // Pointer to interleaved output array of type int.     
    __vptr_uint32   out_acc_h_ptr  // Pointer to an horz accumulator 1-D array of type int.
)
{

  __vector Vin_even, Vin_odd, Vin_B0, Vin_B1, V_C0, Vin_a, Vin_b;
  __vector Vacc_h_even, Vacc_h_odd, Vacc_v;

    /*-------------------------------------------------------------------*/
    /* First we add row-wise and write out the result in transposed form.*/
    /* The data is also read in 'deinterleave' format, so we have two    */
    /* separate blocks of even and odd results. Even results are stored  */
    /* in the intermediate array B0, odd results are stored in B1.       */
    /* Cycle count for this loop should be 1/16                          */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        __agen accAddr;

        accAddr  = I1 * (2 * VCOP_SIMD_WIDTH) * ELEMSZ_OUT;

        Vacc_h_even = acc_h_ptr[accAddr];
        Vacc_h_odd = (acc_h_ptr + 32)[accAddr];
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        {
            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
        
                
                 dataAddr = (I3 * in_width * ELEMSZ_IN) + 
                            (I2 * in_width * TRANSPOSE_WIDTH * ELEMSZ_IN) + 
                            (I1 * VECTORSZ_IN * 2);
        
                outAddr  = (I3 * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) +
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER);
        
                (Vin_even, Vin_odd)  =  in_ptr[dataAddr].deinterleave();  

                Vacc_h_even = Vacc_h_even + Vin_even;   
                Vacc_h_odd = Vacc_h_odd + Vin_odd;   
                    
#ifdef __PRINT__

                Vacc_h_even.printx();
                printf("\n");
                Vacc_h_odd.printx();
#endif

                B0_ptr[outAddr].offset_np1() = Vacc_h_even;
                B1_ptr[outAddr].offset_np1() = Vacc_h_odd;               

           }
       }

       //acc_h_ptr[accAddr] = Vacc_h_even;
       //(acc_h_ptr + 32)[accAddr] = Vacc_h_odd;
       
       out_acc_h_ptr[accAddr] = Vacc_h_even;
       (out_acc_h_ptr + 32)[accAddr] = Vacc_h_odd;

       

    }

    /*-------------------------------------------------------------------*/
    /* Now, we add the transposed array in the row-wise direction again. */
    /* Here, we consider inter_w = blk_h, inter_h = blk_w, as the        */
    /* original array dimensions are switched.                           */
    /* Cycle count for this loop should be 1/8                           */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
    printf("\n\n 2nd loop \n\n");
#endif

    for (int I1 = 0; I1 < blk_w/( 2 * VCOP_SIMD_WIDTH); I1++)
    {
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        { 
        
            __agen accAddr;
            
            accAddr  = I2 * TRANSPOSE_WIDTH *  ELEMSZ_INTER;

            Vacc_v   = acc_v_ptr[accAddr].npt();

            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
          
                dataAddr = (I3 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER) ;

                outAddr =  (I3 * ELEMSZ_OUT) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_OUT) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_OUT) ;

                Vin_B0  =  B0_ptr[dataAddr].npt();  
                Vin_B1  =  B1_ptr[dataAddr].npt();  

                V_C0     = Vacc_v + Vin_B0;   
                Vacc_v  += Vin_B0 + Vin_B1;  

#ifdef __PRINT__
                V_C0.printx();
                Vacc_v.printx();
#endif

                C0_ptr[outAddr].offset_np1() = V_C0;
                C1_ptr[outAddr].offset_np1() = Vacc_v;

            } 
      
           acc_v_ptr[accAddr] = Vacc_v;

      }

    }


    /*-------------------------------------------------------------------*/
    /* This is the third VLOOP, where we 'interleave' the two output     */
    /* buffers to get back or correct output block. We also reformat the */
    /* data by removing the 9th word, inserted as part of the transpose  */
    /* store feature.                                                    */
    /* Estimated cycle count 2/16                                        */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
     printf("\n\nThird loop\n\n");
#endif

    for (int I1 = 0; I1 <  blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        for (int I2 = 0; I2 < blk_h; I2++)
        {
            __agen dataAddr, outAddr;
                 
            dataAddr = (I1 * blk_h * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT) + (I2 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT);
            outAddr  = (I2 * in_width * ELEMSZ_OUT) +  (I1 * 2 * VECTORSZ_OUT);
            
            Vin_a = C0_ptr[dataAddr];
            Vin_b = C1_ptr[dataAddr];

#ifdef __PRINT__           
            Vin_a.printx();
            Vin_b.printx();
#endif
            (Vin_a, Vin_b).interleave();
            
            out_ptr[outAddr] = Vin_a;
            (out_ptr + (8 * 4))[outAddr] = Vin_b;
            
        }
    }  
}


/*-----------------------------------------------------------------------*/
/* For input type of 'short' or 'ushort', we call the function           */
/* eve_integral_image_short_int_int().                                   */
/*-----------------------------------------------------------------------*/

void eve_integral_image_u16_int_int
(
    unsigned int    blk_w,
    unsigned int    blk_h,
    unsigned int    in_width,
    __vptr_uint32   acc_h_ptr,
    __vptr_uint32   acc_v_ptr,
    __vptr_uint16   in_ptr,
    __vptr_uint32   B0_ptr,
    __vptr_uint32   B1_ptr,
    __vptr_uint32   C0_ptr,
    __vptr_uint32   C1_ptr,
    __vptr_uint32   out_ptr
)
{

  __vector Vin_even, Vin_odd, Vin_B0, Vin_B1, V_C0, Vin_a, Vin_b;
  __vector Vacc_h_even, Vacc_h_odd, Vacc_v;


    /*-------------------------------------------------------------------*/
    /* First we add row-wise and write out the result in transposed form.*/
    /* The data is also read in 'deinterleave' format, so we have two    */
    /* separate blocks of even and odd results. Even results are stored  */
    /* in the intermediate array B0, odd results are stored in B1.       */
    /* Cycle count for this loop should be 1/16                          */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        __agen accAddr;
        
        accAddr  = I1 * (2 * VCOP_SIMD_WIDTH) * ELEMSZ_OUT;
        Vacc_h_even = acc_h_ptr[accAddr];
        Vacc_h_odd = (acc_h_ptr + 32)[accAddr];
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        {
            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
        
                
                 dataAddr = (I3 * in_width * ELEMSZ_IN) + 
                            (I2 * in_width * TRANSPOSE_WIDTH * ELEMSZ_IN) + 
                            (I1 * VECTORSZ_IN * 2);
        
                outAddr  = (I3 * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) +
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER);
        
                (Vin_even, Vin_odd)  =  in_ptr[dataAddr].deinterleave();  

                Vacc_h_even = Vacc_h_even + Vin_even;   
                Vacc_h_odd = Vacc_h_odd + Vin_odd;   
                    
#ifdef __PRINT__

                Vacc_h_even.printx();
                printf("\n");
                Vacc_h_odd.printx();
#endif

                B0_ptr[outAddr].offset_np1() = Vacc_h_even;
                B1_ptr[outAddr].offset_np1() = Vacc_h_odd;
                 

           }
       }

       acc_h_ptr[accAddr] = Vacc_h_even;
       (acc_h_ptr + 32)[accAddr] = Vacc_h_odd;

    }

    /*-------------------------------------------------------------------*/
    /* Now, we add the transposed array in the row-wise direction again. */
    /* Here, we consider inter_w = blk_h, inter_h = blk_w, as the        */
    /* original array dimensions are switched.                           */
    /* Cycle count for this loop should be 1/8                           */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
    printf("\n\n 2nd loop \n\n");
#endif

    for (int I1 = 0; I1 < blk_w/( 2 * VCOP_SIMD_WIDTH); I1++)
    {
        
        for (int I2 = 0; I2 < blk_h/TRANSPOSE_WIDTH; I2++ )
        { 
        
            __agen accAddr;
            
            accAddr  = I2 * TRANSPOSE_WIDTH *  ELEMSZ_INTER;

            Vacc_v   = acc_v_ptr[accAddr].npt();

            for ( int I3 = 0; I3 < TRANSPOSE_WIDTH; I3++)
            {
                __agen dataAddr;
                __agen outAddr;
          
                dataAddr = (I3 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_INTER) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_INTER) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_INTER) ;

                outAddr =  (I3 * ELEMSZ_OUT) + 
                           (I2 * (TRANSPOSE_WIDTH + 1) * TRANSPOSE_WIDTH * ELEMSZ_OUT) + 
                           (I1 * TRANSPOSE_WIDTH * (TRANSPOSE_WIDTH + 1) * (blk_h/TRANSPOSE_WIDTH) * ELEMSZ_OUT) ;

                Vin_B0  =  B0_ptr[dataAddr].npt();  
                Vin_B1  =  B1_ptr[dataAddr].npt();  

                V_C0     = Vacc_v + Vin_B0;   
                Vacc_v  += Vin_B0 + Vin_B1;  

#ifdef __PRINT__
                V_C0.printx();
                Vacc_v.printx();
#endif

                C0_ptr[outAddr].offset_np1() = V_C0;
                C1_ptr[outAddr].offset_np1() = Vacc_v;

            } 
      
           acc_v_ptr[accAddr] = Vacc_v;

      }

    }


    /*-------------------------------------------------------------------*/
    /* This is the third VLOOP, where we 'interleave' the two output     */
    /* buffers to get back or correct output block. We also reformat the */
    /* data by removing the 9th word, inserted as part of the transpose  */
    /* store feature.                                                    */
    /* Estimated cycle count 2/16                                        */
    /*-------------------------------------------------------------------*/

#ifdef __PRINT__
     printf("\n\nThird loop\n\n");
#endif

    for (int I1 = 0; I1 <  blk_w/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        for (int I2 = 0; I2 < blk_h; I2++)
        {
            __agen dataAddr, outAddr;
                 
            dataAddr = (I1 * blk_h * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT) + (I2 * (TRANSPOSE_WIDTH + 1) * ELEMSZ_OUT);
            outAddr  = (I2 * in_width * ELEMSZ_OUT) +  (I1 * 2 * VECTORSZ_OUT);
            
            Vin_a = C0_ptr[dataAddr];
            Vin_b = C1_ptr[dataAddr];

#ifdef __PRINT__           
            Vin_a.printx();
            Vin_b.printx();
#endif
            (Vin_a, Vin_b).interleave();
            
            out_ptr[outAddr] = Vin_a;
            (out_ptr + (8 * 4))[outAddr] = Vin_b;
            
        }
    }  
}

/* ======================================================================== */
/*  End of file:  eve_integral_image_kernel.k                               */
/*--------------------------------------------------------------------------*/
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
