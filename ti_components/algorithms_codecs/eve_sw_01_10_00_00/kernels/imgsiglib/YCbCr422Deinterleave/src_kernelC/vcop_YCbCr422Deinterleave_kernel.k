/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDeinterleave                                   */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDeinterleave" acceptsd 8 or 16-bit data */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 422 or */
/* 422 format, the output can be of 422, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCr422_Deinterleave422_char                         */
/* (                                                               */
/*     __vptr_uint32  YCbCr_char,                                  */
/*     __vptr_int8    YCbCrmask,                                   */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint8   Y_char,                                      */
/*     __vptr_uint8   Cb_char,                                     */
/*     __vptr_uint8   Cr_char                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop_YCbCr422_Deinterleave422_short                        */
/* (                                                               */
/*     __vptr_uint32  YCbCr_short,                                 */
/*     __vptr_int8    YCbCrmask,                                   */
/*     unsigned int   npixels,                                     */
/*     __vptr_uint16  Y_short,                                     */
/*     __vptr_uint16  Cb_short,                                    */
/*     __vptr_uint16  Cr_short                                     */
/* );                                                              */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* YCbCr422_Deinterleave422_char: 1/8 cyc/pix                      */
/* YCbCr422_Deinterleave422_short: 1/8 cyc/pix                     */
/*                                                                 */
/*=================================================================*/


#define VCOP_2SIMD_WIDTH    (16) 

#define ELEMSZ_IN_CHAR      sizeof( *YCbYCr_char )
#define VECTORSZ_IN_CHAR    (VCOP_2SIMD_WIDTH * ELEMSZ_IN_CHAR)

#define ELEMSZ_IN_SHORT     sizeof( *YCbYCr_short )
#define VECTORSZ_IN_SHORT   (VCOP_2SIMD_WIDTH * ELEMSZ_IN_SHORT)

#define ELEMSZ_Y_CHAR       sizeof( *Y_char )
#define VECTORSZ_Y_CHAR     (VCOP_SIMD_WIDTH * ELEMSZ_Y_CHAR)

#define ELEMSZ_Cb_CHAR       sizeof( *Cb_char )
#define VECTORSZ_Cb_CHAR     ((VCOP_SIMD_WIDTH - 4) * ELEMSZ_Cb_CHAR)

#define ELEMSZ_Y_SHORT       sizeof( *Y_short )
#define VECTORSZ_Y_SHORT    (VCOP_SIMD_WIDTH * ELEMSZ_Y_SHORT)

#define ELEMSZ_Cb_SHORT       sizeof( *Cb_short )
#define VECTORSZ_Cb_SHORT    ((VCOP_SIMD_WIDTH - 4) * ELEMSZ_Cb_SHORT)

#define K0                  0
#define K1                  1
#define K2                  2
#define K3                  3
#define K4                  4
#define K5                  5
#define K6                  6
#define K7                  7
#define K8                  8

/* * * * * * * * * * * * * * * * * * * * */


void vcop_YCbCr422_Deinterleave422_char
(
    __vptr_uint8   YCbYCr_char,  
    unsigned int   npixels,
    __vptr_uint8   Y_char,
    __vptr_uint8   Cb_char,
    __vptr_uint8   Cr_char
)
{
    __vector VY, VCb, VCr;
    __vector VCbCr;
    __vector Vdummy;

    /*-----------------------------------------------------------*/
    /* YCbCr 422 pattern is:                                     */
    /* Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr                   */
    /*-----------------------------------------------------------*/
    
   Vdummy = 0;
   for (int I1 = 0; I1 < (npixels/VCOP_2SIMD_WIDTH); I1++)
   {
       __agen Addr_in;
       __agen Addr_Y_out;
       __agen Addr_Cb_out;

       Addr_in     = I1 * VECTORSZ_IN_CHAR;
       Addr_Y_out  = I1 * VECTORSZ_Y_CHAR;
       Addr_Cb_out = I1 * VECTORSZ_Cb_CHAR;

       (VY, VCbCr) = YCbYCr_char[Addr_in].deinterleave();

       (VCb, VCr) = (VCbCr, Vdummy).deinterleave();

       Y_char[Addr_Y_out]   = VY;
       Cb_char[Addr_Cb_out].npt()  = VCb;
       Cr_char[Addr_Cb_out].npt()  = VCr;

   }
}

void vcop_YCbCr422_Deinterleave422_short
(
    __vptr_uint16  YCbYCr_short,
    unsigned int   npixels,
    __vptr_uint16  Y_short,
    __vptr_uint16  Cb_short,
    __vptr_uint16  Cr_short
)
{
    __vector VY, VCb, VCr;
    __vector VCbCr;
    __vector Vdummy;

    /*-----------------------------------------------------------*/
    /* YCbCr 422 pattern is:                                     */
    /* Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr                   */
    /*-----------------------------------------------------------*/
    
   Vdummy = 0;
   for (int I1 = 0; I1 < (npixels/VCOP_2SIMD_WIDTH); I1++)
   {
       __agen Addr_in;
       __agen Addr_Y_out;
       __agen Addr_Cb_out;

       Addr_in     = I1 * VECTORSZ_IN_SHORT;
       Addr_Y_out  = I1 * VECTORSZ_Y_SHORT;
       Addr_Cb_out = I1 * VECTORSZ_Cb_SHORT;

       (VY, VCbCr) = YCbYCr_short[Addr_in].deinterleave();
       (VCb, VCr) = (VCbCr, Vdummy).deinterleave();

       Y_short[Addr_Y_out]   = VY;
       Cb_short[Addr_Cb_out].npt()  = VCb;
       Cr_short[Addr_Cb_out].npt()  = VCr;
   }
}


/* * * * * * * * * * * * * * * * * * * * */
