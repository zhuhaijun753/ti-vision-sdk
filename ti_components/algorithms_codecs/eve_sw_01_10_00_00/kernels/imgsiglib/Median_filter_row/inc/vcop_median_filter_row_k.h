/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef __VCOP_MEDIAN_FILTER_ROW_K_H__

#define __VCOP_MEDIAN_FILTER_ROW_K_H__

void vcop_median_3tap_filt_row_char
(
    __vptr_int8 input_ptr,	/* starting address of input */
    __vptr_int8 output_ptr, /* starting address of output */
    unsigned short input_width,	    /* height of input array */
    unsigned short input_height,     /* width of input array */
    unsigned short output_width,     /* height of output array */
    unsigned short output_height,    /* width of output array */
    unsigned short compute_width,    /* height of compute block */
    unsigned short compute_height,   /* width of compute block */
    unsigned short median_size,	    /* 3 or 5-tap median filter */
    unsigned short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    unsigned short output_type	    /* 0 - BYTE,  1 - SHORT */
);

void vcop_median_3tap_filt_row_short
(
    __vptr_int16   input_ptr,	/* starting address of input */                           
    __vptr_int16   output_ptr,/* starting address of output */
    unsigned short input_width,	    /* height of input array */
    unsigned short input_height,     /* width of input array */
    unsigned short output_width,     /* height of output array */
    unsigned short output_height,    /* width of output array */
    unsigned short compute_width,    /* height of compute block */
    unsigned short compute_height,   /* width of compute block */
    unsigned short median_size,	    /* 3 or 5-tap median filter */
    unsigned short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    unsigned short output_type	    /* 0 - BYTE,  1 - SHORT */
);

void vcop_median_5tap_filt_row_char
(
    __vptr_int8 input_ptr,	/* starting address of input */
    __vptr_int8 output_ptr, /* starting address of output */
    unsigned short input_width,	    /* height of input array */
    unsigned short input_height,     /* width of input array */
    unsigned short output_width,     /* height of output array */
    unsigned short output_height,    /* width of output array */
    unsigned short compute_width,    /* height of compute block */
    unsigned short compute_height,   /* width of compute block */
    unsigned short median_size,	    /* 3 or 5-tap median filter */
    unsigned short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    unsigned short output_type	    /* 0 - BYTE,  1 - SHORT */
);


void vcop_median_5tap_filt_row_short
(
    __vptr_int16   input_ptr,	/* starting address of input */
    __vptr_int16   output_ptr,/* starting address of output */
    unsigned short input_width,	    /* height of input array */
    unsigned short input_height,     /* width of input array */
    unsigned short output_width,     /* height of output array */
    unsigned short output_height,    /* width of output array */
    unsigned short compute_width,    /* height of compute block */
    unsigned short compute_height,   /* width of compute block */
    unsigned short median_size,	    /* 3 or 5-tap median filter */
    unsigned short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    unsigned short output_type	    /* 0 - BYTE,  1 - SHORT */
);


#endif
