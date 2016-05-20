/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_hamming_distance_kernel.k                                     */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing hamming distance between two input*/
/* byte array string pointers each having "ysize" number of byte array      */
/* elements each having a size of "xsize" and pitch of "xpitch" in bytes    */
/* Hamming distance indicates the total number of bit locations wherein the */
/* two input strings differ.                                                */
/*                                                                          */
/* Hamming distance kernel accepts two input byte array string pointers of  */
/* type unsigned char in "pString1", "pString2" of length "ysize * xpitch"  */
/* in bytes. The kernel writes the result in an unsigned int output pointer */
/* "pHammingDistance"                                                       */
/*                                                                          */
/* The following functions are supported:                                   */
/*  1. vcop_hamming_distance - Used for computing hamming distance          */
/*     when "xsize" > 128 & non-multiple of 128                             */
/*                                                                          */
/*  2. vcop_hamming_distance_multiple_128 - Used for computing hamming      */
/*     distance when the "xsize" is an exact multiple of 128                */
/*                                                                          */
/*  3. vcop_hamming_distance_size_lt_128 - Used for computing hamming       */
/*     distance when the "xsize" is less than 128                           */
/*                                                                          */
/*           Computes the hamming distance between two input byte array     */
/*           string pointers. Each byte array pointer is represented        */
/*           as depicted below                                              */
/*     Supports the following two modes                                     */
/*       1. mode = 0 :Many-to-One                                           */
/*          pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[0]);*/
/*       2. mode = 1 :One-to-One                                            */
/*          pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[i]);*/
/*       where i = 0,1,2, ...ySize-1                                        */
/*                                                                          */
/*                 xpitch                             xpitch                */
/*       <----------------------->          <----------------------->       */
/*            xsize                              xsize                      */
/*       <---------->                       <---------->                    */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[0]            |          |bytearr2[0]            |       */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[1]            |          |bytearr2[1]            |       */
/*       |-----------------------|          |-----------------------|       */
/*       |                       |          |                       |       */
/*       |                       |          |                       |       */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[ysize-1]      |          |bytearr2[ysize-1]      |       */
/*       |-----------------------|          |-----------------------|       */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Input strings are of 8-bit                                          */
/*   2. "xsize" & "xpitch" is specified in bytes                            */
/*   3. Maximum value of "ysize*xpitch" is 4096 bytes                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_hamming_distance          ~ 3/64 i.e.,(4/128 + 1/64)              */
/*   Above estimate is true when xsize is multiple of 128 and excludes      */
/*   overheads. Recommended xsize is multiple of 128 bytes to achieve       */
/*   optimal performance and larger the xsize, the better the performance   */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (July 2013) : Base version.                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ              sizeof(*pString1)
#define ELEMSZBYTE          sizeof(*pStringByte1)
#define VECTORSZ            (2 * VCOP_SIMD_WIDTH*ELEMSZ)
#define VECTORSZBYTE        (2 * VCOP_SIMD_WIDTH*ELEMSZBYTE)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)
#define VCOP_4SIMD_WIDTH    (4 * VCOP_SIMD_WIDTH)
#define VCOP_8SIMD_WIDTH    (8 * VCOP_SIMD_WIDTH)


/*  vcop_hamming_distance - Used for computing hamming distance             */
/*  when "xsize" > 32 & non-multiple of 32                                  */
void vcop_hamming_distance
(
   __vptr_uint32 pString1,         // input 1 data word pointer
   __vptr_uint32 pString2,         // input 2 data word pointer
   __vptr_uint8  pStringByte1,     // input 1 data byte pointer
   __vptr_uint8  pStringByte2,     // input 2 data byte pointer
    unsigned int xsize,            // size of input string element in bytes
    unsigned int ysize,            // number of byte array elements in intput string
    unsigned int mode,             // mode 0: many to one; mode 1: one to one
    unsigned int xpitch,           // pitch of each input string byte array element
   __vptr_uint32 pHammingDistance, // output data pointer
   __vptr_uint16 pScratch          // scratch pointer
)
{
    for(int I1 = 0; I1 < (ysize+1)/2; I1++)
    {
      __vector Vout1, Vout2;
      __agen AddrOut;

      AddrOut = I1*sizeof(*pScratch)*2*VCOP_SIMD_WIDTH;

      Vout1 = 0;
      Vout2 = 0;

      //Compute the hamming distance vector outputs for the bytes up to
      //the nearest multiple of VCOP_4SIMD_WIDTH for 'xsize' parameter
      for(int I2 = 0; I2 < (xsize)/VCOP_4SIMD_WIDTH; I2++)
      {
        __agen Addr1, Addr2;
        __vector Vin11, Vin12, Vin21, Vin22;
        __vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;

        Addr1 = I1*2*xpitch + I2*VCOP_4SIMD_WIDTH;
        Addr2 = I1*2*xpitch*mode + I2*VCOP_4SIMD_WIDTH;

        Vin11 = pString1[Addr1];
        Vin21 = pString2[Addr2];

        Vin12 = (pString1 + xpitch)[Addr1];
        Vin22 = (pString2 + xpitch*mode)[Addr2];

        // Takes 1 cycle using two functional units in parallel
        Vxor1    = Vin11 ^ Vin21;
        Vxor2    = Vin12 ^ Vin22;

        // Takes 1 cycles using two functional units in parallel
        Vbitcnt1 = count_bits(Vxor1);
        Vbitcnt2 = count_bits(Vxor2);

        Vout1 += Vbitcnt1;
        Vout2 += Vbitcnt2;
      }
      pScratch[AddrOut] = Vout1.saturate(0x0, 0x0, 0xFFFF, 0xFFFF);
      (pScratch + sizeof(*pScratch)*VCOP_SIMD_WIDTH)[AddrOut] = Vout2.saturate(0x0, 0x0, 0xFFFF, 0xFFFF);
    }

   //Compute the hamming distance for the remaining bytes which is not a multiple of 32 reading one byte at a time
   for(int I1 = 0; I1 < ysize; I1++)
   {
     __agen AddrOut;
     __vector Vout1, Vout2;

     AddrOut = I1*sizeof(*pHammingDistance);
     Vout1 = 0;

     for(int I2 = 0; I2 < (xsize % VCOP_4SIMD_WIDTH); I2++)
     {
       __agen Addr1, Addr2;
       __vector Vin11, Vin12, Vin21, Vin22;
       __vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;

       Addr1 = I1*xpitch + I2*ELEMSZBYTE;
       Addr2 = I1*xpitch*mode + I2*ELEMSZBYTE;

       Vin11 = (pStringByte1 + (xsize/VCOP_4SIMD_WIDTH)*VCOP_4SIMD_WIDTH)[Addr1].onept();
       Vin21 = (pStringByte2 + (xsize/VCOP_4SIMD_WIDTH)*VCOP_4SIMD_WIDTH)[Addr2].onept();

       Vxor1 = Vin11 ^ Vin21;

       Vbitcnt1 = count_bits(Vxor1);

       Vout1 += Vbitcnt1;
     }
     pHammingDistance[AddrOut].onept() = Vout1.saturate(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
   }

   //Sum the counts within the scratch buffer vector to get the final
   //hamming distance output
   for(int I1 = 0; I1 < ysize; I1++)
   {
     __agen AddrOut;
     __vector Vout1, Vout2;

     AddrOut = I1*sizeof(*pHammingDistance);

     Vout1 = pHammingDistance[AddrOut].onept();

     for (int I2 = 0; I2 < VCOP_SIMD_WIDTH; I2++)
     {
       __agen Addr1;
       __vector Vin;

       Addr1 = I1*sizeof(*pScratch)*VCOP_SIMD_WIDTH + I2*sizeof(*pScratch);

       Vin = pScratch[Addr1].onept();

       Vout1 += Vin;
     }
     pHammingDistance[AddrOut].onept() = Vout1.saturate(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
   }
}


#define Vout1 V8
#define Vout2 V10
#define Vin11 V0
#define Vin12 V2
#define Vin21 V4
#define Vin22 V6
#define Vxor1 V1
#define Vxor2 V3
#define Vbitcnt1 V5
#define Vbitcnt2 V7

/*  vcop_hamming_distance_multiple_32 - Used for computing hamming          */
/*  distance when the "xsize" is an exact multiple of 32                    */
void vcop_hamming_distance_multiple_32
(
  __vptr_uint32  pString1,          // input 1 data pointer
  __vptr_uint32  pString2,          // input 2 data pointer
  unsigned int   xsize,             // size of input string element in bytes
  unsigned int   ysize,             // number of byte array elements in input string
  unsigned int   mode,              // mode 0: many to one; mode 1: one to one
  unsigned int   xpitch,            // pitch of each input string byte array element
  __vptr_uint32  pHammingDistance,  // output data pointer
  __vptr_uint16  pScratch           // scratch pointer
)
{
    //__vector Vout1, Vout2, Vin11, Vin12, Vin21, Vin22;
    //__vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;
    for(int I2 = 0; I2 < (ysize+1)/2; I2++)
    {
      //__vector Vout1, Vout2;
      __agen AddrOut;

      AddrOut = I2*sizeof(*pScratch)*2*VCOP_SIMD_WIDTH;

      Vout1 = 0;
      Vout2 = 0;

      //Compute the hamming distance vector outputs for the bytes up to
      //the nearest multiple of VCOP_4SIMD_WIDTH for 'xsize' parameter
      for (int I3 = 0; I3 < (xsize)/VCOP_4SIMD_WIDTH; I3++)
      {
        __agen Addr1, Addr2;
        //__vector Vin11, Vin12, Vin21, Vin22;
        //__vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;

        Addr1 = I2*2*xpitch + I3*VCOP_4SIMD_WIDTH;
        Addr2 = I2*2*xpitch*mode + I3*VCOP_4SIMD_WIDTH;

        Vin11 = (pString1)[Addr1];
        Vin21 = (pString2)[Addr2];

        Vin12 = (pString1 + xpitch)[Addr1];
        Vin22 = (pString2 + xpitch*mode)[Addr2];

        // Takes 1 cycle using two functional units in parallel
        Vxor1 = Vin11 ^ Vin21;
        Vxor2 = Vin12 ^ Vin22;

        // Takes 1 cycles using two functional units in parallel
        Vbitcnt1 = count_bits(Vxor1);
        Vbitcnt2 = count_bits(Vxor2);

        Vout1 += Vbitcnt1;
        Vout2 += Vbitcnt2;
      }
      pScratch[AddrOut] = Vout1.saturate(0x0, 0x0, 0xFFFF, 0xFFFF);
      (pScratch + sizeof(*pScratch)*VCOP_SIMD_WIDTH)[AddrOut] = Vout2.saturate(0x0, 0x0, 0xFFFF, 0xFFFF);
    }

    //Sum the counts within the scratch buffer vector to get the final
    //hamming distance output
    for(int I2 = 0; I2 < (ysize+1)/2; I2++)
    {
      __agen AddrOut;
      //__vector Vout1, Vout2;

      AddrOut = I2*2*sizeof(*pHammingDistance);

      Vout1 = 0;
      Vout2 = 0;

      for(int I3 = 0; I3 < VCOP_SIMD_WIDTH; I3++)
      {
        __agen Addr1;
        __vector Vin1, Vin2;

        Addr1 = I2*2*sizeof(*pScratch)*VCOP_SIMD_WIDTH + I3*sizeof(*pScratch);

        Vin1 = pScratch[Addr1].onept();
        Vin2 = (pScratch + sizeof(*pScratch)*VCOP_SIMD_WIDTH)[Addr1].onept();

        Vout1 += Vin1;
        Vout2 += Vin2;
      }
      pHammingDistance[AddrOut].onept() = Vout1.saturate(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
      (pHammingDistance + sizeof(*pHammingDistance))[AddrOut].onept() = Vout2.saturate(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
    }
}

/*  vcop_hamming_distance_size_lt_32 - Used for computing hamming           */
/*  distance when the "xsize" is less than 32                               */
void vcop_hamming_distance_size_lt_32
(
  __vptr_uint8  pStringByte1,     // input 1 data byte pointer
  __vptr_uint8  pStringByte2,     // input 2 data byte pointer
  unsigned int  xsize,            // size of input string element in bytes
  unsigned int  ysize,            // number of byte array elements in intput string
  unsigned int  mode,             // mode 0: many to one; mode 1: one to one
  unsigned int  xpitch,           // pitch of each input string byte array element
  __vptr_uint32 pHammingDistance  // output data pointer
)
{
  //Computes the hamming distance output by reading 1 byte at a time
  for(int I1 = 0; I1 < (ysize+1)/2; I1++)
  {
    __agen AddrOut = 0;
    //__vector Vout1, Vout2;

    AddrOut = I1*2*sizeof(*pHammingDistance);

    Vout1 = 0;
    Vout2 = 0;

    for(int I2 = 0; I2 < xsize; I2++)
    {
      __agen Addr1, Addr2;
      //__vector Vin11, Vin12, Vin21, Vin22;
      //__vector Vxor1, Vxor2, Vbitcnt1, Vbitcnt2;

      Addr1 = I1*2*xpitch + I2*ELEMSZBYTE;
      Addr2 = I1*2*xpitch*mode + I2*ELEMSZBYTE;

      Vin11 = pStringByte1[Addr1].onept();
      Vin21 = pStringByte2[Addr2].onept();

      Vin12 = (pStringByte1 + xpitch)[Addr1].onept();
      Vin22 = (pStringByte2 + xpitch*mode)[Addr2].onept();

      Vxor1 = Vin11 ^ Vin21;
      Vxor2 = Vin12 ^ Vin22;

      Vbitcnt1 = count_bits(Vxor1);
      Vbitcnt2 = count_bits(Vxor2);

      Vout1 += Vbitcnt1;
      Vout2 += Vbitcnt2;
    }
    pHammingDistance[AddrOut].onept() = Vout1.saturate(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
    (pHammingDistance + sizeof(*pHammingDistance))[AddrOut].onept() = Vout2.saturate(0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF);
  }
}

#if 0
#undef Vout1
#undef Vout2
#undef Vin11
#undef Vin12
#undef Vin21
#undef Vin22
#undef Vxor1
#undef Vxor2
#undef Vbitcnt1
#undef Vbitcnt2
#endif

/*----------------------------------------------------------------------------*/
/* End of file: vcop_hamming_distance_kernel.k                                */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2013.                                  */
/*============================================================================*/
