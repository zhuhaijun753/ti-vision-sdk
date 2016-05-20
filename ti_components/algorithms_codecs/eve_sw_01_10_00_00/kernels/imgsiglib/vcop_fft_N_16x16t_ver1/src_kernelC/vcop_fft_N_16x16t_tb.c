/* ========================================================================= */
/*   NAME                                                                    */
/*   vcop_fft_N_16x16t :  Test Bench.                                        */
/*   N-pt complex FFT with 16-bit inputs and 16-bit twiddle.                 */
/*                                                                           */
/*                                                                           */
/*   USAGE                                                                   */
/*     This routine is C-callable  and performs an N-pt complex FFT          */
/*   Maximum precision of input and outputs are 16-bit, and since FFT        */
/*   grows in precision by 2-bits per stage, and since we have log4(N)       */
/*   stages, it will grow to occupy full 16-bits. User is expected to        */
/*   control the input to be in a signed (16-2*Stages) bit range.            */
/*                                                                           */
/*    API:                                                                   */
/*                                                                           */
/*   void vcop_fft_N_16x16t_cn                                               */
/*   (                                                                       */
/*       const short  SC[],                                                  */
/*       const short  digit_rev[],                                           */
/*       int          npoints,                                               */
/*       short        X[],                                                   */
/*       short        Y[]                                                    */
/*   )                                                                       */
/*                                                                           */
/*   This function accepts a special vector form of twiddle factors in       */
/*   the array "SC" organized as sine first followed by cosine,              */
/*   an array of N complex points in X. Thes result is in an N point array Y.*/
/*   The digit reverse array is maintained in an N/4 length digit_rev array  */
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
/*   16-bit range. No range checking is performed. This code will            */
/*   work for the any N power of 4 except N=16 point complex FFT.            */
/*                                                                           */                                                                        
/*   NOTE                                                                    */
/*   It expects input and output arrays to be word aligned.                  */
/*                                                                           */ 
/*   CYCLES                                                                  */ 
/*                                                                           */
/*   Stage 1 :   (log4(N) - 2) * N/32 * 10  cycles                           */
/*   Stage 2:    1 * N/32 * 12    cycles                                     */
/*   Stage 3:    1 * N/32 * 16   cycles                                      */
/*   Stage digit reversal     = N cycles                                     */
/*   Total : N/32*(16+12+10*(log4(N)-2)) + N cycles                          */
/*                                                                           */                                                                     
/*   CODESIZE                                                                */
/*          496 bytes.                                                       */ 
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"
#include <math.h>

#undef uint16
#undef int16
#undef int32

typedef unsigned short uint16;

#if VCOP_HOST_EMULATION
  #include "vcop_fft_N_16x16t_kernel.k"    // kernel source
#else
  void vcop_fft_N_16x16t_stages_initial
  (
    __vptr_int16_arr  Pxi0,
    __vptr_int16_arr  Pxi1,
    __vptr_int16_arr  Pxi2,
    __vptr_int16_arr  Pxi3,
    __vptr_int16_arr  PCS1,
    __vptr_int16_arr  PCS2,
    __vptr_int16_arr  PCS3,
    uint16            bfys_per_grp[],
    uint16            grps[],
    uint16            passes,
    uint16            pinc3[],
    uint16            pinc4[],
    uint16            ptnc3[],
    uint16            ptnc4[]
  );

  void vcop_fft_N_16x16t_stage_2ndLast
  (

    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    __vptr_int16      PCS1,
    __vptr_int16      PCS2,
    __vptr_int16      PCS3,
    uint16            bfys_per_grp,
    uint16            grps,
    uint16            pinc3,
    uint16            pinc4,
    uint16            ptnc3,
    uint16            ptnc4
  );

  void vcop_fft_N_16x16t_stage_Last
  (
    __vptr_int16      Pxi0,
    __vptr_int16      Pxi1,
    __vptr_int16      Pxi2,
    __vptr_int16      Pxi3,
    uint16            bfys_per_grp,
    uint16            grps,
    uint16            pinc3,
    uint16            pinc4
  );

  void vcop_fft_digit_rev_N
  (
    __vptr_int32      Px,
    __vptr_uint16     digit_rev,
    __vptr_int32      Py,
    unsigned short    N
  );


#endif


#define uint16  unsigned short 
#define int16   short 
#define int32   int
#define true    1
#define false   0

/* ------------------------------------------------------------------------- */
/*  Input test data, limited to signed (16 - (2*log4(N))) bit input range to */
/*  dealwith signal growth in FFT, As an example, a 64 point FFT has 3       */
/*  stages, hence can grow by as much as 6-bits to fit in the 16-bit range.  */
/*  So input should be within 10-bit signed value                            */
/* ------------------------------------------------------------------------- */

#define N (64)
#define STAGES 3  //STAGES = LOG4(N)

#pragma DATA_SECTION (in, "Adata");
  short in[2*N] =
  {
    	0x03F9, 0x00B3, 0x028E, 0x02A4, 0x0391, 0x03FC, 0x0346, 0x01BE,
    	0x02D2, 0x0110, 0x0269, 0x0331, 0x0331, 0x003B, 0x0229, 0x012B,
    	0x01E3, 0x01B6, 0x021B, 0x02BC, 0x0297, 0x02DC, 0x033E, 0x01B9,
    	0x0064, 0x021E, 0x028D, 0x02CC, 0x0106, 0x0037, 0x0047, 0x006E,
    	0x0063, 0x03B2, 0x000D, 0x00D8, 0x0103, 0x02EB, 0x024B, 0x0076,
    	0x023F, 0x0303, 0x006A, 0x003D, 0x0109, 0x0038, 0x0225, 0x03FF,
    	0x018D, 0x02A4, 0x018B, 0x02EC, 0x0216, 0x01E5, 0x0045, 0x023B,
    	0x0193, 0x023D, 0x0209, 0x03FA, 0x029C, 0x001B, 0x002E, 0x0232,
    	0x0270, 0x01AA, 0x0160, 0x032E, 0x0200, 0x0138, 0x0236, 0x023D,
    	0x0302, 0x02B9, 0x0132, 0x03F6, 0x029E, 0x013D, 0x0089, 0x001C,
    	0x02FD, 0x030F, 0x0284, 0x0332, 0x01B4, 0x00E0, 0x0126, 0x00B0,
    	0x022B, 0x02D4, 0x0130, 0x0297, 0x0132, 0x023B, 0x0171, 0x0342,
    	0x03E6, 0x0222, 0x0261, 0x011D, 0x0021, 0x009B, 0x001F, 0x031A,
    	0x03F0, 0x02DA, 0x02D9, 0x0192, 0x0339, 0x0392, 0x018D, 0x0309,
    	0x012C, 0x03C0, 0x033E, 0x0105, 0x0029, 0x0295, 0x01D9, 0x00A0,
    	0x03A2, 0x038A, 0x03A9, 0x004C, 0x0333, 0x003F, 0x02B7, 0x03F6,
    };

/* ------------------------------------------------------------------------- */
/*  Twiddle factor array organized as SC, or sinecosine pairs, and as        */
/*  e^j*2*pi*n*k/N eventhough it is an FFT (like an IFFT) with the negative  */
/*  sign comprehended by software.                                           */
/* ------------------------------------------------------------------------- */

#pragma DATA_SECTION (SC_vector, "Bdata");
  short SC_vector[200] =
  {
  		0x0000, 0x7FFF, 0x0C8B, 0x7F61, 0x18F8, 0x7D89, 0x2527, 0x7A7C,
  		0x30FB, 0x7640, 0x3C56, 0x70E1, 0x471C, 0x6A6C, 0x5133, 0x62F1,
  		0x0000, 0x7FFF, 0x18F8, 0x7D89, 0x30FB, 0x7640, 0x471C, 0x6A6C,
  		0x5A81, 0x5A81, 0x6A6C, 0x471C, 0x7640, 0x30FB, 0x7D89, 0x18F8,
  		0x0000, 0x7FFF, 0x2527, 0x7A7C, 0x471C, 0x6A6C, 0x62F1, 0x5133,
  		0x7640, 0x30FB, 0x7F61, 0x0C8B, 0x7D89, 0xE708, 0x70E1, 0xC3AA,
  		0x5A81, 0x5A81, 0x62F1, 0x5133, 0x6A6C, 0x471C, 0x70E1, 0x3C56,
  		0x7640, 0x30FB, 0x7A7C, 0x2527, 0x7D89, 0x18F8, 0x7F61, 0x0C8B,
  		0x7FFF, 0x0000, 0x7D89, 0xE708, 0x7640, 0xCF05, 0x6A6C, 0xB8E4,
  		0x5A81, 0xA57F, 0x471C, 0x9594, 0x30FB, 0x89C0, 0x18F8, 0x8277,
  		0x5A81, 0xA57F, 0x3C56, 0x8F1F, 0x18F8, 0x8277, 0xF375, 0x809F,
  		0xCF05, 0x89C0, 0xAECD, 0x9D0F, 0x9594, 0xB8E4, 0x8584, 0xDAD9,
  		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
  		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
  		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
  		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
  		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
  		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
  		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
  		0x0000, 0x7FFF, 0x30FB, 0x7640, 0x5A81, 0x5A81, 0x7640, 0x30FB,
  		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
  		0x0000, 0x7FFF, 0x5A81, 0x5A81, 0x7FFF, 0x0000, 0x5A81, 0xA57F,
  		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
  		0x0000, 0x7FFF, 0x7640, 0x30FB, 0x5A81, 0xA57F, 0xCF05, 0x89C0,
  		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  };
/* ------------------------------------------------------------------------- */
/*  Region for output.                                                       */
/* ------------------------------------------------------------------------- */

#pragma DATA_SECTION (out, "Cdata");
short out[2*N] = {0};


/* ------------------------------------------------------------------------- */
/*  N/4 linear digit reversal table. For example, normal index 1, is         */
/*  placed in digit reversed index of 32 .                                   */
/* ------------------------------------------------------------------------- */

#pragma DATA_SECTION (digit_rev, "Bdata");
unsigned short digit_rev[N/4];

int16 EOut[2*N] =
{
		0x7EE3, 0x83F2, 0x0BEA, 0x05CC, 0x0CEF, 0xFC96, 0x0714, 0xF73E,
		0xFFED, 0xF80A, 0x07CB, 0x0997, 0x1234, 0x04DD, 0x03DD, 0x0BA1,
		0x0024, 0x04E2, 0xFCCF, 0xFF9A, 0xF81D, 0xFA11, 0x0635, 0xFCC0,
		0xFE21, 0xFED7, 0x06C9, 0x02D6, 0xFF4E, 0x05F9, 0xF17B, 0xF27A,
		0x0C0A, 0x0813, 0x0037, 0xFF5F, 0x00D7, 0xF128, 0xFBB2, 0x081C,
		0x02C8, 0xFF69, 0xF6B6, 0xF8C6, 0xF6F5, 0x039E, 0xF605, 0xF8A3,
		0xF3F4, 0xF504, 0x0160, 0x0097, 0x0292, 0xF310, 0xFD54, 0xFA55,
		0x03C1, 0x0269, 0x12E9, 0x07D4, 0x0BF4, 0xF549, 0xF8C8, 0x0185,
		0x0BEF, 0xFD7C, 0xF738, 0x0DC4, 0xFED5, 0xF160, 0xF1D6, 0xFEF4,
		0x05AD, 0xF3A8, 0x0889, 0xF3C7, 0xFE4A, 0x0251, 0x06A3, 0x0A57,
		0x0EA6, 0x02C4, 0x0081, 0xF07E, 0x0C05, 0xF6D7, 0xFE07, 0xF424,
		0x110F, 0x0355, 0x0AE9, 0xFDCA, 0xFE50, 0xEC13, 0x0EF9, 0xEDF6,
		0x016C, 0x1563, 0xFE17, 0x062D, 0xF3A1, 0x0F5E, 0x0198, 0xF822,
		0xFFB2, 0xF809, 0x0332, 0x12FC, 0xF8CD, 0xFBF4, 0xF4C7, 0xEFB5,
		0xF752, 0xFF42, 0x0254, 0x0D45, 0xFD0C, 0x009C, 0x0278, 0xFFEF,
		0xFDBB, 0x0083, 0x0029, 0x0004, 0x1416, 0x0767, 0x16C4, 0xF683,
};

/* ----------------------------------------------------------------------------*/
/*  Repeat loop is leveraged for (STAGES-2) pass, last 2 stages are done using */
/*  vloop, total of log4(N) stages.                                            */
/* --------------------------------------------------------------------------- */

uint16 passes       = STAGES;
uint16 passes_vloop = 2;
uint16 passes_rpt   = STAGES - 2;

/* ------------------------------------------------------------------------- */
/*  Spacing of the legs of the butterfly, as follows:                        */
/*                                                                           */
/*  Stage 1: N/4 points apart.                                               */
/*  Stage 2: N/16 points apart.                                              */
/*  And so on depending upon N                                               */
/*  Stage 2nd Last:  4  points apart, loaded as 8 points apart, re-arranged. */
/*  Stage Last:  1  point  apart, loaded as 8 points apart, re-arranged.     */
/*---------------------------------------------------------------------------*/

short *pxi0[STAGES];
short *pxi1[STAGES];
short *pxi2[STAGES];
short *pxi3[STAGES];

/*---------------------------------------------------------------------------*/
/*  Twiddle factors, are stored as 3 inputs per butterfly sequentially.      */
/*                                                                           */
/*  First stage: 0,     8,  16  3 twiddle factors per bfly, 16 bfys(N/4)     */
/*  Secd  stage: 16, 24, 32  3 twiddle factors per bfly, 4  bfys(N/16)       */
/*  In the second last stage the bfys are twice replicated for parallel      */
/*  processing 																 */
/*  In the last stage no twiddle factors required							 */
/*---------------------------------------------------------------------------*/

short *cs1[STAGES];
short *cs2[STAGES];
short *cs3[STAGES];

/*---------------------------------------------------------------------------*/
/* The comments below are for 64 Point FFT case. For any other N, please     */
/* refer to the FFTguide.                                                    */  
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* In the Parameters for 1st stage, we perform 1 set of N/4 4-point          */
/* FFT's. Since the vector core has two operation slots, each of             */
/* which works on eight data points, we work on 8 radix-4 bflies             */
/* in parallel. Therefore we only need one level of loop, which              */
/* will iterate N/32 times, so loop counter is set to this value             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* In the first stage of the radix-4 FFT, we point the data at inp.          */
/* offsets of 0, N/4, N/2 and 3 N/4 which for example N = 64 maps to         */
/* 0, 64, 128, 192 in byte offsets, as each offset is 4 bytes                */
/* corresponding to 2 bytes real, 2 bytes imaginary. After we                */
/* calculate the radix-4 butterfly we write the output at the                */
/* same locations. Since we load 8 complex inputs from each of               */
/* the legs of the butterfly, input increment is 32 bytes. We                */
/* maintain twiddle factors in sets of 8, for the three inputs,              */
/* (2*pi*n*k)/N, (4*pi*n*k/N) and (6*pi*N*k)/N, so we jump by 96             */
/* bytes. Since we only have one level of loop, outer level loop             */
/* increments are set to 0. The shift by 15 as twiddle factors               */
/* are in Q15 is done by the store out. This is also why twiddle             */
/* factors for the three legs are set to be 8 complex values                 */
/* apart at 0, 32 and 64.                                                    */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* Parameters for 2nd stage  4 sets of 4 4-point FFT's.                      */
/* Note SIMD width is 8, but now we have only 4 radix-4 FFt's, so            */
/* we do two sets, replicating the twiddle factor. Therefore inner           */
/* loop iterates twice, outer loop iterates 1 time to accomplish             */
/* 16 radix-4 butterflies. We can only load 8 points apart, so               */
/* we set the 4 legs of the butterfly to point to offsets 0, 8,              */
/* 16 and 32, which correspond to byte offsets of 0, 32, 64 and              */
/* 128. We offset twiddle by the amount of 3*(16). The                       */
/* data pointer increments by 128 for inner loop iteration, and              */
/* by 128 for every outer loop iteration, as we load consecutive             */
/* points. Once again round out by 15 is done through the store              */
/* unit. Although in this iteration we need data at offsets 0,               */
/* 4, 8 and 12 we will have to prepare this in register file.                */
/*---------------------------------------------------------------------------*/    

/*---------------------------------------------------------------------------*/    
/* Parameters for 3rd stage  64 sets of 4 4-point FFT's. Note                */
/* SIMD width is 8, but now we have only 4 radix-4 FFt's, so do              */
/* two sets in parallel, we do not need twiddle factor. Here we              */
/* merely load, re-arrange data as required and do radix-4                   */
/* butterflies without any multiply. So, we only have inner loop             */
/* where we increment by 128. So both twiddle factor increments are 0.       */                                                
/*---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/    
/* In this implementation, we do a seperate digit reversal stage.           */
/* We have a table of 16(N/4) entries to do this. So inner loop             */
/* iterates 2 times = 16/8, and outer loop reuses this                      */
/* table 4 times. For every iteration of the inner loop, we                 */
/* jump by one radix 4, ie 0, 32, 64, and so on, which in a byte            */
/* index is 0, 128, 256 and so on. We then rewind by -128*31 and            */
/* jump to the next leg of the butterfly by adding 32. For the              */
/* digit reversal table, we jump by 8 entries, being hw 16 bytes            */
/* rewinding by -16 x 31, to achieve re-use.                                */
/*                                                                          */
/* This is coded as an explicit loop, so these pointer increments are       */
/* not carried as part of the array.                                        */
/*--------------------------------------------------------------------------*/ 
 
uint16 bfys_per_grp[STAGES];    //These are inner loop iterations
uint16 grps[STAGES] ;           //outer loop iterations
uint16 pinc3[STAGES];           //Pointers to 1st leg of 1st BF of 2nd Groups for the input array in bytes.
uint16 ptnc3[STAGES];           //For twiddle factors
uint16 pinc4[STAGES];           //Increments within a group between different inner loop iterations for input.
uint16 ptnc4[STAGES];           //pointer increments for twiddle factors. 96 Bytes


/*--------------------------------------------------------------------------*/ 
/*  Top level FFT function, which leverages repeat loops for first stage    */
/*  It uses a regular loop for 2nd and 3rd stage, with pointer increments   */
/*  passed as arguments. It then does a seperate digit reversal loop.       */
/*  This is a good example, where RISC core queues up back to back loops    */
/*  for execution on the vector core.                                       */
/*--------------------------------------------------------------------------*/ 
void parameters_generator();
void digitrev_index(unsigned short *index, int n2, int radix);
void vcop_fft_N_16x16t_cn (short in[2*N], short SC[200], unsigned short digit_rev[N/4], short out[2*N])
{

	vcop_fft_N_16x16t_stages_initial
    (
        pxi0, 
        pxi1, 
        pxi2, 
        pxi3, 
        cs1, 
        cs2, 
        cs3, 
        bfys_per_grp,
        grps,
        passes_rpt,
        pinc3,
        pinc4,
        ptnc3,
        ptnc4
     );

    vcop_fft_N_16x16t_stage_2ndLast
    (
        pxi0[STAGES - 2],
        pxi1[STAGES - 2],
        pxi2[STAGES - 2],
        pxi3[STAGES - 2],
        cs1[STAGES - 2],
        cs2[STAGES - 2],
        cs3[STAGES - 2],
        bfys_per_grp[STAGES - 2],
        grps[STAGES - 2],
        pinc3[STAGES - 2],
        pinc4[STAGES - 2],
        ptnc3[STAGES - 2],
        ptnc4[STAGES - 2]
     );

    vcop_fft_N_16x16t_stage_Last
    (
        pxi0[STAGES - 1],
        pxi1[STAGES - 1],
        pxi2[STAGES - 1],
        pxi3[STAGES - 1],
        bfys_per_grp[STAGES - 1],
        grps[STAGES - 1],
        pinc3[STAGES - 1],
        pinc4[STAGES - 1]
     );

     vcop_fft_digit_rev_N
     (
         (int *) (&in[0]),   
         digit_rev,
         (int *) (&out[0]),
         N
     );
}

/*-------------------------------------------------------------------------- */
/*  Call FFT function, where input data is in "in", twiddle factor array     */
/*  is in "SC_vector", digit reversal array is in "digit_rev" and            */
/*  output array is in "out".                                                */
/*-------------------------------------------------------------------------- */

int main()
{
	/*-----------------------------------------------------------------------*/
	/*  Fill the digit_rev, pxix,csx, grps, pincx, ptncx arrays              */
	/*-----------------------------------------------------------------------*/
	parameters_generator();
	digitrev_index(digit_rev, N/4, 4);
	

	/*-----------------------------------------------------------------------*/
    /*  Call FFT routine here.                                               */
    /*-----------------------------------------------------------------------*/

    vcop_fft_N_16x16t_cn(in, SC_vector, digit_rev, out);

    /*-----------------------------------------------------------------------*/
    /*  Compare output "out" with expected output after digit reversal.      */
    /*-----------------------------------------------------------------------*/
    if (memcmp (out, EOut, sizeof (EOut)))
        printf ("\nFail \n");
        else
        printf ("\nPass \n");

}

/*-----------------------------------------------------------------------*/
/*  Fills the pxiX,csX, grps, pincX, ptncX arrays                        */
/*-----------------------------------------------------------------------*/


void parameters_generator(){
	int i,power;
	int MUL = 0;//Multiplier for twiddle factor index calculation
	for (i=0; i<STAGES; i++){

		power = pow(4,i+1);
		if (i < (STAGES - 2)){

			pxi0[i]= &in[2 * N/ power*0];
			pxi1[i]= &in[2 * N/ power*1];
			pxi2[i]= &in[2 * N/ power*2];
			pxi3[i]= &in[2 * N/ power*3];

			bfys_per_grp[i] = N/(8 * pow(4,i+1));

			pinc4[i] = 32;
			}
		else {
			pxi0[i]= &in[2 * 0];
			pxi1[i]= &in[2 * 8];
			pxi2[i]= &in[2 * 16];
			pxi3[i]= &in[2 * 24];

			if (i==(STAGES-2))
				bfys_per_grp[i] = 2;
			else
				bfys_per_grp[i] = N/32;

			pinc4[i] = 128;
		}

		if (i < STAGES - 1){
			cs1[i] = &SC_vector[MUL + 2*0];
			cs2[i] = &SC_vector[MUL + 2*8];
			cs3[i] = &SC_vector[MUL + 2*16];
			MUL = MUL + 2 * 3 * N/power;

			ptnc4[i] = 96;
		}
		grps[i] = N/(4 * 8 * bfys_per_grp[i]);

		if (i == 0 | i == STAGES - 1)
			pinc3[i] = 0;
		else
			pinc3[i] = 4 * N / grps[i];

		ptnc3[i] = 0;

	}


}

/*-----------------------------------------------------------------------*/
/*  Fills the digit_rev array passed as 'index'                          */
/*-----------------------------------------------------------------------*/

void digitrev_index(unsigned short *index, int n2, int radix){
	int i,j,k;
	index[0] = 0;
	for ( i = 1, j = n2/radix + 1; i < n2 - 1; i++){
		index[i] = 4*(j - 1);
	for (k = n2/radix; k*(radix-1) < j; k /= radix)
			j -= k*(radix-1);
		j += k;
	}
	index[n2 - 1] = 4*(n2 - 1);
}


/*-------------------------------------------------------------------------- */
/* End of file: vcop_fft_N_16x16t_tb.c                                    */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */

