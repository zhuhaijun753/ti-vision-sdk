/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
void vcop_dct8x8row_cn
(
    short *in, 
    short *f, 
    short *out,
    int w_input, 
    int h_input, 
    int w_out,
    int h_out,
    int calc_HBLKS,
    int calc_VBLKS,
    int type_input,
    int type_coeff,
    int type_output,
    int rnd_shift 
);
