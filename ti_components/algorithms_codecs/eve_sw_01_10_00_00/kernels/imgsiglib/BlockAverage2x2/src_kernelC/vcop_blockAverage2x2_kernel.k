/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_blockAverage2x2_uchar for the imgsig library.               */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_blockAverage2x2_uchar                                      */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *out,                                             */
/*          int           w_input,                                          */
/*          int           w_out,                                            */
/*          int           w_compute,                                        */
/*          int           h_compute,                                        */
/*     );                                                                   */
/*                                                                          */
/*                                                                          */
/*     *in        :  Pointer to an input array of "type_input".             */
/*     *out       :  Pointer to output array of "type_output".              */
/*     w_input    :  Width (stride) of the input block in pixels.           */
/*     w_out     :   Width (stride) of the output block in pixels.          */
/*     blk_w      :  Width of the computation ROI within the input block to be processed */
/*     blk_h      :  Height of the computation ROI within the input block to be processed */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*     The avg2x2 decomposes the ROI of the input block into 2x2 tiles and  */
/*     computes the average value within each tile.                         */
/*     Th output size is effectively 4 times smaller than the input         */
/*    VARIANTS                                                              */
/*    There are four versions of the function based on the type of the      */
/*    input data. They are:                                                 */
/*    vcop_blockAvaerage2x2_uchar()                                         */
/*    vcop_blockAvaerage2x2_char()                                          */
/*    vcop_blockAvaerage2x2_ushort()                                        */
/*    vcop_blockAvaerage2x2_short()                                         */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*    - w_compute <= w_input and h_compute <= h_input.                      */
/*    - w_compute must be a multiple of 16.                                 */
/*    - h_compute must be a multiple of 2.                                  */
/*                                                                          */
/*     PERFORMANCE/CYCLES                                                   */
/*     2/16= 0.125 cyc/pix                                                  */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT       sizeof(*result)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_blockAverage2x2_uchar
(
    __vptr_uint8  in,                  //  Pointer to an input array of "type_input".
    __vptr_uint8 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute +(2*VCOP_SIMD_WIDTH-1)) / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;
            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}

void vcop_blockAverage2x2_char
(
    __vptr_int8  in,                  //  Pointer to an input array of "type_input".
    __vptr_int8 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute +(2*VCOP_SIMD_WIDTH-1))  / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;

            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}

void vcop_blockAverage2x2_ushort
(
    __vptr_uint16  in,                  //  Pointer to an input array of "type_input".
    __vptr_uint16 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute +(2*VCOP_SIMD_WIDTH-1))  / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;

            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}

void vcop_blockAverage2x2_short
(
    __vptr_int16  in,                  //  Pointer to an input array of "type_input".
    __vptr_int16 result,               //  Pointer to output array of "type_output".
    int          w_in,              //  Width of the input image in pixels.
    int          w_out,                //  Width of the compute block in pixels.
    int          w_compute,                //  The compute width over which avg2x2 values are found.
    int          h_compute                //  The compute height for avg2x2 filter.
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    for (int i=0; i< h_compute / 2; i++) {

        for (int j=0; j< (w_compute + (2*VCOP_SIMD_WIDTH-1))  / (2*VCOP_SIMD_WIDTH); j++) {

            __vector vIn0a, vIn0b, vIn1a, vIn1b,vAver0,vAver1;
            __agen AddrIn, AddrOut;

            AddrIn= j*2*VECTORSZ_IN + i*ELEMSZ_IN*w_in*2;
            AddrOut= j*VECTORSZ_OUT + i*ELEMSZ_OUT*w_out;

            (vIn0a, vIn0b)= in[AddrIn].deinterleave();
            (vIn1a, vIn1b)= (in + ELEMSZ_IN*w_in)[AddrIn].deinterleave();

            vAver0= vIn0a + vIn0b;
            vAver1= vIn1a + vIn1b;

            vAver0+= vAver1;

            result[AddrOut].npt()= vAver0.round(2);

        }
    }

}
