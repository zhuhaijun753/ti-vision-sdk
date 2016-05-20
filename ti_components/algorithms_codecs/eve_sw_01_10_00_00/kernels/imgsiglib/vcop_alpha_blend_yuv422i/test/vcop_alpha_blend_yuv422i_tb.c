/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/* ======================================================================== */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_alpha_blend_yuv422i_tb                                         */
/*                                                                          */
/*  Driver file for testing YUV422 interleaved alpha blending               */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_alpha_    */
/*  blend_yuv422i" function by injecting it with the a random data set      */
/*  and comparing the output against the natural C function output.         */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ======================================================================== */

#include <stdio.h>
#include <stdlib.h>

#include "vcop.h"
#include "eve_profile.h"

/* ------------------------------------------------------------------------ */
/*  Include the "C" implementation of YUV422i Alpha Blend function.         */
/* ------------------------------------------------------------------------ */
#include "../src_C/vcop_alpha_blend_yuv422i_cn.c"

#include "vcop_host.h"
#include "vcop_alpha_blend_yuv422i_kernel.h"

//#define __DEBUG

#define NUM_ITER (1)
#define BLK_WIDTH (64)
#define BLK_STRIDE (2*BLK_WIDTH)
#define BLK_HEIGHT (64)

#pragma DATA_SECTION(IN_1, "Adata");
unsigned char IN_1[BLK_STRIDE*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(IN_2, "Bdata");
unsigned char IN_2[BLK_STRIDE*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(ALPHA, "Adata");
unsigned char ALPHA[BLK_WIDTH*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(OUT, "Bdata");
unsigned char OUT[BLK_STRIDE*BLK_HEIGHT] = {0};

#pragma DATA_SECTION(OUT_REF, "DDR_MEM");
unsigned char OUT_REF[BLK_STRIDE*BLK_HEIGHT] = {0};


void createPattern(unsigned char *img, unsigned short width, unsigned short height,
                   unsigned short stride, unsigned short upper_bound)
{
    int i, j;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            img[i*stride + j] = (rand() & 0xFF) % (upper_bound + 1);
        }
    }
}


int test_alpha_blend_yuv422i()
{
    int i, j, iter, fail = 0, status = 0;
    unsigned int seed;

    profiler_init();

    printf("Block size = %dx%d \n", BLK_WIDTH, BLK_HEIGHT);

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    vcop_alpha_blend_yuv422i_init(IN_1, IN_2, ALPHA, OUT, BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE,
                                BLK_STRIDE, BLK_STRIDE, __pblock_vcop_alpha_blend_yuv422i);

    for (iter = 0; iter < NUM_ITER; iter++)
    {
        printf("Iteration %d:\n", iter);

        seed = _tsc_gettime();
        srand(seed);
        printf("Pattern Generation Seed = %d\n", seed);
        createPattern(IN_1, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 255);
        createPattern(IN_2, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 255);
        createPattern(ALPHA, BLK_WIDTH, BLK_HEIGHT, BLK_WIDTH, 16);

#ifdef __DEBUG
        printf("\nInput Image 1 Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",IN_1[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nInput Image 2 Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",IN_2[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nInput Alpha Block:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < BLK_WIDTH; j++) {
                printf("%3d ",ALPHA[i*BLK_WIDTH+j]);
            }
            printf("\n");
        }
        printf("\n");
#endif

        /*---------------------------------------------------------------------*/
        /*  Function call to the Natural-C API to generate reference output    */
        /*---------------------------------------------------------------------*/
        vcop_alpha_blend_yuv422i_cn(IN_1, IN_2, ALPHA, OUT_REF, BLK_WIDTH, BLK_HEIGHT,
                                    BLK_STRIDE, BLK_STRIDE, BLK_STRIDE);

        profiler_start();

        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP,
                        IBUFHA_VCOP, IBUFLA_VCOP);

        /*---------------------------------------------------------------------*/
        /*  Function call to the VCOP-C API to be tested                       */
        /*---------------------------------------------------------------------*/
        vcop_alpha_blend_yuv422i_vloops(__pblock_vcop_alpha_blend_yuv422i);
        _vcop_vloop_done();

        VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST,
                        IBUFHA_SYST, IBUFLA_SYST);

        profiler_end();

        /*---------------------------------------------------------------------*/
        /*  Compare the results of output arrays with expected output arrays.  */
        /*---------------------------------------------------------------------*/
        fail = memcmp(OUT, OUT_REF, 2*BLK_HEIGHT*BLK_WIDTH);

        if(fail != 0) {
            for (i = 0; i < BLK_HEIGHT; i++)
            {
                for (j = 0; j < 2*BLK_WIDTH; j++)
                {
                    if (OUT[i*BLK_STRIDE+j] != OUT_REF[i*BLK_STRIDE+j])
                    {
                        printf("Error: At (%d, %d) Output = %d, Expected = %d\n",
                               i, j, OUT[i*BLK_STRIDE+j], OUT_REF[i*BLK_STRIDE+j]);
                    }
                }
            }
        }

#ifdef __DEBUG
        printf("\nOutput Blended Frame:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",OUT[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\nReference Blended Frame:\n");
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                printf("%3d ",OUT_REF[i*BLK_STRIDE+j]);
            }
            printf("\n");
        }
        printf("\n");
#endif

        printf(fail ? "FAIL\n":"PASS\n");
        status |= fail;
    }

    profiler_deinit();

    printf(status ? "test_alpha_blend_yuv422i: FAIL\n":"test_alpha_blend_yuv422i: PASS\n");

    return (status);
}


int test_alpha_blend_yuv422i_cn(unsigned char alpha, unsigned char *ref_out)
{
    int i, j, status = 0;

    printf("test_alpha_blend_yuv422i_cn (alpha = %2d): ", alpha);

    createPattern(IN_1, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 256);
    createPattern(IN_2, 2*BLK_WIDTH, BLK_HEIGHT, BLK_STRIDE, 256);

    for(i = 0; i < BLK_HEIGHT; i++) {
        for(j = 0; j < BLK_WIDTH; j++) {
            ALPHA[i*BLK_WIDTH + j] = alpha;
        }
    }
    
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*  Alpha blending of YUV422 interleaved images IN_1 & IN_2            */
    /*---------------------------------------------------------------------*/
    vcop_alpha_blend_yuv422i_cn(IN_1, IN_2, ALPHA, OUT, BLK_WIDTH, BLK_HEIGHT,
                                BLK_STRIDE, BLK_STRIDE, BLK_STRIDE);
                                 
    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    status = memcmp(OUT, ref_out, 2*BLK_HEIGHT*BLK_WIDTH);

    if(status != 0) {
        for(i = 0; i < BLK_HEIGHT; i++) {
            for(j = 0; j < 2*BLK_WIDTH; j++) {
                if(OUT[i*BLK_STRIDE + j] != ref_out[i*BLK_STRIDE + j]) {
                    printf("\nOutput mismatch at (%d, %d), Output = %d, Expected = %d\n", i, j, OUT[i*BLK_STRIDE + j], ref_out[i*BLK_STRIDE + j]);
                }
            }
        }
    }

    printf(status ? "FAIL\n" : "PASS\n");
    return (status);
}


int main()
{
    int status = 0;

    /* Validate the C reference */
    printf ("\nYUV422i Alpha Blending Test Bench: Validating C-model\n");
    status = test_alpha_blend_yuv422i_cn(16, IN_1);
    status = test_alpha_blend_yuv422i_cn(0, IN_2);

    /* Validate the Kernel */
    printf ("\nYUV422i Alpha Blending Test Bench: Validating Kernel\n");
    status = test_alpha_blend_yuv422i();

    return status;
}
