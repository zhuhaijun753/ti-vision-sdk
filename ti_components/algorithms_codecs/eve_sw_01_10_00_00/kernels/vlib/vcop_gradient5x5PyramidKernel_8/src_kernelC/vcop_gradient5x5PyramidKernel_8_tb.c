/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_gradient5x5PyramidKernel_8                                     */
/*                                                                          */
/*  Driver file for testing Gradient Pyramid - 8 bit                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_gradient  */
/*  5x5PyramidKernel_8" function by injecting it with the same data set as  */
/*  in the  natural C testbench functions.                                  */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <string.h>
#include <vcop.h>

#include "test_profile.h"

#define BLOCK_WIDTH  (16)
#define BLOCK_HEIGHT (16)

#if VCOP_HOST_EMULATION
  #include "vcop_gradient5x5PyramidKernel_8_kernel.k"  // kernel source
#else
void  vcop_gradientV5x5PyramidKernel_8
(
    __vptr_uint8    pIn,
    __vptr_int16    pB,
    unsigned short  width,
    unsigned short  pitch,
    unsigned short  height,
    __vptr_uint8    pOut
);


void vcop_gradientH5x5PyramidKernel_8
(
    __vptr_uint8    pIn,
    __vptr_int16    pB,
    unsigned short  width,
    unsigned short  pitch,
    unsigned short  height,
    __vptr_uint8    pOut
);
#endif

#pragma DATA_SECTION(InData_Gradient5x5PyramidKernel_8, "Adata");
unsigned char InData_Gradient5x5PyramidKernel_8[16*5+10] =
{

    0x97, 0x39, 0x74, 0xaa, 0x09, 0xf7, 0xd0, 0x8c,
    0x96, 0x3c, 0x58, 0x4d, 0x04, 0x06, 0xa2, 0x06,
    0x1f, 0x8f, 0xb2, 0x03, 0x87, 0x5b, 0x36, 0x9a,
    0xc1, 0xa1, 0x14, 0xa2, 0x89, 0x96, 0x80, 0xe0,
    0xd6, 0x71, 0x09, 0x1c, 0x35, 0xd3, 0x62, 0xd9,
    0x95, 0xe9, 0xe7, 0x7f, 0x73, 0xcb, 0xb1, 0x2a,
    0x3e, 0x9b, 0x03, 0x67, 0x7f, 0x10, 0x87, 0x83,
    0xd3, 0x9e, 0x09, 0x02, 0x6a, 0xe3, 0xf9, 0xff,
    0x97, 0x39, 0x74, 0xaa, 0x09, 0xf7, 0xd0, 0x8c,
    0x96, 0x3c, 0x58, 0x4d, 0x04, 0x06, 0xa2, 0x06,

};

#pragma DATA_SECTION(Temp_Gradient5x5PyramidKernel_8, "Bdata");
short Temp_Gradient5x5PyramidKernel_8[16*5+10];

#pragma DATA_SECTION(trueOutData_GradientH5x5PyramidKernel_8, "Eoutdata");
unsigned char trueOutData_GradientH5x5PyramidKernel_8[6] =
{
    149, 103, 109, 128, 156, 100
};

#pragma DATA_SECTION(trueOutData_GradientV5x5PyramidKernel_8, "Eoutdata");
unsigned char trueOutData_GradientV5x5PyramidKernel_8[6] =
{
    137, 129, 126, 127, 139, 134
};

#pragma DATA_SECTION(calculatedOutData_GradientH5x5PyramidKernel_8, "Cdata");
unsigned char calculatedOutData_GradientH5x5PyramidKernel_8[6+10];

#pragma DATA_SECTION(calculatedOutData_GradientV5x5PyramidKernel_8, "Cdata");
unsigned char calculatedOutData_GradientV5x5PyramidKernel_8[6+10];

#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2];

int main( )
{

    int i, fail_h, fail_v;

#ifdef REPORT
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
#endif
    FILE* fpReport = fopen("../../../report.csv","a+");
#endif

#if VCOP_HOST_EMULATION
#else
    unsigned int t0, t1;
    _tsc_start();
#endif

   for (i = 0; i < 2; i++)
   {
#if VCOP_HOST_EMULATION
#else
        t0 = _tsc_gettime();
#endif

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
#ifdef REPORT
#ifdef SCTM
        EVE_SCTM_Enable(CTM);
        EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
        EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
        sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif
        vcop_gradientH5x5PyramidKernel_8(InData_Gradient5x5PyramidKernel_8,
                                         Temp_Gradient5x5PyramidKernel_8,
                                         BLOCK_WIDTH-4,
                                         BLOCK_HEIGHT,
                                         5,
                                         calculatedOutData_GradientH5x5PyramidKernel_8);

        vcop_gradientV5x5PyramidKernel_8(InData_Gradient5x5PyramidKernel_8,
                                         Temp_Gradient5x5PyramidKernel_8,
                                         BLOCK_WIDTH-4,
                                         BLOCK_HEIGHT,
                                         5,
                                         calculatedOutData_GradientV5x5PyramidKernel_8);
#ifdef REPORT
#ifdef SCTM
        sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
        overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
        assert(overflow!=1);

        exec_diff = sctm_t2 - sctm_t1;
        EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif
#endif

#if VCOP_HOST_EMULATION
#else
        t1 = _tsc_gettime();
        profile_array[i]  = (t1 - t0);
#endif
    }

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail_h = memcmp(calculatedOutData_GradientH5x5PyramidKernel_8,
                    trueOutData_GradientH5x5PyramidKernel_8, 6);

    fail_v = memcmp(calculatedOutData_GradientV5x5PyramidKernel_8,
                    trueOutData_GradientV5x5PyramidKernel_8, 6);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
    fprintf(fpReport,"vcop_gradient5x5PyramidKernel_8,");
    fprintf(fpReport,"%d,",BLOCK_WIDTH);
    fprintf(fpReport,"%d,",BLOCK_HEIGHT);
    fprintf(fpReport,"%d,",BLOCK_WIDTH);
    fprintf(fpReport,"%d,",BLOCK_HEIGHT);
    fprintf(fpReport,"1,");
#endif

    if (fail_h)
    {
#ifdef CONSOLE
        for (i = 0; i < 6; i++)
        {
             printf("i:%d, out:%u, EOut:%u, %c \n",
                   i,
                   calculatedOutData_GradientH5x5PyramidKernel_8[i],
                   trueOutData_GradientH5x5PyramidKernel_8[i],
                   (calculatedOutData_GradientH5x5PyramidKernel_8[i]!=
                   trueOutData_GradientH5x5PyramidKernel_8[i])
                   ? '*':' '
                   );
        }
#endif
    }

    if (fail_v)
    {
#ifdef CONSOLE
        for (i = 0; i < 6; i++)
        {
             printf("i:%d, out:%u, EOut:%u, %c \n",
                   i,
                   calculatedOutData_GradientV5x5PyramidKernel_8[i],
                   trueOutData_GradientV5x5PyramidKernel_8[i],
                   (calculatedOutData_GradientV5x5PyramidKernel_8[i]!=
                   trueOutData_GradientV5x5PyramidKernel_8[i])
                   ? '*':' '
                   );
        }
#endif
    }

    if(!fail_h & !fail_v){
#ifdef CONSOLE
        printf ("Pass \n");
#endif
#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif
    }
    else{
#ifdef CONSOLE
        printf("Fail \n");
#endif
#ifdef REPORT
        fprintf(fpReport,"FAIL,");
#endif
    }

#if VCOP_HOST_EMULATION
#else
#ifdef CONSOLE
    for(i = 0; i < 2; i++)
        printf ("Time taken: %d cycles \n", profile_array[i]);
#endif
#endif

#ifdef REPORT
#ifdef SCTM
    fprintf(fpReport,"%d\n",exec_diff);
#endif

    if(fpReport) {
        fclose(fpReport);
    }
#endif
}

/* ======================================================================== */
/*  End of file:  vcop_gradient5x5PyramidKernel_8.c                         */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
