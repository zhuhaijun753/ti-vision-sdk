/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_image_pyramid_uv_u8                                             */
/*                                                                          */
/*S    REVISION HISTORY                                                    S*/
/*S    03/02/10..............Initial Version.........Y.Senthil Kumar       S*/
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_image_pyramid_uv_u8                                        */
/*     (                                                                    */
/*         __vptr_uint8  pIn,                                              */
/*         unsigned short inCols,                                           */
/*         unsigned short inRows,                                           */
/*         __vptr_uint8  pOut                                              */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  16-bit input image                                       */
/*     inCols   :  Number of coluns in the image                            */
/*     inRows   :  Number of rows in the image                              */
/*     pOut     :  16-bit output image                                      */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 16-bit input image and outputs three */
/*     levels of image pryamid in the pOut array.                           */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 16. */
/*                                                                          */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_image_pyramid_uv_u8
(
    __vptr_uint8  pIn,
    unsigned short inCols,
    unsigned short inRows,
    __vptr_uint8  pOut
)
{
    __vector S;
    __vector in00,in01,in10,in11,temp;

    for( int I1 = 0; I1 < inRows/2; I1++)
    {
        for(int I2 = 0; I2 < inCols/(2*VCOP_SIMD_WIDTH); I2++)
        {
            __agen Addr1,Addr2;

            Addr1 = I1*2*inCols*ELEMSZ + I2*2*VECTORSZ;
            Addr2 = inCols/2*I1*ELEMSZ + I2*VECTORSZ;

            in00 = pIn                           [Addr1];
            in01 = (pIn+VECTORSZ)                [Addr1];
            in10 = (pIn+inCols*ELEMSZ)           [Addr1];
            in11 = (pIn+inCols*ELEMSZ+VECTORSZ)[Addr1];

            (in00,in01).deinterleave2();
            (in10,in11).deinterleave2();

            temp = in01 + in10;
            temp += in11 + in00;

            pOut[Addr2] = temp.round(2);
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_image_pyramid_uv_u8_one_level_kernel.k                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


