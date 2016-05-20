/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_grayscale_morphology_c.c                                */
/*                                                                          */
/*     @brief : This file contains C reference implementation for grayscale */
/*     morphological processing with flat structuring elements (SE).        */
/*                                                                          */
/*     The following basic morphological operations are provided:           */
/*     1. vcop_grayscale_dilate_mask_cn                                     */
/*           Performs grayscale dilation of an 8-bit grayscale input image  */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     2. vcop_grayscale_erode_mask_cn                                      */
/*           Performs grayscale erosion of an 8-bit grayscale input image   */
/*           at data_ptr, of size blk_w by blk_h, with a flat structuring   */
/*           element of size se_w by se_h, specified with a mask of 1's     */
/*           and 0's at se_ptr. The output is written into output_ptr.      */
/*     3. vcop_grayscale_morp_diff_cn                                       */
/*           Performs image difference operation between two 8-bit gray-    */
/*           scale images at data_ptr and data2_ptr, both of size blk_w     */
/*           by blk_h, and writes the output into output_ptr. The function  */
/*           assumes that the image pixel values at data_ptr is greater     */
/*           than the corresponding pixel values at data2_ptr.              */
/*                                                                          */
/*     @author Anoop K P(a-kp@ti.com)                                       */
/*                                                                          */
/*     @version 1.0 (February 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

void vcop_grayscale_dilate_mask_cn
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    unsigned char         *data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    unsigned char         *se_ptr,       // structuring element data pointer
    unsigned char         *output_ptr    // output data pointer
)
{
    int i1, i2, i3, i4;
    unsigned int max_val;
    unsigned char in_data, se_data;

    for (i1 = 0; i1 < blk_h-se_h+1; i1++)
    {
        for (i2 = 0; i2 < blk_w-se_w+1; i2++)
        {
            max_val = 0;
            for (i3 = 0; i3 < se_h; i3++)
            {
                for (i4 = 0; i4 < se_w; i4++)
                {
                    in_data = data_ptr[(i1 * line_ofst) + i2 + (i3 * line_ofst) + i4];
                    se_data = se_ptr[(i3 * se_w) + i4];
                    if(se_data > 0)
                    {
                        max_val = (in_data > max_val)? in_data : max_val;
                    }
                }
            }
            output_ptr[i1 * line_ofst + i2] = max_val;
        }
    }
}

void vcop_grayscale_erode_mask_cn
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    unsigned char         *data_ptr,     // input data pointer
    unsigned short         se_w,         // width of structuring element block, in elements
    unsigned short         se_h,         // height of structuring element block
    unsigned char         *se_ptr,       // structuring element data pointer
    unsigned char         *output_ptr    // output data pointer
)
{
    int i1, i2, i3, i4;
    unsigned int min_val;
    unsigned char in_data, se_data;

    for (i1 = 0; i1 < blk_h-se_h+1; i1++)
    {
        for (i2 = 0; i2 < blk_w-se_w+1; i2++)
        {
            min_val = 255;
            for (i3 = 0; i3 < se_h; i3++)
            {
                for (i4 = 0; i4 < se_w; i4++)
                {
                    in_data = data_ptr[(i1 * line_ofst) + i2 + (i3 * line_ofst) + i4];
                    se_data = se_ptr[(i3 * se_w) + i4];
                    if(se_data > 0)
                    {
                        min_val = (in_data < min_val)? in_data : min_val;
                    }
                }
            }
            output_ptr[i1 * line_ofst + i2] = min_val;
        }
    }
}

void vcop_grayscale_morp_diff_cn
(
    unsigned short         blk_w,        // width of input block, in elements
    unsigned short         line_ofst,    // offset between input lines, in elements
    unsigned short         blk_h,        // height of input block
    unsigned char         *data_ptr,     // input 1 data pointer (data >= data2)
    unsigned char         *data2_ptr,    // input 2 data pointer
    unsigned char         *output_ptr    // output data pointer
)
{
    int i1, i2;

    for (i1 = 0; i1 < blk_h; i1++)
    {
        for (i2 = 0; i2 < blk_w; i2++)
        {
            output_ptr[(i1*line_ofst) + i2] = data_ptr[(i1*line_ofst) + i2] -
                data2_ptr[(i1*line_ofst) + i2];
        }
    }
}


/* Grayscale Mask Open */
void vcop_grayscale_open_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_C,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B)
{
    vcop_grayscale_erode_mask_cn(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_C, scratch_ptr_C);

    vcop_grayscale_dilate_mask_cn(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, refl_se_ptr_C, output_ptr_B);


}

/* Grayscale Mask Close */
void vcop_grayscale_close_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_C,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B)
{
    vcop_grayscale_dilate_mask_cn(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, refl_se_ptr_C, scratch_ptr_C);

    vcop_grayscale_erode_mask_cn(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr_C, se_w, se_h, se_ptr_C, output_ptr_B);

}

/* Grayscale Mask Tophat Operation */
void vcop_grayscale_tophat_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_C,
   unsigned char *refl_se_ptr_A,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B)
{
    vcop_grayscale_erode_mask_cn(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_C,
        output_ptr_B);

    vcop_grayscale_dilate_mask_cn(blk_w-(se_w-1), line_ofst, blk_h-(se_h-1),
        output_ptr_B, se_w, se_h, refl_se_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff_cn(blk_w-2*(se_w-1), line_ofst, blk_h-2*(se_h-1),
        data_ptr_A + (se_w-1)*line_ofst + (se_w-1), scratch_ptr_C, output_ptr_B);

}

/* Grayscale Mask Bottom hat Operation */
void vcop_grayscale_bottomhat_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_A,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr_C,
   unsigned char *output_ptr_B)
{
    vcop_grayscale_dilate_mask_cn(blk_w, line_ofst,
        blk_h, data_ptr_A, se_w, se_h, refl_se_ptr_C, output_ptr_B);

    vcop_grayscale_erode_mask_cn(blk_w-(se_w-1),
        line_ofst, blk_h-(se_h-1), output_ptr_B, se_w, se_h, se_ptr_A, scratch_ptr_C);

    vcop_grayscale_morp_diff_cn(blk_w-2*(se_w-1),
        line_ofst, blk_h-2*(se_h-1), scratch_ptr_C,
        (data_ptr_A + (se_w-1)*line_ofst + (se_w-1)), output_ptr_B);

}

/* Grayscale Mask Morphological Gradient */
void vcop_grayscale_morph_grad_mask_cn(
   unsigned short blk_w,
   unsigned short line_ofst,
   unsigned short blk_h,
   unsigned char *data_ptr_A,
   unsigned short se_w,
   unsigned short se_h,
   unsigned char *se_ptr_B,
   unsigned char *refl_se_ptr_C,
   unsigned char *scratch_ptr1_C,
   unsigned char *scratch_ptr2_A,
   unsigned char *output_ptr_B)
{
    vcop_grayscale_dilate_mask_cn(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, refl_se_ptr_C, scratch_ptr1_C);

    vcop_grayscale_erode_mask_cn(blk_w, line_ofst, blk_h,
        data_ptr_A, se_w, se_h, se_ptr_B, scratch_ptr2_A);

    vcop_grayscale_morp_diff_cn(blk_w-(se_w-1), line_ofst,
        blk_h-(se_h-1), scratch_ptr1_C, scratch_ptr2_A, output_ptr_B);

}

