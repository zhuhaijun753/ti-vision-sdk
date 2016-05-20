/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_memcpy                                     */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     12/2/13..............Second Version........Saurabh Chandra           */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_memcpy(                               */
/*             __vptr_uint8        src,                                     */
/*             __vptr_uint8        dst,                                     */
/*             unsigned short      outputBlockSize,                         */
/*             __vptr_uint16       tluIndexArray,                           */
/*             __vptr_uint16       scratch,                                 */
/*             __vptr_uint8        scratchHbuf,                             */
/*             __vptr_uint16       stride_ptr,                              */
/*             unsigned char       mnQShift,                                */
/*             unsigned char       oQShift,                                 */
/*             unsigned short      qScale,                                  */
/*             unsigned char       mult,                                    */
/*             unsigned char       rightShift,                              */
/*             long                sat_high,                                */
/*             long                sat_high_set,                            */
/*             long                sat_low,                                 */
/*             long                sat_low_set                              */
/*     )                                                                    */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#include "vcop_remap.h"

/* Compute the bilinear interpolated luma pixels for U8BIT format */
void vcop_memcpy(
        __vptr_uint32       src,
        __vptr_uint32       dst,
        unsigned short      blockSize
)
{
    for (int I1 = 0; I1 < ALIGN_4SIMD(blockSize)/(4*VCOP_SIMD_WIDTH); I1++) {

        __vector Vsrc, Vdst;
        __agen Addr1;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*src);

        Vsrc = src[Addr1].npt();
        Vdst = Vsrc;
        dst[Addr1] = Vdst;

    }
}
void vcop_memcpy2d(
        __vptr_uint16       src,
        __vptr_uint16       dst,
        unsigned short      width,
        unsigned short      height,
        unsigned short      pitch
)
{
  for (int I1 = 0; I1 < height; I1++)
  {

    for (int I2 = 0; I2 < ALIGN_2SIMD(width)/(2*VCOP_SIMD_WIDTH); I2++)
    {

      __vector Vsrc;
      __agen Addr1;
      __agen Addr2;

      Addr1 = I1*pitch + I2*VCOP_SIMD_WIDTH*sizeof(*src);
      Addr2 = I1*width + I2*VCOP_SIMD_WIDTH*sizeof(*dst);

      Vsrc = src[Addr1].npt();
      dst[Addr2] = Vsrc;

    }
  }
}
