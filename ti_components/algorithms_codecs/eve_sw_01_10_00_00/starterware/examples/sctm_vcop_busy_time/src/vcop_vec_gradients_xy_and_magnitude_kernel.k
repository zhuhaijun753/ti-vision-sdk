/*==========================================================================*/ 
/*     TEXAS INSTRUMENTS, INC.                                              */ 
/*                                                                          */ 
/*     NAME                                                                 */ 
/*     vcop_vec_gradients_xy_and_magnitude_cn                               */ 
/*                                                                          */ 
/*     USAGE                                                                */ 
/*     This routine is C-callable and can be called as:                     */ 
/*                                                                          */ 
/*     void vcop_vec_gradients_xy_and_magnitude                             */ 
/*     (                                                                    */ 
/*         __vptr_uint8   pIn,                                              */ 
/*         __vptr_int16   pGradX,                                           */ 
/*         __vptr_int16   pGradY,                                           */
/*         __vptr_int16   pMag,                                             */ 
/*         unsigned short width,                                            */ 
/*         unsigned short height                                            */ 
/*     )                                                                    */ 
/*                                                                          */ 
/*     pIn       :  8-bit input image                                       */ 
/*     pGradX    :  gradient value in X direction                           */ 
/*     pGradY    :  gradient value in Y direction                           */ 
/*     pMag      :  gradient magnitude                                      */ 
/*     width     :  width of the input image                                */ 
/*     height    :  height of the input image                               */ 
/*                                                                          */ 
/*     Returns :  None or void.                                             */ 
/*                                                                          */ 
/*                                                                          */ 
/*     DESCRIPTION                                                          */ 
/*            This routine accepts a 8-bit input image and returns gradient */ 
/*     value in X direction, Y direction and its magnitude.                 */ 
/*                                                                          */ 
/*     ASSUMPTIONS                                                          */ 
/*             The number of pixels (width*height) is assumed to be a       */
/*     multiple of 16. Output pointers Gx, Gy and Gmax are assumed to be    */
/*     word aligned.                                                        */
/*                                                                          */
/*==========================================================================*/ 
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */ 
/*                      All Rights Reserved                                 */ 
/*==========================================================================*/ 

#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_vec_gradients_xy_and_magnitude
(                                                                    
    __vptr_uint8   pIn,                                               
    __vptr_int16   pGradX,
    __vptr_int16   pGradY,
    __vptr_int16   pMag,  
    unsigned short width,                                                       
    unsigned short height                                                       
)
{
    __vector VinT1,VinT2;               //Top pixel 
    __vector VinL1,VinL2;               //Left pixel
    __vector VinR1,VinR2;               //Right pixel 
    __vector VinB1,VinB2;               //Bottom pixel 
    __vector VgX_1,VgX_2;               //Gx 
    __vector VgY_1,VgY_2;               //Gy 
    __vector Vabs_gX_1,Vabs_gX_2;       //abs of Gx
    __vector Vabs_gY_1,Vabs_gY_2;       //abs of Gy
    __vector Vmag1,Vmag2, Z;               //Mag
    
    Z = 0;
   
    for (int I1 = 0; I1 < width*height/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr1,Addr2;
        
        Addr1 = I1*VECTORSZ*2;
        Addr2 = I1*VECTORSZ*4;
                                        
        (VinT1,VinT2) = (pIn+1)        [Addr1].deinterleave();                  
        (VinL1,VinL2) = (pIn+width)    [Addr1].deinterleave();                
        (VinR1,VinR2) = (pIn+width+2)  [Addr1].deinterleave();        
        (VinB1,VinB2) = (pIn+2*width+1)[Addr1].deinterleave();     
        
        VgX_1 = VinR1 - VinL1; 
        VgY_1 = VinB1 - VinT1; 
        
        VgX_2 = VinR2 - VinL2; 
        VgY_2 = VinB2 - VinT2; 
        
        Vmag1 = abs(VgX_1);
        Vmag2 = abs(VgX_2);
        
        Vmag1 += abs(VgY_1 - Z);
        Vmag2 += abs(VgY_2 - Z);
        
        pGradX[Addr2].interleave() = (VgX_1,VgX_2);
        pGradY[Addr2].interleave() = (VgY_1,VgY_2);
        pMag[Addr2].interleave()   = (Vmag1,Vmag2);
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_kernel.k              */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


