/*=========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                             */
/*                                                                         */
/*     NAME                                                                */
/*         vcop_median_filt_col, median filter for the VICP library.       */
/*                                                                         */
/*                                                                         */
/*     USAGE                                                               */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void vcop_median_3tap_filt_col_cn                                   */ 
/*     (                                                                   */
/*         signed short *input_ptr,	                                       */
/*         signed short *output_ptr,	                                   */
/*         signed short input_width,	                                   */
/*         signed short input_height,                                      */
/*         signed short output_width,                                      */
/*         signed short output_height,                                     */
/*         signed short compute_width,                                     */
/*         signed short compute_height,                                    */
/*         signed short median_size,	                                   */
/*         signed short input_type,	                                       */
/*         signed short output_type	                                       */
/*     );                                                                  */
/*                                                                         */
/*                                                                         */
/*     void vcop_median_5tap_filt_col_cn                                   */ 
/*     (                                                                   */
/*         signed short *input_ptr,	                                       */
/*         signed short *output_ptr,	                                   */
/*         signed short input_width,	                                   */
/*         signed short input_height,                                      */
/*         signed short output_width,                                      */
/*         signed short output_height,                                     */
/*         signed short compute_width,                                     */
/*         signed short compute_height,                                    */
/*         signed short median_size,	                                   */
/*         signed short input_type,	                                       */
/*         signed short output_type	                                       */
/*     );                                                                  */
/*                                                                         */
/*     *input_ptr	 :  Pointer to an input array of "type_input"          */
/*     *output_ptr	 :  Pointer to output array of "type_output"           */
/*     input_width	 :  Input width size                                   */
/*     input_height  :  Input height size                                  */
/*     output_width  :  Output width size                                  */
/*     output_height :  Output height size                                 */
/*     compute_width :  The compute width over which median is computed    */
/*     compute_height:  The compute height for median filter               */
/*     median_size	 :  Indicates 3-tap or 5-tap filter                    */
/*     input_type	 :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT         */
/*     output_type	 :  0 - BYTE,  1 - SHORT                               */
/*                                                                         */
/*     Returns       :  None or void.                                      */
/*                                                                         */
/*     DESCRIPTION                                                         */
/*             This routine accepts pointers to a input region "in", and   */
/*     computes the median on a 3-tap or 5-tap col block of the image.     */
/*                                                                         */
/*     PERFORMANCE                                                         */
/*             This performance numbers for this function are as follows:  */
/*     3-tap filter:                                                       */
/*             3/16 cyc/pix                                                */
/*     5-tap filter:                                                       */
/*             9/16 cyc/pix                                                */
/*                                                                         */
/*                                                                         */
/*=========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.            */
/*                      All Rights Reserved                                */
/*=========================================================================*/


#define ELEMSZ_IN      sizeof(*input_ptr)
#define VECTORSZ_IN    (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT     sizeof(*output_ptr)
#define VECTORSZ_OUT   (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

/*-----------------------------------------------------------------------*/
/* Median col-wise filter with 3 taps.                                   */
/* This routine takes 3/16 VCOP cycles per pixel and is lD-ST bound.     */
/*-----------------------------------------------------------------------*/

void vcop_median_3tap_filt_col_short
(
    __vptr_int16 input_ptr,	        /* starting address of input */                           
    __vptr_int16 output_ptr,        /* starting address of output */
    signed short input_width,	    /* height of input array */
    signed short input_height,      /* width of input array */
    signed short output_width,      /* height of output array */
    signed short output_height,     /* width of output array */
    signed short compute_width,     /* height of compute block */
    signed short compute_height,    /* width of compute block */
    signed short median_size,	    /* 3 or 5-tap median filter */
    signed short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    signed short output_type	    /* 0 - BYTE,  1 - SHORT */
)
{
    __vector low_e, mid_e, high_e;
    __vector low_o, mid_o, high_o;
    
    /*---------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive cols are     */
    /* re ordered as min, med and max cols. Thus, the output of this loop  */
    /* has a height of 3x that of the input array.                         */
    /*---------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < compute_height; I1++) 
    {
       for (int I2 = 0; I2 <  compute_width/(2 * VCOP_SIMD_WIDTH); I2++ ) 
       {            
           __agen dataAddr0;

           dataAddr0 =  (I2 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN) +
                        (I1 * input_width * ELEMSZ_IN);

          /*--------------------------------------------------------------*/
          /* Read in the latest column.                                   */
          /*--------------------------------------------------------------*/

          (low_e, low_o)   = input_ptr[dataAddr0].deinterleave();  
          (mid_e, mid_o)   = (input_ptr + (1 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();
          (high_e, high_o) = (input_ptr + (2 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();
          
          /*--------------------------------------------------------------*/
          /* First level of sorting.                                      */
          /*--------------------------------------------------------------*/

          (mid_e, high_e).minmax();       
          (mid_o, high_o).minmax();       
          
          (low_e, high_e).minmax();
          (low_o, high_o).minmax();
          
          (low_e, mid_e).minmax();
          (low_o, mid_o).minmax();
           
          output_ptr[dataAddr0].interleave() = (mid_e, mid_o);
       }
   }
}

/*-------------------------------------------------------------------------*/
/* Median col-wise filter with 5 taps.                                     */
/* This routine takes 9/16 VCOP cycles per pixel and is computations       */
/* bound.                                                                  */
/*-------------------------------------------------------------------------*/

void vcop_median_5tap_filt_col_short
(
    __vptr_int16 input_ptr,	        /* starting address of input */                           
    __vptr_int16 output_ptr,        /* starting address of output */
    signed short input_width,	    /* height of input array */
    signed short input_height,      /* width of input array */
    signed short output_width,      /* height of output array */
    signed short output_height,     /* width of output array */
    signed short compute_width,     /* height of compute block */
    signed short compute_height,    /* width of compute block */
    signed short median_size,	    /* 3 or 5-tap median filter */
    signed short input_type,	    /* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    signed short output_type	    /* 0 - BYTE,  1 - SHORT */
)
{

    __vector data0_e, data1_e, data2_e, data3_e, data4_e;
    __vector data0_o, data1_o, data2_o, data3_o, data4_o;
    
    /*---------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive cols are     */
    /* re ordered as min, med and max cols. Thus, the output of this loop  */
    /* has a height of 3x that of the input array.                         */
    /*---------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < compute_height; I1++) 
    {       
       for (int I2 = 0; I2 <  compute_width/(2 * VCOP_SIMD_WIDTH); I2++ ) 
       {            
           __agen dataAddr0;

           dataAddr0 = (I2 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT) +
                       (I1 * input_width * ELEMSZ_OUT);

          /*--------------------------------------------------------------*/
          /* Read in the latest column.                                   */
          /*--------------------------------------------------------------*/

          (data4_e, data4_o) =  (input_ptr + (0 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();  
          (data3_e, data3_o) =  (input_ptr + (1 * input_width * ELEMSZ_IN))[dataAddr0].deinterleave();  
          (data2_e, data2_o) =  (input_ptr + (2 * input_width  * ELEMSZ_IN))[dataAddr0].deinterleave();  
          (data1_e, data1_o) =  (input_ptr + (3 * input_width  * ELEMSZ_IN))[dataAddr0].deinterleave();  
          (data0_e, data0_o) =  (input_ptr + (4 * input_width  * ELEMSZ_IN))[dataAddr0].deinterleave();  

          /*--------------------------------------------------------------*/
          /* First level of sorting.                                      */
          /*--------------------------------------------------------------*/
          
          (data0_e, data1_e).minmax();
          (data0_o, data1_o).minmax();
          
          (data1_e, data2_e).minmax();
          (data1_o, data2_o).minmax();
          
          (data2_e, data3_e).minmax();
          (data2_o, data3_o).minmax();
          
          (data3_e, data4_e).minmax();
          (data3_o, data4_o).minmax();

          /*--------------------------------------------------------------*/
          /* Second level of sorting.                                     */
          /*--------------------------------------------------------------*/

          (data0_e, data1_e).minmax();
          (data0_o, data1_o).minmax();

          (data1_e, data2_e).minmax();
          (data1_o, data2_o).minmax();
          
          (data2_e, data3_e).minmax();
          (data2_o, data3_o).minmax();
                       
          /*--------------------------------------------------------------*/
          /* Third level of sorting.                                      */
          /*--------------------------------------------------------------*/
          
          (data0_e, data1_e).minmax();
          (data0_o, data1_o).minmax();

          (data1_e, data2_e).minmax();
          (data1_o, data2_o).minmax();

           output_ptr[dataAddr0].interleave() = (data2_e, data2_o);
       }
   }
}
