/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_vec_array_add_uns_char-tb                                      */
/*                                                                          */
/*  Driver file for testing vector addition of two unsigned character       */
/*  arrays, (results can overflow)                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vec_array_add_ */
/*  _uns_char" function by injecting it with the same data set as in the    */
/*  assembly testbench functions.                                           */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array "EOut" by doing a standard "memcmp" and printing a pass/fail      */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/*  To build the "C" executable type:                                       */
/*                                                                          */
/*  gcc *.c -lm -o a.out                                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */



#include "GlobalTypes.h"
#include "baseaddress.h"

#include "INTH.h"

#include "pcache.h"
#include <stdio.h>
#include <arp32.h>
#include <vcop/vcop.h>

typedef unsigned short Uint16;
typedef unsigned char  Uint8;

#define W_INPUT 16
#define H_INPUT 4
#define N0         (W_INPUT * H_INPUT)
#define PAD        (16)
#define N1         (N0 + PAD)


#define W_OUTPUT 16
#define H_OUTPUT 5


#pragma DATA_SECTION(in1, "Adata");
Uint8 in1[N0] = 
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

#pragma DATA_SECTION(in2, "Bdata");
Uint8 in2[N1] = 
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
};

#pragma DATA_SECTION(in3, "Bdata");
Uint8 in3[N1] = {0};

#pragma DATA_SECTION(profile_array, "Bdata");
unsigned int profile_array[10];


#pragma DATA_SECTION(out, "Cdata");
Uint8 out[N1] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

#pragma DATA_SECTION(reference, "EOutdata");
Uint8 reference[N1] = 
{
    0x01, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0f, 
    0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1f, 
    0x21, 0x23, 0x25, 0x27, 0x29, 0x2B, 0x2D, 0x2f, 
    0x31, 0x33, 0x35, 0x37, 0x39, 0x3B, 0x3D, 0x3f, 
    0x41, 0x43, 0x45, 0x47, 0x49, 0x4B, 0x4D, 0x4f, 
    0x51, 0x53, 0x55, 0x57, 0x59, 0x5B, 0x5D, 0x5f,  
    0x61, 0x63, 0x65, 0x67, 0x69, 0x6B, 0x6D, 0x6f, 
    0x71, 0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D, 0x7f,       
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

void eve_array_add_uns_char
(
   __vptr_uint8  in1_ptr,         // input 1 data pointer
   __vptr_uint8  in2_ptr,         // input 2 data pointer
   __vptr_uint8  optr,            // output data pointer
          Uint16 width,           // width of each line
          Uint16 height           // height of each line
);

void print_output();
int verify_output();

int test_main()
{
   unsigned int t0, t1;
   unsigned int i = 0;

   _tsc_start();



   for (i = 0; i < 2; i++)
   {
       t0  = _tsc_gettime();
       EVE_PROGCACHE_BlockInvalidate (EVE_CONTROL, (unsigned int *) eve_array_add_uns_char, 0x6C1 ); 
       t1 = _tsc_gettime();

       profile_array[0] = (t1 - t0);
       
       t0 = _tsc_gettime();
       // invoke kernel
       eve_array_add_uns_char
       (
           in1,
           (in2 + 1),
           out,
           W_INPUT,
           H_INPUT
       );
       t1 = _tsc_gettime();

       profile_array[i + 1] = (t1 - t0);
   }


   /*print_output();*/
   return verify_output();
}

void print_output()
{
   int i, j;

   for (i = 0; i < H_OUTPUT; ++i)
   {
      for (j = 0; j < W_OUTPUT; ++j)
	printf("%3d ", out[i * W_OUTPUT + j]);
	printf("\n");
   }
}

int verify_output()
{
   int ok = true;
   int i;

   for (i = 0; i < H_OUTPUT * W_OUTPUT; ++i)
      if (out[i] != reference[i]) 
      {
	/* printf("ERROR: \noutput[%d] = %u\nreference[%d] = %d\n",
	   i, out[i], i, reference[i]); */
         ok = false;
      }
   printf(ok ? "PASS\n" : "FAIL\n"); 
   return ok;
}
