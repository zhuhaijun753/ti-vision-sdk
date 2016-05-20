/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_deInterleaveYUV422IBE                                           */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/22/12..............Initial Version........Victor Cheng             */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_deInterleaveYUV422IBE(                                     */
/*          __vptr_uint8        src,                                        */
/*          __vptr_uint8        dst,                                        */
/*          __vptr_uint8        dst_u,                                      */
/*          __vptr_uint8        dst_v,                                      */
/*          unsigned short      size                                        */
/*     )                                                                    */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#include "vcop_remap.h"

/* Deinterleaves the chroma and luma pixels */
void vcop_deInterleaveYUV422IBE(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        __vptr_uint8        dst_u,
        __vptr_uint8        dst_v,
        unsigned short      size
){
    for (int I1 = 0; I1 < ALIGN_2SIMD(2*size)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr, Addr_yout, Addr_uvout;

        __vector yVec, uvVec, vVec;

        Addr = I1*2*VCOP_SIMD_WIDTH*sizeof(*src);
        Addr_yout= I1*VCOP_SIMD_WIDTH*sizeof(*dst);
        Addr_uvout= I1*(VCOP_SIMD_WIDTH/2)*sizeof(*dst);

        (yVec, uvVec) = src[Addr].deinterleave();
        (uvVec, vVec).deinterleave();

        dst_u[Addr_uvout]= uvVec;
        dst[Addr_yout]= yVec;
        dst_v[Addr_uvout]= vVec;
    }
}
