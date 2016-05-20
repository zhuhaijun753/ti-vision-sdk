/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDownsample                                     */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDownsample" accepts  8 or 16-bit data   */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 444 or */
/* 422 format, the output can be of 444, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCr444_Downsample422_char                           */
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
/* void vcop_YCbCr444_Downsample422_short                          */
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
/* YCbCr444_Downsample422_char: 5/8 cyc/pix                        */
/* YCbCr444_Downsample422_short: 5/4 cyc/pix                       */
/*                                                                 */
/*=================================================================*/


#define VCOP_2SIMD_WIDTH    (16) 

#define ELEMSZ_IN_CHAR      sizeof( *YCbCr_char )
#define VECTORSZ_IN_CHAR    ((VCOP_SIMD_WIDTH - 2) * ELEMSZ_IN_CHAR)

#define ELEMSZ_IN_SHORT     sizeof( *YCbCr_short )
#define VECTORSZ_IN_SHORT   ((VCOP_SIMD_WIDTH - 2) * ELEMSZ_IN_SHORT)

#define ELEMSZ_Y_CHAR       sizeof( *Y_char )
#define VECTORSZ_Y_CHAR     (VCOP_SIMD_WIDTH * ELEMSZ_Y_CHAR)

#define VECTORSZ_Cb_CHAR    ((VCOP_SIMD_WIDTH - 4) * ELEMSZ_Y_CHAR)

#define ELEMSZ_Y_SHORT       sizeof( *Y_short )
#define VECTORSZ_Y_SHORT    ((VCOP_SIMD_WIDTH - 4) * ELEMSZ_Y_SHORT)

#define VECTORSZ_Cb_SHORT   (2 * ELEMSZ_Y_SHORT)


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


void vcop_YCbCr444_Downsample422_char
(
    __vptr_uint32  YCbCr_char,  
    __vptr_int8    YCbCrmask,
    unsigned int   npixels,
    __vptr_uint8   Y_char,
    __vptr_uint8   Cb_char,
    __vptr_uint8   Cr_char
)
{
    __vector VY, VCb, VCr;
    __vector VCb0, VCb1;
    __vector VCr0, VCr1;

    /*-----------------------------------------------------------*/
    /* YCbCr 444 pattern is:                                     */
    /* Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr                   */
    /*-----------------------------------------------------------*/
    
   __vector  VYm,    VYs;
   __vector  VCbm,   VCbs;
   __vector  VCrm,   VCrs;
   __vector  VCb422, VCr422;
   __vector  V_shft1, Vdummy;

   /*------------------------------------------------------------*/
   /* We use an outer loop to load various masks to extract      */
   /* bytes.                                                     */
   /*------------------------------------------------------------*/

   for (int I0 = 0; I0 < 1; I0++)
   {
       __agen Addr_m = I0;

       VYm  = (YCbCrmask +  0)[Addr_m];
       VCbm = (YCbCrmask +  8)[Addr_m];
       VCrm = (YCbCrmask + 16)[Addr_m];

       /*--------------------------------------------------------*/
       /* We work on VCOP_SIMD_WIDTH elements at a time, load    */
       /* the values, using custom load so that each way has     */
       /* one pixel of "Y", "Cb" or "Cr".                        */
       /*--------------------------------------------------------*/

       Vdummy  = 0;
       V_shft1 = -1;

       for (int I1 = 0; I1 < (npixels/VCOP_SIMD_WIDTH); I1++)
       {
            __agen Addr_in;
            __agen Addr_out;
            __agen Addr_Cb_out;

            Addr_in  = I1 * VECTORSZ_IN_CHAR;
            Addr_out = I1 * VECTORSZ_Y_CHAR;
            Addr_Cb_out = I1 * VECTORSZ_Cb_CHAR;

            VY       = YCbCr_char[Addr_in].dist(K0, K0, K1, K2, K3, K3, K4, K5);
            VCb      = YCbCr_char[Addr_in].dist(K0, K1, K1, K2, K3, K4, K4, K5);
            VCr      = YCbCr_char[Addr_in].dist(K0, K1, K2, K2, K3, K4, K5, K5);

            /*---------------------------------------------------*/
            /* The shift amounts to be applied are as follows:   */
            /*                                                   */
            /* Y:   0 24 16  8   0 24  16   8                    */
            /* Cb:  8 0  24 16   8  0  16  24                    */
            /* Cr: 16 8   0 24  16  8   0  24                    */
            /*---------------------------------------------------*/

            VYs    =  (VY  << VYm);  
            VCbs   =  (VCb << VCbm);  
            VCrs   =  (VCr << VCrm);  

            /*--------------------------------------------------*/
            /* Deinterleave Cb and Cr for averaging             */
            /*--------------------------------------------------*/

            (VCb0, VCb1) = (VCbs, VCbs).deinterleave();
            VCb422 = (VCb0 + VCb1);
            VCb0 = VCb422 << V_shft1;
            
            (VCr0, VCr1) = (VCrs, VCrs).deinterleave();
            VCr422 = (VCr0 + VCr1);
            VCr0 = VCr422 << V_shft1;
            
            Y_char[Addr_out]   = VYs;
            Cb_char[Addr_Cb_out].npt()  = VCb0;
            Cr_char[Addr_Cb_out].npt()  = VCr0;
        }
    }
}

void vcop_YCbCr444_Downsample422_short
(
    __vptr_uint32  YCbCr_short,
    __vptr_int8    YCbCrmask,
    unsigned int   npixels,
    __vptr_uint16  Y_short,
    __vptr_uint16  Cb_short,
    __vptr_uint16  Cr_short
)
{
    __vector VY, VCb, VCr;
    __vector VCb0, VCb1;
    __vector VCr0, VCr1;

    /*-----------------------------------------------------------*/
    /* YCbCr 444 pattern is:                                     */
    /* Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr Y Cb Cr                   */
    /*-----------------------------------------------------------*/
    
   __vector  VYm,    VYs;
   __vector  VCbm,   VCbs;
   __vector  VCrm,   VCrs;
   __vector  VCb422, VCr422;
   __vector  V_shft1, Vdummy;

   /*------------------------------------------------------------*/
   /* We use an outer loop to load various masks to extract      */
   /* bytes.                                                     */
   /*------------------------------------------------------------*/

   for (int I0 = 0; I0 < 1; I0++)
   {
       __agen Addr_m = I0;

       VYm  = (YCbCrmask +  0)[Addr_m];
       VCbm = (YCbCrmask +  8)[Addr_m];
       VCrm = (YCbCrmask + 16)[Addr_m];

       /*--------------------------------------------------------*/
       /* We work on VCOP_SIMD_WIDTH elements at a time, load    */
       /* the values, using custom load so that each way has     */
       /* one pixel of "Y", "Cb" or "Cr".                        */
       /*--------------------------------------------------------*/

       Vdummy  =  0;
       V_shft1 = -1;

       for (int I1 = 0; I1 < (npixels/VCOP_SIMD_WIDTH); I1++)
       {
            __agen Addr_in;
            __agen Addr_out;
            __agen Addr_Cb_out;

            Addr_in     =  I1 * VECTORSZ_IN_SHORT;
            Addr_out    =  I1 * VECTORSZ_Y_SHORT;
            Addr_Cb_out =  I1 * VECTORSZ_Cb_SHORT;

            VY   =  YCbCr_short[Addr_in].dist(K0, K1, K3, K4, K6, K7, K0, K0);
            VCb  =  YCbCr_short[Addr_in].dist(K0, K2, K3, K5, K6, K0, K0, K0);
            VCr  =  YCbCr_short[Addr_in].dist(K1, K2, K4, K5, K7, K0, K0, K0);

            /*---------------------------------------------------*/
            /* The shift amounts to be applied are as follows:   */
            /*                                                   */
            /* Y:   0 24 16  8   0 24  16   8                    */
            /* Cb:  8 0  24 16   8  0  16  24                    */
            /* Cr: 16 8   0 24  16  8   0  24                    */
            /*---------------------------------------------------*/

            VYs    =  (VY  << VYm);  
            VCbs   =  (VCb << VCbm);  
            VCrs   =  (VCr << VCrm);  

            /*--------------------------------------------------*/
            /* Deinterleave Cb and Cr for averaging             */
            /*--------------------------------------------------*/

            (VCb0, VCb1) = (VCbs, VCbs).deinterleave();
            VCb422 = VCb0 + VCb1;
            VCb422 = VCb422 << V_shft1;

            (VCr0, VCr1) = (VCrs, VCrs).deinterleave();
            VCr422 = (VCr0 + VCr1);
            VCr422 = VCr422 << V_shft1;

            Y_short[Addr_out]   = VYs;
            Cb_short[Addr_Cb_out].npt()  = VCb422;
            Cr_short[Addr_Cb_out].npt()  = VCr422;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * */
