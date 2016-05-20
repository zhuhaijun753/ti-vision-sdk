/* ========================================================================= */
/*   NAME                                                                    */
/*   vcop_fft_64_16x16t :  Test Bench.                                       */
/*   64-pt complex FFT with 16-bit inputs and 16-bit twiddle.                */
/*                                                                           */
/*                                                                           */
/*   USAGE                                                                   */
/*     This routine is C-callable  and performs a 64-pt complex FFT.         */
/*   Maximum precision of input and outputs are 16-bit, and since FFT        */
/*   grows in precision by 2-bits per stage, and since we have 3             */
/*   stages, it will grow to occupy full 16-bits. User is expected to        */
/*   control the input to be in a signed 10-bit range.                       */
/*                                                                           */
/*    API:                                                                   */
/*                                                                           */
/*   void vcop_fft_64_16x16t_cn                                              */
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
/*   table of 16 entries in digit_rev for digit reversal, the number         */
/*   of complex points "npoints" is FIXED at 64 complex points and           */
/*   should not be changed, input array of 64 complex points in X,           */
/*   an output array of 64 complex points in Y.                              */
/*                                                                           */
/*   Even though this is an FFT, twiddle factors are maintained for          */
/*   exp^(2*pi*j*n*k)/N and not for exp^(-2*pi*j*n*k/N). Please refer        */
/*   to the behavC sub-directory for more explanation on how vector          */
/*   array of twiddle factors are generated.                                 */ 
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
/*   work for the specific case of a 64 point complex FFT.                   */
/*                                                                           */                                                                        
/*   NOTE                                                                    */
/*   It expects input and output arrays to be word aligned.                  */
/*                                                                           */ 
/*   CYCLES                                                                  */ 
/*                                                                           */
/*   Stage 1 : 1 * 2 * 10  =  20  cycles                                     */
/*   Stage 2:    1 * 2 * 12  = 24   cycles                                   */
/*   Stage 3:    1 * 2 * 16  = 32  cycles                                    */
/*   Stage digit reversal     = 64 cycles                                    */
/*   Total : 140 cycles                                                      */
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

#include "vcop_fft_64_16x16t_regs.inc"


void vcop_fft_64_16x16t_stage_1
(
    __vptr_int16_arr  Pxi0,
    __vptr_int16_arr  Pxi1,
    __vptr_int16_arr  Pxi2,
    __vptr_int16_arr  Pxi3,
    __vptr_int16_arr  PCS1,
    __vptr_int16_arr  PCS2,
    __vptr_int16_arr  PCS3,
    unsigned short            bfys_per_grp[],
    unsigned short            grps[],
    unsigned short            passes,
    unsigned short            pinc3[],
    unsigned short            pinc4[],
    unsigned short            ptnc3[],
    unsigned short            ptnc4[]
)
{


    foreach (I0, passes, 5)
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

                (VX0_76543210, VY0_76543210) =  Pxi0[I0][Addr_in].deinterleave();
                (VX1_76543210, VY1_76543210) =  Pxi1[I0][Addr_in].deinterleave();
                (VX2_76543210, VY2_76543210) =  Pxi2[I0][Addr_in].deinterleave();
                (VX3_76543210, VY3_76543210) =  Pxi3[I0][Addr_in].deinterleave();

                (VS1_76543210, VC1_76543210) =  PCS1[I0][Addr_tw].deinterleave();
                (VS2_76543210, VC2_76543210) =  PCS2[I0][Addr_tw].deinterleave();
                (VS3_76543210, VC3_76543210) =  PCS3[I0][Addr_tw].deinterleave();

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
/* In second last stage, operations are similar to previous stage(s). However*/
/* most vector architectures face trouble, as we need to add or subtract     */
/* data within a vector word. Hence we have to re-arrange the data.          */
/* Further we use two sets of twiddle factors, none the less, we use         */
/* two pointer increments for both input and twiddle.                        */
/*---------------------------------------------------------------------------*/

void vcop_fft_64_16x16t_stage2
(

    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    __vptr_int16      PCS1,
    __vptr_int16      PCS2,
    __vptr_int16      PCS3,
    unsigned short            bfys_per_grp,
    unsigned short            grps,
    unsigned short            pinc3,
    unsigned short            pinc4,
    unsigned short            ptnc3,
    unsigned short            ptnc4
)
{
   for (int I3 = 0; I3 < grps; I3++)
   {
       for (int I4 = 0; I4 < bfys_per_grp; I4++)
       {
           __agen  Addr_in = I3*pinc3 + I4*pinc4;
           __agen  Addr_tw = I3*ptnc3 + I4*ptnc4;

           /*-----------------------------------------------------------------*/
           /* Read the four samples that are the input to this                */
           /* particular butterfly.                                           */
           /*                                                                 */
           /* x0r = x[2*(i+j      ) + 0]; x0i = x[2*(i+j      ) + 1];         */
           /* x1r = x[2*(i+j +   s) + 0]; x1i = x[2*(i+j +   s) + 1];         */
           /* x2r = x[2*(i+j + 2*s) + 0]; x2i = x[2*(i+j + 2*s) + 1];         */
           /* x3r = x[2*(i+j + 3*s) + 0]; x3i = x[2*(i+j + 3*s) + 1];         */
           /*                                                                 */
           /* Note that legs are swapped, loading data meant for X1           */
           /* into X2, so that after we apply INTRLV4, we can re-use          */
           /* the same butterfly equations as before                          */
           /* ----------------------------------------------------------------*/

           (VX0_76543210, VY0_76543210) =  Pxi0[Addr_in].deinterleave();
           (VX2_76543210, VY2_76543210) =  Pxi1[Addr_in].deinterleave();
           (VX1_76543210, VY1_76543210) =  Pxi2[Addr_in].deinterleave();
           (VX3_76543210, VY3_76543210) =  Pxi3[Addr_in].deinterleave();

           /* ----------------------------------------------------------------*/
           /* We keep twiddle factors ordered as firrst 8 Cosines and         */
           /* then 8 Sines.                                                   */
           /*                                                                 */
           /* Memory:                                                         */
           /* C1: 101112131415161718  S1: 101112131415161718                  */
           /* C2: 202122232425262728  S2: 202122232425262728                  */
           /* C3: 303132333435363738  S3: 303132333435363738                  */
           /*                                                                 */
           /* C1 is W[0......7]       S1: W[8..15]                            */
           /* C2 is W[16.....23]      S2: W[24..31]                           */
           /* C3 is W[24.....31]      S3: W[32..39]                           */
           /*                                                                 */
           /* C1: 2*pi*i*j/N   C2: 4*pi*i*j/N  C3:6*pi*i*j/N                  */
           /* ----------------------------------------------------------------*/

           (VS1_76543210, VC1_76543210) =  PCS1[Addr_tw].deinterleave();
           (VS2_76543210, VC2_76543210) =  PCS2[Addr_tw].deinterleave();
           (VS3_76543210, VC3_76543210) =  PCS3[Addr_tw].deinterleave();

           /*-----------------------------------------------------------------*/
           /* In penultimate stage we need to align X0, X8, X10, X18          */
           /*                                                                 */
           /* VX0 = X00X02X04X06X08X10X12X14  VX1=X20X22X24X26X28X2AX2CX2E    */
           /* VX2 = X10X12X14X16X18X1AX1CX1E  VX3=X30X32X34x36X38X3AX3CX3E    */
           /* VY0 = Y01Y03Y05Y07Y09Y0BY0DY0F  VY1=Y21Y23Y25Y27Y29Y2BY2DY2F    */
           /* VY2 = Y11Y13Y15Y17Y19Y1BY1DY1F  VY3=Y31Y33Y35Y37Y39Y3BY3DY3F    */
           /*-----------------------------------------------------------------*/

           (VX0_76543210, VX1_76543210).interleave4();
           (VX2_76543210, VX3_76543210).interleave4();
           (VY0_76543210, VY1_76543210).interleave4();
           (VY2_76543210, VY3_76543210).interleave4();

           /*-----------------------------------------------------------------*/
           /* This exchange is done using VINTRLV4, align X00, X08, X10, X18  */
           /*                                                                 */
           /* VX0 = X00X02X04X06X20X22X24X26  VX1=X08X0AX0CX0EX28X2AX2CX2E    */
           /* VX2 = X10X12X14X16X30X32X34X36  VX3=X18X1AX1Cx1EX38X3AX3CX3E    */
           /* VY0 = Y01Y03Y05Y07Y21Y23Y25Y27  VY1=Y09Y0BY0DY0FY29Y2BY2DY2F    */
           /* VY2 = Y11Y13Y15Y17Y31Y33Y35Y37  VY3=Y19Y1BY1DY1FY39Y3BY3DY3F    */
           /*-----------------------------------------------------------------*/

           /*--------------------------------------------------------------*/
           /* x0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20               */
           /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21               */
           /* x1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21               */
           /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20               */
           /*                                                              */
           /* x2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20               */
           /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21               */
           /* x3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21               */
           /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20               */
           /*--------------------------------------------------------------*/

           (Vxh0_76543210,  Vxl0_76543210)   =  (VX0_76543210, VX2_76543210).addsub();
           (Vxh1_76543210,  Vxl1_76543210)   =  (VY0_76543210, VY2_76543210).addsub();
           (Vxh20_76543210, Vxl20_76543210)  =  (VX1_76543210, VX3_76543210).addsub();
           (Vxh21_76543210, Vxl21_76543210)  =  (VY1_76543210, VY3_76543210).addsub();

           (V_x0r, Vxt2)    =  (Vxh0_76543210, Vxh20_76543210).addsub();
           (Vxt1,  Vxt3)    =  (Vxl0_76543210, Vxl21_76543210).addsub();
           (V_y0i, Vyt2)    =  (Vxh1_76543210, Vxh21_76543210).addsub();
           (Vyt3,  Vyt1)    =  (Vxl1_76543210, Vxl20_76543210).addsub();

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
           /*  Store the final results back to the input array.          */
           /*                                                            */
           /*  x[2*(i+j      ) + 0] = y0r; x[2*(i+j      ) + 1] = y0i    */
           /*  x[2*(i+j +   s) + 0] = y2r; x[2*(i+j +   s) + 1] = y2i    */
           /*  x[2*(i+j + 2*s) + 0] = y1r; x[2*(i+j + 2*s) + 1] = y1i    */
           /*  x[2*(i+j + 3*s) + 0] = y3r; x[2*(i+j + 3*s) + 1] = y3i    */
           /*                                                            */
           /* Store once again like data was loaded x0, x2, followed     */
           /* by x1 and x3.                                              */
           /* -----------------------------------------------------------*/

           Pxi0[Addr_in].interleave() = (V_x0r, V_y0i);
           Pxi1[Addr_in].interleave() = (V_x2r, V_y2i).truncate(15);
           Pxi2[Addr_in].interleave() = (V_x1r, V_y1i).truncate(15);
           Pxi3[Addr_in].interleave() = (V_x3r, V_y3i).truncate(15);
       }
   }
}

/*---------------------------------------------------------------------------*/
/* In last stage, we only have simple twiddle factors of 1, j, 1, -j         */
/* So, no twiddle factor array is needed, but a lot of data arrangement      */
/* is needed, to take data contained within one SIMD word and having to      */
/* take it apart.                                                            */
/*---------------------------------------------------------------------------*/

void vcop_fft_64_16x16t_stage3
(
    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    unsigned short            bfys_per_grp,
    unsigned short            grps,
    unsigned short            pinc3,
    unsigned short            pinc4
)
{
   Vcond = 1;

   for (int I3 = 0; I3 < grps; I3++)
   {
       for (int I4 = 0; I4 < bfys_per_grp; I4++)
       {
           __agen  Addr_in = I3*pinc3 + I4*pinc4;

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
           (VnX4_76543210, VnY4_76543210) =  Pxi1[Addr_in].deinterleave();
           (VnX2_76543210, VnY2_76543210) =  Pxi2[Addr_in].deinterleave();
           (VnX6_76543210, VnY6_76543210) =  Pxi3[Addr_in].deinterleave();

           /*--------------------------------------------------------------*/
           /*  We did not do INTLV4() to fix the output, so when we load   */
           /*  the data as follows:                                        */
           /*                                                              */
           /*  X00X02X04X06X20X22X24X26                                    */
           /*  X10X12X14X16X30X32X34X36                                    */
           /*  X08X0AX0CX0EX28X2AX2CX2E                                    */
           /*  X18Z1AX1CX1EX38X3AX3CX3E                                    */
           /*--------------------------------------------------------------*/

           (VnX0_76543210, VnX2_76543210).interleave4();
           (VnX4_76543210, VnX6_76543210).interleave4();
           (VnY0_76543210, VnY2_76543210).interleave4();
           (VnY4_76543210, VnY6_76543210).interleave4();

           /*---------------------------------------------------------------*/
           /*  Here we need to take a 4x4 transpose as the legs of the      */
           /*  FFT butterfly are spaced 1 element apart.                    */
           /*                                                               */
           /*  INTRLV4:                                                     */
           /*  X0 = X00X02X04X06X10X12X14X16  X4 = X08X0AX0CX0EX18X1AX1CX1E */
           /*  X2 = X20X22X24X26X30X32X38X3A  X6 = X28X2AX2CX2EX38X3AX3CX3E */
           /*                                                               */
           /*  INTRLV2:                                                     */
           /*  X0 = X00X02X08X0AX04X06X0CX0E  X4 = X10X12X18X1AX14X16X1CX1E */
           /*  X2 = X20X22X28X2AX24X26X2CX2E  X6 = X30X32X38X3AX34X36X3CX3E */
           /*                                                               */
           /*  INTRLV4:                                                     */
           /*  X0 = X00X02X08X0AX10X12X18X1A  X4 = X04X06X0CX0EX14X16X1CX1E */
           /*  X2 = X20X22X28X2AX30X32X38X3A  X6 = X24X26X2CX2EX34X36X3CX3E */
           /*                                                               */
           /*  DINTRLV:                                                     */
           /*  X0 = X00X08X10X18X20X28X30X38  X2 = X02X0AX12X1AX22X2AX32X3A */
           /*  X4 = X04X0CX14X1CX24X2CX34X3C  X6 = X06X0EX16X1EX26X2EX36X3E */
           /*                                                               */
           /*  Similarly for imaginary.                                     */
           /*---------------------------------------------------------------*/

           (VnX0_76543210, VnX4_76543210).interleave4();
           (VnX2_76543210, VnX6_76543210).interleave4();
           (VnX0_76543210, VnX4_76543210).interleave2();
           (VnX2_76543210, VnX6_76543210).interleave2();
           (VnX0_76543210, VnX4_76543210).interleave4();
           (VnX2_76543210, VnX6_76543210).interleave4();
           (VnX0_76543210, VnX2_76543210).deinterleave();
           (VnX4_76543210, VnX6_76543210).deinterleave();

           (VnY0_76543210, VnY4_76543210).interleave4();
           (VnY2_76543210, VnY6_76543210).interleave4();
           (VnY0_76543210, VnY4_76543210).interleave2();
           (VnY2_76543210, VnY6_76543210).interleave2();
           (VnY0_76543210, VnY4_76543210).interleave4();
           (VnY2_76543210, VnY6_76543210).interleave4();
           (VnY0_76543210, VnY2_76543210).deinterleave();
           (VnY4_76543210, VnY6_76543210).deinterleave();

           /*----------------------------------------------------------------*/
           /*   xh0_0 = x_0 + x_4;       xh1_0 = x_1 + x_5;                  */
           /*   xl0_0 = x_0 - x_4;       xl1_0 = x_1 - x_5;                  */
           /*   xh0_1 = x_2 + x_6;       xh1_1 = x_3 + x_7;                  */
           /*   xl0_1 = x_2 - x_6;       xl1_1 = x_3 - x_7;                  */
           /*----------------------------------------------------------------*/
           
           (VnX0_76543210, VnX4_76543210).addsub();
           (VnY0_76543210, VnY4_76543210).addsub();
           (VnX2_76543210, VnX6_76543210).addsub();
           (VnY2_76543210, VnY6_76543210).addsub();

           /*----------------------------------------------------------------*/
           /*  n00 = xh0_0 + xh0_1;       n01 = xh1_0 + xh1_1;               */
           /*  n10 = xl0_0 + xl1_1;       n11 = xl1_0 - xl0_1;               */
           /*  n20 = xh0_0 - xh0_1;       n21 = xh1_0 - xh1_1;               */
           /*  n30 = xl0_0 - xl1_1;       n31 = xl1_0 + xl0_1;               */
           /*----------------------------------------------------------------*/

           (Vxh0,          Vxh1).addsub();
           (Vyh0,          Vyh1).addsub();
           (Vxl0,          Vyl1).addsub();
           (Vyl0,          Vxl1).addsub();

           /*----------------------------------------------------------------*/
           /* Use atomic swap with Vcond set to 1, to achieve both registers */
           /* swapping in same cycle.                                        */
           /*                                                                */
           /* y0[2*h2] = n00;           y0[2*h2 + 1] = n01;                  */
           /* y1[2*h2] = n10;           y1[2*h2 + 1] = n31;                  */
           /* y2[2*h2] = n20;           y2[2*h2 + 1] = n21;                  */
           /* y3[2*h2] = n11;           y3[2*h2 + 1] = n30;                  */
           /*----------------------------------------------------------------*/

           (Vxl1, Vyl0).swap(Vcond);
           (Vxl1, Vyl1).swap(Vcond);

           Pxi0[Addr_in].interleave() = (V_n00, V_n01);           
           Pxi1[Addr_in].interleave() = (V_n10, V_n31);
           Pxi2[Addr_in].interleave() = (V_n20, V_n21);
           Pxi3[Addr_in].interleave() = (V_n11, V_n30);

       }
   }
}

/*---------------------------------------------------------------------------*/
/*  We implement the digit reversal as a seperate loop, where we use the     */
/*  store with write offsets. We load input data in as words, read the       */
/*  first 8 indices, obtain their digit reversed indices, and then use       */
/*  scatter to scatter them back. In digit reversal indices, that are        */
/*  close go further apart, and the entire digit reversal can be done        */
/*  with a lookup table whose size is N/4 if FFT size is N.                  */
/*---------------------------------------------------------------------------*/

void vcop_fft_digit_rev_64
(
    __vptr_int32      Px,
    __vptr_uint16     digit_rev,
    __vptr_int32      Py
)
{
    for (int I3 = 0; I3 < 4; I3++)
    {
       for (int I4 = 0; I4 < 2; I4++)//i4 < n/32
       {
           __agen  Addr_in = I3*32   + I4*128;//no change
           __agen  Addr_o  = I3*64 + I4*0;//n, nochange
           __agen  Addr_d  = I3*0    + I4*16;//no change

           VnYX76543210  = Px[Addr_in];
           VidYX76543210 = digit_rev[Addr_d];
           Py[Addr_o].s_scatter(VidYX76543210)  = VnYX76543210;
       }
    }
}
           
/*-------------------------------------------------------------------------- */
/*  End of file: vcop_fft-64_16x16t_kernel.k                               */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */



    
