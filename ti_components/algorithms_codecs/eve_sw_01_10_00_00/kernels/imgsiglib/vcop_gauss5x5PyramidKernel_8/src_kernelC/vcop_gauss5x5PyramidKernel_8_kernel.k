/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_gauss5x5PyramidKernel_8_kernel                                  */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_gauss5x5PyramidKernel_8_horiz                              */
/*     (                                                                    */
/*         __vptr_uint8   pIn,                                              */
/*         __vptr_uint8   pOut,                                             */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short inPitch,                                          */
/*         unsigned short outPitch                                          */
/*     )                                                                    */
/*                                                                          */
/*     void vcop_gauss5x5PyramidKernel_8_vert                               */
/*     (                                                                    */
/*         __vptr_uint8   pIn,                                              */
/*         __vptr_uint8   pOut,                                             */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsinged short inPitch                                           */
/*         unsinged short outPitch                                           */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  8-bit input image                                        */
/*     pB       :  Intermediate buffer                                      */
/*     inCols   :  Number of coluns in the image                            */
/*     inRows   :  Number of rows in the image                              */
/*     pOut     :  8-bit output image                                       */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of Gaussian pyramid in the pOut array.                        */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 8.  */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_SIMD_WIDTH2 (2*VCOP_SIMD_WIDTH)
#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD2(a)   (((a) + (2*VCOP_SIMD_WIDTH)-1) & ~(2*VCOP_SIMD_WIDTH-1))

/*--------------------------------------------------------------------------------*/
/* Input to this kernel is WxH block and output of this kernel is (W/2) x H block */
/*--------------------------------------------------------------------------------*/
void vcop_gauss5x5PyramidKernel_8_horiz
(
    __vptr_uint8   pIn,
    __vptr_uint8   pOut,
    unsigned short width,
    unsigned short height,
    unsigned short inPitch,
    unsigned short outPitch
)
{

    __vector vIn024_14, vIn135_15,	vIn246_16, vIn357_17, vIn468_18, vIn579_19, vTemp, C_4, C_6;
    __vector  vTemp1,vTemp2;

    C_4 = 4;
    C_6 = 6;

    for( int i = 0; i < height; i++)
    {
        for(int j = 0; j < ALIGN_SIMD2(width)/VCOP_SIMD_WIDTH2; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*inPitch*ELEMSZ  + j*2*VECTORSZ;
            Addr2 = i*outPitch*ELEMSZ + j*VECTORSZ;

            (vIn024_14, vIn135_15)= (pIn)[Addr1].deinterleave();
            (vIn246_16, vIn357_17)= (pIn+ 2*ELEMSZ)[Addr1].deinterleave();
            (vIn468_18, vIn579_19)= (pIn+ 4*ELEMSZ)[Addr1].deinterleave();

            vTemp1      = vIn135_15 + vIn357_17;
            vTemp2      = vIn468_18 + vIn024_14;
            vTemp       = vIn246_16*C_6;
            vTemp1      = vTemp1*C_4;
            vTemp2     += vTemp1 + vTemp;
            pOut[Addr2] = vTemp2.truncate(4);

        }
    }
}

/*----------------------------------------------------------------------------------*/
/* Input to this kernel is WxH block and output of this kernel is (W) x (H/2) block */
/*----------------------------------------------------------------------------------*/
void vcop_gauss5x5PyramidKernel_8_vert
(
    __vptr_uint8   pIn,
    __vptr_uint8   pOut,
    unsigned short width,
    unsigned short height,
    unsigned short inPitch,
    unsigned short outPitch
)
{
    __vector vec1_e,vec2_e,vec3_e,vec4_e, vec5_e, vTemp_e, vec1_o,vec2_o,vec3_o,vec4_o, vec5_o, vTemp_o, C_4, C_6;
    __vector  vTemp1,vTemp2;

    C_4 = 4;
    C_6 = 6;

    for(int i = 0; i < (height/2); i++)
    {
        for(int j = 0; j < ALIGN_SIMD2(width)/VCOP_SIMD_WIDTH2; j++)
        {
            __agen Addr1,Addr2;

            Addr1 = i*2*inPitch*ELEMSZ + j*2*VECTORSZ;
            Addr2 = i*outPitch*ELEMSZ  + j*2*VECTORSZ  ;

            (vec1_e, vec1_o) = (pIn                   )[Addr1].deinterleave();
            (vec2_e, vec2_o) = (pIn+   inPitch*ELEMSZ )[Addr1].deinterleave();
            (vec3_e, vec3_o) = (pIn+ 2*inPitch*ELEMSZ )[Addr1].deinterleave();
            (vec4_e, vec4_o) = (pIn+ 3*inPitch*ELEMSZ )[Addr1].deinterleave();
            (vec5_e, vec5_o) = (pIn+ 4*inPitch*ELEMSZ )[Addr1].deinterleave();

            vTemp1  = vec2_e + vec4_e;
            vec1_e += vec5_e;
            vTemp_e = vec3_e*C_6;
            vTemp1  = vTemp1*C_4;
            vec1_e  += vTemp_e + vTemp1   ;

            vTemp2  = vec2_o + vec4_o;
            vec1_o += vec5_o;
            vTemp_o = vec3_o*C_6;
            vTemp2  = vTemp2*C_4;
            vec1_o  += vTemp_o + vTemp2   ;

            pOut[Addr2].interleave() = (vec1_e, vec1_o).truncate(4);
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_gauss5x5PyramidKernel_8_kernel.k                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

