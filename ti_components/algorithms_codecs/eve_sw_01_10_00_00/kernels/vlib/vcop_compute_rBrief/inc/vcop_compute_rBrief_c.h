/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME : rBrief : header file.                                         */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*
@param  *in_src_dst_x    Pointer to source and destination x location used for binary test

@param  *in_src_dst_y   Pointer to source and destination y location used for binary test

@param  *cos_out_ptr    Pointer to cos looked up value

@param  *sin_out_ptr     Pointer to sin looked up value

@param  *patch_sum        Pointer to 5x5 patch sum

@param  *orb_descriptor    Pointer to the Orb descriptor output
*/

#define MOMENTS_PATCH_SIZE (32)
#define PATCH_SIZE (48)

#define CORB_NUM_ORIENTATIONS 30
#define CORB_NUM_PATTERNS 256


void compute_Orb(unsigned char* pIn,
                      char* moment_col_mask,
                      char* moment_row_mask,
                      char* in_src_dst_x,
                      char* in_src_dst_y,
                      short *cos_ptr,
                      short* sin_ptr,
                      unsigned short* arc_thrx,
                      unsigned char* descriptor );


