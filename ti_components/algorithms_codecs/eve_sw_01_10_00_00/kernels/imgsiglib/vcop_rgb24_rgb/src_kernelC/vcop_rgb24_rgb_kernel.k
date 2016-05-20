/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb24_rgb : Test bench data                         */ 
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit data in     */
/* the form of 8-bit "r", "g" and "b", and writes out seperate     */
/* 8-bit "r", 8-bit "g" and "b". The reason for having this        */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb24_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb24[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b". Since we are       */
/* packing 24-bit pixels in 32-bit memory, the actual size of      */
/* the input buffer "rgb24" is (3 * npixels) >> 2 and each of      */
/* the output buffers "r", "g" and "b" are of size "npixels".      */
/*                                                                 */
/*=================================================================*/
/*-----------------------------------------------------------------*/

#define K0                  0
#define K1                  1
#define K2                  2
#define K3                  3
#define K4                  4
#define K5                  5
#define K6                  6
#define K7                  7

/*----------------------------------------------------------------*/
/* Increment by 6 words for every 8 words we read. Therefore we   */
/* deduct 2, from IN_VECTORSZ. We write out 8 elements, at a      */
/* time.                                                          */
/*----------------------------------------------------------------*/

#define IN_ELEMSZ           sizeof(*rgb24)
#define IN_VECTORSZ         (IN_ELEMSZ * (VCOP_SIMD_WIDTH - 2))

#define OUT_ELEMSZ          sizeof(*r)
#define OUT_VECTORSZ        (OUT_ELEMSZ * VCOP_SIMD_WIDTH)

void vcop_rgb24_rgb
(
    __vptr_uint32  rgb24,
    __vptr_int8    rgbmask,
    unsigned int   npixels,
    __vptr_uint8   r,
    __vptr_uint8   g,
    __vptr_uint8   b 
)
{
   __vector  Vr,    Vg;
   __vector  Vb;
   __vector  Vrm,   Vgm;
   __vector  Vbm,   Vrs;
   __vector  Vgs,   Vbs;


   /*------------------------------------------------------------*/
   /* We use an outer loop to load various masks to extract      */
   /* bytes.                                                     */
   /*------------------------------------------------------------*/

   __agen Addr_m = 0;

   Vrm = (rgbmask +  0)[Addr_m];
   Vgm = (rgbmask +  8)[Addr_m];
   Vbm = (rgbmask + 16)[Addr_m];

   for (int I0 = 0; I0 < 1; I0++)
   {
       /*--------------------------------------------------------*/
       /* We work on VCOP_SIMD_WIDTH elements at a time, load    */
       /* the values, using custom load so that each way has     */
       /* one pixel of "r", "g" or "b".                          */
       /*--------------------------------------------------------*/

       for (int I1 = 0; I1 < (npixels/VCOP_SIMD_WIDTH); I1++)
       {
            __agen Addr_in;
            __agen Addr_out;

            Addr_in  = I1 * IN_VECTORSZ;
            Addr_out = I1 * OUT_VECTORSZ;

            Vr       = rgb24[Addr_in].dist(K0, K0, K1, K2, K3, K3, K4, K5);
            Vg       = rgb24[Addr_in].dist(K0, K1, K1, K2, K3, K4, K4, K5);
            Vb       = rgb24[Addr_in].dist(K0, K1, K2, K2, K3, K4, K5, K5);

            /*---------------------------------------------------*/
            /* The shift amounts to be applied are as follows:   */
            /*                                                   */
            /* R:  0 24 16  8   0 24  16   8                     */
            /* G:  8 0  24 16   8  0  16  24                     */
            /* B: 16 8   0 24  16  8   0  24                     */
            /*---------------------------------------------------*/

            Vrs      = (Vr << Vrm);  
            Vgs      = (Vg << Vgm);  
            Vbs      = (Vb << Vbm);  

            r[Addr_out]  = Vrs;
            g[Addr_out]  = Vgs;
            b[Addr_out]  = Vbs;
        }
    }
}


/*------------------------------------------------------------------*/
/*  End of file: vcop_mpy_32x32_to_64_kernel.k                      */
/* -----------------------------------------------------------------*/
/*             Copyright (c) 2012 Texas Instruments, Incorporated.  */
/*                            All Rights Reserved.                  */
/* =================================================================*/



