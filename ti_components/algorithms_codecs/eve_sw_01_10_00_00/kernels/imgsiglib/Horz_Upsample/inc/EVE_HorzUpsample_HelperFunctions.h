/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         Helper functions definitions used in the polyphase filter kernel.*/
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef __VCOP_FILTER_POLY_HELPERFUNCS_H__
#define __VCOP_FILTER_POLY_HELPERFUNCS_H__

short GenResamplingCoeffs
(
    int   U,                 // Up sampling value
    int   D,                 // Down sampling value
    int   taps,              // original number of taps 
    short *coeffs,
    unsigned char *sampling_pattern,
    int   *pattern_size
);

void print_output();

int  verify_output();

void write_pgm_file
(
   int up_SAMPLE, 
   int down_SAMPLE, 
   int NUM_TAPS
);

#endif
