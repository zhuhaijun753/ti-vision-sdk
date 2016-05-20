/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nonMaxSuppress_mxn_32s_cn                                       */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This is the c-reference for the vcop_nonMaxSuppress_mxn_32s  */
/*     kernel. This routine accepts an 32-bit input image and outputs non-  */
/*     maxima suppressed image using a mxn window.                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nonMaxSuppress_mxn_32s_cn                                  */
/*     (                                                                    */
/*         unsigned int   im [],                                            */
/*         unsigned char  out[],                                            */
/*         int            height,                                           */
/*         int            width,                                            */
/*         int            m,                                                */
/*         int            n,                                                */
/*         int            thresh                                            */
/*     )                                                                    */
/*                                                                          */
/*     im         :  32-bit input image                                     */
/*     out        :  8-bit binary output image                              */
/*     height     :  Height of the input image                              */
/*     width      :  Width of the input image                               */
/*     m          :  Height of the NMS window                               */
/*     n          :  Width of the NMS window                                */
/*     thresh     :  Threshold for pruning peaks                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*==========================================================================*/

void vcop_nonMaxSuppress_mxn_32s_cn
(
    int   im[],
    unsigned char  out[],
    int            width,
    int            height,
    int            input_stride,
    int            output_stride,
    int            m,
    int            n,
    int            thresh
)
{
    int x, y, i, j, k, l, o;
    int start_x, start_y;

    start_x = (n - 1)/2;
    start_y = (m - 1)/2;

    for (y = start_y; y <= height-m+start_y; y++)
    {
        for (x = start_x; x <= width-n+start_x; x++)
        {
            int v = 0;
            int max = 0;
            i = (y * input_stride) + x;
            v = im[i];
            for (l = (y - start_y); l < (y + m - start_y); l++)
            {
                for (k = (x - start_x); k < (x + n - start_x); k++)
                {
                    j = (l * input_stride) + k;
                    if (max < im[j])
                        max = im[j];
                }
            }
            o = ((y-start_y) * output_stride) + (x-start_x); // Output starts from upper left corner
            if (v == max && v > thresh)
                out[o] = 255;
            else
                out[o] = 0;
        }
    }
}


void vcop_nonMaxSuppress_mxn_32s_bitPack_cn
(
    int im[],
    unsigned char  out[],
    unsigned short width,
    unsigned short height,
    unsigned short inputStride,
    unsigned short outputSrtide,
    int            windowWidth,
    int            windowHeight,
    int            thresh
)
{
    int x, y, i, j, k, l;
    int start_x, start_y;
    unsigned char bitMask = 0;
    int bitCount = 0;

    start_x = (windowWidth - 1)/2;
    start_y = (windowHeight - 1)/2;

    for (y = start_y; y <= height-windowHeight+start_y; y++)
    {
        for (x = start_x; x <= width-windowWidth+start_x; x++)
        {
            int v = 0;
            int max = 0;
            i = (y * inputStride) + x;
            v = im[i];
            for (l = (y - start_y); l < (y + windowHeight - start_y); l++)
            {
                for (k = (x - start_x); k < (x + windowWidth - start_x); k++)
                {
                    j = (l * inputStride) + k;
                    if (max < im[j])
                        max = im[j];
                }
            }

            if (v == max && v > thresh)
            {
              bitMask = (bitMask >> 0x1U) | 0x80U;
            }
            else
            {
               bitMask = (bitMask >> 0x1U);
            }

            bitCount++;
            if ( x == (width-windowWidth+start_x) )
            {
              bitMask = (bitMask >> (8 - bitCount ));
              bitCount = 8;
            }
            if ( bitCount % 8  == 0)
            {
              out[ (x - start_x)/8  + ( (y - start_y) * outputSrtide)] = bitMask;
              bitCount = 0;
              bitMask = 0;
            }
        }
    }
}

