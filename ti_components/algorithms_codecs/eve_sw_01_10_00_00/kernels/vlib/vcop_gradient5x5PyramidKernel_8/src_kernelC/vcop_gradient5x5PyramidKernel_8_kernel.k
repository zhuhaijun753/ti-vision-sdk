/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_gradient5x5PyramidKernel_8_kernel                               */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_gradientH5x5PyramidKernel_8                                */
/*     (                                                                    */
/*         __vptr_uint8    pIn,                                             */
/*         __vptr_int16    pB,                                              */
/*         unsigned short  width,                                           */
/*         unsigned short  pitch,                                           */
/*         unsigned short  height,                                          */
/*         __vptr_uint8    pOut                                             */
/*     )                                                                    */
/*     void vcop_gradientV5x5PyramidKernel_8                                */
/*     (                                                                    */
/*         __vptr_uint8   pIn,                                              */
/*         __vptr_int16   pB,                                               */
/*         unsigned short width,                                            */
/*         unsigned short pitch,                                            */
/*         unsigned short height,                                           */
/*         __vptr_uint8   pOut                                              */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  8-bit input image                                        */
/*     pB       :  Intermediate buffer                                      */
/*     width    :  Width of the input image                                 */
/*     pitch    :  Pitch of the input image                                 */
/*     height   :  Height of the input image                                */
/*     pOut     :  8-bit output image                                       */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of gradient pyramid in the pOut array.                        */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 8.  */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define ELEMSZ          sizeof(*pIn)
#define ELEMSZ1         sizeof(*pB)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define VECTORSZ1       (VCOP_SIMD_WIDTH*ELEMSZ1)

void vcop_gradientH5x5PyramidKernel_8
(
    __vptr_uint8    pIn,
    __vptr_int16    pB,
    unsigned short  width,
    unsigned short  pitch,
    unsigned short  height,
    __vptr_uint8    pOut
)
{
   __vector R1 ,R2 ,R3 ,R4 ,R5 ,R6 ,R , R7;
   __vector R1p,R2p,R3p,R4p,R5p,R6p,Rp;
   __vector C_1, C_2, C_6, C_64, C_128, C_M7;

    C_1=1;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < (width)/(2*VCOP_SIMD_WIDTH)+1; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*pitch*ELEMSZ  + j*VECTORSZ;
            Addr2 = i*width*ELEMSZ1 + j*VECTORSZ1;

            (R1,R1p)= (pIn  )[Addr1].deinterleave();
            (R2,R2p)= (pIn+1)[Addr1].deinterleave();
            (R3,R3p)= (pIn+3)[Addr1].deinterleave();
            (R4,R4p)= (pIn+4)[Addr1].deinterleave();

            R6  = R2  - R3;
            R6p = R2p - R3p;

            R5  = R1  - R4;
            R5p = R1p - R4p;

            R6  = R6  << C_1;
            R6p = R6p << C_1;

            R6  += R5;
            R6p += R5p;

            pB[Addr2].interleave() = (R6,R6p);
        }
    }

    C_2   = 2  ;
    C_6   = 6  ;
    C_64  = 64 ;
    C_128 = 128;
    C_M7  = -7 ;

    for(int i = 0; i < (height - 4)/2 + 1; i++)
    {
        for(int j = 0; j < width/(2*VCOP_SIMD_WIDTH)+1; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*width*ELEMSZ1    + j*VECTORSZ1;
            Addr2 = i*(width/2)*ELEMSZ + j*VECTORSZ;

            R1 = (pB+0*width*2)[Addr1].ds2();
            R2 = (pB+1*width*2)[Addr1].ds2();
            R3 = (pB+2*width*2)[Addr1].ds2();
            R4 = (pB+3*width*2)[Addr1].ds2();
            R5 = (pB+4*width*2)[Addr1].ds2();

            R7 = R2 + R4 ;
            R6 = R3 * C_6;

            R7  = R7 << C_2 ;
            R1 += R5 +  C_64;

            R1 += R6 + R7;

            R1 = R1 << C_M7;

            R1 = R1 + C_128;

            pOut[Addr2] = R1;
        }
    }

}

void vcop_gradientV5x5PyramidKernel_8
(
    __vptr_uint8    pIn,
    __vptr_int16    pB,
    unsigned short  width,
    unsigned short  pitch,
    unsigned short  height,
    __vptr_uint8    pOut
)
{

    __vector R ,R1 ,R2 ,R3 ,R4 ,R5 , R6 , R7;
    __vector Rp,R1p,R2p,R3p,R4p,R5p, R6p, R7p;
    __vector C_2, C_6, C_1, C_64, C_128, C_M7;

    C_2 = 2;
    C_6 = 6;

    for (int i = 0; i < height ; i++)
    {
         for(int j = 0; j < width/(2*VCOP_SIMD_WIDTH)+1; j++)
         {
             __agen Addr1,Addr2;

             Addr1 = i*pitch*ELEMSZ  + j*VECTORSZ ;
             Addr2 = i*width*ELEMSZ1 + j*VECTORSZ1;

             (R1,R1p) = (pIn+0)[Addr1].deinterleave();
             (R2,R2p) = (pIn+1)[Addr1].deinterleave();
             (R3,R3p) = (pIn+2)[Addr1].deinterleave();
             (R4,R4p) = (pIn+3)[Addr1].deinterleave();
             (R5,R5p) = (pIn+4)[Addr1].deinterleave();

             R5  += R3  * C_6;
             R5p += R3p * C_6;

             R7  = R2  + R4;
             R7p = R2p + R4p;

             R7  = R7  << C_2;
             R7p = R7p << C_2;

             R1  += R5  + R7;
             R1p += R5p + R7p;

             pB[Addr2].interleave() = (R1,R1p);
         }
     }

     C_1   = 1  ;
     C_64  = 64 ;
     C_128 = 128;
     C_M7  = -7 ;

    for (int i = 0; i < (height - 3)/2; i++)
    {
        for(int j = 0; j < width/(2*VCOP_SIMD_WIDTH) +1; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*width*ELEMSZ1    + j*VECTORSZ1;
            Addr2 = i*(width/2)*ELEMSZ + j*VECTORSZ;

            R1 = (pB+0*width*2)[Addr1].ds2();
            R2 = (pB+1*width*2)[Addr1].ds2();
            R3 = (pB+3*width*2)[Addr1].ds2();
            R4 = (pB+4*width*2)[Addr1].ds2();

            R1 += C_64 - R4;
            R6  = R2   - R3;

            R6 = R6 << C_1;

            R1 += R6;

            R  = R1 << C_M7;

            R  = R + C_128;

            pOut[Addr2] = R;
        }
    }

}

/* ======================================================================== */
/*  End of file: vcop_gradient5x5PyramidKernel_8_kernel.k                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
