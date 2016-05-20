/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/* NAME:                                                                    */
/*    vcop_intensity_scaling                                                */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*             The routine accepts a gray-scale input image (inImg) and     */
/*     bins the input gray-scale pixels into bins as specified by           */
/*     'scalingLUT'. The output at 'outImg' is of size blockHeight by       */
/*     blockWidth.                                                          */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF Low, IMBUF  */
/*     High or WMEM.                                                        */
/*                                                                          */
/* USAGE:                                                                   */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_intensity_scaling                                           */
/*    (                                                                     */
/*        __vptr_uint8       inImg_A,                                       */
/*        __vptr_uint8       scalingLUT_C,                                  */
/*        __vptr_uint8       outImg_B,                                      */
/*        unsigned short     blockWidth,                                    */
/*        unsigned short     blockHeight,                                   */
/*        unsigned short     blockStride                                    */
/*    )                                                                     */
/*                                                                          */
/*    inImg_A         : 8-bit grayscale image block. This buffer should     */
/*                      contain atleast blockHeight*blockStride bytes.      */
/*    scalingLUT_C    : Pointer to look-up table for performing intensity   */
/*                      scaling.                                            */
/*    outImg_B        : Pointer to intensity scaled output image.           */
/*    blockWidth      : Width of the input image block.                     */
/*    blockHeight     : Height of the input image block.                    */
/*    blockStride     : Stride of the input image block.                    */
/*                                                                          */
/*    Returns    :  None or void.                                           */
/*                                                                          */
/* PERFORMANCE MEASUREMENT:                                                 */
/*    0.125 cycles/pix + 54 VCOP cycles overhead.                           */
/*                                                                          */
/* VERSION:                                                                 */
/*    1.0 (Jan 2014) : Base version.                                        */
/*                                                                          */
/*==========================================================================*/

#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define NUM_TBLS        (8)
#define NUM_PTS_TLU     (1)

#define IND_ELEMSZ (sizeof(*inImg_A))
#define IND_VECTORSZ (IND_ELEMSZ * NUM_TBLS)
#define IND_ROWSZ (blockStride*IND_ELEMSZ)

#define OUT_ELEMSZ (sizeof(*outImg_B))
#define OUT_VECTORSZ (OUT_ELEMSZ * NUM_TBLS)
#define OUT_ROWSZ (blockWidth *OUT_ELEMSZ)

void vcop_intensity_scaling
(
    __vptr_uint8       inImg_A,
    __vptr_uint8       scalingLUT_C,
    __vptr_uint8       outImg_B,
    unsigned short     blockWidth,
    unsigned short     blockHeight,
    unsigned short     blockStride
)
{
  __vector Vin, Vscaledpix;

  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

  for (int I1 = 0; I1 < blockHeight; I1++)
  {
    for (int I2 = 0; I2 < (blockWidth + NUM_TBLS - 1)/NUM_TBLS; I2++)
    {
      __agen table_addr = 0;
      __agen index_addr = I2 * IND_VECTORSZ + I1 * IND_ROWSZ;
      __agen out_addr = I2 * OUT_VECTORSZ + I1 * OUT_ROWSZ;

      Vin = inImg_A[index_addr];

      Vscaledpix = scalingLUT_C[table_addr].lookup(Vin);

      outImg_B[out_addr].table_npt() = Vscaledpix;
    }
  }
}

