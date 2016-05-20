/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*----------------------------------------------------------------------------*/
/* NAME : vcop_bayer_subsampling_kernel                                       */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*  Version : 0.0 (Base Version) :Gajanan Ambi                                */
/*============================================================================*/
/* Texas Instruments Incorporated 2009-2012.                                  */
/*----------------------------------------------------------------------------*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMBSZ    (sizeof (*CFA_short))

void bayer_subSampling
(
  __vptr_uint16 CFA_short,      /*Input block pointer*/
  __vptr_uint16 subSample_out,  /*Output block pointer*/
  unsigned int  blk_w,          /*Input block width*/
  unsigned int  blk_h,          /*Input block height*/
  unsigned int  input_stride,
  unsigned int  output_stride,
  unsigned int  subSample_X,    /*Horizontal sampling value*/
  unsigned int  subSample_Y,    /*Vertical sampling  value*/
  unsigned int  NumOfSample     /*Number of samples to be taken*/
)
{
  __vector pixel1,pixel2;
  for(int I0 = 0; I0 < (blk_h/subSample_Y); I0++)
  {
    for(int I1 = 0; I1 < (blk_w/subSample_X); I1++)
    {
      __agen Addr_in,Addr_out;
      Addr_in  = (I0*input_stride*subSample_Y*ELEMBSZ) + (I1*subSample_X*ELEMBSZ);
      Addr_out = (I0*output_stride*ELEMBSZ*2) + (I1*NumOfSample*2*ELEMBSZ);

      pixel1 = CFA_short[Addr_in];
      pixel2 = (CFA_short + (input_stride*ELEMBSZ))[Addr_in];

      subSample_out[Addr_out] = pixel1;
      (subSample_out + (output_stride*ELEMBSZ))[Addr_out] = pixel2;
    }
  }
}


