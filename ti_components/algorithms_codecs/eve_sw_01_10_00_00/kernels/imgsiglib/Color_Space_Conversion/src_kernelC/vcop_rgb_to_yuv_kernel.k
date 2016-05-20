/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_to_yuv                                          */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*                                                                 */
/* The function rgb_to_yuv, converts rgb to interleaved yuv.       */
/* by applying coefficients weighting red, blue and green,         */
/* to luma. Similarly we aplly a weighted product of red,          */
/* blue and green to U and V.                                      */
/*                                                                 */
/* A possible set of coefficients, to use is suggnsted at:         */
/* http://msdn.microsoft.com/en-us/library/ms893078.aspx           */
/*                                                                 */
/* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16          */
/* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128          */
/* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128          */
/*                                                                 */
/* The values from this equation, will have to be clamped          */
/* between 0..255.                                                 */
/*                                                                 */
/* This benchmark is intended to highlight the value of predicated */
/* stores to memory.                                               */
/*                                                                 */
/* API:                                                            */
/* void rgb_to_yuv                                                 */
/* (                                                               */
/*     unsigned char    iPtrR[],                                   */
/*     unsigned char    iPtrG[],                                   */
/*     unsigned char    iPtrB[],                                   */
/*     unsigned short   width,                                     */
/*     short            coefs[],                                   */
/*     unsigned char    iPtrOut[]                                  */
/* )                                                               */
/*                                                                 */
/* The function "rgb_to_yuv" accepts red, green and blue pixels    */
/* in arrays "iPtrR", "iPtrG" and "iPtrB" into an interleaved      */
/* array of YUYV pixels stored in "iPtrOut" by applying a 3x3      */
/* array of coefficients to convert from RGB to YUV space.         */
/*                                                                 */
/*=================================================================*/


#define ELEMBSZ    (sizeof (*iPtrR))
#define VECTORBSZ  (VCOP_SIMD_WIDTH * ELEMBSZ)
#define VECTOROSZ  (2 * VCOP_SIMD_WIDTH * ELEMBSZ)

void rgb_to_yuv 
(
    __vptr_uint8     iPtrR,
    __vptr_uint8     iPtrG,
    __vptr_uint8     iPtrB,
    unsigned short   width,
    short            coefs_r,
    short            coefs_g,
    short            coefs_b,
    __vptr_int16     coefs,
    __vptr_uint8     iPtrOut
)
{
    __vector  Vry0,    Vgy0,    Vby0;
    __vector  Vru_rv0, Vgu_gv0, Vbu_bv0;
    __vector  Vy0,     Vuv0,    Vred;
    __vector  Vgrn,    Vblu;

     Vry0  =  coefs_r;
     Vgy0  =  coefs_g;
     Vby0  =  coefs_b;

    for (int I0 = 0; I0 < 1; I0++)
    {
       __agen Addr_c  = I0 * 0;

       Vru_rv0     = (coefs +  6)[Addr_c].circ2();
       Vgu_gv0     = (coefs + 10)[Addr_c].circ2();
       Vbu_bv0     = (coefs + 14)[Addr_c].circ2();

       for (int I1 =0; I1 < (width/VCOP_SIMD_WIDTH); I1++)
       {
           __agen Addr_i = (I1 * VECTORBSZ);
	   __agen Addr_o = (I1 * VECTOROSZ);

	   Vuv0   =    0x8000U;

	   Vred   =  (iPtrR)[Addr_i].npt();
	   Vgrn   =  (iPtrG)[Addr_i].npt();
	   Vblu   =  (iPtrB)[Addr_i].npt();

	   Vy0    =  (Vry0     *  Vred);
	   Vuv0  +=  (Vru_rv0  *  Vred);

	   Vy0   +=  (Vgy0     *  Vgrn);
	   Vuv0  +=  (Vgu_gv0  *  Vgrn);

	   Vy0   +=  (Vby0     *  Vblu);
	   Vuv0  +=  (Vbu_bv0  *  Vblu);

	   (iPtrOut)[Addr_o].interleave() = (Vuv0, Vy0).round(8).saturate(0,255);
       }
   }
}

/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv_kernel.k                          */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

