/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*----------------------------------------------------------------------------*/
/* NAME: vcop_calc_determinant_tensor_matrix_kernel                           */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*     This kernel to compute determinant of tensor matrix                    */
/*     computation on EVE                                                     */
/* AUTHOR:                                                                    */
/*             Kumar Desappan(kumar.desappan@ti.com)                          */
/*                                                                            */
/* VERSION:                                                                   */
/*            1.0 (Nov 2013) : Base version.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif
#define NORM_ELEM_SZ       (4)
#define NRSB_ELEM_SZ       (2)

void vcop_calc_determinant_tensor_matrix
  (
  __vptr_uint16 Ix2L_a, 
  __vptr_uint16 Iy2L_b,
  __vptr_uint16 IxyL_c,
  __vptr_int16 Ix2H_a, 
  __vptr_int16 Iy2H_b,
  __vptr_int16 IxyH_c,
  __vptr_uint16 d_nrsb_a,
  __vptr_int32  d_norm_b,
  unsigned short n
  )
{
  /*-----------------------------------------------------------------
  Compiler could not allocate the regusters automaticaly for this loop.
  Manged the registers manually
  ------------------------------------------------------------------*/
  __vector Vec0;
  __vector Vec2;
  __vector Vec4;
  __vector Vec6;
  __vector Vec8;
  __vector Vec10;
  __vector Vec12;
  __vector Vec14;
  __vector Vec1;
  __vector Vec3;
  __vector Vec5;
  __vector Vec7;
  __vector Vec9;
  __vector Vec11;
  __vector Vec13;
  __vector Vec15;
 
#define Vmask         Vec15
#define Vcst31        Vec13
#define Vcst32        Vec12

  Vmask         = 0xFFFFFFFFU;      
  Vcst31        = 31;
  Vcst32        = 32;
  Vec14 = 0;


  for (int I1 = 0; I1 < n/VCOP_SIMD_WIDTH; I1++)
  {        
    __agen Addr1;
    __agen Addr2;

    Addr1 = I1*NORM_ELEM_SZ*VCOP_SIMD_WIDTH;
    Addr2 = I1*NRSB_ELEM_SZ*VCOP_SIMD_WIDTH;

    Vec0  = (Ix2L_a )[Addr1].ds2();
    Vec2  = (Ix2H_a )[Addr1].ds2();
    Vec4  = (Iy2L_b )[Addr1].ds2();
    Vec6  = (Iy2H_b )[Addr1].ds2();                 
    Vec8  = (IxyL_c )[Addr1].ds2();           
    Vec10 = (IxyH_c )[Addr1].ds2();   
    
    // Ixx*Iyy -- > Vec5(Low), Vec7(High)
    Vec1        = Vec0*Vec6;        //(VIx2L * VIy2H); 
    Vec3        = Vec2*Vec4;        //(VIx2H * VIy2L); 
             
    Vec7       = Vec2*Vec6;        //(VIx2H * VIy2H); 
    Vec5       = Vec0*Vec4;        //(VIx2L * VIy2L); 

    (Vec0, Vec2) = jus16(Vec1);
    (Vec4, Vec6) = jus16(Vec3);

    Vec5      += (Vec0 + Vec4); //Lo1 = Lo+Lo
    Vec7      += (Vec2 + Vec6) ; //Hi1 = Hi+Hi
    Vec7      += hi(Vec5);    //Hi1 += hi(Lo1)    

    // Ixy*Iyy -- > Vec0(Low), Vec1(High)
    Vec0      = Vec8*Vec8;          //(VIxyL * VIxyL);    
    Vec1      = Vec10*Vec10;        //(VIxyH * VIxyH);    
    Vec2      = Vec8*Vec10;         //(VIxyL * VIxyH);    

    (Vec3, Vec4) = jus16(Vec2);

    Vec0     += (Vec3 + Vec3);  //Lo2 = Lo+Lo
    Vec1     += (Vec4 + Vec4);  //Hi2 = Hi+Hi
    Vec1     += hi(Vec0);     //Hi2 += hi(Lo2)    

    Vec5 = Vec5 & Vmask; // Lo1
    Vec0 = Vec0 & Vmask; // Lo2

    // Ixx*Iyy - Ixy*Iyy -- > Vec0(Low), Vec1(High)
    Vec0  = Vec5 - Vec0; //Lo = Lo1-Lo2
    Vec1  = Vec7 - Vec1; //Hi = Hi1-Hi2

    Vec1 += hi(Vec0); //Hi += hi(Lo)         

    Vec0 = Vec0 & Vmask; // Lo2
     // Counting the NRSB --> Vec4
    Vec2  = Vec1 >= Vec14; 

    Vec3     = leading_bit(Vec0, Vec2);

    Vec4 = Vcst31 - Vec3; 

    Vec3     = leading_bit(Vec1, Vec2);
    Vec3     = Vcst31 - Vec3; 
    Vec8   = Vec0 >= Vec14;
    Vec2   = Vec2 ^ Vec8;
    Vec4   = Vec4 + Vec3;
    Vec4   = select(Vec2, Vcst32, Vec4); 

    Vec2      = Vcst32 > Vec3;
    Vec4      = select(Vec2, Vec3, Vec4); 
    Vec4   += Vcst31 - Vcst32; 

    //Vec0 = Vec0 & Vmask;
    
    // Calculating normalized determinant --> Vec6 
    Vec5      = Vec4 - Vcst32;
    Vec6      = (Vec0 << Vec5);
    Vec1      = Vec1 << Vec4;
    Vec1     |= Vec6;
   
    Vec2      = Vcst32 > Vec4;

    Vec6      = select(Vec2, Vec1, Vec6); 

    (d_nrsb_a)[Addr2]=Vec4 ;
    (d_norm_b)[Addr1]=Vec6 ;        

  }
} 

/*----------------------------------------------------------------------------*/
/* End of file:vcop_calc_determinant_tensor_matrix_kernel.k                   */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
