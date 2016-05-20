/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_update_ewr_mean_s16                                        */
/*                                                                          */
/*  Driver file for testing                                                 */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_vec_      */
/*   update_ewr_mean_s16" function by injecting it with the same data set   */
/*  as in the assembly testbench functions.                                 */
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
#include <stdlib.h>

#include <vcop.h>

#include "test_profile.h"

#if VCOP_HOST_EMULATION
  #include "vcop_vec_update_ewr_mean_s16_kernel.k"    // kernel source
#else
void vcop_vec_update_ewr_mean_s16
(
    __vptr_int16   currentMean,
    __vptr_uint8   newestData,
    __vptr_uint8   foreground,
    unsigned short weight,
    unsigned short weight_neg,
    unsigned int   frameSize
);
#endif

#define NUM_PIXELS   (32)
#define UPDATE_RATE  (0x10)

#pragma DATA_SECTION(newLuma, "Adata");
unsigned char newLuma[32]   =
{
    0x000, 0x001, 0x002, 0x003, 0x004, 0x005, 0x006, 0x007,
    0x008, 0x009, 0x00a, 0x00b, 0x00c, 0x00d, 0x00e, 0x00f,
    0x010, 0x011, 0x012, 0x013, 0x014, 0x015, 0x016, 0x017,
    0x018, 0x019, 0x01a, 0x01b, 0x01c, 0x01d, 0x01e, 0x01f
};

#pragma DATA_SECTION(mask32packed, "Bdata");
unsigned char mask32packed[16] = {0xC0,0x07,0xFF,0xFF};

#pragma DATA_SECTION(runningMean, "Cdata");
short runningMean[32] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800,
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000
};

#pragma DATA_SECTION(trueRunningMean, "EOutdata");
short trueRunningMean[32] =
{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0800, 0x0800, 0x0800, 0x07FF, 0x07FF, 0x07FF, 0x07FF, 0x07FF,
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
    0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000
};


#pragma DATA_SECTION(profile_array, "Cdata");
unsigned int profile_array[2];

int main()
{
    int fail;
    int i;
#ifdef REPORT
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
#endif
    FILE* fpReport = fopen("../../../report.csv","a+");
#endif

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/

#if VCOP_HOST_EMULATION
#else
    unsigned int t0, t1;
    _tsc_start();
#endif

    //For profiling, use 2 as loop counter
    for (i = 0; i < 1; i++)
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

        vcop_vec_update_ewr_mean_s16(runningMean,newLuma,mask32packed,
                                     UPDATE_RATE,2^16-1-UPDATE_RATE,NUM_PIXELS);
#ifdef REPORT
#ifdef SCTM
        sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
        overflow = EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
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
    fail = memcmp (runningMean, trueRunningMean, NUM_PIXELS);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/
#ifdef REPORT
    fprintf(fpReport,"vcop_vec_update_ewr_mean_s16,");
    fprintf(fpReport,"%d,",NUM_PIXELS);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",NUM_PIXELS);
    fprintf(fpReport,"%d,",1);
    fprintf(fpReport,"%d,",1);
#endif

    if (fail)
    {
#ifdef CONSOLE
        for (i = 0; i < NUM_PIXELS; i++)
        {
             printf ("i:%d, out:%u, EOut:%u, %c \n",
                      i, runningMean[i], trueRunningMean[i],
                      (runningMean[i]!=trueRunningMean[i]) ? '*':' '
                    );
        }
#endif

#ifdef REPORT
        fprintf(fpReport,"FAIL,");
#endif
    }
    else {
#ifdef CONSOLE
        printf("Pass\n");
#endif
#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif
    }

#if VCOP_HOST_EMULATION
#else
#ifdef CONSOLE
    for(i = 0; i < 2; i++)
        printf("Time taken: %d cycles \n", profile_array[i]);
#endif
#endif

#ifdef REPORT
#ifdef SCTM
    fprintf(fpReport,"%d\n",exec_diff);
#endif
    if(fpReport){
        fclose(fpReport);
    }
#endif
}

/* ======================================================================== */
/*  End of file:  vcop_vec_update_ewr_mean_s16.c                            */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
