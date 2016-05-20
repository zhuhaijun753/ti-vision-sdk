/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
void filter_cn
(
    unsigned short *in,          // Pointer to an input array of "type_input".
    unsigned short *f,           // Pointer to cofficient array of type 'type_coef'.
    unsigned short *out,         // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            w_out,        // Width of the output image in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            type_output,  // 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int            rnd_shift     // Rounding and shifting amount.
);


void filter_uchar_cn
(
    unsigned char *in,          // Pointer to an input array of "type_input".
    char          *f,           // Pointer to cofficient array of type 'type_coef'.
    unsigned char *out,         // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            w_out,        // Width of the output image in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            type_output,  // 0 - CHAR,  1 - SHORT, 2 - UCHAR
    int            rnd_shift     // Rounding and shifting amount.
);
