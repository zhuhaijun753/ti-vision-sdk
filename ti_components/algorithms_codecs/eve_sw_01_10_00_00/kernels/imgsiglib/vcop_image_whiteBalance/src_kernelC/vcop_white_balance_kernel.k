/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*----------------------------------------------------------------------------*/
/* NAME : vcop_white_balance_kernel                                       */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*  Version : 0.0 (Base Version) :Gajanan Ambi                                */
/*============================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define VCOP_2SIMD_WIDTH   (VCOP_SIMD_WIDTH * 2)

#define ELEMSZ           sizeof(*CFA_short_in)
#define VECTORSZ_1SIMD  (ELEMSZ * VCOP_SIMD_WIDTH)
#define VECTORSZ_2SIMD  (ELEMSZ * VCOP_2SIMD_WIDTH)
#define NUM_OF_LINES_PROCESSED 2

void vcop_white_balance_BGGR
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VB0, VG0) = CFA_short_in[Addr_in].deinterleave();
      (VG1, VR0) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VB0_wb = (VB0 * VGAIN_FACT_B);
      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);
      VR0_wb = (VR0 * VGAIN_FACT_R);

      CFA_short_out[Addr_out].interleave() = (VB0_wb,VG0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VG1_wb,VR0_wb).round(shift_val);
    }
  }
}


void vcop_white_balance_GBRG
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VG0 , VB0) = CFA_short_in[Addr_in].deinterleave();
      (VR0 , VG1) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VB0_wb = (VB0 * VGAIN_FACT_B);
      VR0_wb = (VR0 * VGAIN_FACT_R);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);

      CFA_short_out[Addr_out].interleave() = (VG0_wb,VB0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VR0_wb,VG1_wb).round(shift_val);
    }
  }
}


void vcop_white_balance_GRBG
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VG0 , VR0 ) = CFA_short_in[Addr_in].deinterleave();
      (VB0 , VG1) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VR0_wb = (VR0 * VGAIN_FACT_R);
      VB0_wb = (VB0 * VGAIN_FACT_B);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);

      CFA_short_out[Addr_out].interleave() = (VG0_wb,VR0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VB0_wb,VG1_wb).round(shift_val);
    }
  }
}


void vcop_white_balance_RGGB
(
  __vptr_uint16 CFA_short_in,      /*Input block pointer*/
  __vptr_uint16 CFA_short_out,     /*Output block pointer*/
  unsigned int  blk_w,             /*Input block width*/
  unsigned int  blk_h,             /*Input block height*/
  unsigned int  gain_factor_R,     /*Gain value for R component*/
  unsigned int  gain_factor_Gr,    /*Gain value for Gr component*/
  unsigned int  gain_factor_Gb,    /*Gain value for Gb component*/
  unsigned int  gain_factor_B,     /*Gain value for B component*/
  unsigned int  shift_val,         /*Shift val*/
  unsigned int  input_stride,      /*Input stride value*/
  unsigned int  output_stride      /*Output stride value*/
)
{
  __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;
  __vector VB0_wb, VR0_wb, VR1_wb, VG0_wb, VG1_wb;
  __vector VGAIN_FACT_R, VGAIN_FACT_Gr, VGAIN_FACT_Gb, VGAIN_FACT_B;

  VGAIN_FACT_R  = gain_factor_R;
  VGAIN_FACT_Gb = gain_factor_Gb;
  VGAIN_FACT_Gr = gain_factor_Gr;
  VGAIN_FACT_B  = gain_factor_B;

  for(int I0 = 0; I0 < ((blk_h/2) +1); I0++)
  {
    for(int I1 =0; I1 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I1++)
    {
      __agen Addr_in,Addr_out;

      Addr_in     = (I0 * NUM_OF_LINES_PROCESSED * input_stride * ELEMSZ)  +   (I1 * VECTORSZ_2SIMD);
      Addr_out    = (I0 * NUM_OF_LINES_PROCESSED * output_stride * ELEMSZ) +   (I1 * VECTORSZ_2SIMD);

      (VR0, VG0) = CFA_short_in[Addr_in].deinterleave();
      (VG1, VB0) = (CFA_short_in + (input_stride * ELEMSZ))[Addr_in].deinterleave();

      VR0_wb = (VR0 * VGAIN_FACT_R);
      VG0_wb = (VG0 * VGAIN_FACT_Gb);
      VG1_wb = (VG1 * VGAIN_FACT_Gr);
      VB0_wb = (VB0 * VGAIN_FACT_B);

      CFA_short_out[Addr_out].interleave() = (VR0_wb,VG0_wb).round(shift_val);
      (CFA_short_out + (output_stride*ELEMSZ))[Addr_out].interleave() = (VG1_wb,VB0_wb).round(shift_val);
    }
  }
}

