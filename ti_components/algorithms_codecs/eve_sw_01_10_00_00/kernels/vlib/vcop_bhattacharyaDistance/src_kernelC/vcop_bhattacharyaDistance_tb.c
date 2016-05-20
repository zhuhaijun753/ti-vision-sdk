/*==========================================================================*/
/*                                                                          */
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION        */
/*                                                                          */
/*  Property of Texas Instruments                                           */
/*  For Unrestricted Internal Use Only                                      */
/*  Unauthorized reproduction and/or distribution is strictly prohibited.   */
/*  This product is protected under copyright law and trade secret law      */
/*  as an unpublished work.                                                 */
/*  Created 2012, (C) Copyright 2012 Texas Instruments.                     */
/*  All rights reserved.                                                    */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vcop.h"

#include "test_profile.h"

#if VCOP_HOST_EMULATION
    #include "vcop_bhattacharyaDistance_kernel.k"
#else
    #include "vcop_bhattacharyaDistance_kernel.h"
    void eve_array_sqrt_intlv_lut_idx_log4
    (
        __vptr_uint16 in1_ptr,
        __vptr_uint16 TLU_idx_ptr,
        __vptr_uint8 log4_ptr,
        unsigned short num_data,
        int TLU_Qbits_p1,
        int idx_norm2
    );

    void eve_tlu_1c_hword
    (
        __vptr_uint16    Table,
        __vptr_uint16    inp_data,
        unsigned int     blk_hght,
        unsigned int    blk_wdth,
        __vptr_uint16    Out
    );

    void eve_array_sqrt_intlv_align
    (
        __vptr_uint16    in1_ptr,
        __vptr_uint8    log4_ptr,
        unsigned short    num_data,
        __vptr_uint32    out_ptr
    );
#endif


typedef unsigned short Uint16;
typedef unsigned char  Uint8;
typedef unsigned int   Uint32;
typedef int            Int32;


#define true   1
#define false  0

#define W_INPUT 8
#define H_INPUT 8
#define N    (W_INPUT*H_INPUT)

#define MANT_MIN    1
#define MANT_MAX    4
#define SQRT_QBITS  16
#define TLU_QBITS   8
#define TLU_SIZE    (1+(MANT_MAX*(1<<TLU_QBITS))-(1<<TLU_QBITS))

#define MAX_U16_B 65536


#pragma DATA_SECTION(X, "IBUFHA");
Uint16 X[N] =
{
    1, 2, 3, 1, 1, 2, 1, 1,
    2, 1, 3, 1, 2, 1, 2, 3,
    2, 1, 1, 1, 1, 2, 1, 2,
    1, 2, 1, 1, 1, 2, 3, 1,
    1, 1, 2, 3, 2, 1, 1, 2,
    3, 1, 2, 1, 1, 3, 2, 3,
    1, 1, 2, 3, 1, 3, 2, 1,
    2, 1, 2, 3, 1, 1, 2, 2
};

#pragma DATA_SECTION(Y, "IBUFLA");
Uint16 Y[N]=
{
    1, 2, 1, 1, 2, 3, 1, 2,
    1, 2, 3, 1, 1, 2, 2, 2,
    1, 2, 1, 1, 2, 1, 1, 2,
    2, 1, 1, 2, 1, 1, 2, 1,
    2, 2, 2, 1, 1, 2, 3, 2,
    3, 1, 1, 1, 1, 1, 2, 2,
    3, 2, 3, 2, 2, 1, 2, 2,
    3, 2, 3, 2, 2, 3, 2, 2
};

#pragma DATA_SECTION(in1, "WBUF");
Uint16 in1[N] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma DATA_SECTION(sqrt_LUT, "WBUF");
Uint16 sqrt_LUT[TLU_SIZE] = {0};

#pragma DATA_SECTION(sqrt_out, "WBUF");
Uint32 sqrt_out[N] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma DATA_SECTION (LUT_value, "WBUF");
Uint16 LUT_value[N] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma DATA_SECTION (LUT_idx, "WBUF");
Uint16 LUT_idx[N] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma DATA_SECTION (log4_data, "WBUF");
Uint8 log4_data[N] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma DATA_SECTION(UBD, "WBUF");
Uint32 UBD[1] = {0};


#pragma DATA_SECTION(gt_UBD, "EOutdata")
Uint32 gt_UBD[1] = {4294705157U};//{4267413128}; //3445728529;


void generate_sqrt_LUT
(
    int sqrt_Qbits,
    int TLU_Qbits,
    int lut_size,
    unsigned short *sqrt_LUT
);

void compute_sqrt
(
    Uint32 *sqrt_out,
    Uint32 *UBD
);

void print_output();


/* ------------------------------------------------------------------------------ */
/* Function to generate the lookup table for sqrt(mantissa(x))                    */
/* ------------------------------------------------------------------------------ */

void generate_sqrt_LUT(int sqrt_Qbits, int TLU_Qbits, int lut_size, unsigned short *sqrt_LUT)
{
    int i, table_scale, Q_sqrt;

    double x;

    table_scale = 1 << sqrt_Qbits;

    for(i = 0; i < lut_size; i++)
    {
        /* ---------------------------------------------------------------- */
        /* Get floating point mantissa                                      */
        /* ---------------------------------------------------------------- */

        x = ((double) (i + (1 << TLU_Qbits)))/((double) (1 << TLU_Qbits));


        /* ---------------------------------------------------------------- */
        /* Scale sqrt(mantissa) by sqrt_Qbits                               */
        /* ---------------------------------------------------------------- */

        Q_sqrt = (int) ((((double) table_scale) * sqrt(x)) + 0.5);


        /* ---------------------------------------------------------------- */
        /* Saturate                                                         */
        /* ---------------------------------------------------------------- */

        if(Q_sqrt > ((1 << 16) -1))
        {
            Q_sqrt = ((1 << 16) -1);
        }

        sqrt_LUT[i] = Q_sqrt;
    }
}

void compute_sqrt(Uint32 *sqrt_out, Uint32 *UBD)
{
    int i, count;
    unsigned int root, remHi, remLo, testDiv;// count;
    unsigned int BD = 0;

    for(i=0;i<(W_INPUT*H_INPUT);i++)
    {
        BD += sqrt_out[i];
    }

    BD = 1 - sqrt_out[0];

    root = 0; /* Clear root */
    remHi = 0; /* Clear high part of partial remainder */
    remLo = BD; /* Get argument into low part of partial remainder */

    //#pragma UNROLL(32)
    //#pragma MUST_ITERATE(32, 32, )

    for(count=31;count>=0;count--){
        remHi = (remHi<<2) | (remLo>>30);
        remLo <<= 2; /* get 2 bits of arg */
        root <<= 1; /* Get ready for the next bit in the root */
        testDiv = (root << 1) + 1; /* Test radical */
        if (remHi >= testDiv) {
            remHi -= testDiv;
            root++;
        }
    }
    UBD[0] = BD;
}


int main()
{
    int fail = 0;

#ifdef REPORT
    FILE* fpReport = fopen("../../../report.csv","a+");
#ifdef SCTM
    unsigned int sctm_t1, sctm_t2, exec_diff;
    unsigned int overflow;
    EVE_SCTM_Enable(CTM);
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
#endif
#endif

#ifdef CONSOLE
    printf("\nvcop_bhattacharyaDistance:\n");
    printf("Generating LUT\n");
#endif

    generate_sqrt_LUT(SQRT_QBITS, TLU_QBITS, TLU_SIZE, sqrt_LUT);

#ifdef CONSOLE
    printf("Invoking EVE kernels\n");
#endif

#if VCOP_HOST_EMULATION
#else
    unsigned int t0, t1;
    _tsc_start();
#endif

#ifdef REPORT
#ifdef SCTM
    sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif

#if VCOP_HOST_EMULATION
#else
    t0 = _tsc_gettime();
#endif

    vcop_bhattacharyaDistance
    (
        (short *)X,
        (short *)Y,
        W_INPUT*H_INPUT,
        (short *)in1
    );

    eve_array_sqrt_intlv_lut_idx_log4
    (
        in1,
        LUT_idx,
        log4_data,
        W_INPUT*H_INPUT,
        TLU_QBITS + 1,
        2*(1 << TLU_QBITS)
    );

    eve_tlu_1c_hword
    (
        sqrt_LUT,
        LUT_idx,
        H_INPUT,
        W_INPUT,
        LUT_value
    );

    eve_array_sqrt_intlv_align(LUT_value, log4_data, W_INPUT*H_INPUT, sqrt_out);

    compute_sqrt(sqrt_out, UBD);

#if VCOP_HOST_EMULATION
#else
    t1 = _tsc_gettime();
#endif

#ifdef REPORT
#ifdef SCTM
    sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
    overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
    assert(overflow!=1);

    exec_diff = sctm_t2 - sctm_t1;
    EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif
#endif

    //print_output();

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = memcmp(UBD, gt_UBD, 1);

#ifdef REPORT
    fprintf(fpReport,"vcop_bhattacharyaDistance,");
    fprintf(fpReport,"%d,",W_INPUT);
    fprintf(fpReport,"%d,",H_INPUT);
    fprintf(fpReport,"%d,",W_INPUT);
    fprintf(fpReport,"%d,",H_INPUT);
    fprintf(fpReport,"1,");
#endif

    if(fail){
#ifdef CONSOLE
        printf("UBD:%u, gt_UBD:%u", UBD[0], gt_UBD[0]);
#endif

#ifdef REPORT
    fprintf(fpReport,"FAIL,");
#endif
    }
    else {
#ifdef CONSOLE
        printf("PASS\n");
#endif

#ifdef REPORT
        fprintf(fpReport,"PASS,");
#endif
    }

#ifdef REPORT
#ifdef SCTM
    fprintf(fpReport,"%d\n",exec_diff);
#endif
#endif

#if VCOP_HOST_EMULATION
#else
#ifdef CONSOLE
    printf("Time taken: %d cycles \n", (t1 - t0));
#endif
#endif

#ifdef REPORT
    if(fpReport) {
        fclose(fpReport);
    }
#endif
}


void print_output()
{
   int i, j;

   for (i = 0; i < H_INPUT; ++i)
   {
      for (j = 0; j < W_INPUT; ++j)
          printf("%u ", sqrt_out[i * W_INPUT + j]);
      printf("\n");
   }
}

/* ======================================================================== */
/*  End of file:  vcop_normalFlow.c                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
