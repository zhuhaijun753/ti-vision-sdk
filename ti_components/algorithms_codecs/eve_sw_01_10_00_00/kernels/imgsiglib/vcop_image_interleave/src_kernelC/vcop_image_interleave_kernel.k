/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_image_pyramid_u8_one_level_kernel                               */
/*                                                                          */
/*S    REVISION HISTORY                                                    S*/
/*S    03/02/10..............Initial Version.........Sarthak Aggrwal       S*/
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_image_pyramid_u8                                           */
/*     (                                                                    */
/*        	 __vptr_uint8   pIn,                                            */
/*         	unsigned short inCols,                                          */
/*         	unsigned short inRows,                                          */
/*			__vptr_uint8   pOutY,											*/
/*			__vptr_uint8   pOutUV                                           */
/*     )                                                                    */
/*                                                                          */
/*     pIn      :  8-bit input image                                        */
/*     inCols   :  Number of coluns in the image                            */
/*     inRows   :  Number of rows in the image                              */
/*     pOutY    :  8-bit Y output image                                     */
/*     pOutUV    :  8-bit UV output image                                   */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an 8-bit input image and outputs three  */
/*     levels of image pryamid in the pOut array.                           */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of columns in the input image should be a multiple of 16. */
/*                                                                          */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ          sizeof(*pInY)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_image_interleave_u8
(
    __vptr_uint8   pInY,
	__vptr_uint8   pInUV,
    unsigned short inCols,
    unsigned short inRows,
    __vptr_uint8   pOut
)
{
    __vector in00,in01,a,b;

    for( int I1 = 0; I1 < inRows; I1++)
    {
        for(int I2 = 0; I2 < inCols/(VCOP_SIMD_WIDTH); I2++)
        {
            __agen Addr1,Addr2;

            Addr1 = I1*inCols*ELEMSZ + I2*VECTORSZ;
            Addr2 = (2*inCols)*I1*ELEMSZ + I2*2*VECTORSZ  ;

            in00 = pInY[Addr1];
            in01 = pInUV[Addr1];

			//(in01,in00).interleave();
            //pOut[Addr2] = in01;
            //(pOut + VECTORSZ)[Addr2] = in00;

            a = in00;
            b = in01;
            pOut[Addr2].interleave() = (b,a);
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_image_pyramid_u8_one_level_kernel.k                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


