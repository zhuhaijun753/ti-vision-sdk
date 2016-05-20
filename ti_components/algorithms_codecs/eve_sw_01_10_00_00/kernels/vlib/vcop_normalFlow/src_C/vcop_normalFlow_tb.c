/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      vcop_normalFlow-tb                                                  */
/*                                                                          */
/*  Driver file for testing normal flow distance function                   */
/*                                                                          */
/*  USAGE                                                                   */
/*     This code contains a driver program for testing the 'vcop_normalFlow'*/
/*  function by injecting it with the same data set as in the natural C     */
/*  testbench functions.                                                    */
/*                                                                          */
/*  This testbench then compares the results with the expected output       */
/*  array by doing a standard "memcmp" function and printing a pass/fail    */
/*  message. If it failed it prints a byte by byte trace.                   */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*      Copyright (C) 2011 Texas Instruments Incorporated.                  */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>

void vcop_normalFlow_c(short imDiff[],       // SQ15.0
                       short Emag[],         // SQ15.0
                       short Ex[],           // SQ15.0
                       short Ey[],           // SQ15.0
                       short LUT[],          // QS0.15
                       short T,              // SQ15.0
                       char  numEls,         // SQ31.0
                       short normalFlowU[],  // SQ8.7
                       short normalFlowV[]); // SQ8.7


#define imW 8
#define imH 8

// Input Arrays
//--------------
// Gradient magnitude array
#pragma DATA_SECTION(Emag, "Adata");
short Emag[imW*imH] = 
{
    0x65, 0x69, 0x6e, 0x72, 0x74, 0x7c, 0x84, 0x85, 
    0xb5, 0xae, 0xbb, 0xc4, 0xc3, 0xca, 0xd2, 0xc9, 
    0x26, 0x0f, 0x3c, 0x32, 0x32, 0x35, 0x30, 0x23, 
    0x26, 0x0a, 0x3b, 0x03, 0x06, 0x0c, 0x09, 0x15, 
    0x3e, 0x2b, 0x2a, 0x0d, 0x0a, 0x07, 0x06, 0x13, 
    0x13, 0x1d, 0x0f, 0x2a, 0x11, 0x03, 0x05, 0x05, 
    0x06, 0x21, 0x2b, 0x36, 0x30, 0x12, 0x14, 0x0f, 
    0x06, 0x1a, 0x32, 0x15, 0x2d, 0x09, 0x05, 0x09 
};

// Look-Up Table for values in Emag array
#pragma DATA_SECTION(LUT, "Bdata");
short LUT[] = 
{
    0x0000, 0x7fff, 0x3fff, 0x2aaa, 0x1fff, 0x1999, 0x1555, 0x1249,
    0x0fff, 0x0e38, 0x0ccc, 0x0ba2, 0x0aaa, 0x09d8, 0x0924, 0x0888,
    0x07ff, 0x0787, 0x071c, 0x06bc, 0x0666, 0x0618, 0x05d1, 0x0590,
    0x0555, 0x051e, 0x04ec, 0x04bd, 0x0492, 0x0469, 0x0444, 0x0421,
    0x03ff, 0x03e0, 0x03c3, 0x03a8, 0x038e, 0x0375, 0x035e, 0x0348,
    0x0333, 0x031f, 0x030c, 0x02fa, 0x02e8, 0x02d8, 0x02c8, 0x02b9,
    0x02aa, 0x029c, 0x028f, 0x0282, 0x0276, 0x026a, 0x025e, 0x0253,
    0x0249, 0x023e, 0x0234, 0x022b, 0x0222, 0x0219, 0x0210, 0x0208,
    0x01ff, 0x01f8, 0x01f0, 0x01e9, 0x01e1, 0x01da, 0x01d4, 0x01cd,
    0x01c7, 0x01c0, 0x01ba, 0x01b4, 0x01af, 0x01a9, 0x01a4, 0x019e,
    0x0199, 0x0194, 0x018f, 0x018a, 0x0186, 0x0181, 0x017d, 0x0178,
    0x0174, 0x0170, 0x016c, 0x0168, 0x0164, 0x0160, 0x015c, 0x0158,
    0x0155, 0x0151, 0x014e, 0x014a, 0x0147, 0x0144, 0x0141, 0x013e,
    0x013b, 0x0138, 0x0135, 0x0132, 0x012f, 0x012c, 0x0129, 0x0127,
    0x0124, 0x0121, 0x011f, 0x011c, 0x011a, 0x0118, 0x0115, 0x0113,
    0x0111, 0x010e, 0x010c, 0x010a, 0x0108, 0x0106, 0x0104, 0x0102,
    0x00ff, 0x00fe, 0x00fc, 0x00fa, 0x00f8, 0x00f6, 0x00f4, 0x00f2,
    0x00f0, 0x00ef, 0x00ed, 0x00eb, 0x00ea, 0x00e8, 0x00e6, 0x00e5,
    0x00e3, 0x00e1, 0x00e0, 0x00de, 0x00dd, 0x00db, 0x00da, 0x00d9,
    0x00d7, 0x00d6, 0x00d4, 0x00d3, 0x00d2, 0x00d0, 0x00cf, 0x00ce,
    0x00cc, 0x00cb, 0x00ca, 0x00c9, 0x00c7, 0x00c6, 0x00c5, 0x00c4,
    0x00c3, 0x00c1, 0x00c0, 0x00bf, 0x00be, 0x00bd, 0x00bc, 0x00bb,
    0x00ba, 0x00b9, 0x00b8, 0x00b7, 0x00b6, 0x00b5, 0x00b4, 0x00b3,
    0x00b2, 0x00b1, 0x00b0, 0x00af, 0x00ae, 0x00ad, 0x00ac, 0x00ab,
    0x00aa, 0x00a9, 0x00a8, 0x00a8, 0x00a7, 0x00a6, 0x00a5, 0x00a4,
    0x00a3, 0x00a3, 0x00a2, 0x00a1, 0x00a0, 0x009f, 0x009f, 0x009e,
    0x009d, 0x009c, 0x009c, 0x009b, 0x009a, 0x0099, 0x0099, 0x0098,
    0x0097, 0x0097, 0x0096, 0x0095, 0x0094, 0x0094, 0x0093, 0x0092,
    0x0092, 0x0091, 0x0090, 0x0090, 0x008f, 0x008f, 0x008e, 0x008d,
    0x008d, 0x008c, 0x008c, 0x008b, 0x008a
};

// Image difference array
#pragma DATA_SECTION(imDiff, "Adata");   
short imDiff[imW*imH] = 
{
    0xffea, 0xffe3, 0xffe2, 0xffe8, 0xffe8, 0xffe3, 0xffda, 0xffe0,
    0x0075, 0x0077, 0x0079, 0x007f, 0x0080, 0x0080, 0x0082, 0x008a,
    0x0072, 0x0041, 0x005e, 0x006e, 0x005f, 0x0064, 0x005f, 0x0062,
    0xffd9, 0xffea, 0x0000, 0x0000, 0xffea, 0x0000, 0x0000, 0xffe8,
    0x0000, 0x0024, 0x0024, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0xffe4, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0xffe3, 0x0000, 0xffeb, 0x0000, 0x0000
};

// X-direction gradient array
#pragma DATA_SECTION(Ex, "Adata");
short Ex[imW*imH] = 
{
    0x0002, 0x0002, 0xfffc, 0xfffb, 0x0000, 0x000a, 0xffff, 0xfff3,
    0x0008, 0xffff, 0xffed, 0xfffd, 0xfffe, 0xfffd, 0xfffb, 0xfffd,
    0x001c, 0xfffa, 0xffd2, 0x0000, 0xfffe, 0xfff4, 0x0002, 0x0011,
    0x0026, 0xfff7, 0xffc5, 0xfffe, 0xfffd, 0xfff4, 0x0009, 0x0015,
    0x0020, 0x0006, 0xffd6, 0xfff4, 0xffff, 0xfffa, 0x0003, 0x0008,
    0x0010, 0x0019, 0xfffd, 0xffe6, 0xfff6, 0x0000, 0xfffe, 0x0000,
    0x0005, 0x0021, 0x0025, 0xffe1, 0xffdd, 0x0005, 0xfffe, 0xfffc,
    0x0006, 0x001a, 0x0032, 0xffed, 0xffd3, 0x0005, 0xfffb, 0xfff7
};

// Y-direction gradient array
#pragma DATA_SECTION(Ey, "Adata");
short Ey[imW*imH] = 
{
    0xff9b, 0xff97, 0xff92, 0xff8e, 0xff8c, 0xff84, 0xff7c, 0xff7b,
    0xff4b, 0xff52, 0xff45, 0xff3c, 0xff3d, 0xff36, 0xff2e, 0xff37,
    0xffe9, 0xfff1, 0xffdd, 0xffce, 0xffce, 0xffcb, 0xffd0, 0xffe2,
    0xfffa, 0xfffb, 0xffff, 0xfffe, 0xfffa, 0xfffd, 0xffff, 0xfff9,
    0xffcd, 0xffd5, 0xfff1, 0xfffa, 0xfff6, 0xfffc, 0xfffb, 0xffee,
    0xfff6, 0xfff2, 0x000f, 0x001f, 0x000d, 0x0003, 0x0005, 0x0005,
    0x0003, 0x0003, 0x0015, 0x0029, 0x001d, 0x0012, 0x0014, 0x000f,
    0x0002, 0xfffc, 0xfff1, 0xfff7, 0x0005, 0x0007, 0x0002, 0xffff
};


#pragma DATA_SECTION(normalFlowX, "Cdata");
short normalFlowX[imW*imH];

#pragma DATA_SECTION(normalFlowY, "Cdata");
short normalFlowY[imW*imH];


// Ground-truth Arrays
//---------------------
#pragma DATA_SECTION(gt_nFlowX, "EOutdata");
short gt_nFlowX[imW*imH] = 
{
    0x0000, 0x0000, 0xfffe, 0xfffe, 0x0000, 0x0002, 0xffff, 0xfffc, 
    0xfffc, 0x0000, 0x0008, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 
    0xfee6, 0x00e1, 0x009b, 0x0000, 0x000b, 0x0036, 0xfff6, 0xff52, 
    0x0081, 0xff01, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0090, 
    0x0000, 0xfff1, 0x006e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0xffd9, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0xff60, 0x0000, 0x0000, 0x0000, 0x0000
};

#pragma DATA_SECTION(gt_nFlowY, "EOutdata");
short gt_nFlowY[imW*imH] = 
{
    0xffe5, 0xffdd, 0xffde, 0xffe6, 0xffe6, 0xffe3, 0xffdc, 0xffe2, 
    0x0053, 0x0058, 0x0053, 0x0053, 0x0054, 0x0051, 0x0050, 0x0058, 
    0x00ea, 0x022b, 0x0075, 0x011a, 0x00f4, 0x00f2, 0x00fe, 0x0134, 
    0xffea, 0xff73, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffce, 
    0x0000, 0x006c, 0x0027, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0032, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0xffb4, 0x0000, 0x0000, 0x0000, 0x0000
};


void main(void)
{
    int i, fail;
    
    /*---------------------------------------------------------------------*/
    /*  Function call to the Natural-C API to be tested                    */
    /*---------------------------------------------------------------------*/
   
    vcop_normalFlow_c(imDiff, Emag, Ex, Ey, LUT, 10, imW*imH, 
                                                  normalFlowX, normalFlowY);

    /*---------------------------------------------------------------------*/
    /*  Compare the results of output arrays with expected output arrays.  */
    /*---------------------------------------------------------------------*/

    fail = memcmp(normalFlowX, gt_nFlowX, imW*imH);
    
    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

        if (fail) 
        {
            for (i = 0; i < imW*imH; i++)
            {
                printf ("i:%d, out:%d, EOut:%d, %c \n",
                      i, normalFlowX[i], gt_nFlowX[i], 
                      (normalFlowX[i]!= gt_nFlowX[i]) ? '*':' '
                    );
            }
        }
    else      printf ("Pass in X direction\n");
    
    fail = memcmp(normalFlowY, gt_nFlowY, imW*imH);
    
    /*---------------------------------------------------------------------*/
    /*  If there is a mis-compare, print out a memory trace, else print    */
    /*  pass.                                                              */
    /*---------------------------------------------------------------------*/

        if (fail) 
        {
            for (i = 0; i < imW*imH; i++)
            {
                printf ("i:%d, out:%d, EOut:%d, %c \n",
                      i, normalFlowY[i], gt_nFlowY[i], 
                      (normalFlowY[i]!= gt_nFlowY[i]) ? '*':' '
                    );
            }
        }
    else      printf ("Pass in Y direction\n");
}

/* ======================================================================== */
/*  End of file:  vcop_normalFlow_tb.c                                      */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */