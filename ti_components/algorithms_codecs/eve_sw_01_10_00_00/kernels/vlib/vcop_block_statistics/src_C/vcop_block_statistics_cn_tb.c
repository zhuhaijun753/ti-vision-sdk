/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_block_statistics_cn_tb                                         */
/*                                                                          */
/*  Driver file for testing Block Statistics C reference                    */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_          */
/*  block_statistics_cn" natural C reference function.                      */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it fails it prints a byte by byte trace.                    */
/*                                                                          */
/* ======================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of block statistics        */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_block_statistics_cn.h"

#define IMG_HEIGHT (16)
#define IMG_WIDTH  (16)
#define IMG_STRIDE (IMG_WIDTH)

#define STAT_BLOCK_HEIGHT (8)
#define STAT_BLOCK_WIDTH  (8)

#define OUT_WIDTH  (IMG_WIDTH/STAT_BLOCK_WIDTH)
#define OUT_HEIGHT (IMG_HEIGHT/STAT_BLOCK_HEIGHT)

#pragma DATA_SECTION(IMAGE, "Adata");
unsigned char IMAGE[IMG_HEIGHT*IMG_STRIDE] = {0x00};

#pragma DATA_SECTION(MEAN_OUT, "Bdata");
unsigned short MEAN_OUT[OUT_HEIGHT*OUT_WIDTH] = {0x00};

#pragma DATA_SECTION(VAR_OUT, "Bdata");
unsigned int VAR_OUT[OUT_HEIGHT*OUT_WIDTH] = {0x00};

#pragma DATA_SECTION(MIN_OUT, "Bdata");
unsigned char MIN_OUT[OUT_HEIGHT*OUT_WIDTH] = {0x00};

#pragma DATA_SECTION(MAX_OUT, "Bdata");
unsigned char MAX_OUT[OUT_HEIGHT*OUT_WIDTH] = {0x00};

#pragma DATA_SECTION(REF_MEAN_OUT, "Eoutdata");
unsigned short REF_MEAN_OUT[OUT_HEIGHT*OUT_WIDTH] = {32*255, 32*255, 32*255, 32*255};

#pragma DATA_SECTION(REF_VAR_OUT, "Eoutdata");
unsigned int REF_VAR_OUT[OUT_HEIGHT*OUT_WIDTH] = {1024*255*255, 1024*255*255, 1024*255*255, 1024*255*255};

#pragma DATA_SECTION(REF_MIN_OUT, "Eoutdata");
unsigned char REF_MIN_OUT[OUT_HEIGHT*OUT_WIDTH] = {0, 0, 0, 0};

#pragma DATA_SECTION(REF_MAX_OUT, "Eoutdata");
unsigned char REF_MAX_OUT[OUT_HEIGHT*OUT_WIDTH] = {255, 255, 255, 255};

int main()
{
    int i, j, fail;

    printf ("Block Statistics C-model Test Bench:\n");

    memset(IMAGE, 0, sizeof(IMAGE));

    for(i = 0; i < IMG_HEIGHT; i++) {
        for(j = 0; j < IMG_WIDTH; j += 2) {
            IMAGE[i*IMG_WIDTH + j] = 0;
            IMAGE[i*IMG_WIDTH + j + 1] = 255;
        }
    }

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_block_statistics_cn(IMAGE, IMG_STRIDE, IMG_WIDTH, IMG_HEIGHT, STAT_BLOCK_WIDTH,
                    STAT_BLOCK_HEIGHT, MIN_OUT, MAX_OUT, MEAN_OUT, VAR_OUT);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
    for (i = 0; i < OUT_HEIGHT; i++)
    {
        for (j = 0; j < OUT_WIDTH; j++)
        {
            if (MEAN_OUT[OUT_WIDTH*i+j] != REF_MEAN_OUT[OUT_WIDTH*i+j])
            {
                printf("Error: pixel mean at     (%d, %d) Output = %5d, Expected = %5d\n",
                       i, j, MEAN_OUT[OUT_WIDTH*i+j], (REF_MEAN_OUT[OUT_WIDTH*i+j]));
                fail++;
            }
            if (VAR_OUT[OUT_WIDTH*i+j] != REF_VAR_OUT[OUT_WIDTH*i+j])
            {
                printf("Error: pixel variance at (%d, %d) Output = %5d, Expected = %5d\n",
                       i, j, VAR_OUT[OUT_WIDTH*i+j], REF_VAR_OUT[OUT_WIDTH*i+j]);
                fail++;
            }
            if (MIN_OUT[OUT_WIDTH*i+j] != REF_MIN_OUT[OUT_WIDTH*i+j])
            {
                printf("Error: pixel min at      (%d, %d) Output = %d, Expected = %d\n",
                       i, j, MIN_OUT[OUT_WIDTH*i+j], REF_MIN_OUT[OUT_WIDTH*i+j]);
                fail++;
            }
            if (MAX_OUT[OUT_WIDTH*i+j] != REF_MAX_OUT[OUT_WIDTH*i+j])
            {
                printf("Error: pixel max at      (%d, %d) Output = %d, Expected = %d\n",
                       i, j, MAX_OUT[OUT_WIDTH*i+j], REF_MAX_OUT[OUT_WIDTH*i+j]);
                fail++;
            }
        }
    }

    printf(fail ? "FAIL\n":"PASS\n");
}
