/*==========================================================================*/ 
/*     TEXAS INSTRUMENTS, INC.                                              */ 
/*                                                                          */ 
/*     NAME                                                                 */ 
/*     vcop_vec_bin_image_erode_single_pixel_kernel                         */ 
/*                                                                          */ 
/*     USAGE                                                                */ 
/*     This routine is C-callable and can be called as:                     */ 
/*                                                                          */ 
/*     void vcop_vec_bin_image_erode_single_pixel                           */ 
/*     (                                                                    */ 
/*         __vptr_uint32 pIn,                                               */ 
/*         __vptr_uint32 out,                                               */ 
/*         int           cols,                                              */ 
/*         int           pitch,                                             */ 
/*         int           height                                             */ 
/*     )                                                                    */ 
/*                                                                          */ 
/*                                                                          */ 
/*     in        :  32-bit packed input binary image                        */ 
/*     out       :  32-bit packed output binary image                       */ 
/*     cols      :  Number of columns in the binary image                   */ 
/*     pitch     :  Pitch of the binary image                               */ 
/*     height    :  Number of rows in the binary image                      */ 
/*                                                                          */ 
/*     Returns :  None or void.                                             */ 
/*                                                                          */ 
/*                                                                          */ 
/*     DESCRIPTION                                                          */ 
/*             This routine accepts 32-bit packed input binary image and    */ 
/*     performs erosion of isolated pixels (ON pixels that do not have any  */ 
/*     ON neighbors) and outputs a 32-bit packed output binary image.        */ 
/*                                                                          */ 
/*     ASSUMPTIONS                                                          */ 
/*     The number of columns in the input binary image should be a          */ 
/*     multiple of 256.                                                     */ 
/*                                                                          */ 
/*==========================================================================*/ 
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */ 
/*                      All Rights Reserved                                 */ 
/*==========================================================================*/ 

#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_vec_bin_image_erode_single_pixel                      
(                                                                    
    __vptr_uint32 pIn,         
    __vptr_uint32 out,                                                  
    int           cols,                                                            
    int           pitch,                                                       
    int           height                                                       
)
{
    __vector  R8, R9, R10, R11;
    
    __vector r,in00, in01, in10, in11, in20, in21; 
    __vector t1, t2, t3, t4;
    __vector m1, m2, m3, m4;
    
    R8=-31;
    R9=-30; 
    R10=2; 
    R11=1;

    for(int I1 = 0; I1 < height; I1 ++ )
    {
        for (int I2 = 0; I2 < cols/(32*VCOP_SIMD_WIDTH); I2++)
        {
            __agen Addr1;
        
            Addr1 = I1*(pitch/32)*ELEMSZ + I2*VECTORSZ;

            in00 = (pIn)               [Addr1];                     
            in01 = (pIn+1*4)           [Addr1];                 
            in10 = (pIn+pitch*4/32)    [Addr1];         
            in11 = (pIn+pitch*4/32+1*4)[Addr1];      
            in20 = (pIn+pitch*4/16)    [Addr1];         
            in21 = (pIn+pitch*4/16+1*4)[Addr1];  
            
            m1 = in00 | in20;
            m4 = in10<<R11; 

            m2 = in01 | in21 ;
            in00 |= in20 | in10 ;

            in00 |= m1 <<R11;
            m3 = m2 | in11 ;
            
            t3 = m2<<R8 ;
            t3 |= m3 <<R9;
            
            t2  = in00<<R10  ;
            m4 |= in11 <<R8;
            
            t3 |= t2 | in00;

            t3 &= m4;
                        
            out[Addr1] = t3 ; 
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_single_pixel_kernel.k            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


