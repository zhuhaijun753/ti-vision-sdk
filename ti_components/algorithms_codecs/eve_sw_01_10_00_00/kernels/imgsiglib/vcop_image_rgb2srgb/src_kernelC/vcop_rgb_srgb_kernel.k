/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMBSZ    (sizeof (*iPtrR))
#define VECTORSZ  (VCOP_SIMD_WIDTH * ELEMBSZ)

void rgb_to_srgb
(
__vptr_uint16   iPtrR,
__vptr_uint16   iPtrG,
__vptr_uint16   iPtrB,
__vptr_uint16   oPtrR,
__vptr_uint16   oPtrG,
__vptr_uint16   oPtrB,
unsigned short  blk_w,
unsigned short  blk_h,
unsigned short  input_stride,
unsigned short  output_stride,
__vptr_int16    rgb2srgb_coefs
)
{
  __vector  Vred,Vgrn, Vblu;
  __vector  Vcoef0,Vcoef1,Vcoef2,Vcoef3,Vcoef4,Vcoef5,Vcoef6,Vcoef7,Vcoef8;
  __vector VsRed,VsGreen,VsBlue;

  Vcoef0 = *(rgb2srgb_coefs);
  Vcoef1 = *(rgb2srgb_coefs+1);
  Vcoef2 = *(rgb2srgb_coefs+2);
  Vcoef3 = *(rgb2srgb_coefs+3);
  Vcoef4 = *(rgb2srgb_coefs+4);
  Vcoef5 = *(rgb2srgb_coefs+5);
  Vcoef6 = *(rgb2srgb_coefs+6);
  Vcoef7 = *(rgb2srgb_coefs+7);
  Vcoef8 = *(rgb2srgb_coefs+8);

  for(int I0 = 0; I0 < blk_h; I0++)
  {
    for(int I1 =0; I1 < (blk_w/VCOP_SIMD_WIDTH); I1++)
    {
      __agen Addr_in  = (I0 * input_stride * ELEMBSZ) + (I1 * VECTORSZ);
      __agen Addr_out = (I0 * output_stride * ELEMBSZ) + (I1 * VECTORSZ);

      Vred   =  (iPtrR)[Addr_in].npt();
      Vgrn   =  (iPtrG)[Addr_in].npt();
      Vblu   =  (iPtrB)[Addr_in].npt();

      VsRed   = 0x80;
      VsGreen = 0x80;
      VsBlue  = 0x80;

      VsRed  +=  (Vcoef0  *  Vred);
      VsRed  +=  (Vcoef1  *  Vgrn);
      VsRed  +=  (Vcoef2  *  Vblu);

      VsGreen  +=  (Vcoef3  *  Vred);
      VsGreen  +=  (Vcoef4  *  Vgrn);
      VsGreen  +=  (Vcoef5  *  Vblu);

      VsBlue  +=  (Vcoef6  *  Vred);
      VsBlue  +=  (Vcoef7  *  Vgrn);
      VsBlue  +=  (Vcoef8  *  Vblu);

      (oPtrR)[Addr_out] = VsRed.truncate(8).saturate(0,4095);
      (oPtrG)[Addr_out] = VsGreen.truncate(8).saturate(0,4095);
      (oPtrB)[Addr_out] = VsBlue.truncate(8).saturate(0,4095);
    }
  }
}

/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv_kernel.k                          */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

