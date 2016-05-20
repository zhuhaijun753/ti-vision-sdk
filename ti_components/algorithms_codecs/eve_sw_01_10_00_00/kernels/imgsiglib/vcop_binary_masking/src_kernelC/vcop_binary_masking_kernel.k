/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define   VCOP_2SIMD_WIDTH   (2 * VCOP_SIMD_WIDTH)
#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))
#define ALIGN_SIMD(a)   (((a) + VCOP_SIMD_WIDTH-1) & ~(VCOP_SIMD_WIDTH-1))

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_binary_masking
 *
 *  @desc     This kernel does the "AND" operation on a byte mask containing 0 and 1 with
 *                a bit packed mask binary image
 *
 *  @inputs   This kernel takes following Inputs
 *                  inByteData :
 *                          Input byte data containing only 0 and 1
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  inBitPackedData :
 *                          Input bit data containing bit packed data
 *                          Size of this buffer should be blockWidth /8 * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel.
 *                  computeHeight :
 *                          Width of the output of this kernel.
 *                  inputByteDataPitch :
 *                          Pitch in bytes for the byte data
 *                  inputBitDataPitch :
 *                          Pitch in bytes for the bit packed data
 *                  outputPitch :
 *                          Pitch of the output data
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                  outBitPackedData
 *                          Pointer to the output buffer containing the output of this kernel in bit packed data
 *                          Size of this buffer should be ( (computeWidth) / 8 * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_binary_masking
(
     __vptr_uint8  inByteData,
     __vptr_uint8  inBitPackedData,
     __vptr_uint8  outBitPackedData,
     unsigned short computeWidth,
     unsigned short computeHeight,
     unsigned short inputByteDataPitch,
     unsigned short inputBitDataPitch,
     unsigned short outputPitch
)
{
    __vector VByteData;
    __vector VBitData;
    __vector VPackedData;
    __vector VOutData;
    __vector Vk1;


    for (int I1 = 0; I1 < computeHeight; I1++)
    {
        for ( int I2 = 0; I2 < ALIGN_SIMD(computeWidth)/VCOP_SIMD_WIDTH; I2++)
        {
            __agen byteDataAddr;
            __agen bitDataAddr;
            __agen outAddr;

            Vk1 = 1;

            byteDataAddr = (I1 * inputByteDataPitch * sizeof(*inByteData)) + (I2 * VCOP_SIMD_WIDTH * sizeof(*inByteData));
            bitDataAddr  = (I1 * inputBitDataPitch  * sizeof(*inBitPackedData)) + (I2 * sizeof(*inBitPackedData));
            outAddr     =  (I1 * outputPitch * sizeof(*outBitPackedData)) + (I2 * sizeof(*outBitPackedData));

            VByteData = inByteData[byteDataAddr].npt();
            VBitData  = inBitPackedData[bitDataAddr].onept();

            VPackedData = pack(VByteData >= Vk1);

            VOutData = VPackedData & VBitData;

            outBitPackedData[outAddr].onept() = VOutData;
        }
    }


}



