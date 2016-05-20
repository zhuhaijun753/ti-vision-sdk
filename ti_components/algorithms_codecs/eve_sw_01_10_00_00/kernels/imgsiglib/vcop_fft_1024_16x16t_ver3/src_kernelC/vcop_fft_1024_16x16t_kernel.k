/* ========================================================================= */
/*   NAME                                                                    */
/*   vcop_fft_1024_16x16t :  Test Bench.                                     */
/*   1024-pt complex FFT with 16-bit inputs and 16-bit twiddle.              */
/*                                                                           */
/*                                                                           */
/*   USAGE                                                                   */
/*     This routine is C-callable  and performs a 1024-pt complex FFT.       */
/*   Maximum precision of input and outputs are 16-bit, and since FFT        */
/*   grows in precision by 2-bits per stage, and since we have 5             */
/*   stages, it will grow to occupy full 16-bits. User is expected to        */
/*   control the input to be in a signed 6-bit range.                        */
/*                                                                           */
/*    API:                                                                   */
/*                                                                           */
/*   void vcop_fft_1024_16x16t_cn                                            */
/*   (                                                                       */
/*       const short  SC[],                                                  */
/*       const short  digit_rev[],                                           */
/*       int          npoints,                                               */
/*       short        X[],                                                   */
/*       short        Y[]                                                    */
/*   )                                                                       */
/*                                                                           */
/*   This function accepts a special vector form of twiddle factors in       */
/*   the array "SC" organized as sine first followed by cosine, a            */
/*   table of 256 entries in digit_rev for digit reversal, the number        */
/*   of complex points "npoints" is FIXED at 1024 complex points and         */
/*   should not be changed, input array of 1024 complex points in X,         */
/*   an output array of 1024 complex points in Y.                            */
/*                                                                           */
/*   Even though this is an FFT, twiddle factors are maintained for          */
/*   exp^(2*pi*j*n*k)/N and not for exp^(-2*pi*j*n*k/N). Please refer        */
/*   to the behavC sub-directory for more explanation on how vector          */
/*   array of twissle factors are generated.                                 */ 
/*                                                                           */
/*   C CODE                                                                  */ 
/*                                                                           */
/* void fft16x16t_cn                                                         */
/* (const short *restrict ptr_w, int  npoints, short * ptr_x, short * ptr_y) */
/* {                                                                         */
/*   int   i, j, l1, l2, h2, predj, tw_offset, stride, fft_jmp;              */
/*   short xt0_0, yt0_0, xt1_0, yt1_0, xt2_0, yt2_0;                         */
/*   short xt0_1, yt0_1, xt1_1, yt1_1, xt2_1, yt2_1;                         */
/*   short xh0_0, xh1_0, xh20_0, xh21_0, xl0_0, xl1_0, xl20_0, xl21_0;       */
/*   short xh0_1, xh1_1, xh20_1, xh21_1, xl0_1, xl1_1, xl20_1, xl21_1;       */
/*   short x_0, x_1, x_2, x_3, x_l1_0, x_l1_1, x_l1_2, x_l1_3, x_l2_0, x_l2_1*/
/*   short xh0_2, xh1_2, xl0_2, xl1_2, xh0_3, xh1_3, xl0_3, xl1_3;           */
/*   short x_4, x_5, x_6, x_7, x_l2_2, x_l2_3, x_h2_0, x_h2_1, x_h2_2, x_h2_3*/
/*   short x_8, x_9, x_a, x_b, x_c, x_d, x_e, x_f;                           */
/*   short si10, si20, si30, co10, co20, co30;                               */
/*   short si11, si21, si31, co11, co21, co31;                               */
/*   short * x, * x2, * x0;                                                  */
/*   short * y0, * y1, * y2, *y3;                                            */
/*   short n00, n10, n20, n30, n01, n11, n21, n31;                           */
/*   short n02, n12, n22, n32, n03, n13, n23, n33;                           */
/*   short y0r, y0i, y4r, y4i;                                               */
/*   int   n0, j0;                                                           */
/*   int   radix,  m;                                                        */
/*   int   norm;                                                             */
/*                                                                           */
/*   const short *w;                                                         */
/*                                                                           */
/*   for (i = 31, m = 1; (npoints & (1 << i)) == 0; i--, m++);               */
/*   radix     =   m & 1 ? 2 :  4;                                           */
/*   norm      =   m - 2;                                                    */
/*                                                                           */
/*   stride     =   npoints;                                                 */
/*   tw_offset  =   0;                                                       */
/*   fft_jmp    =   6 * stride;                                              */
/*                                                                           */
/*                                                                           */
/*   while (stride > radix)                                                  */
/*   {                                                                       */
/*       j         = 0;                                                      */
/*       fft_jmp >>= 2;                                                      */
/*                                                                           */
/*       h2 = stride>>1;                                                     */
/*       l1 = stride;                                                        */
/*       l2 = stride + (stride >> 1);                                        */
/*                                                                           */
/*       x = ptr_x;                                                          */
/*       w = ptr_w + tw_offset;                                              */
/*       tw_offset += fft_jmp;                                               */
/*       stride >>=   2;                                                     */
/*                                                                           */
/*                                                                           */
/*       for (i = 0; i < npoints; i += 8)                                    */
/*       {                                                                   */
/*           co10 = w[j+1];    si10 = w[j+0];                                */
/*           co11 = w[j+3];    si11 = w[j+2];                                */
/*           co20 = w[j+5];    si20 = w[j+4];                                */
/*           co21 = w[j+7];    si21 = w[j+6];                                */
/*           co30 = w[j+9];    si30 = w[j+8];                                */
/*           co31 = w[j+11];   si31 = w[j+10];                               */
/*                                                                           */
/*           x_0 = x[0];       x_1 = x[1];                                   */
/*           x_2 = x[2];       x_3 = x[3];                                   */
/*                                                                           */
/*           x_l1_0 = x[l1  ]; x_l1_1 = x[l1+1];                             */
/*           x_l1_2 = x[l1+2]; x_l1_3 = x[l1+3];                             */
/*                                                                           */
/*           x_l2_0 = x[l2  ]; x_l2_1 = x[l2+1];                             */
/*           x_l2_2 = x[l2+2]; x_l2_3 = x[l2+3];                             */
/*                                                                           */
/*           x_h2_0 = x[h2  ]; x_h2_1 = x[h2+1];                             */
/*           x_h2_2 = x[h2+2]; x_h2_3 = x[h2+3];                             */
/*                                                                           */
/*           xh0_0  = x_0    + x_l1_0;     xh1_0  = x_1    + x_l1_1;         */
/*           xh0_1  = x_2    + x_l1_2;     xh1_1  = x_3    + x_l1_3;         */
/*           xl0_0  = x_0    - x_l1_0;     xl1_0  = x_1    - x_l1_1;         */
/*           xl0_1  = x_2    - x_l1_2;     xl1_1  = x_3    - x_l1_3;         */
/*                                                                           */
/*           xh20_0 = x_h2_0 + x_l2_0;     xh21_0 = x_h2_1 + x_l2_1;         */
/*           xh20_1 = x_h2_2 + x_l2_2;     xh21_1 = x_h2_3 + x_l2_3;         */
/*           xl20_0 = x_h2_0 - x_l2_0;     xl21_0 = x_h2_1 - x_l2_1;         */
/*           xl20_1 = x_h2_2 - x_l2_2;     xl21_1 = x_h2_3 - x_l2_3;         */
/*                                                                           */
/*           x0 = x;                                                         */
/*           x2 = x0;                                                        */
/*                                                                           */
/*           j += 12;                                                        */
/*           x += 4;                                                         */
/*                                                                           */
/*           predj = (j - fft_jmp);                                          */
/*           if (!predj) x += fft_jmp;                                       */
/*           if (!predj) j = 0;                                              */
/*                                                                           */
/*                                                                           */
/*            y0r   = xh0_0 + xh20_0;  y0i   = xh1_0 + xh21_0;               */
/*            y4r   = xh0_1 + xh20_1;  y4i   = xh1_1 + xh21_1;               */
/*                                                                           */
/*            xt0_0 = xh0_0 - xh20_0;  yt0_0 = xh1_0 - xh21_0;               */
/*            xt0_1 = xh0_1 - xh20_1;  yt0_1 = xh1_1 - xh21_1;               */
/*                                                                           */
/*            xt1_0 = xl0_0 + xl21_0;  yt2_0 = xl1_0 + xl20_0;               */
/*            xt2_0 = xl0_0 - xl21_0;  yt1_0 = xl1_0 - xl20_0;               */
/*            xt1_1 = xl0_1 + xl21_1;  yt2_1 = xl1_1 + xl20_1;               */
/*            xt2_1 = xl0_1 - xl21_1;  yt1_1 = xl1_1 - xl20_1;               */
/*                                                                           */
/*            x2[0] = y0r;             x2[1] = y0i;                          */
/*            x2[2] = y4r;             x2[3] = y4i;                          */
/*                                                                           */
/*            x2[h2  ] = (si10 * yt1_0 + co10 * xt1_0) >> 15;                */
/*            x2[h2+1] = (co10 * yt1_0 - si10 * xt1_0) >> 15;                */
/*                                                                           */
/*            x2[h2+2] = (si11 * yt1_1 + co11 * xt1_1) >> 15;                */
/*            x2[h2+3] = (co11 * yt1_1 - si11 * xt1_1) >> 15;                */
/*                                                                           */
/*            x2[l1  ] = (si20 * yt0_0 + co20 * xt0_0) >> 15;                */
/*            x2[l1+1] = (co20 * yt0_0 - si20 * xt0_0) >> 15;                */
/*                                                                           */
/*            x2[l1+2] = (si21 * yt0_1 + co21 * xt0_1) >> 15;                */
/*            x2[l1+3] = (co21 * yt0_1 - si21 * xt0_1) >> 15;                */
/*                                                                           */
/*            x2[l2  ] = (si30 * yt2_0 + co30 * xt2_0) >> 15;                */
/*            x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0) >> 15;                */
/*                                                                           */
/*            x2[l2+2] = (si31 * yt2_1 + co31 * xt2_1) >> 15;                */
/*            x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1) >> 15;                */
/*        }                                                                  */
/*    }                                                                      */
/*                                                                           */
/*    y0 = ptr_y;                                                            */
/*    y2 = ptr_y + (int) npoints;                                            */
/*    x0 = ptr_x;                                                            */
/*    x2 = ptr_x + (int) (npoints >> 1);                                     */
/*                                                                           */
/*    y1 = y0 + (int) (npoints >> 1);                                        */
/*    y3 = y2 + (int) (npoints >> 1);                                        */
/*    l1 = norm + 2;                                                         */
/*    j0 = 4;                                                                */
/*   n0 = npoints >> 2;                                                      */
/*                                                                           */
/*   j = 0;                                                                  */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*   for (i = 0; i < npoints; i += 8)                                        */
/*   {                                                                       */
/*       DIG_REV(j, l1, h2);                                                 */
/*                                                                           */
/*       x_0 = x0[0];             x_1 = x0[1];                               */
/*       x_2 = x0[2];             x_3 = x0[3];                               */
/*       x_4 = x0[4];             x_5 = x0[5];                               */
/*       x_6 = x0[6];             x_7 = x0[7];                               */
/*       x0 += 8;                                                            */
/*                                                                           */
/*       xh0_0 = x_0 + x_4;       xh1_0 = x_1 + x_5;                         */
/*       xl0_0 = x_0 - x_4;       xl1_0 = x_1 - x_5;                         */
/*       xh0_1 = x_2 + x_6;       xh1_1 = x_3 + x_7;                         */
/*       xl0_1 = x_2 - x_6;       xl1_1 = x_3 - x_7;                         */
/*                                                                           */
/*       n00 = xh0_0 + xh0_1;     n01 = xh1_0 + xh1_1;                       */
/*       n10 = xl0_0 + xl1_1;     n11 = xl1_0 - xl0_1;                       */
/*       n20 = xh0_0 - xh0_1;     n21 = xh1_0 - xh1_1;                       */
/*       n30 = xl0_0 - xl1_1;     n31 = xl1_0 + xl0_1;                       */
/*                                                                           */
/*       y0[2*h2] = n00;           y0[2*h2 + 1] = n01;                       */
/*       y1[2*h2] = n10;           y1[2*h2 + 1] = n11;                       */
/*       y2[2*h2] = n20;           y2[2*h2 + 1] = n21;                       */
/*       y3[2*h2] = n30;           y3[2*h2 + 1] = n31;                       */
/*                                                                           */
/*       x_8 = x2[0];              x_9 = x2[1];                              */
/*       x_a = x2[2];              x_b = x2[3];                              */
/*       x_c = x2[4];              x_d = x2[5];                              */
/*       x_e = x2[6];              x_f = x2[7];                              */
/*       x2 += 8;                                                            */
/*                                                                           */
/*       xh0_2 = x_8 + x_c;        xh1_2  = x_9 + x_d;                       */
/*       xl0_2 = x_8 - x_c;        xl1_2  = x_9 - x_d;                       */
/*       xh0_3 = x_a + x_e;        xh1_3 = x_b + x_f;                        */
/*       xl0_3 = x_a - x_e;        xl1_3 = x_b - x_f;                        */
/*                                                                           */
/*       n02 = xh0_2 + xh0_3;      n03 = xh1_2 + xh1_3;                      */
/*       n12 = xl0_2 + xl1_3;      n13 = xl1_2 - xl0_3;                      */
/*       n22 = xh0_2 - xh0_3;      n23 = xh1_2 - xh1_3;                      */
/*       n32 = xl0_2 - xl1_3;      n33 = xl1_2 + xl0_3;                      */
/*                                                                           */
/*       if (radix == 2)                                                     */
/*       {                                                                   */
/*         n02 = x_8 + x_a;        n03 = x_9 + x_b;                          */
/*         n22 = x_8 - x_a;        n23 = x_9 - x_b;                          */
/*         n12 = x_c + x_e;        n13 = x_d + x_f;                          */
/*         n32 = x_c - x_e;        n33 = x_d - x_f;                          */
/*       }                                                                   */
/*                                                                           */
/*       y0[2*h2+2] = n02;         y0[2*h2+3] = n03;                         */
/*       y1[2*h2+2] = n12;         y1[2*h2+3] = n13;                         */
/*       y2[2*h2+2] = n22;         y2[2*h2+3] = n23;                         */
/*       y3[2*h2+2] = n32;         y3[2*h2+3] = n33;                         */
/*                                                                           */
/*       j += j0;                                                            */
/*                                                                           */
/*       if (j == n0)                                                        */
/*       {                                                                   */
/*          j  += n0;                                                        */
/*          x0 += (int) npoints>>1;                                          */
/*          x2 += (int) npoints>>1;                                          */
/*       }                                                                   */
/*   }                                                                       */
/* }                                                                         */
/*                                                                           */
/*   ASSUMPTIONS                                                             */
/*   This code expects inputs and intermediat results to not overflow a      */
/*   16-bit range. No range checking is performed. This code will only       */
/*   work for the specific case of a 1024 point complex FFT.                 */
/*                                                                           */                                                                        
/*   NOTE                                                                    */
/*   It expects input and output arrays to be word aligned.                  */
/*                                                                           */ 
/*   CYCLES                                                                  */ 
/*                                                                           */
/*   Stage 1-3 : 3 * 32 * 10  = 960  cycles                                  */
/*   Stage 4:    1 * 32 * 12  = 384  cycles                                  */
/*   Stage 5:    1 * 32 * 16  = 512  cycles                                  */
/*   Stage digit reversal     = 1024 cycles                                  */
/*   Total : 2880 cycles                                                     */
/*                                                                           */                                                                     
/*   CODESIZE                                                                */
/*          496 bytes.                                                       */ 
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
/*  Register mappings for manual register allocations.                       */
/* ------------------------------------------------------------------------- */

#include "vcop_fft_1024_16x16t_regs.inc"

/* ------------------------------------------------------------------------- */
/* #defines for typecasting unsigned short as unsigned short.                */
/* ------------------------------------------------------------------------- */


void vcop_fft_1024_16x16t_stage_1_to_2
(
    __vptr_int16_arr  Pxi0,
    __vptr_int16_arr  Pxi1,
    __vptr_int16_arr  Pxi2,
    __vptr_int16_arr  Pxi3,
    __vptr_int16_arr  PCS1,
    __vptr_int16_arr  PCS2,
    __vptr_int16_arr  PCS3,
    unsigned short    bfys_per_grp[],
    unsigned short    grps[],
    unsigned short    passes,
    unsigned short    pinc3[],
    unsigned short    pinc4[],
    unsigned short    ptnc3[],
    unsigned short    ptnc4[]
)
{
    /*----------------------------------------------------------------------*/
    /* The first 3 stages of the FFT do the same processing, with the       */
    /* spacing adjusted between the four legs of the FFT, initially         */
    /* starting off with N/4, N/16, N/64 which for a 1024 pt FFT is         */
    /* 256, 64, and 16. We see the 3-loop structure of the FFT, where       */
    /* we have an outer loop with passes which is 3 out of 5 passes,        */
    /* 1, 4, 16 groups. In the first pass, there is no re-use of twiddle    */
    /* factors, next group we re-use the same twiddle factor 4 times,       */
    /* in the third stage we re-use the same twiddle factors 16-times.      */
    /*----------------------------------------------------------------------*/

    foreach (I0, passes, 2)
    {
        for (int I3 = 0; I3 < grps[I0]; I3++)
        {
            for (int I4 = 0; I4 < bfys_per_grp[I0]; I4++)
            {
                /*-----------------------------------------------------------*/
                /* Set up an address generation, two seperate ones, one for  */
                /* input, and one for twiddle factors.                       */
                /*-----------------------------------------------------------*/

                __agen  Addr_in = I3*pinc3[I0] + I4*pinc4[I0];
                __agen  Addr_tw = I3*ptnc3[I0] + I4*ptnc4[I0];

                /*-----------------------------------------------------------*/
                /*  Read the complex input and de-interleave into real and   */
                /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
                /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
                /*  in parallel.                                             */
                /*                                                           */
                /*  x_0    = x[0];       x_1 = x[1];                         */
                /*  x_2    = x[2];       x_3 = x[3];                         */
                /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
                /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
                /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
                /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
                /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
                /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
                /*                                                           */
                /*  Convention here is to denote the four input legs of the  */
                /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
                /*  CS1, CS2 and CS3.                                        */
                /*-----------------------------------------------------------*/

                (VS1_76543210, VC1_76543210) =  PCS1[I0][Addr_tw].deinterleave();
                (VS2_76543210, VC2_76543210) =  PCS2[I0][Addr_tw].deinterleave();
                (VS3_76543210, VC3_76543210) =  PCS3[I0][Addr_tw].deinterleave();

                (VX0_76543210, VY0_76543210) =  Pxi0[I0][Addr_in].deinterleave();
                (VX1_76543210, VY1_76543210) =  Pxi1[I0][Addr_in].deinterleave();
                (VX2_76543210, VY2_76543210) =  Pxi2[I0][Addr_in].deinterleave();
                (VX3_76543210, VY3_76543210) =  Pxi3[I0][Addr_in].deinterleave();

                /*------------------------------------------------------------*/
                /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
                /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
                /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
                /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
                /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
                /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
                /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
                /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
                /*                                                            */
                /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */  
                /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
                /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
                /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
                /* -----------------------------------------------------------*/

                (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
                (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
                (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();
                (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

                /*------------------------------------------------------------*/
                /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
                /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
                /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
                /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
                /*                                                            */
                /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
                /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
                /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
                /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
                /*------------------------------------------------------------*/

                (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
                (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
                (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
                (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

                /*------------------------------------------------------------*/
                /* Perform twiddle factor multiplies of three terms,top       */
                /* term does not have any multiplies. Note the twiddle        */
                /* factors for a normal FFT are C + j (-S). Since the         */
                /* factors that are stored are C + j S, this is               */
                /* corrected for in the multiplies.                           */
                /*                                                            */
                /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
                /*                                                            */
                /* x0r = xt0;                                                 */
                /* y0i = yt0;                                                 */
                /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
                /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
                /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
                /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
                /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
                /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
                /*------------------------------------------------------------*/

                V_x2r  = (Vxt2 * VC2_76543210);
                V_y2i  = (Vyt2 * VC2_76543210);
                V_x2r += (Vyt2 * VS2_76543210);
                V_y2i -= (Vxt2 * VS2_76543210);

                V_x1r  = (Vxt1 * VC1_76543210);
                V_y1i  = (Vyt1 * VC1_76543210);
                V_x3r  = (Vxt3 * VC3_76543210);
                V_y3i  = (Vyt3 * VC3_76543210);

                V_x3r += (Vyt3 * VS3_76543210);
                V_y3i -= (Vxt3 * VS3_76543210);

                V_x1r += (Vyt1 * VS1_76543210);
                V_y1i -= (Vxt1 * VS1_76543210);

                /* -----------------------------------------------------------*/
                /*  Store the final results back to the input array.          */
                /*                                                            */
                /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
                /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
                /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
                /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
                /* -----------------------------------------------------------*/

                Pxi0[I0][Addr_in].interleave() = (V_x0r, V_y0i);
                Pxi1[I0][Addr_in].interleave() = (V_x1r, V_y1i).truncate(15);
                Pxi2[I0][Addr_in].interleave() = (V_x2r, V_y2i).truncate(15);
                Pxi3[I0][Addr_in].interleave() = (V_x3r, V_y3i).truncate(15);
            }
        }
    }
}

/*---------------------------------------------------------------------------*/
/* In stage 3, operations are similar to previous stages of 1..2. Even       */
/* though repeat loop can be leveraged for this stage as shown in ver1       */
/* and ver2, we break out, so that we can make the task of digit reversal    */
/* for free by purposefully writing results within a vector word further     */
/* apart, by using transpisition, as we will need to work on them in         */
/* later iterations.                                                         */
/*---------------------------------------------------------------------------*/

void vcop_fft_1024_16x16t_stage3
(

    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    __vptr_int16      PCS1,
    __vptr_int16      PCS2,
    __vptr_int16      PCS3,
    __vptr_int16      Pox0,
    __vptr_int16      Pox1,
    __vptr_int16      Pox2,
    __vptr_int16      Pox3,
    __vptr_int16      Poy0,
    __vptr_int16      Poy1,
    __vptr_int16      Poy2,
    __vptr_int16      Poy3
)
{
   for (int I1 = 0; I1 < 4; I1++)
   {
       for (int I2 = 0; I2 < 2; I2++)
       {
           for (int I3 = 0; I3 < 2; I3++)
           {
               for (int I4 = 0; I4 < 2; I4++)
               {
                   __agen  Addr_in = I4 * 32    + I3 *  256 + I2 * 512   + I1 * 1024 ;
                   __agen  Addr_tw = I4 * 96    + I3 *  0   + I2 * 0     + I1 * 0;
                   __agen  Addr_ou = I4 * 8*9*4 + I3 *  4*4 + I2 *64*9*4 + I1*  4;  

                   /*-----------------------------------------------------------*/
                   /*  Read the complex input and de-interleave into real and   */
                   /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
                   /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
                   /*  in parallel.                                             */
                   /*                                                           */
                   /*  x_0    = x[0];       x_1 = x[1];                         */
                   /*  x_2    = x[2];       x_3 = x[3];                         */
                   /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
                   /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
                   /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
                   /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
                   /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
                   /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
                   /*                                                           */
                   /*  Convention here is to denote the four input legs of the  */
                   /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
                   /*  CS1, CS2 and CS3.                                        */
                   /*-----------------------------------------------------------*/

                   (VS1_76543210, VC1_76543210) =  PCS1[Addr_tw].deinterleave();
                   (VS2_76543210, VC2_76543210) =  PCS2[Addr_tw].deinterleave();
                   (VS3_76543210, VC3_76543210) =  PCS3[Addr_tw].deinterleave();

                   (VX0_76543210, VY0_76543210) =  Pxi0[Addr_in].deinterleave();
                   (VX1_76543210, VY1_76543210) =  Pxi1[Addr_in].deinterleave();
                   (VX2_76543210, VY2_76543210) =  Pxi2[Addr_in].deinterleave();
                   (VX3_76543210, VY3_76543210) =  Pxi3[Addr_in].deinterleave();

                   /*------------------------------------------------------------*/
                   /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
                   /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
                   /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
                   /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
                   /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
                   /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
                   /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
                   /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
                   /*                                                            */
                   /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */  
                   /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
                   /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
                   /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
                   /* -----------------------------------------------------------*/

                   (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
                   (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
                   (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();
                   (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

                   /*------------------------------------------------------------*/
                   /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
                   /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
                   /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
                   /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
                   /*                                                            */
                   /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
                   /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
                   /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
                   /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
                   /*------------------------------------------------------------*/

                   (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
                   (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
                   (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
                   (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

                   /*------------------------------------------------------------*/
                   /* Perform twiddle factor multiplies of three terms,top       */
                   /* term does not have any multiplies. Note the twiddle        */
                   /* factors for a normal FFT are C + j (-S). Since the         */
                   /* factors that are stored are C + j S, this is               */
                   /* corrected for in the multiplies.                           */
                   /*                                                            */
                   /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
                   /*                                                            */
                   /* x0r = xt0;                                                 */
                   /* y0i = yt0;                                                 */
                   /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
                   /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
                   /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
                   /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
                   /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
                   /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
                   /*------------------------------------------------------------*/

                   V_x2r  = (Vxt2 * VC2_76543210);
                   V_y2i  = (Vyt2 * VC2_76543210);
                   V_x2r += (Vyt2 * VS2_76543210);
                   V_y2i -= (Vxt2 * VS2_76543210);

                   V_x1r  = (Vxt1 * VC1_76543210);
                   V_y1i  = (Vyt1 * VC1_76543210);
                   V_x3r  = (Vxt3 * VC3_76543210);
                   V_y3i  = (Vyt3 * VC3_76543210);

                   V_x1r += (Vyt1 * VS1_76543210);
                   V_y1i -= (Vxt1 * VS1_76543210);
                   V_x3r += (Vyt3 * VS3_76543210);
                   V_y3i -= (Vxt3 * VS3_76543210);

                   /* -----------------------------------------------------------*/
                   /*  Store the final results back to output with transpoition. */
                   /*                                                            */
                   /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
                   /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
                   /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
                   /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
                   /* -----------------------------------------------------------*/

                   Pox0[Addr_ou].offset_np1() = V_x0r; 
                   Pox1[Addr_ou].offset_np1() = V_x1r.truncate(15); 
                   Pox2[Addr_ou].offset_np1() = V_x2r.truncate(15); 
                   Pox3[Addr_ou].offset_np1() = V_x3r.truncate(15);

                   Poy0[Addr_ou].offset_np1() = V_y0i;
                   Poy1[Addr_ou].offset_np1() = V_y1i.truncate(15);
                   Poy2[Addr_ou].offset_np1() = V_y2i.truncate(15);
                   Poy3[Addr_ou].offset_np1() = V_y3i.truncate(15);
               }
           }
       }
   }
}

/*---------------------------------------------------------------------------*/
/* In stage 4, operations are similar to previous stages of 1..2. Even       */
/*---------------------------------------------------------------------------*/

void vcop_fft_1024_16x16t_stage4
(

    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    __vptr_int16      PCS1,
    __vptr_int16      PCS2,
    __vptr_int16      PCS3,
    __vptr_int16      Pox0,
    __vptr_int16      Pox1,
    __vptr_int16      Pox2,
    __vptr_int16      Pox3
)
{
    for (int I3 = 0; I3 < 8; I3++)
    {
        for (int I4 = 0; I4 < 4; I4++)
        {
            __agen  Addr_in = I4 * 36    + I3 *  144 * 4;
            __agen  Addr_tw = I4 * 96    + I3 *  0   ;

            /*-----------------------------------------------------------*/
            /*  Read the complex input and de-interleave into real and   */
            /*  imaginary parts. Note we will be working on "VCOP_SIMD"  */
            /*  "_WIDTH" radix-4 butterflies or 8 radix-4 butterflies    */
            /*  in parallel.                                             */
            /*                                                           */
            /*  x_0    = x[0];       x_1 = x[1];                         */
            /*  x_2    = x[2];       x_3 = x[3];                         */
            /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                   */
            /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                   */
            /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                   */
            /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                   */
            /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                   */
            /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                   */
            /*                                                           */
            /*  Convention here is to denote the four input legs of the  */
            /*  butterfly as input 0, 1, 2, 3, and twiddle factors as    */
            /*  CS1, CS2 and CS3.                                        */
            /*-----------------------------------------------------------*/
            
            (VS1_76543210, VC1_76543210) =  PCS1[Addr_tw].deinterleave();
            (VS2_76543210, VC2_76543210) =  PCS2[Addr_tw].deinterleave();
            (VS3_76543210, VC3_76543210) =  PCS3[Addr_tw].deinterleave();

            (VX0_76543210, VY0_76543210) =  Pxi0[Addr_in].deinterleave();
            (VX1_76543210, VY1_76543210) =  Pxi1[Addr_in].deinterleave();
            (VX2_76543210, VY2_76543210) =  Pxi2[Addr_in].deinterleave();
            (VX3_76543210, VY3_76543210) =  Pxi3[Addr_in].deinterleave();

            /*------------------------------------------------------------*/
            /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20            */
            /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21            */
            /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21            */
            /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20            */
            /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20            */
            /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21            */
            /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21            */
            /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20            */
            /*                                                            */
            /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;             */  
            /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;             */
            /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;             */
            /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;             */
            /* -----------------------------------------------------------*/

            (Vxh0_76543210,  Vxl0_76543210)   = (VX0_76543210, VX2_76543210).addsub();
            (Vxh1_76543210,  Vxl1_76543210)   = (VY0_76543210, VY2_76543210).addsub();
            (Vxh20_76543210, Vxl20_76543210)  = (VX1_76543210, VX3_76543210).addsub();
            (Vxh21_76543210, Vxl21_76543210)  = (VY1_76543210, VY3_76543210).addsub();

            /*------------------------------------------------------------*/
            /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
            /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
            /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
            /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
            /*                                                            */
            /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
            /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
            /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
            /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
            /*------------------------------------------------------------*/

            (V_x0r, Vxt2) = (Vxh0_76543210, Vxh20_76543210).addsub();
            (Vxt1,  Vxt3) = (Vxl0_76543210, Vxl21_76543210).addsub();
            (V_y0i, Vyt2) = (Vxh1_76543210, Vxh21_76543210).addsub();
            (Vyt3,  Vyt1) = (Vxl1_76543210, Vxl20_76543210).addsub();

            /*------------------------------------------------------------*/
            /* Perform twiddle factor multiplies of three terms,top       */
            /* term does not have any multiplies. Note the twiddle        */
            /* factors for a normal FFT are C + j (-S). Since the         */
            /* factors that are stored are C + j S, this is               */
            /* corrected for in the multiplies.                           */
            /*                                                            */
            /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)          */
            /*                                                            */
            /* x0r = xt0;                                                 */
            /* y0i = yt0;                                                 */
            /* x1r = (xt1 * w1c +  yt1 * w1s) >> 15;                      */
            /* y1i = (yt1 * w1c -  xt1 * w1s) >> 15;                      */
            /* x2r = (xt2 * w2c +  yt2 * w2s) >> 15;                      */
            /* y2i = (yt2 * w2c -  xt2 * w2s) >> 15;                      */
            /* x3r = (xt3 * w3c +  yt3 * w3s) >> 15;                      */
            /* y3i = (yt3 * w3c -  xt3 * w3s) >> 15;                      */
            /*------------------------------------------------------------*/

            V_x2r  = (Vxt2 * VC2_76543210);
            V_y2i  = (Vyt2 * VC2_76543210);
            V_x2r += (Vyt2 * VS2_76543210);
            V_y2i -= (Vxt2 * VS2_76543210);

            V_x1r  = (Vxt1 * VC1_76543210);
            V_y1i  = (Vyt1 * VC1_76543210);
            V_x3r  = (Vxt3 * VC3_76543210);
            V_y3i  = (Vyt3 * VC3_76543210);

            V_x1r += (Vyt1 * VS1_76543210);
            V_y1i -= (Vxt1 * VS1_76543210);
            V_x3r += (Vyt3 * VS3_76543210);
            V_y3i -= (Vxt3 * VS3_76543210);

            /* -----------------------------------------------------------*/
            /*  Store the final results back to output with transpoition. */
            /*                                                            */
            /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
            /*  x[2*(i+j +   s) + 0] = y1r; x[2*(i+j +   s) + 1] = y1i    */
            /*  x[2*(i+j + 2*s) + 0] = y2r; x[2*(i+j + 2*s) + 1] = y2i    */
            /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
            /* -----------------------------------------------------------*/

            Pox0[Addr_in].interleave() = (V_x0r, V_y0i);
            Pox1[Addr_in].interleave() = (V_x1r, V_y1i).truncate(15);
            Pox2[Addr_in].interleave() = (V_x2r, V_y2i).truncate(15);
            Pox3[Addr_in].interleave() = (V_x3r, V_y3i).truncate(15);
        }
    }
}

/*---------------------------------------------------------------------------*/
/* In Stage 5, we only have simple twiddle factors of 1, j, 1, -j            */
/* So, no twiddle factor array is needed, but a lot of data arrangement      */
/* is needed, to take data contained within one SIMD word and having to      */
/* take it apart.                                                            */
/*---------------------------------------------------------------------------*/

void vcop_fft_1024_16x16t_stage5
(
    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    __vptr_int16      Pox0,
    __vptr_int16      Pox1,
    __vptr_int16      Pox2,
    __vptr_int16      Pox3
)
{
   Vcond = 1;

   for (int I2 = 0; I2 < 2;  I2++)
   {
       for (int I3 = 0; I3 < 4; I3++)
       {
           for (int I4 = 0; I4 < 4; I4++)
           {
               __agen  Addr_in = I4 * 144 + I3 * 144 * 4  + I2 * 144 * 16;
               __agen  Addr_ou = I4 * 256 + I3 * 64       + I2 * 32;

               /*--------------------------------------------------------------*/
               /*  x_0    = x[0];       x_1 = x[1];                            */
               /*  x_2    = x[2];       x_3 = x[3];                            */
               /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                      */
               /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                      */
               /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                      */
               /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                      */
               /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                      */
               /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                      */
               /*--------------------------------------------------------------*/

               (VnX0_76543210, VnY0_76543210) =  Pxi0[Addr_in].deinterleave();
               (VnX1_76543210, VnY1_76543210) =  Pxi1[Addr_in].deinterleave();
               (VnX2_76543210, VnY2_76543210) =  Pxi2[Addr_in].deinterleave();
               (VnX3_76543210, VnY3_76543210) =  Pxi3[Addr_in].deinterleave();

               #if 0
               printf ("Vnx0_76543210: ");  VnX0_76543210.printx();  
               printf ("Vny0_76543210: ");  VnY0_76543210.printx();  
               printf ("Vnx1_76543210: ");  VnX1_76543210.printx();  
               printf ("Vny1_76543210: ");  VnY1_76543210.printx();  
               printf ("Vnx2_76543210: ");  VnX2_76543210.printx();  
               printf ("Vny2_76543210: ");  VnY2_76543210.printx();  
               printf ("Vnx3_76543210: ");  VnX3_76543210.printx();  
               printf ("Vny3_76543210: ");  VnY3_76543210.printx();  
               #endif

               /*-------------------------------------------------------------*/
               /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
               /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
               /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
               /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
               /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
               /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
               /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
               /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
               /*                                                             */
               /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;              */   
               /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;              */
               /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;              */
               /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;              */
               /*                                                             */
               /* ------------------------------------------------------------*/

               (Vxh0_0, Vxl0_0)  =  (VnX0_76543210, VnX2_76543210).addsub();
               (Vxh1_0, Vxl1_0)  =  (VnY0_76543210, VnY2_76543210).addsub();

               (Vxh0_1, Vxl0_1)  =  (VnX1_76543210, VnX3_76543210).addsub();
               (Vxh1_1, Vxl1_1)  =  (VnY1_76543210, VnY3_76543210).addsub();

               #if 0
               printf ("Vxh0_0: ");  Vxh0_0.printx();
               printf ("Vxl0_0: ");  Vxl0_0.printx();
               printf ("Vxh1_0: ");  Vxh1_0.printx();
               printf ("Vxl1_0: ");  Vxl1_0.printx();

               printf ("Vxh0_1: ");  Vxh0_1.printx();
               printf ("Vxl0_1: ");  Vxl0_1.printx();
               printf ("Vxh1_1: ");  Vxh1_1.printx();
               printf ("Vxl1_1: ");  Vxl1_1.printx();
               #endif

               /*----------------------------------------------------------------*/
               /*  n00 = xh0_0 + xh0_1;       n01 = xh1_0 + xh1_1;               */
               /*  n10 = xl0_0 + xl1_1;       n11 = xl1_0 - xl0_1;               */
               /*  n20 = xh0_0 - xh0_1;       n21 = xh1_0 - xh1_1;               */
               /*  n30 = xl0_0 - xl1_1;       n31 = xl1_0 + xl0_1;               */
               /*                                                                */
               /*  In this implementation since X2 and X4 are swapped, xl0 <->   */
               /*  xh1 and yl0 <-> yh1                                           */
               /*----------------------------------------------------------------*/

               (V_n00, V_n20) =  (Vxh0_0,  Vxh0_1).addsub();
               (V_n10, V_n30) =  (Vxl0_0,  Vxl1_1).addsub();
               
               (V_n01, V_n21) =  (Vxh1_0,  Vxh1_1).addsub();
               (V_n31, V_n11) =  (Vxl1_0,  Vxl0_1).addsub();

               #if 0
               printf ("V_n00: ");  V_n00.printx();
               printf ("V_n20: ");  V_n20.printx();
               printf ("V_n10: ");  V_n10.printx();
               printf ("V_n30: ");  V_n30.printx();

               printf ("V_n01: ");  V_n01.printx();
               printf ("V_n21: ");  V_n21.printx();
               printf ("V_n31: ");  V_n31.printx();
               printf ("V_n11: ");  V_n11.printx();
               #endif
               

               /*----------------------------------------------------------------*/
               /* Use atomic swap with Vcond set to 1, to achieve both registers */
               /* swapping in same cycle.                                        */
               /*                                                                */
               /* y0[2*h2] = n00;           y0[2*h2 + 1] = n01;                  */
               /* y1[2*h2] = n10;           y1[2*h2 + 1] = n31;                  */
               /* y2[2*h2] = n20;           y2[2*h2 + 1] = n21;                  */
               /* y3[2*h2] = n11;           y3[2*h2 + 1] = n30;                  */
               /*----------------------------------------------------------------*/

               (V_n11, V_n31).swap(Vcond);    // (V_n11,  V_n31).swap(Vcond);
               (V_n31c,V_n30c).swap(Vcond);   // (V_n30c, V_n31c).swap(Vcond);

               #if 0
               printf ("V_n00: ");  V_n00.printx();
               printf ("V_n01: ");  V_n01.printx();
               printf ("V_n10: ");  V_n10.printx();
               printf ("V_n11: ");  V_n31.printx();
               printf ("V_n20: ");  V_n20.printx();
               printf ("V_n21: ");  V_n21.printx();
               printf ("V_n30: ");  V_n30c.printx();
               printf ("V_n31: ");  V_n31c.printx();
               #endif
               
               Pox0[Addr_ou].interleave() = (V_n00,  V_n01);           
               Pox1[Addr_ou].interleave() = (V_n10,  V_n31);
               Pox2[Addr_ou].interleave() = (V_n20,  V_n21);
               Pox3[Addr_ou].interleave() = (V_n30c, V_n31c);
           }
       }
   }
}


/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft-1024_16x16t_kernel.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */



    
