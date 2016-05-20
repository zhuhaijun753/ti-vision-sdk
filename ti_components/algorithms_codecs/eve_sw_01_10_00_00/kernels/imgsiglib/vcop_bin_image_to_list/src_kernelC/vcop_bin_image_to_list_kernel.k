/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/* NAME:                                                                    */
/*     vcop_bin_image_to_list_kernel                                        */
/*                                                                          */
/* USAGE:                                                                   */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bin_image_to_list                                          */
/*     (                                                                    */
/*         __vptr_uint8   im_A,                                             */
/*         __vptr_uint32  upperLeftXY,                                      */
/*         __vptr_uint16  outXY_B,                                          */
/*         __vptr_uint32  listSize,                                         */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short inputStride,                                      */
/*         __vptr_uint8   xSequence_C                                       */
/*     )                                                                    */
/*                                                                          */
/*     im_A          :  8-bit binary input image. This buffer should        */
/*                      contain height*stride/8 bytes. The exact format of  */
/*                      the binary bit mask in image is as shown below:     */
/*                      Pix7  Pix6  Pix5  ... Pix0  Pix15 Pix14 ... Pix8    */
/*                      Pix23 Pix22 Pix21 ... Pix16 ...                     */
/*     upperLeftXY   :  (X, Y) co-ordinate of the top-left pixel.           */
/*                      X co-ordinate is expected in the upper 16-bits and  */
/*                      the Y co-ordinate is expected in the lower 16-bits. */
/*     outXY_B       :  32-bit (X, Y) co-ordinate list of locations of      */
/*                      non-zero entries in im_A. Here lower 16-bits        */
/*                      contain Y co-ordinate and upper 16-bits contain     */
/*                      the X co-oridinate. The buffer should be of size    */
/*                      equal to 'width*height' words to accomodate worst   */
/*                      case scenario where all pixels are 1's.             */
/*     width         :  Width of the input image. Good to be a multiple of  */
/*                      8. In case width is not a multiple of 8 the stride  */
/*                      should be atleast aligned to next mutiple of 8 and  */
/*                      the image should be all zeros in the padded region. */
/*     height        :  Height of the input image.                          */
/*     inputStride   :  Input image stride. Should be a multiple of 8.      */
/*     xSequence_C   :  Point to the following pre-generated sequence of    */
/*                      numbers: 0, 1, 2, ..., width-1.                     */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*             This routine accepts an 8-bit input image and outputs a      */
/*     list of (X, Y) locations of non-zeros pixels in the image.           */
/*     The recomended memory bank for each of the buffers is captured as    */
/*     A/B/C as part of the buffer pointer. A/B/C can either be IMBUF High, */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/* PERFORMANCE MEASUREMENT:                                                 */
/*     0.377 cycles/pix + 93 cycle VCOP overhead                            */
/*                                                                          */
/* VERSION:                                                                 */
/*            1.0 (Nov 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/
#if VCOP_HOST_EMULATION

#include <vcop.h>
#endif

#define IMG_ELEMSZ     (sizeof(*im_A))
#define LIST_ELEMSZ    (sizeof(*listSize))
#define IMG_VECTORSZ   (1)
#define SEQ_VECTORSZ   (VCOP_SIMD_WIDTH*sizeof(*xSequence_C))

void vcop_bin_image_to_list
(
    __vptr_uint8   im_A,
    __vptr_uint32  upperLeftXY,   /* AL: point to the (X, Y) coordinate of the upper left pixel in the block being processed, these are updated by ARP32 */
    __vptr_uint32  outXY_B,
    __vptr_uint32  listSize,
    unsigned short width,
    unsigned short height,
    unsigned short inputStride,
    unsigned char  outputQformat,
    __vptr_uint32  xSequence_C    /* WMEM: point to the following pre-generated sequence of numbers: 0, 1, 2, ..., width-1 */
)
{
    __vector upLeftXY, numEntries, XYIncr;
    __vector VoutQformat;
    __vector xyOffset, XYIncrQFormat;
    __agen Addr0;
    Addr0 = 0;
    numEntries = 0;

    /* Read the (X, Y) coordinate of the upper left pixel in the block being processed, these are updated by ARP32 */
    upLeftXY = upperLeftXY[Addr0].onept();
    XYIncr = height;
    VoutQformat = outputQformat;

    /* This loop produces the list of coordinates (X, Y) corresponding to non-zeros pixels in the input binary image.
     * Iterates height*ceil(width/8) times.
     * */

    for(int k = 0; k < 1; k++)
    {
        __vector K0, K1;
        K0 = 0;
        K1 = 1;

        for (int i = 0; i < height; i++)                                        /* This loop iterates height*ceil(width/8) times */
        {
            for (int j = 0; j < (width+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; j++)     /* This loop iterates ceil(width/8) times */
            {
                __agen Addr1, Addr2;
                __vector xseq, I, mask, y, xy;

                Addr1 = j*SEQ_VECTORSZ;
                Addr2 = i*(inputStride/8)*IMG_ELEMSZ + j*IMG_VECTORSZ;

                /* Initialize y to the current row counter 'i' */
                y = i;

                /* Read the X coordinate of sequence 0, 1, 2, 3, ..., width -1 */
                xseq = xSequence_C[Addr1];

                /* Read the input image mask of 0 or 1 */
                I = im_A[Addr2].onept();

                /* Unpack the input binary image */
                mask = unpack(I, K1);                    /* 1 cycle to execute + 1 delay slot */
                xy = y << VoutQformat;

                /* Calculate (X, Y) coordinates */
                xy += xseq + upLeftXY;

                numEntries += mask;                      /* 1 cycle to execute */

                outXY_B[collate(mask)] = xy;
            }
        }
        listSize[Addr0] = numEntries;
    }

    for(int i = 0; i < 1; i++)
    {
        __vector updatedXY;

        for(int j = 0; j < 7; j++)
        {
            __agen Addr1;
            __vector sz;

            Addr1 = j*LIST_ELEMSZ;

            sz = (listSize + LIST_ELEMSZ)[Addr1].onept();

            XYIncrQFormat  = XYIncr << VoutQformat;

            numEntries += sz;
            xyOffset = upLeftXY + XYIncrQFormat ;
        }
        listSize[Addr0].onept() = numEntries;
        upperLeftXY[Addr0].onept() = xyOffset;
    }
}

