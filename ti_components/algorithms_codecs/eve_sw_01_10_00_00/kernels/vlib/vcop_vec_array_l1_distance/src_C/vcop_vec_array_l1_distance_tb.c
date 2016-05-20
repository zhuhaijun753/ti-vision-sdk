/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_array_l1_distance-tb                                       */
/*                                                                          */
/*  Driver file for testing L1 distance function                            */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_vec_array */
/*  _l1_distance" function by injecting it with the same data set as in the */
/*  natural C testbench functions.                                          */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include "vcop_vec_array_l1_distance_c.h"

#define array_len (64)

short A[64] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,  
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,  
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F 
};

short B[64] =
{
    0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 
    0x11, 0x13, 0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1f, 
    0x21, 0x23, 0x25, 0x27, 0x29, 0x2b, 0x2d, 0x2f, 
    0x31, 0x33, 0x35, 0x37, 0x39, 0x3b, 0x3d, 0x3f, 
    0x41, 0x43, 0x45, 0x47, 0x49, 0x4b, 0x4d, 0x4f, 
    0x51, 0x53, 0x55, 0x57, 0x59, 0x5b, 0x5d, 0x5f,  
    0x61, 0x63, 0x65, 0x67, 0x69, 0x6b, 0x6d, 0x6f, 
    0x71, 0x73, 0x75, 0x77, 0x79, 0x7b, 0x7d, 0x7f       
};

unsigned int C[1]   ={0};
unsigned int Cout[1]={2080};

int main()
{
    int fail;
    
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/

    vcop_vec_array_l1_distance_cn (A, B , C, array_len);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/

    fail = memcmp (C, Cout, 1);

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

    if (fail) 
    {
           printf ("C:%d, Cout:%d", 
                     C[0], Cout[0]
                  );
    }
    else      printf ("Pass \n");
}

/* ======================================================================== */
/*  End of file:  vcop_vec_array_l1_distance_tb.c                           */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

