/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDeinterleave                                   */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDeinterleave" accepts  8 or 16-bit data */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 422 or */
/* 422 format, the output can be of 422, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCr422_Deinterleave422_char                         */
/* (                                                               */
/*     __vptr_uint32  YCbCr_char,                                  */
/*     __vptr_int8    YCbCrmask,                                   */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint8   Y_char,                                      */
/*     __vptr_uint8   Cb_char,                                     */
/*     __vptr_uint8   Cr_char                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop_YCbCr422_Deinterleave422_short                        */
/* (                                                               */
/*     __vptr_uint32  YCbCr_short,                                 */
/*     __vptr_int8    YCbCrmask,                                   */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  Y_short,                                     */
/*     __vptr_uint16  Cb_short,                                    */
/*     __vptr_uint16  Cr_short                                     */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/*=================================================================*/


#include <stdio.h>
#include <vcop.h>

#include "test_profile.h"

typedef unsigned short Uint16;
typedef unsigned char  Uint8;

#define NUM_SAMPLES1  32
#define NUM_PIXELS1   (NUM_SAMPLES1 * 4)

#pragma DATA_SECTION (YCbCr422_char, "Adata");
unsigned char YCbCr422_char[NUM_PIXELS1] =
{
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
};

#pragma DATA_SECTION (YCbCr422_short, "Adata");
unsigned short YCbCr422_short[NUM_PIXELS1] =
{
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,

};

#pragma DATA_SECTION (Y1, "Cdata");
unsigned char Y1[NUM_SAMPLES1 * 2] = {0};

/*-----------------------------------------------------------------------*/
/* !!!!! IMPORTANT !!!!                                                  */
/* Need enough room here (NUM_SAMPLES1 * 2) size so that Cb data does    */
/* NOT overwrite Cr data.                                                */
/*-----------------------------------------------------------------------*/

#pragma DATA_SECTION (Cb1, "Cdata");
#pragma DATA_ALIGN(Cb1, 32);
unsigned char Cb1[NUM_SAMPLES1 * 2] = {0};

/*-----------------------------------------------------------------------*/
/* !!!!! IMPORTANT !!!!                                                  */
/* Need enough room here (NUM_SAMPLES1 * 2) size so that Cr data does    */
/* NOT overwrite next buffer.                                            */
/*-----------------------------------------------------------------------*/

#pragma DATA_SECTION (Cr1, "Cdata");
#pragma DATA_ALIGN(Cr1, 32);
unsigned char Cr1[NUM_SAMPLES1 * 2] = {0};

#pragma DATA_SECTION (EY1, "EOutdata");
unsigned char EY1[NUM_SAMPLES1 * 2] =
{
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D, 0x7F, 0x3D,
};

#pragma DATA_SECTION (ECb1, "EOutdata");
unsigned char ECb1[NUM_SAMPLES1] =
{
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F
};

#pragma DATA_SECTION (ECr1, "EOutdata");
unsigned char ECr1[NUM_SAMPLES1] =
{
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
};

#pragma DATA_SECTION (Y2, "Cdata");
unsigned short Y2[NUM_SAMPLES1 * 2] = {0};

/*-----------------------------------------------------------------------*/
/* !!!!! IMPORTANT !!!!                                                  */
/* Need enough room here (NUM_SAMPLES1 * 2) size so that Cb data does    */
/* NOT overwrite Cr data.                                                */
/*-----------------------------------------------------------------------*/

#pragma DATA_SECTION (Cb2, "Cdata");
unsigned short Cb2[NUM_SAMPLES1 * 2] = {0};

/*-----------------------------------------------------------------------*/
/* !!!!! IMPORTANT !!!!                                                  */
/* Need enough room here (NUM_SAMPLES1 * 2) size so that Cr data does    */
/* NOT overwrite next buffer.                                            */
/*-----------------------------------------------------------------------*/

#pragma DATA_SECTION (Cr2, "Cdata");
unsigned short Cr2[NUM_SAMPLES1 * 2] = {0};

#pragma DATA_SECTION (EY2, "EOutdata");
unsigned char EY2[NUM_SAMPLES1 * 2] =
{
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,  0x7F, 0x3D, 0x7F, 0x3D,
};

#pragma DATA_SECTION (ECb2, "EOutdata");
unsigned char ECb2[NUM_SAMPLES1] =
{
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F,
    0x9A, 0x9F, 0x9A, 0x9F
};

#pragma DATA_SECTION (ECr2, "EOutdata");
unsigned char ECr2[NUM_SAMPLES1] =
{
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
    0xFF, 0xFA, 0xFF, 0xFA,
};

#if VCOP_HOST_EMULATION
  #include "vcop_YCbCr422Deinterleave_kernel.k"           // kernel source
#else
  #include "../inc/vcop_YCbCr422Deinterleave_kernel.h"    // translated kernel
#endif

void print_output();
int  verify_output();

int main()
{
    int ok;
#ifdef REPORT
    FILE* fpReport = fopen("../../../report.csv","a+");
    #ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
    EVE_SCTM_Enable(CTM);
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);

    sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    #endif
#endif
    vcop_YCbCr422_Deinterleave422_char
    (
        &YCbCr422_char[0],
        NUM_PIXELS1,
        Y1,
        Cb1,
        Cr1
    );

    vcop_YCbCr422_Deinterleave422_short
    (
        &YCbCr422_short[0],
        NUM_PIXELS1,
        Y2,
        Cb2,
        Cr2
    );

#ifdef REPORT
    #ifdef SCTM
    sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
    assert(overflow!=1);

    exec_diff = sctm_t2 - sctm_t1;
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
    #endif

    fprintf(fpReport,"YCbCr422Deinterleave,");
    fprintf(fpReport,"%d,",NUM_PIXELS1);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",NUM_PIXELS1);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",1);

    ok = verify_output();

    if(ok) {
        fprintf(fpReport,"PASS,");
    }
    else {
        fprintf(fpReport,"FAIL,");
    }
    #ifdef SCTM
        fprintf(fpReport,"%d\n",exec_diff);
    #endif
    if(fpReport){
        fclose(fpReport);
    }
#else
    ok = verify_output();
    if(ok)
       printf("PASS\n"); 
    else
       printf("FAIL\n"); 
#endif

    return 0;
}

void print_output()
{
   int i;

   printf("\n\n Y - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1 * 2; ++i)
   {
      printf("0x%2.2x, ", Y1[i]);

      if (!((i+1) % 8 ))
          printf("\n");
   }

   printf("\n\n Cb - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Cb1[i]);
      if (!((i+1) % 4 ))
          printf("\n");
   }

   printf("\n\n Cr - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Cr1[i]);
      if (!((i+1) % 4 ))
          printf("\n");
   }

   printf("\n\n Y - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1 * 2; ++i)
   {
      printf("0x%2.2x, ", Y2[i]);
      if (!((i+1) % 8 ))
          printf("\n");
   }

   printf("\n\n Cb - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Cb2[i]);
      if (!((i+1) % 4 ))
          printf("\n");
   }

   printf("\n\n Cr - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Cr2[i]);
      if (!((i+1) % 4 ))
          printf("\n");
   }
}

int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < NUM_SAMPLES1 * 2; ++i)
   {
      if (Y1[i] != EY1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Cb1[i] != ECb1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Cr1[i] != ECr1[i])
      {
          ok = 0;
      }
   }

   for (i = 0; i < NUM_SAMPLES1 * 2; ++i)
   {
      if (Y2[i] != EY2[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Cb2[i] != ECb2[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Cr2[i] != ECr2[i])
          ok = 0;
   }

  return (ok);

}

/*=================================================================*/
/* End of file: vcop_YCbCrDeinterleave.c                           */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/
