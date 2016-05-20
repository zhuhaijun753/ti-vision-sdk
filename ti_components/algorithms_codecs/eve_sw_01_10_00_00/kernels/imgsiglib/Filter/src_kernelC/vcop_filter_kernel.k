/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_filter, FIR filter for the VICP library.                    */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_filter                                                     */
/*     (                                                                    */
/*         unsigned char  *in,                                              */
/*         unsigned char  *f,                                               */
/*         unsigned char  *out,                                             */
/*         int            w_input,                                          */
/*         int            w_coeff,                                          */
/*         int            h_coeff,                                          */
/*         int            w_compute,                                        */
/*         int            h_compute,                                        */
/*         int            dnsmpl_vert,                                      */
/*         int            dnsmpl_horz,                                      */
/*         int            rnd_shift                                         */
/*      );                                                                  */
/*                                                                          */
/*                                                                          */
/*     *in         :  Pointer to an input array of "type_input".            */
/*     *f          :  Pointer to cofficient array of type 'type_coef'.      */
/*     *out        :  Pointer to output array of "type_output".             */
/*     w_input     :  Width of the input image in pixels.                   */
/*     w_coeff     :  Width of the coefficients in pixels.                  */
/*     h_coeff     :  Height of the coefficients in pixels.                 */
/*     w_compute   :  Compute width in pixels.                              */
/*     h_compute   :  Compute height in pixels.                             */
/*     dnsmpl_vert :  Vertical downsampling value.                          */
/*     dnsmpl_horz :  Horizontal downsampling value.                        */
/*     rnd_shift   :  Rounding and shifting amount.                         */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the FIR filter result over a block of the image. Horizontal */
/*     and vertical downsampling are supported.                             */
/*                                                                          */
/*                                                                          */
/*     ASSUMPTION                                                           */
/*     --This code assumes that 'w_compute' >= 'w_coeff' and                */
/*     'h_compute' >= 'h_coeff'.                                            */
/*     --This code assumes that 'w_compute' <= 'w_input' and                */
/*     'h_compute' <= 'h_input'.                                            */
/*     --This code assumes that 'w_compute' <= 'w_out' and                  */
/*     'h_compute' <= 'h_out'.                                              */
/*     --VERTICAL downsampling is applied in this loop, but HORIZONTAL      */
/*     downsampling is carried out on the ARP32.                            */
/*                                                                          */
/*     CYCLES/PERFORMANCE                                                   */
/*                                                                          */
/*     (w_coeff * h_coeff ) / VCOP_SIMD_WIDTH                               */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_COEF      sizeof(*coef)
#define VECTORSZ_COEF    (VCOP_SIMD_WIDTH * ELEMSZ_COEF)

#define ELEMSZ_OUT       sizeof(*res)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define SAT_LO_UCHAR          (0)
#define SAT_HI_UCHAR          (255)
#define SAT_LO_CHAR           (-128)
#define SAT_HI_CHAR           (127)
#define SAT_LO_SHORT          (-32768)
#define SAT_HI_SHORT          (32767)

void vcop_filter_uchar_char_uchar
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_uint8   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_UCHAR, SAT_HI_UCHAR);
         }

     }
}


void vcop_filter_uchar_char_char
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int8    res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            //outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_CHAR, SAT_HI_CHAR);
         }

     }
}

void vcop_filter_uchar_char_short
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}


void vcop_filter_ushort_short_short
(
    __vptr_uint16   in,          // Pointer to an input array of "type_input".
    __vptr_int16   coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}


void vcop_filter_short_short_short
(
    __vptr_int16   in,           // Pointer to an input array of "type_input".
    __vptr_int16   coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}

void vcop_filter_ushort_ushort_short
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".
    __vptr_uint16  coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}

void vcop_filter_ushort_short_int
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".
    __vptr_int16   coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int32   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift);
         }

     }
}
/*-----------------------------------------------------------------*/
/* End of file : vcop_filter_kernel.k                              */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                       */
/*=================================================================*/
