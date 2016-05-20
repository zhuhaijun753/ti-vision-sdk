/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      eve_SAD_tb.c                                                        */
/*                                                                          */
/*  Driver file for sum of absolute difference compute for a given block.   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code is a driver file for testing the 'vcop_SAD'               */
/*  function by injecting it with the same data set as in the               */
/*  assembly testbench functions.                                           */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array "EOut" by doing a standard "memcmp" and printing a pass/fail      */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/*  To build the "C" executable type:                                       */
/*                                                                          */
/*  gcc *.c -lm -o a.out                                                    */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../inc/EVE_SAD_cn.h"

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;

#define   IMAGE_W           (18)
#define   IMAGE_H           (14)
#define   BLK_W             (3)
#define   BLK_H             (3)
#define   IN_W              (8)
#define   IN_H              (3)
#define   REF_W             (8)    
#define   REF_H             (8)
#define   OFFSET_HORZ       (1)
#define   OFFSET_VERT       (1)
#define   NO_STEPS_HORZ     (1)
#define   NO_STEPS_VERT     (1)

#define   N0                (IMAGE_W * IMAGE_H)
#define   Nout              ((IN_W - (BLK_W - 1) ) * ( IN_H - (BLK_H - 1)))

#pragma DATA_SECTION(in_data, "Adata");
signed char in_data[N0] =
{
  
   0x0a, 0x0a, 0x0a, 0x18, 0x18, 0x18, 0x0B, 0x0B, 
   0x09, 0x09, 0x09, 0x17, 0x17, 0x17, 0x0B, 0x0B,
   0x08, 0x08, 0x08, 0x16, 0x16, 0x16, 0x0B, 0x0B,
};

#pragma DATA_SECTION(ref_data, "Bdata");
signed char ref_data[N0] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x09, 0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x17, 0x17, 0x17, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x16, 0x16, 0x16, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

#pragma DATA_SECTION(ref, "Cdata");
signed int ref[Nout] = {
0x0, 0x02a, 0x01b, 0x0, 0x021, 0x036

};
  
#pragma DATA_SECTION(out, "Bdata");
signed int sad_data[N0] = {0};

#pragma DATA_SECTION(out, "Cdata");
signed int out[Nout] = {0};


void print_output();
int  verify_output();


int main()
{
    int ok = 0;

    /*-------------------------------------------------------------------*/
    /* Actual filtering operation happens here as part of the test bench */
    /* and the results are written out so as to be compared with EVE     */
    /* results.                                                          */
    /*-------------------------------------------------------------------*/
 
    vcop_SAD_cn
    ( 
        in_data, 
        ref_data,
        sad_data,
        out,
        BLK_W,  
        BLK_H,
        IN_W,  
        IN_H,
        REF_W,
        REF_H,
        OFFSET_HORZ,
        OFFSET_VERT,
        NO_STEPS_HORZ,
        NO_STEPS_VERT
    ); 
    
   print_output();
   ok =  verify_output();

   return ok;
}


void print_output()
{
   int i, j;

   printf("Minimum SADs for input blocks\n\n");

   for (i = 0; i < IN_H - (BLK_H - 1); ++i)
   {
      for (j = 0; j < IN_W - (BLK_W - 1); ++j)
         printf("0x%2.2x, ", out[i * ( IN_W - (BLK_W - 1) ) + j]); 
      printf("\n"); 
   }

}


int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < Nout; ++i)
   {
      if (out[i] != ref[i]) 
      {
         ok = 0;
      }
   }

   printf("\n\nSAD C-kernel:  "); 
   printf(ok ? "PASS\n\n" : "FAIL\n\n"); 

   return ok;
}

