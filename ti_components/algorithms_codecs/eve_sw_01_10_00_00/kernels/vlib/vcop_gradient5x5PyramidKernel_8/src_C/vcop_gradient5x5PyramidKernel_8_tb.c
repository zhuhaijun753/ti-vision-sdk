/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_gradient5x5PyramidKernel_8-tb                                  */
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

void vcop_gradientH5x5PyramidKernel_8
(                                    
    unsigned char   pIn[],           
    short           pB[],            
    unsigned short  width,           
    unsigned short  pitch,           
    unsigned short  height,          
    unsigned char   pOut[]           
);                                   
                                     
vcop_gradientV5x5PyramidKernel_8     
(                                    
    unsigned char  pIn[],            
    short          pB[],             
    unsigned short width,            
    unsigned short pitch,            
    unsigned short height,           
    unsigned char  pOut[]            
);                                    

#pragma DATA_SECTION(InData_Gradient5x5PyramidKernel_8, "Adata");
unsigned char InData_Gradient5x5PyramidKernel_8[16*5] = 
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
short Temp_Gradient5x5PyramidKernel_8[16*5];

#pragma DATA_SECTION(trueOutData_GradientH5x5PyramidKernel_8, "EOutdata");
unsigned char trueOutData_GradientH5x5PyramidKernel_8[6] = 
{ 
    149, 103, 109, 128, 156, 100 
}; 

#pragma DATA_SECTION(trueOutData_GradientV5x5PyramidKernel_8, "EOutdata");
unsigned char trueOutData_GradientV5x5PyramidKernel_8[6] = 
{ 
    137, 129, 126, 127, 139, 134 
}; 

#pragma DATA_SECTION(calculatedOutData_GradientH5x5PyramidKernel_8, "Cdata");
unsigned char calculatedOutData_GradientH5x5PyramidKernel_8[6];

#pragma DATA_SECTION(calculatedOutData_GradientV5x5PyramidKernel_8, "Cdata");
unsigned char calculatedOutData_GradientV5x5PyramidKernel_8[6];

int main() 
{

    int i, j, fail_h, fail_v;

    /*---------------------------------------------------------------------*/
    /*  Function call to the VCOP-C API to be tested                       */
    /*---------------------------------------------------------------------*/    
    
    vcop_gradientH5x5PyramidKernel_8(InData_Gradient5x5PyramidKernel_8,         
                                     Temp_Gradient5x5PyramidKernel_8,               
                                     16-4,                                          
                                     16,                                            
                                     5,
                                     calculatedOutData_GradientH5x5PyramidKernel_8);

    vcop_gradientV5x5PyramidKernel_8(InData_Gradient5x5PyramidKernel_8,          
                                     Temp_Gradient5x5PyramidKernel_8,                
                                     16-4,                                           
                                     16,                                             
                                     5,
                                     calculatedOutData_GradientV5x5PyramidKernel_8);
                                     
    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/

    fail_h = memcmp (calculatedOutData_GradientH5x5PyramidKernel_8, 
                                   trueOutData_GradientH5x5PyramidKernel_8, 6);                                     

    fail_v = memcmp (calculatedOutData_GradientV5x5PyramidKernel_8, 
                                   trueOutData_GradientV5x5PyramidKernel_8, 6);                                     

    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

    if (fail_h) 
    {
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
    }
    
    if (fail_v) 
    {
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
    }    
                                   
   if( !( fail_v | fail_h ) )
   printf ("Pass \n");
    
}
/* ======================================================================== */
/*  End of file:  vcop_gradient5x5PyramidKernel_8_tb.c                      */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */