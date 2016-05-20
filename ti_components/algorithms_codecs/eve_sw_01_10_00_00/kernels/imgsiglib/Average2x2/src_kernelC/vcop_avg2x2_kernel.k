/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_avg2x2, avg2x2 filter for the VICP library.                 */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_avg2x2                                                     */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *scratch1,                                        */
/*          signed char   *out,                                             */
/*          int           w_input,                                          */
/*          int           w_out,                                            */                  
/*          int           blk_w,                                            */
/*          int           blk_h,                                            */
/*          int           shift,                                            */
/*          int           type_input,                                       */
/*          int           type_output                                       */
/*     );                                                                   */
/*                                                                          */
/*                                                                          */
/*     *in        :  Pointer to an input array of "type_input".             */
/*     *scratch1  :  Pointer to intermediate array.                         */
/*     *out       :  Pointer to output array of "type_output".              */
/*     w_input    :  Width of the input image in pixels.                    */
/*     w_out     :  Width of the compute block in pixels.                   */
/*     blk_w      :  The block width for computing the average.             */
/*     blk_h      :  The compute height for computing average.              */
/*     shift      :  The no. of elements in the block, to compute average.  */
/*     type_input :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT             */
/*     type_output:  0 - BYTE,  1 - SHORT                                   */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*    VARIANTS                                                              */
/*    There are four versions of the function based on the type of the      */
/*    input data. They are:                                                 */
/*    vcop_avg2x2_uchar()                                                   */
/*    vcop_avg2x2_char()                                                    */
/*    vcop_avg2x2_ushort()                                                  */
/*    vcop_avg2x2_short()                                                   */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*    - block_width <= image_width and block_height <= image_height.        */
/*    - block_width must be a multiple of 16.                               */
/*                                                                          */
/*     PERFORMANCE/CYCLES                                                   */
/*     3/16 cyc/pix                                                         */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_INTER     sizeof(*inter)
#define VECTORSZ_INTER   (VCOP_SIMD_WIDTH * ELEMSZ_INTER)

#define ELEMSZ_OUT       sizeof(*result)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define TRANSPOSE_WIDTH  8
#define WORD_SIZE        4

/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_uchar
(
    __vptr_uint8  in,                  //  Pointer to an input array of "type_input".            
    __vptr_int16 result,               //  Pointer to output array of "type_output".             
    int          w_input,              //  Width of the input image in pixels.                   
    int          w_out,                //  Width of the compute block in pixels.                   
    int          w_blk,                //  The compute width over which avg2x2 values are found. 
    int          h_blk,                //  The compute height for avg2x2 filter.                 
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging                  
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            
    int          type_output           //  0 - BYTE,  1 - SHORT                                            
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;
        
        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2; 

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}


/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_char
(
    __vptr_int8  in,                   //  Pointer to an input array of "type_input".            
    __vptr_int16 result,               //  Pointer to output array of "type_output".             
    int          w_input,              //  Width of the input image in pixels.                   
    int          w_out,                //  Width of the compute block in pixels.                   
    int          w_blk,                //  The compute width over which avg2x2 values are found. 
    int          h_blk,                //  The compute height for avg2x2 filter.                 
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging                  
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            
    int          type_output           //  0 - BYTE,  1 - SHORT                                            
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;
        
        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2; 

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}


/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_ushort
(
    __vptr_uint16  in,                 //  Pointer to an input array of "type_input".            
    __vptr_int16 result,               //  Pointer to output array of "type_output".             
    int          w_input,              //  Width of the input image in pixels.                   
    int          w_out,                //  Width of the compute block in pixels.                   
    int          w_blk,                //  The compute width over which avg2x2 values are found. 
    int          h_blk,                //  The compute height for avg2x2 filter.                 
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging                  
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            
    int          type_output           //  0 - BYTE,  1 - SHORT                                            
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;
        
        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2; 

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}

/*--------------------------------------------------------------------------*/
/*     The avg2x2 code computes the average over a block of size 2x2.       */
/*     This block can be located at any offset within an image. The         */
/*     starting address of the block is passed the kernel from the calling  */
/*     function. Compute width is equal to 8. This value is the minimum     */
/*     SIMD width for gives the kernel useful information on loop           */
/*     iterations to compute the avg2x2.                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/

void vcop_avg2x2_short
(
    __vptr_int16  in,                  //  Pointer to an input array of "type_input".            
    __vptr_int16 result,               //  Pointer to output array of "type_output".             
    int          w_input,              //  Width of the input image in pixels.                   
    int          w_out,                //  Width of the compute block in pixels.                   
    int          w_blk,                //  The compute width over which avg2x2 values are found. 
    int          h_blk,                //  The compute height for avg2x2 filter.                 
    int          shift_val,            //  (blk_w * blk_h) amount to shift or divide for averaging                  
    int          type_input,           //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            
    int          type_output           //  0 - BYTE,  1 - SHORT                                            
)
{

    __vector Vprev0, Vprev1, Vin0, Vin1, Vin2, Vin3, Vout0, Vout1;

    /*-------------------------------------------------------------------*/
    /* This is the first loop where we add the rows of the block from    */
    /* top to bottom and write the final 'summed' row as a column.       */
    /* cycle count for this loop = (h_blk * w_blk)/VCOP_SIMD_WIDTH       */
    /* y0 = x0 + x1, y2 = x2 + x3; y4 = x4 + x5 ...                      */
    /* y1 = x1 + x2, y3 = x3 + x4; y5 = x5 + x6 ...                      */
    /*-------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < w_out/(2 * VCOP_SIMD_WIDTH); I1++)
    {
        Vprev0 = 0;
        Vprev1 = 0;
        
        for ( int I2 = 0; I2 < h_blk; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  = I2 * w_input * ELEMSZ_IN + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
            outAddr = I2 * w_out * ELEMSZ_OUT + I1 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;

            (Vin0, Vin1)  =  in[inAddr].deinterleave();
            (Vin2, Vin3)  =  (in + (2 * ELEMSZ_IN))[inAddr].deinterleave();

            Vout0 = Vin0 + Vin1;
            Vout1 = Vin1 + Vin2;

            Vout0 += Vprev0;
            Vout1 += Vprev1;

            Vprev0 = Vin0 + Vin1; //Overwrite prev for next iteration
            Vprev1 = Vin1 + Vin2; 

            result[outAddr].interleave() = (Vout0, Vout1).truncate(shift_val);
        }
    }
}

