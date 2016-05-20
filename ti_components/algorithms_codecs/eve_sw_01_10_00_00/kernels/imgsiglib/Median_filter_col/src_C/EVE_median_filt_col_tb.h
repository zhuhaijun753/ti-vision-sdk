/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
void vcop_median_filt_col_cn
(
    Int16 *input_ptr,		/* starting address of input */
    Int16 *output_ptr,		/* starting address of output */
    Int16 input_width,	    /* height of input array */
    Int16 input_height,     /* width of input array */
    Int16 output_width,    	/* height of output array */
    Int16 output_height,    /* width of output array */
    Int16 compute_width,   	/* height of compute block */
    Int16 compute_height,   /* width of compute block */
    Int16 median_size,		/* 3 or 5-tap median filter */
    Int16 input_type,		/* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    Int16 output_type		/* 0 - BYTE,  1 - SHORT */
);
