/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_yuv_left_right_padding_int.h
 *
 *  @brief      This header defines internal structures for YUV
 *              PAdding into BAM.
 */
#ifndef BAM_YUV_PADDING_INT_H_
#define BAM_YUV_PADDING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_vcop_yuv_left_right_padding.h"

#define NUM_IN_BLOCKS (4)
#define NUM_OUT_BLOCKS (4)
#define NUM_INTERNAL_BLOCKS (2)

#define IN_LEFT_IDX           (BAM_YUV_PADDING_INPUT_PORT_LEFT          )
#define IN_RIGHT_IDX          (BAM_YUV_PADDING_INPUT_PORT_RIGHT         )
#define IN_CHROMA_LEFT_IDX    (BAM_YUV_PADDING_CHROMA_INPUT_PORT_LEFT   )
#define IN_CHROMA_RIGHT_IDX   (BAM_YUV_PADDING_CHROMA_INPUT_PORT_RIGHT  )
#define OUT_LEFT_IDX          (BAM_YUV_PADDING_OUTUT_PORT_LEFT          )
#define OUT_RIGHT_IDX         (BAM_YUV_PADDING_OUTUT_PORT_RIGHT         )
#define OUT_CHROMA_LEFT_IDX   (BAM_YUV_PADDING_CHROMA_OUTUT_PORT_LEFT   )
#define OUT_CHROMA_RIGHT_IDX  (BAM_YUV_PADDING_CHROMA_OUTUT_PORT_RIGHT  )


#define PARAMS_IDX1 (0)                                            
#define PARAMS_IDX2 (1)                                           


typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_yuvLeftRightPadding_Args kernelArgs;
} BAM_yuvLeftRightPadding_Context;

#endif /* BAM_YUV_PADDING_INT_H_*/
