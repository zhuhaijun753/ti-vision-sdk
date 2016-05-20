/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef REMAP_H

#define REMAP_H

#include <stdint.h>
#include "vcop.h"
#include "remap_common.h"

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef NATC
  #define NATC 0
#endif


#define MAX_NUM_PBLOCKS (6U)


typedef void (*VloopFunc)(uint16_t pblock[]);


/*!

  @struct VcopRemapContext

  @brief  This structure contains the kernel level parameters for Remap

  @param  numPblocks         number of param blocks, to each vloop is associated
                             a param block
  @param  pblockSize         Total size of all the param blocks together
  @param  *pblockMem         Pointer to the chunk of memory reserved to store the
                             param blocks, one after the other, to be allocated by caller
  @param  (*pblockRunningMem)[]  for internal use
  @param  *pblockList[MAX_NUM_PBLOCKS]       array of pointers to the pblocks
  @param  *vloopFuncList[MAX_NUM_PBLOCKS]    array of pointers to KernelFunc_vloops functions
  @param  *pblockUpdatePblockList[MAX_NUM_PBLOCKS]  array of pointers to the pblocks
                                            of pblock updation kernels
  @param  *pblockUpdateFuncList[MAX_NUM_PBLOCKS]    array of pointers to KernelFunc_vloops functions
                                            of pblock updation kernels
  @param  pBlockIdx          internal use

*/

typedef struct {
    uint16_t  numPblocks;
    uint16_t  pblockSize;
    uint16_t  *pblockMem;
    uint16_t (*pblockRunningMem)[];
    uint16_t  *pblockList[MAX_NUM_PBLOCKS];
    VloopFunc vloopFuncList[MAX_NUM_PBLOCKS];
    uint16_t  *pblockUpdatePblockList[MAX_NUM_PBLOCKS];
    VloopFunc pblockUpdateFuncList[MAX_NUM_PBLOCKS];
    int16_t   pBlockIdx;
} VcopRemapContext;

/*!

  @fn     vcop_remap_tile_approach_init

  @brief  This function is used to initialize the context structure, allocate
          input and output buffers in internal memory for the given source and
          destination formats
  @param  *blockInfoPtr              pointer to BlockInfo (LUT) in VCOP memory
  @param  *inputImagePtr           pointer to Input Image block in VCOP memory
  @param  *interpolationBuf0Ptr   pointer to Interpolation scratch block in VCOP memory
  @param  *interpolationBuf1Ptr   pointer to Interpolation scratch block in VCOP memory
  @param  *ChromaTLUIndexPtr  pointer to store Chroma LUT in VCOP memory
  @param  *scatteredOffsetPtr     pointer to Scattered Offset for 422 in VCOP memory
  @param  *lumaPtr                     pointer to store deinterleaved Luma for 422 in VCOP memory
  @param  *chromaUVPtr             pointer to store deinterleaved Chroma U and V for 422 in VCOP memory
  @param  *outputPtr                  pointer to output block in VCOP memory
  @param  *params                     pointer to remap parameters
  @param  *context                     pointer to context structure , will be filled by vcop_remap_init

*/
int32_t vcop_remap_tile_approach_init(
                    uint8_t blockInfoPtr[],
                    uint8_t inputImagePtr[],
                    uint8_t interpolationBuf0Ptr[],
                    uint8_t interpolationBuf1Ptr[],
                    uint8_t ChromaTLUIndexPtr[],
                    uint8_t scatteredOffsetPtr[],
                    uint8_t chromaUVPtr[],
                    uint8_t outputPtr[],
                    const RemapParms *params,
                    VcopRemapContext *context
);

/*!

  @fn     vcop_remap_tile_approach

  @brief  This function is used to invoke the processing of remap operation by
          VCOP processor. It invokes the various kernel vloops within the context
          structure
  @param  *context           pointer to VcopRemapContext structure

*/
int32_t vcop_remap_tile_approach(
        VcopRemapContext *context   /* pointer to context structure , will be filled by vcop_remap_init */
);


/*!

  @fn     vcop_remap_bb_approach_init

  @brief  This function is used to initialize the context structure, allocate
          input and output buffers in internal memory for the given source and
          destination formats
  @param  *blockInfoPtr              pointer to BlockInfo (LUT) in VCOP memory
  @param  *inputImagePtr           pointer to Input Image block in VCOP memory
  @param  *interpolationBuf0Ptr   pointer to Interpolation scratch block in VCOP memory
  @param  *interpolationBuf1Ptr   pointer to Interpolation scratch block in VCOP memory
  @param  *ChromaTLUIndexPtr  pointer to store Chroma LUT in VCOP memory
  @param  *scatteredOffsetPtr     pointer to Scattered Offset for 422 in VCOP memory
  @param  *lumaPtr                     pointer to store deinterleaved Luma for 422 in VCOP memory
  @param  *chromaUVPtr            pointer to store deinterleaved Chroma U and V for 422 in VCOP memory
  @param  *outputPtr                  pointer to output block in VCOP memory
  @param  *params                     pointer to remap parameters
  @param  *context                     pointer to context structure , will be filled by vcop_remap_init

*/
int32_t vcop_remap_bb_approach_init(
                    uint8_t blockInfoPtr[],
                    uint8_t inputImagePtr[],
                    uint8_t interpolationBuf0Ptr[],
                    uint8_t interpolationBuf1Ptr[],
                    uint8_t ChromaTLUIndexPtr[],
                    uint8_t scatteredOffsetPtr[],
                    uint8_t chromaUVPtr[],
                    uint8_t outputPtr[],
                    const RemapParms *params,
                    VcopRemapContext *context
);

/*!

  @fn     vcop_remap_bb_approach

  @brief  This function is used to invoke the processing of remap operation by
          VCOP processor. It invokes the various kernel vloops within the context
          structure
  @param  *context           pointer to VcopRemapContext structure

*/
int32_t vcop_remap_bb_approach(
        VcopRemapContext *context   /* pointer to context structure , will be filled by vcop_remap_init */
);

/*!

  @fn     vcop_remap_c

  @brief  This function is a natural C implementation of the remap functionality
          using the internal buffers of VCOP namely IBUF and WBUF
  @param  *blockInfoPtr              pointer to BlockInfo (LUT) in VCOP memory
  @param  *inputImagePtr           pointer to Input Image block in VCOP memory
  @param  *ChromaTLUIndexPtr  pointer to store Chroma LUT in VCOP memory
  @param  *outputPtr                  pointer to output block in VCOP memory
  @param  *params                     pointer to RemapParms structure

*/
int32_t vcop_remap_c(
                uint8_t *blockInfoPtr,      /* pointer to BlockInfo (LUT) in VCOP memory                           */
                uint8_t *inputImagePtr,     /* pointer to Input Image block in VCOP memory                       */
                uint8_t *ChromaTLUIndexPtr, /* pointer to store Chroma LUT in VCOP memory                       */
                uint8_t *outputPtr,         /* pointer to output block in VCOP memory                                */
                RemapParms *params          /* pointer to RemapParms structure                                           */
);

#ifdef __cplusplus
 }
#endif

#endif
