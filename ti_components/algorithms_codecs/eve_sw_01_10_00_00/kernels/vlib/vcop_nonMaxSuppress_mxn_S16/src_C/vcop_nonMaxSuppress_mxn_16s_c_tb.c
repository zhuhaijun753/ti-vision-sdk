/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_nonMaxSuppress_mxn_16s_c_tb                                    */
/*                                                                          */
/*  Driver file for testing Non-maximum suppression mxn                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_          */
/*  nonMaxSuppress_mxn_16s_cn" natural C reference function.                */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ======================================================================== */

#include <stdio.h>

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of non-maximum suppression */
/*  function.                                                               */
/* ------------------------------------------------------------------------ */
#include "vcop_nonMaxSuppress_mxn_16s_c.h"

#define BLOCK_HEIGHT (12)
#define BLOCK_WIDTH  (8)

#define WIN_HEIGHT (7)
#define WIN_WIDTH  (3)

#pragma DATA_SECTION(IMAGE, "Adata");
unsigned short IMAGE[12*8] =
{
    0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x04, 0x05, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x03, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x05, 0x01, 0x02, 0x05,
    0x05, 0x01, 0x05, 0x08, 0x09, 0x01, 0x01, 0x01,
    0x03, 0x04, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x02, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x04, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x04, 0x01, 0x05, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

#pragma DATA_SECTION(OUT, "Cdata");
unsigned char OUT[12*8] = {0x00};

#pragma DATA_SECTION(TRUTH, "Eoutdata");
unsigned char TRUTH[12*8] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int main()
{
    int i, j, fail;

    printf ("MxN Non-Maximum Suprression 16-bit C-model Test Bench:\n");

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
    vcop_nonMaxSuppress_mxn_16s_cn(IMAGE, OUT, BLOCK_HEIGHT, BLOCK_WIDTH,
                                   WIN_HEIGHT, WIN_WIDTH, 1);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/
    fail = 0;
    for (i = 0; i <= (BLOCK_HEIGHT-WIN_HEIGHT); i++)
    {
        for (j = 0; j <= (BLOCK_WIDTH-WIN_WIDTH); j++)
        {
            if (OUT[BLOCK_WIDTH*i+j] != TRUTH[BLOCK_WIDTH*i+j])
            {
                printf("Error: pixel (row: %d, column: %d) is incorrect!\n", i, j);
                fail++;
            }
        }
    }

   if(!fail)
       printf ("Pass \n");

}
