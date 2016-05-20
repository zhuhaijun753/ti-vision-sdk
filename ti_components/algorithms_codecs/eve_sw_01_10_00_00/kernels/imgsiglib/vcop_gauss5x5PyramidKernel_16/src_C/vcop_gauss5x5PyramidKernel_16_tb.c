/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_gauss5x5PyramidKernel_16-tb                                    */
/*                                                                          */
/*  Driver file for testing Gaussian Pyramid - 16 bit                       */
/*                                                                          */
/*  USAGE                                                                   */
/*      This code contains a driver program for testing the 'vcop_gauss5x5  */
/*  PyramidKernel_16" function by injecting it with the same data set as    */
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

#define BLOCK_PITCH   (16)
#define BLOCK_WIDTH   (16-4)
#define BLOCK_HEIGHT  (2)

void vcop_gauss5x5PyramidKernel_16_horiz_c
(
    unsigned short   pIn[],
    unsigned short   pOut[],
    unsigned short  width,
    unsigned short  height,
    unsigned short  inPitch,
    unsigned short  outPitch
);

void vcop_gauss5x5PyramidKernel_16_vert_c
(
    unsigned short   pIn[],
    unsigned short   pOut[],
    unsigned short  width,
    unsigned short  height,
    unsigned short  inPitch,
    unsigned short  outPitch
);   


void vcop_gauss5x5PyramidKernel_16
(
    unsigned short pIn[],   
    unsigned short pB[],   
    unsigned short width,  
    unsigned short pitch,  
    unsigned short height,
    unsigned short pOut[]   
)   
{

    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C APIs to be tested                   */
    /*---------------------------------------------------------------------*/

    vcop_gauss5x5PyramidKernel_16_horiz_c
    (
    pIn,
    pB,
    width,
    height+4,
    pitch,
    width
    );   

    vcop_gauss5x5PyramidKernel_16_vert_c
    (
    pB,
    pOut,
    width,
    height,
    width,
    width/2
    );   

}

#pragma DATA_SECTION(InData_Gauss5x5PyramidKernel_16, "Adata");
unsigned short InData_Gauss5x5PyramidKernel_16[16*5] = 
{
    0x0097, 0x0039, 0x0074, 0x00aa, 0x0009, 0x00f7, 0x00d0, 0x008c, 
    0x0096, 0x003c, 0x0058, 0x004d, 0x0004, 0x0006, 0x00a2, 0x0006, 
    0x001f, 0x008f, 0x00b2, 0x0003, 0x0087, 0x005b, 0x0036, 0x009a, 
    0x00c1, 0x00a1, 0x0014, 0x00a2, 0x0089, 0x0096, 0x0080, 0x00e0, 
    0x00d6, 0x0071, 0x0009, 0x001c, 0x0035, 0x00d3, 0x0062, 0x00d9, 
    0x0095, 0x00e9, 0x00e7, 0x007f, 0x0073, 0x00cb, 0x00b1, 0x002a, 
    0x003e, 0x009b, 0x0003, 0x0067, 0x007f, 0x0010, 0x0087, 0x0083, 
    0x00d3, 0x009e, 0x0009, 0x0002, 0x006a, 0x00e3, 0x00f9, 0x00ff, 
    0x0097, 0x0039, 0x0074, 0x00aa, 0x0009, 0x00f7, 0x00d0, 0x008c, 
    0x0096, 0x003c, 0x0058, 0x004d, 0x0004, 0x0006, 0x00a2, 0x0006
};

#pragma DATA_SECTION(Temp_Gauss5x5PyramidKernel_16, "Bdata");
unsigned short Temp_Gauss5x5PyramidKernel_16[16*5];

#pragma DATA_SECTION(trueOutData_Gauss5x5PyramidKernel_16, "EOutdata");
unsigned short trueOutData_Gauss5x5PyramidKernel_16[2*6] = 
{ 
    0x0051, 0x005b, 0x0086, 0x00a4, 0x007c, 0x007c
}; 

#pragma DATA_SECTION(calculatedOutData_Gauss5x5PyramidKernel_16, "Cdata");
unsigned short calculatedOutData_Gauss5x5PyramidKernel_16[2*6];

int main() 
{

    int i,j, fail;
    unsigned int result1, result2;

    /*---------------------------------------------------------------------*/
    /*  Wrapper to use the VCOP-C API to call horiz and vert filters       */
    /*---------------------------------------------------------------------*/
    
    vcop_gauss5x5PyramidKernel_16(InData_Gauss5x5PyramidKernel_16,             
                                 Temp_Gauss5x5PyramidKernel_16,                
                                 BLOCK_WIDTH,
                                 BLOCK_PITCH,
                                 BLOCK_HEIGHT,
                                 calculatedOutData_Gauss5x5PyramidKernel_16);  

                                 
    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/

    fail = memcmp (calculatedOutData_Gauss5x5PyramidKernel_16, 
                                   trueOutData_Gauss5x5PyramidKernel_16, 6);
                         
    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

    if (fail) 
    {
        for (i = 0; i < 6; i++)
        {
             printf("i:%d, out:%u, EOut:%u, %c \n",
                   i, 
                   calculatedOutData_Gauss5x5PyramidKernel_16[i], 
                   trueOutData_Gauss5x5PyramidKernel_16[i], 
                   (calculatedOutData_Gauss5x5PyramidKernel_16[i]!=
                   trueOutData_Gauss5x5PyramidKernel_16[i]) 
                   ? '*':' '
                   );
        }
    }
    else      printf ("Pass \n");
    
}
/* ======================================================================== */
/*  End of file:  vcop_gauss5x5PyramidKernel_16_tb.c                        */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

